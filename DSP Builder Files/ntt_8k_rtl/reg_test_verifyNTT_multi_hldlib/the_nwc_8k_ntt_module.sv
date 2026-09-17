// ----------------------------------------------------------------------
// Hand-fixed per the fixing-hld-avalon-wrappers pattern (see
// NTT_8K_CHANGES.md and .cursor/skills/fixing-hld-avalon-wrappers for the
// full writeup) -- three bugs in the raw HLS-Compiler-generated wrapper:
//
//   Bug 1 (ABI struct layout / padding): N/A for this design. The real ABI
//   from the_nwc_8k_ntt_sycl.hpp (port_in_v_s + port_in_c_s + 4x
//   uint32_t[2] port_x_in_N = 1+1+8+8+8+8 = 34 bytes = 272 bits) matches
//   the XML's declared idata/odata width (272) exactly, and every VHDL DUT
//   port (In_V_s, In_C_s, X_in_0..3 / Out_V_s, Out_C_s, Out_Q_0..3) maps
//   1:1 onto an ABI field -- no slack bits, no VHDL-only port to tie off.
//   The struct below is therefore unchanged from the raw generated one.
//
//   Bug 2 (1-bit strobe zero-extension): In_V_s/Out_V_s are 1-bit VHDL
//   ports (std_logic_vector(0 downto 0)) but packed as full bytes in the
//   co-sim struct to match the byte-aligned int8_t fields in the software
//   model. Out_V_s must not be wired directly into the 8-bit
//   ChannelOut_port_out_v_s field (leaves upper 7 bits undriven/X) --
//   zero-extended explicitly below. Note In_C_s/Out_C_s are genuinely
//   8-bit "channel" (modulus-select) ports on the DUT itself, not 1-bit
//   strobes, so they need no such fix -- they're threaded straight
//   through untouched, same as any other real data field.
//
//   Bug 3 (missing live handshaking, the main fix): this DUT is NOT
//   fixed-latency -- it accumulates NUM_BLOCKS beats (one full frame)
//   before it starts computing, then bursts NUM_BLOCKS consecutive valid
//   output beats, while a second frame's input may already be filling
//   behind it (2-deep double-buffered pipelining, same as the IFFT
//   designs this pattern was first fixed on). Fixed with an output-side
//   scfifo (show-ahead, 2 frames deep, real M20K storage) plus input-side
//   frame-admission control, sized off NUM_BLOCKS = transform size /
//   lanes-per-beat = 8192 / 4 = 2048.
//
//   The channel bus (In_C_s/Out_C_s) is real per-beat ABI data (it's
//   threaded through every stage of the NTT pipeline in
//   build_PNTT_pipeline_multi.m exactly like the valid/data buses, and
//   delayed identically by the MultiwireTranspose_Multi stages) -- it
//   rides through the output FIFO for free since the whole dataOut
//   struct (including ChannelOut_port_out_c_s) is what gets pushed/popped.
// ----------------------------------------------------------------------

typedef struct packed {
    logic[63:0] ChannelIn_port_x_in_3;
    logic[63:0] ChannelIn_port_x_in_2;
    logic[63:0] ChannelIn_port_x_in_1;
    logic[63:0] ChannelIn_port_x_in_0;
    logic[7:0] ChannelIn_port_in_c_s;
    logic[7:0] ChannelIn_port_in_v_s;
} input_t;

typedef struct packed {
    logic[63:0] ChannelOut_port_out_q_3;
    logic[63:0] ChannelOut_port_out_q_2;
    logic[63:0] ChannelOut_port_out_q_1;
    logic[63:0] ChannelOut_port_out_q_0;
    logic[7:0] ChannelOut_port_out_c_s;
    logic[7:0] ChannelOut_port_out_v_s;
} output_t;

// ----------------------------------------------------------------------
// This DUT is NOT a fixed-latency component: on the input side it
// tolerates bubbles (in_v_s=0 is safe at any time; no state corruption),
// accumulates one full frame (NUM_BLOCKS beats), and only then starts
// computing -- while simultaneously allowing a *second* frame's input to
// begin filling behind it (2-deep, double-buffered pipelining). Once a
// frame's computation completes, its result appears as a burst of
// NUM_BLOCKS consecutive valid output beats. Because the delay between
// "last valid input" and "first valid output" is not a static number of
// cycles, this cannot be honestly described to the offline compiler via
// IS_STALL_FREE="yes"/EXPECTED_LATENCY (see the companion .xml, which now
// sets IS_STALL_FREE="no"). Instead, this wrapper implements real, live
// ivalid/iready/ovalid/oready handshaking:
//
//   - Output side: an internal show-ahead (FWFT) FIFO decouples the
//     DUT's raw one-burst-per-frame out_v_s timing from the
//     compiler-visible ovalid/oready/odata interface. ovalid is simply
//     "FIFO not empty"; a beat is consumed exactly when ovalid && iready.
//     The FIFO is sized for 2 full frames (2 x NUM_BLOCKS beats), which
//     is the worst case of 2 completely computed, fully undrained frames
//     sitting in the FIFO at once.
//
//   - Input side: since the DUT can have at most 2 frames in flight (one
//     draining/computing, one being fed), the wrapper tracks frame-level
//     admission/drain counts and only asserts oready while fewer than 2
//     frames' worth of future output are outstanding. This guarantees
//     the output FIFO can never overflow, and that we never violate the
//     DUT's own 2-deep pipelining limit. Gating applies uniformly to
//     every beat (not just frame-start beats): dropping oready mid-frame
//     just produces a bubble on the DUT's in_v_s, which the DUT is
//     documented to tolerate.
// ----------------------------------------------------------------------

module the_nwc_8k_ntt_module
(
    input  clock,
    input  resetn,

    input  ivalid,
    output ovalid,

    input  iready,
    output oready,

    input[$bits(input_t) - 1:0] idata,
    output[$bits(output_t) - 1:0] odata
);

localparam int NUM_BLOCKS = 2048; // 8192-point transform / 4 lanes per beat
localparam int FRAMES_IN_FLIGHT_MAX = 2; // DUT's own double-buffered input limit
localparam int FIFO_DEPTH = FRAMES_IN_FLIGHT_MAX * NUM_BLOCKS;
localparam int FIFO_ADDR_W = $clog2(FIFO_DEPTH);
localparam int BEAT_CNT_W = $clog2(NUM_BLOCKS);
localparam int DATA_W = $bits(output_t);

input_t dataIn;
output_t dataOut;

logic valid_in;
logic valid_out;
logic areset;

assign dataIn = idata;

assign valid_in = ivalid & oready & dataIn.ChannelIn_port_in_v_s;

// reg_test_verifyNTT_multi_DUT.Out_V_s is a 1-bit RTL port, but
// ChannelOut_port_out_v_s is packed as a full byte in the co-sim struct
// to match the byte-aligned int8_t field in the C++/SYCL software model.
// Zero-extend explicitly rather than leaving the upper 7 bits of the
// struct field undriven. Any entry that made it into the output FIFO is,
// by construction, a real beat, so this field always reads back as 1
// downstream of the FIFO.
assign dataOut.ChannelOut_port_out_v_s = {7'b0, valid_out};

assign areset = ~resetn;

reg_test_verifyNTT_multi_DUT
reg_test_verifyNTT_multi_DUT_inst (
    .In_V_s (valid_in),
    .In_C_s (dataIn.ChannelIn_port_in_c_s),
    .X_in_0 (dataIn.ChannelIn_port_x_in_0),
    .X_in_1 (dataIn.ChannelIn_port_x_in_1),
    .X_in_2 (dataIn.ChannelIn_port_x_in_2),
    .X_in_3 (dataIn.ChannelIn_port_x_in_3),
    .Out_V_s (valid_out),
    .Out_C_s (dataOut.ChannelOut_port_out_c_s),
    .Out_Q_0 (dataOut.ChannelOut_port_out_q_0),
    .Out_Q_1 (dataOut.ChannelOut_port_out_q_1),
    .Out_Q_2 (dataOut.ChannelOut_port_out_q_2),
    .Out_Q_3 (dataOut.ChannelOut_port_out_q_3),
    .clk (clock),
    .areset (areset)
);

// ----------------------------------------------------------------------
// Output-side FIFO (show-ahead / first-word-fall-through, 2 frames deep).
// Pushed unconditionally whenever the DUT asserts valid_out -- this write
// must never be refused; the admission control below guarantees room
// always exists by the time any given frame's output burst lands. Popped
// exactly on a genuine downstream transfer (ovalid && iready). The
// channel bus rides through for free since it's part of dataOut.
//
// Backed by the Quartus `scfifo` LPM megafunction (lpm_showahead="ON",
// matching the FWFT semantics already documented above) with
// use_eab="ON" to force real M20K block-RAM storage, rather than a
// hand-rolled packed-array FIFO with a combinational
// `fifo_mem[fifo_rd_ptr]` read -- a real fMAX/area risk at scale on
// actual hardware, even though it is functionally correct in simulation.
// intended_device_family is left at the same placeholder this build's
// own AOC-generated FIFOs use (Quartus auto-corrects it to the real
// target device); overflow/underflow checking are safely "OFF" since the
// admission control below already guarantees, by construction, the FIFO
// is never pushed while full or popped while empty.
// ----------------------------------------------------------------------

logic fifo_push;
logic fifo_pop;
logic fifo_empty;
logic [FIFO_ADDR_W-1:0] fifo_usedw;

assign fifo_push  = valid_out;
assign ovalid     = ~fifo_empty;
assign fifo_pop   = ovalid & iready;

scfifo #(
    .lpm_width               (DATA_W),
    .lpm_widthu              (FIFO_ADDR_W),
    .lpm_numwords            (FIFO_DEPTH),
    .lpm_showahead           ("ON"),
    .lpm_type                ("scfifo"),
    .lpm_hint                ("USE_EAB=ON"),
    .intended_device_family  ("Stratix 10"),
    .overflow_checking       ("OFF"),
    .underflow_checking      ("OFF"),
    .use_eab                 ("ON"),
    .add_ram_output_register ("OFF")
) ntt_output_fifo (
    .data         (dataOut),
    .clock        (clock),
    .wrreq        (fifo_push),
    .rdreq        (fifo_pop),
    .aclr         (1'b0),
    .sclr         (~resetn),
    .q            (odata),
    .usedw        (fifo_usedw),
    .full         (),
    .empty        (fifo_empty),
    .almost_full  (),
    .almost_empty ()
);

// ----------------------------------------------------------------------
// Input-side admission control: track how many complete NUM_BLOCKS-beat
// frames have been admitted into the DUT but not yet fully drained from
// the output FIFO ("frames in flight"), and deassert oready once
// FRAMES_IN_FLIGHT_MAX are outstanding.
// ----------------------------------------------------------------------

logic [BEAT_CNT_W-1:0] admit_beat_cnt;
logic [BEAT_CNT_W-1:0] drain_beat_cnt;
logic [1:0] frames_admitted;
logic [1:0] frames_drained;
logic [1:0] frames_in_flight;

assign frames_in_flight = frames_admitted - frames_drained;
assign oready = (frames_in_flight < FRAMES_IN_FLIGHT_MAX);

always_ff @(posedge clock) begin
    if (!resetn) begin
        admit_beat_cnt  <= '0;
        drain_beat_cnt  <= '0;
        frames_admitted <= '0;
        frames_drained  <= '0;
    end else begin
        if (valid_in) begin
            if (admit_beat_cnt == NUM_BLOCKS - 1) begin
                admit_beat_cnt  <= '0;
                frames_admitted <= frames_admitted + 1'b1;
            end else begin
                admit_beat_cnt <= admit_beat_cnt + 1'b1;
            end
        end
        if (fifo_pop) begin
            if (drain_beat_cnt == NUM_BLOCKS - 1) begin
                drain_beat_cnt <= '0;
                frames_drained <= frames_drained + 1'b1;
            end else begin
                drain_beat_cnt <= drain_beat_cnt + 1'b1;
            end
        end
    end
end

endmodule;
