// One-frame native control. DMA commands are 4 KiB. The PIM packet cap
// fragments them further. Completion is sticky MMIO after an explicit fence.
// Admission captures a coherent command, then uses three validation edges.
// One accepted sequence owns the configured windows through sticky DONE.
// Rejected admission returns to IDLE.
// Sequence-matched RELEASE reopens admission after DONE.
module ckks_frame_control_pipelined
  #(
    parameter integer HOST_ADDR_WIDTH = 64
    )
    (
    input  logic clk,
    input  logic reset_n,
    input  logic freeze,

    // Locked host-memory windows against which the GO descriptor is checked.
    input  logic cfg_locked,
    input  logic [63:0] cfg_input_iova,
    input  logic [63:0] cfg_output_iova,
    input  logic [31:0] cfg_input_capacity,
    input  logic [31:0] cfg_output_capacity,

    // GO captures all descriptor fields together before staged validation.
    input  logic go_valid,
    input  logic [63:0] go_sequence,
    input  logic [63:0] go_input_iova,
    input  logic [63:0] go_output_iova,
    input  logic [31:0] go_input_bytes,
    input  logic [31:0] go_output_bytes,
    input  logic [31:0] go_slot,
    input  logic [31:0] go_flags,
    input  logic [31:0] go_abi,
    input  logic go_reserved_zero,

    // Ownership release and externally visible controller/completion state.
    input  logic release_valid,
    input  logic [63:0] release_sequence,
    output logic busy,
    output logic done_valid,
    output logic [63:0] done_sequence,
    output logic [31:0] frame_errors,
    output logic [31:0] admin_error,

    // Invocation return and the single status beat have separate handshakes.
    output logic kernel_start_valid,
    input  logic kernel_start_ready,
    input  logic kernel_done_valid,
    output logic kernel_done_ready,
    input  logic status_valid,
    output logic status_ready,
    input  logic [31:0] status_errors,
    input  logic status_last,

    // Input burst LAST is DMA-command RLAST. input_frame_last is the
    // whole fixed input-frame marker presented to the AHLS input stream.
    output logic input_enable,
    input  logic input_fire,
    input  logic input_burst_last,
    output logic input_frame_last,
    input  logic read_response_error,

    // AHLS output LAST marks the whole C0 frame. output_burst_last instead
    // marks each original write command before downstream packet splitting.
    output logic output_enable,
    input  logic output_fire,
    input  logic output_frame_last,
    output logic output_burst_last,

    // Each enabled cycle enqueues one command through an enable-only interface.
    // Responses below count original 4 KiB write commands.
    output logic rd_cmd_enable,
    output logic [63:0] rd_cmd_addr,
    output logic [7:0] rd_cmd_len,
    output logic wr_cmd_enable,
    output logic [63:0] wr_cmd_addr,
    output logic [7:0] wr_cmd_len,
    input  logic write_response_fire,
    input  logic write_response_error,

    // Separate PIM ordering request and response, after the RUN join condition.
    output logic fence_valid,
    input  logic fence_ready,
    input  logic fence_response_valid,
    input  logic fence_response_error
);

    // Counts cover payload only. the command descriptor stays in MMIO.
    // Input is 2048 packed 264-byte records. output is six C0 modulus planes.
    // A word here is one 512-bit (64-byte) stream transfer.
    localparam logic [31:0] INPUT_BYTES = 32'd540672;
    localparam logic [31:0] OUTPUT_BYTES = 32'd196608;
    localparam logic [15:0] INPUT_WORDS = 16'd8448;
    localparam logic [15:0] OUTPUT_WORDS = 16'd3072;

    // Each command covers 64 words (4 KiB), encoded below as AXI LEN=63.
    // Credits count these original commands across packet fragmentation.
    localparam logic [7:0] READ_COMMANDS = 8'd132;
    localparam logic [7:0] WRITE_COMMANDS = 8'd48;
    localparam logic [7:0] COMMAND_CREDITS = 8'd8;
    localparam logic [64:0] HOST_ADDRESS_LIMIT = 65'd1 << HOST_ADDR_WIDTH;

    // Validation precedes invocation. RUN joins independent progress paths.
    // DONE retains ownership. FAULT persists until reset.
    typedef enum logic [3:0] {
        IDLE, START, RUN, FENCE_SEND, FENCE_WAIT, DONE, FAULT,
        VALIDATE_ARITH, VALIDATE_RANGE, VALIDATE_DECIDE
    } state_t;
    state_t state;
    logic go_ready;
    logic [63:0] input_iova, output_iova, active_sequence, last_sequence;
    logic [15:0] input_words, output_words;
    logic [7:0] reads_issued, reads_completed, writes_issued, writes_completed;
    logic kernel_retired, status_seen;
    logic command_valid;
    logic [31:0] next_errors;

    // Snapshot the descriptor, pinned-window config and sequence watermark.
    // Validation consumes this captured snapshot.
    typedef struct packed {
        logic cfg_locked;
        logic [63:0] cfg_input_iova, cfg_output_iova;
        logic [31:0] cfg_input_capacity, cfg_output_capacity;
        logic [63:0] go_sequence, go_input_iova, go_output_iova;
        logic [31:0] go_input_bytes, go_output_bytes;
        logic [31:0] go_slot, go_flags, go_abi;
        logic go_reserved_zero;
        logic [63:0] last_sequence;
    } pending_command_t;
    pending_command_t pending_command;

    // First validation edge: independent simple predicates and full-width sums.
    logic locked_ok, sequence_nonzero, sequence_newer;
    logic slot_ok, flags_ok, abi_ok, reserved_ok;
    logic input_length_ok, output_length_ok;
    logic input_matches_cfg, output_matches_cfg;
    logic input_capacity_ok, output_capacity_ok;
    logic input_nonzero, output_nonzero, input_aligned, output_aligned;
    logic [64:0] input_end, output_end;

    // Second validation edge: comparisons consume the registered sums.
    logic input_range_ok, output_range_ok;
    logic input_before_output, output_before_input;

    always_comb begin
        // Only registered predicates feed the final decision.
        command_valid = locked_ok && sequence_nonzero && sequence_newer &&
            slot_ok && flags_ok && abi_ok && reserved_ok &&
            input_length_ok && output_length_ok &&
            input_matches_cfg && output_matches_cfg &&
            input_capacity_ok && output_capacity_ok &&
            input_nonzero && output_nonzero && input_aligned && output_aligned &&
            input_range_ok && output_range_ok &&
            (input_before_output || output_before_input);

        // Busy includes validation, computation, sticky DONE and FAULT.
        // freeze pauses admission/start/command issue. RUN retirement stays enabled.
        go_ready = state == IDLE && !freeze;
        busy = state != IDLE;
        done_valid = state == DONE;
        done_sequence = active_sequence;
        kernel_start_valid = state == START && !freeze;

        // Accept kernel return and status at most once each during RUN.
        // Host completion follows the RUN join and successful fence response.
        kernel_done_ready = state == RUN && !kernel_retired;
        status_ready = state == RUN && !status_seen;

        // Fixed word counts gate transfers. LAST is meaningful on a handshake.
        // Generate frame and command boundaries from counts.
        input_enable = state == RUN && input_words < INPUT_WORDS;
        output_enable = state == RUN && output_words < OUTPUT_WORDS;
        input_frame_last = input_words == INPUT_WORDS - 1'b1;
        output_burst_last = output_words[5:0] == 6'd63;

        // Credits bound enqueued-minus-completed original 4 KiB commands.
        rd_cmd_enable = state == RUN && !freeze && reads_issued < READ_COMMANDS &&
                        reads_issued - reads_completed < COMMAND_CREDITS;
        wr_cmd_enable = state == RUN && !freeze && writes_issued < WRITE_COMMANDS &&
                        writes_issued - writes_completed < COMMAND_CREDITS;
        rd_cmd_addr = input_iova + {44'd0, reads_issued, 12'd0};
        wr_cmd_addr = output_iova + {44'd0, writes_issued, 12'd0};
        rd_cmd_len = 8'd63;
        wr_cmd_len = 8'd63;
        fence_valid = state == FENCE_SEND;

        // Accumulate transport/protocol flags alongside the fixed-count transfers.
        // RUN errors are reported with completion. On the normal fence path,
        // a successful fence response selects DONE and a failure selects FAULT.
        next_errors = frame_errors;
        if (state == RUN) begin
            if (read_response_error) next_errors[8] = 1'b1;
            if (write_response_error) next_errors[9] = 1'b1;
            if (input_fire && input_burst_last != (input_words[5:0] == 6'd63))
                next_errors[10] = 1'b1;
            if (output_fire && output_frame_last != (output_words == OUTPUT_WORDS - 1'b1))
                next_errors[11] = 1'b1;
            if (input_fire && !input_enable) next_errors[12] = 1'b1;
            if (output_fire && !output_enable) next_errors[13] = 1'b1;
            if (status_valid && status_ready) begin
                next_errors = next_errors | status_errors;
                if (!status_last) next_errors[14] = 1'b1;
            end
            if (write_response_fire && writes_completed >= writes_issued)
                next_errors[15] = 1'b1;
        end
        if (fence_response_valid && fence_response_error) next_errors[16] = 1'b1;
    end

    always_ff @(posedge clk) begin
        if (!reset_n) begin
            state <= IDLE;
            input_iova <= 0;
            output_iova <= 0;
            active_sequence <= 0;
            last_sequence <= 0;
            input_words <= 0;
            output_words <= 0;
            reads_issued <= 0;
            reads_completed <= 0;
            writes_issued <= 0;
            writes_completed <= 0;
            kernel_retired <= 0;
            status_seen <= 0;
            frame_errors <= 0;
            admin_error <= 0;
            pending_command <= '0;
            locked_ok <= 0;
            sequence_nonzero <= 0;
            sequence_newer <= 0;
            slot_ok <= 0;
            flags_ok <= 0;
            abi_ok <= 0;
            reserved_ok <= 0;
            input_length_ok <= 0;
            output_length_ok <= 0;
            input_matches_cfg <= 0;
            output_matches_cfg <= 0;
            input_capacity_ok <= 0;
            output_capacity_ok <= 0;
            input_nonzero <= 0;
            output_nonzero <= 0;
            input_aligned <= 0;
            output_aligned <= 0;
            input_end <= 0;
            output_end <= 0;
            input_range_ok <= 0;
            output_range_ok <= 0;
            input_before_output <= 0;
            output_before_input <= 0;
        end else begin
            frame_errors <= next_errors;

            // Administrative misuse is separate from per-frame error flags.
            // A newly captured attempt below clears prior administrative status.
            if (go_valid && !go_ready) admin_error <= 32'd1;
            if (release_valid && !(state == DONE && release_sequence == active_sequence))
                admin_error <= 32'd3;
            case (state)
                IDLE: if (go_valid && go_ready) begin
                    pending_command.cfg_locked <= cfg_locked;
                    pending_command.cfg_input_iova <= cfg_input_iova;
                    pending_command.cfg_output_iova <= cfg_output_iova;
                    pending_command.cfg_input_capacity <= cfg_input_capacity;
                    pending_command.cfg_output_capacity <= cfg_output_capacity;
                    pending_command.go_sequence <= go_sequence;
                    pending_command.go_input_iova <= go_input_iova;
                    pending_command.go_output_iova <= go_output_iova;
                    pending_command.go_input_bytes <= go_input_bytes;
                    pending_command.go_output_bytes <= go_output_bytes;
                    pending_command.go_slot <= go_slot;
                    pending_command.go_flags <= go_flags;
                    pending_command.go_abi <= go_abi;
                    pending_command.go_reserved_zero <= go_reserved_zero;
                    pending_command.last_sequence <= last_sequence;

                    // A new attempt overrides a capture-edge illegal release.
                    admin_error <= 0;
                    state <= VALIDATE_ARITH;
                end

                // freeze holds each validation stage. Admission requires fixed
                // lengths, matching locked windows and a newer nonzero sequence.
                // Extended base+capacity sums retain overflow for range checks.
                VALIDATE_ARITH: if (!freeze) begin
                    input_end <= {1'b0, pending_command.go_input_iova} +
                                 {33'd0, pending_command.cfg_input_capacity};
                    output_end <= {1'b0, pending_command.go_output_iova} +
                                  {33'd0, pending_command.cfg_output_capacity};
                    locked_ok <= pending_command.cfg_locked;
                    sequence_nonzero <= pending_command.go_sequence != 0;
                    sequence_newer <= pending_command.go_sequence > pending_command.last_sequence;
                    slot_ok <= pending_command.go_slot == 0;
                    flags_ok <= pending_command.go_flags == 0;
                    abi_ok <= pending_command.go_abi == 1;
                    reserved_ok <= pending_command.go_reserved_zero;
                    input_length_ok <= pending_command.go_input_bytes == INPUT_BYTES;
                    output_length_ok <= pending_command.go_output_bytes == OUTPUT_BYTES;
                    input_matches_cfg <= pending_command.go_input_iova == pending_command.cfg_input_iova;
                    output_matches_cfg <= pending_command.go_output_iova == pending_command.cfg_output_iova;
                    input_capacity_ok <= pending_command.cfg_input_capacity >= INPUT_BYTES;
                    output_capacity_ok <= pending_command.cfg_output_capacity >= OUTPUT_BYTES;
                    input_nonzero <= pending_command.go_input_iova != 0;
                    output_nonzero <= pending_command.go_output_iova != 0;
                    input_aligned <= pending_command.go_input_iova[11:0] == 0;
                    output_aligned <= pending_command.go_output_iova[11:0] == 0;
                    state <= VALIDATE_RANGE;
                end
                VALIDATE_RANGE: if (!freeze) begin

                    // The exclusive end may equal 2^64. Retain its carry bit.
                    input_range_ok <= input_end > {1'b0, pending_command.go_input_iova} &&
                                      input_end <= HOST_ADDRESS_LIMIT;
                    output_range_ok <= output_end > {1'b0, pending_command.go_output_iova} &&
                                       output_end <= HOST_ADDRESS_LIMIT;

                    // Check separation using the full configured window capacities.
                    input_before_output <= input_end <= {1'b0, pending_command.go_output_iova};
                    output_before_input <= output_end <= {1'b0, pending_command.go_input_iova};
                    state <= VALIDATE_DECIDE;
                end

                // Commit bases/sequence and clear frame progress only after all
                // registered predicates pass. Rejection preserves prior frame diagnostics
                // and the accepted-sequence watermark.
                VALIDATE_DECIDE: if (!freeze) begin
                    if (command_valid) begin
                        input_iova <= pending_command.go_input_iova;
                        output_iova <= pending_command.go_output_iova;
                        active_sequence <= pending_command.go_sequence;
                        last_sequence <= pending_command.go_sequence;
                        input_words <= 0;
                        output_words <= 0;
                        reads_issued <= 0;
                        reads_completed <= 0;
                        writes_issued <= 0;
                        writes_completed <= 0;
                        kernel_retired <= 0;
                        status_seen <= 0;
                        frame_errors <= 0;
                        state <= START;
                    end else begin

                        // GO is busy and every release is illegal in this stage.
                        // Preserve prior window errors and this edge's events.
                        if (admin_error == 0 && !go_valid && !release_valid)
                            admin_error <= 32'd2;
                        state <= IDLE;
                    end
                end

                // Hold invocation valid until accepted. DMA commands begin in RUN.
                START: if (kernel_start_valid && kernel_start_ready) state <= RUN;

                RUN: begin

                    // Issued counts are FIFO enqueues. Read credits return after
                    // each counted 64-word input segment, independently of RLAST
                    // correctness. Write credits return on counted B responses.
                    if (rd_cmd_enable) reads_issued <= reads_issued + 1'b1;
                    if (wr_cmd_enable) writes_issued <= writes_issued + 1'b1;
                    if (input_fire && input_enable) begin
                        input_words <= input_words + 1'b1;
                        if (input_words[5:0] == 6'd63) reads_completed <= reads_completed + 1'b1;
                    end
                    if (output_fire && output_enable) output_words <= output_words + 1'b1;
                    if (write_response_fire && writes_completed < writes_issued)
                        writes_completed <= writes_completed + 1'b1;
                    if (kernel_done_valid && kernel_done_ready) kernel_retired <= 1'b1;
                    if (status_valid && status_ready) status_seen <= 1'b1;

                    // Join registered word totals, command enqueues, write responses,
                    // kernel return and status before requesting the PIM ordering fence.
                    if (input_words == INPUT_WORDS && output_words == OUTPUT_WORDS &&
                        reads_issued == READ_COMMANDS && writes_issued == WRITE_COMMANDS &&
                        writes_completed == WRITE_COMMANDS && kernel_retired && status_seen)
                        state <= FENCE_SEND;
                end

                // A fence may respond on the request-accept edge or later.
                // Successful response exposes DONE. Failure latches FAULT.
                FENCE_SEND: if (fence_ready) begin
                    if (fence_response_valid) state <= fence_response_error ? FAULT : DONE;
                    else state <= FENCE_WAIT;
                end
                FENCE_WAIT: if (fence_response_valid) state <= fence_response_error ? FAULT : DONE;

                // Only the owning sequence may release sticky completion.
                DONE: if (release_valid && release_sequence == active_sequence) state <= IDLE;
                FAULT: state <= FAULT;
                default: begin
                    state <= FAULT;
                    frame_errors[31] <= 1'b1;
                end
            endcase
        end
    end

endmodule
