// Native host-memory transport around the emitted AHLS component.
`include "ofs_plat_if.vh"

// Combines MMIO admission, original-burst DMA, AHLS streams and fence handling.
// The packet cap outside this module splits host bursts into smaller packets.
// The controller and generated IP use fixed input/output frame lengths.
module ckks_native_top (
    // Control registers and DMA share the application domain supplied by PIM.
    ofs_plat_axi_mem_lite_if.to_source mmio,
    ofs_plat_axi_mem_if.to_sink host_mem,
    input logic freeze
);
    wire clk = host_mem.clk;
    wire reset_n = host_mem.reset_n;
    logic cfg_locked, go_valid, release_valid, busy, done_valid;
    logic [63:0] cfg_input_iova, cfg_output_iova, done_sequence, release_sequence;
    logic [31:0] cfg_input_capacity, cfg_output_capacity, frame_errors, admin_error;
    logic [63:0] command_words [8];
    logic start_valid, start_ready, finish_valid, finish_ready;
    logic input_enable, input_fire, input_frame_last, output_enable, output_fire, output_burst_last;
    logic input_ready, output_valid, output_ready, output_last;
    logic [511:0] output_data;
    logic status_valid, status_ready, status_last;
    logic [31:0] status_data;

    logic rd_enable, wr_enable;
    logic [63:0] rd_addr, wr_addr;
    logic [7:0] rd_len, wr_len;
    logic fence_valid, fence_ready, fence_response_valid, fence_response_error;
    logic fence_active, fence_aw_sent, fence_w_sent;
    wire fence_mode = fence_active || fence_valid;
    wire is_fence_response = host_mem.b.id == 2;

    copy_engine_pkg::t_rd_cmd rd_cmd;
    copy_engine_pkg::t_wr_cmd wr_cmd;

    ofs_plat_axi_mem_if #(`OFS_PLAT_AXI_MEM_IF_REPLICATE_PARAMS(host_mem)) reader_mem();
    ofs_plat_axi_mem_if #(`OFS_PLAT_AXI_MEM_IF_REPLICATE_PARAMS(host_mem)) writer_mem();
    ofs_plat_axi_stream_if #(.TDATA_TYPE(logic [511:0]), .TUSER_TYPE(logic)) reader_stream();
    ofs_plat_axi_stream_if #(.TDATA_TYPE(logic [511:0]), .TUSER_TYPE(logic)) writer_stream();

    assign reader_mem.clk = clk;
    assign reader_mem.reset_n = reset_n;
    assign reader_mem.instance_number = host_mem.instance_number;
    assign writer_mem.clk = clk;
    assign writer_mem.reset_n = reset_n;
    assign writer_mem.instance_number = host_mem.instance_number;
    assign reader_stream.clk = clk;
    assign reader_stream.reset_n = reset_n;
    assign reader_stream.instance_number = 0;
    assign writer_stream.clk = clk;
    assign writer_stream.reset_n = reset_n;
    assign writer_stream.instance_number = 0;

    // Donor interrupt/memory-status fields stay zero. Native completion
    // uses the controller's MMIO state and explicit fence.
    always_comb begin
        rd_cmd = '{default: '0};
        rd_cmd.enable = rd_enable;
        rd_cmd.addr = rd_addr;
        rd_cmd.num_lines = rd_len;
        wr_cmd = '{default: '0};
        wr_cmd.enable = wr_enable;
        wr_cmd.addr = wr_addr;
        wr_cmd.num_lines = wr_len;
    end

    // Enable-only command enqueues use controller credits to limit outstanding
    // original 4 KiB commands to eight for these 32-entry FIFOs.
    copy_read_engine #(.MAX_REQS_IN_FLIGHT(32)) reader (
        .host_mem(reader_mem),
        .data_stream(reader_stream),
        .rd_cmd,
        .rd_state()
        );

    copy_write_engine_core #(.MAX_REQS_IN_FLIGHT(32)) writer (
        .host_mem(writer_mem),
        .data_stream(writer_stream),
        .wr_cmd,
        .wr_state()
        );

    // Read channels are dedicated to the reader. The write side is shared
    // with the fence injector below. Unused donor directions are tied off.
    assign host_mem.arvalid = reader_mem.arvalid;
    assign host_mem.ar = reader_mem.ar;
    assign reader_mem.arready = host_mem.arready;
    assign reader_mem.rvalid = host_mem.rvalid;
    assign reader_mem.r = host_mem.r;
    assign host_mem.rready = reader_mem.rready;
    assign reader_mem.awready = 1'b0;
    assign reader_mem.wready = 1'b0;
    assign reader_mem.bvalid = 1'b0;
    assign reader_mem.b = '0;
    assign writer_mem.arready = 1'b0;
    assign writer_mem.rvalid = 1'b0;
    assign writer_mem.r = '0;

    // Fence ID bit 1 is reserved. The data writer always clears that bit.
    // The controller gates fencing with its counted RUN join.
    // HC_AXI_UFLAG_FENCE requests ordering from PIM.
    // Its response is distinguished from data-write responses by ID 2.
    always_comb begin
        host_mem.awvalid = writer_mem.awvalid;
        host_mem.aw = writer_mem.aw;
        host_mem.wvalid = writer_mem.wvalid;
        host_mem.w = writer_mem.w;
        writer_mem.awready = host_mem.awready && !fence_mode;
        writer_mem.wready = host_mem.wready && !fence_mode;
        if (fence_mode) begin
            host_mem.awvalid = !fence_aw_sent;
            host_mem.aw = '0;
            host_mem.aw.id = 2;
            host_mem.aw.len = 0;
            host_mem.aw.size = host_mem.ADDR_BYTE_IDX_WIDTH;
            host_mem.aw.user[ofs_plat_host_chan_axi_mem_pkg::HC_AXI_UFLAG_FENCE] = 1'b1;
            host_mem.wvalid = !fence_w_sent;
            host_mem.w = '0;
            host_mem.w.strb = '1;
            host_mem.w.last = 1'b1;
        end
    end

    // Data B responses feed normal write accounting. ID 2 belongs to the fence.
    // BREADY is always high, so each observed BVALID is a response handshake.
    assign writer_mem.bvalid = host_mem.bvalid && !is_fence_response;
    assign writer_mem.b = host_mem.b;
    assign host_mem.bready = 1'b1;

    // AW and W can be accepted on different cycles. Track each handshake
    // independently and retain its accepted state until the B response.
    assign fence_ready = fence_mode &&
        (fence_aw_sent || (host_mem.awvalid && host_mem.awready)) &&
        (fence_w_sent || (host_mem.wvalid && host_mem.wready));
    assign fence_response_valid = host_mem.bvalid && is_fence_response && fence_mode;
    assign fence_response_error = host_mem.b.resp != 0;
    always_ff @(posedge clk) begin
        if (!reset_n) begin
            fence_active <= 0;
            fence_aw_sent <= 0;
            fence_w_sent <= 0;
        end else begin
            if (fence_valid && !fence_active) begin
                fence_active <= 1;
                fence_aw_sent <= 0;
                fence_w_sent <= 0;
            end
            if (fence_mode && host_mem.awvalid && host_mem.awready) fence_aw_sent <= 1;
            if (fence_mode && host_mem.wvalid && host_mem.wready) fence_w_sent <= 1;
            if (fence_response_valid) begin
                fence_active <= 0;
                fence_aw_sent <= 0;
                fence_w_sent <= 0;
            end
        end
    end

    // Propagate backpressure and count only enabled, accepted stream words.
    assign reader_stream.tready = input_ready && input_enable;
    assign input_fire = reader_stream.tvalid && reader_stream.tready;
    assign writer_stream.tvalid = output_valid && output_enable;
    assign output_ready = writer_stream.tready && output_enable;
    assign output_fire = output_valid && output_ready;

    // AHLS TLAST describes the entire C0 frame. Substitute the every-64-word
    // command boundary here for writer WLAST. The packet cap later reconstructs
    // the shorter host-packet WLASTs separately.
    always_comb begin
        writer_stream.t = '0;
        writer_stream.t.data = output_data;
        writer_stream.t.last = output_burst_last;
    end

    // Controller checks incoming DMA burst RLAST separately, then supplies
    // AHLS input TLAST on the final word of the fixed input frame. The HLS
    // parser uses a fixed word count for record reassembly.
    ckks_pipeline_binding pipeline (
        .clock_clk(clk),
        .reset_n_reset_n(reset_n),
        .freeze_freeze(freeze),
        .invoke_start_valid(start_valid),
        .invoke_start_ready(start_ready),
        .invoke_done_valid(finish_valid),
        .invoke_done_ready(finish_ready),
        .dma_input_tdata(reader_stream.t.data),
        .dma_input_tlast(input_frame_last),
        .dma_input_tvalid(reader_stream.tvalid && input_enable),
        .dma_input_tready(input_ready),
        .dma_output_tdata(output_data),
        .dma_output_tlast(output_last),
        .dma_output_tvalid(output_valid),
        .dma_output_tready(output_ready),
        .frame_status_tdata(status_data),
        .frame_status_tlast(status_last),
        .frame_status_tvalid(status_valid),
        .frame_status_tready(status_ready)
        );

    // The MMIO descriptor packs sequence, IOVAs, lengths, slot/flags, ABI and
    // zero-checked reserved fields.
    ckks_frame_control_pipelined #(.HOST_ADDR_WIDTH(host_mem.ADDR_WIDTH)) control (
        .clk,
        .reset_n,
        .freeze,
        .cfg_locked,
        .cfg_input_iova,
        .cfg_output_iova,
        .cfg_input_capacity,
        .cfg_output_capacity,
        .go_valid,
        .go_sequence(command_words[0]),
        .go_input_iova(command_words[1]),
        .go_output_iova(command_words[2]),
        .go_input_bytes(command_words[3][31:0]),
        .go_output_bytes(command_words[3][63:32]),
        .go_slot(command_words[4][31:0]),
        .go_flags(command_words[4][63:32]),
        .go_abi(command_words[5][31:0]),
        .go_reserved_zero(command_words[5][63:32] == 0 && command_words[6] == 0 && command_words[7] == 0),
        .release_valid,
        .release_sequence,
        .busy,
        .done_valid,
        .done_sequence,
        .frame_errors,
        .admin_error,
        .kernel_start_valid(start_valid),
        .kernel_start_ready(start_ready),
        .kernel_done_valid(finish_valid),
        .kernel_done_ready(finish_ready),
        .status_valid,
        .status_ready,
        .status_errors(status_data),
        .status_last,
        .input_enable,
        .input_fire,
        .input_burst_last(reader_stream.t.last),
        .input_frame_last,
        .read_response_error(host_mem.rvalid && host_mem.rready && host_mem.r.resp != 0),
        .output_enable,
        .output_fire,
        .output_frame_last(output_last),
        .output_burst_last,
        .rd_cmd_enable(rd_enable),
        .rd_cmd_addr(rd_addr),
        .rd_cmd_len(rd_len),
        .wr_cmd_enable(wr_enable),
        .wr_cmd_addr(wr_addr),
        .wr_cmd_len(wr_len),
        .write_response_fire(host_mem.bvalid && !is_fence_response),
        .write_response_error(host_mem.bvalid && !is_fence_response && host_mem.b.resp != 0),
        .fence_valid,
        .fence_ready,
        .fence_response_valid,
        .fence_response_error
        );

    // Extend CSR busy across freeze and the outgoing GO pulse, blocking edits
    // in the cycle before the controller captures the staged descriptor.
    ckks_csr csr (
        .mmio,
        .busy(busy || freeze || go_valid),
        .done_valid,
        .done_sequence,
        .frame_errors,
        .admin_error,
        .cfg_locked,
        .cfg_input_iova,
        .cfg_output_iova,
        .cfg_input_capacity,
        .cfg_output_capacity,
        .command_words,
        .go_valid,
        .release_valid,
        .release_sequence
        );

endmodule
