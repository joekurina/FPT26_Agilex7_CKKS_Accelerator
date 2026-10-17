// OFS/PIM host transport follows the capped copy-engine donor. The application
// runs on the exported user clock with the standard PIM clock crossing.
`include "ofs_plat_if.vh"

// Bind the native CKKS application to host channel zero and tie off the rest.
// Clock frequency is supplied by platform/persona configuration.
module ofs_plat_afu (ofs_plat_if plat_ifc);
    wire core_clk = plat_ifc.clocks.uClk_usrDiv2.clk;
    wire core_reset_n;
    wire core_freeze;

    // Join the exported user-clock reset and platform soft reset in core_clk.
    ofs_plat_join_resets join_reset (
        .a_clk(core_clk), .a_reset_n(plat_ifc.clocks.uClk_usrDiv2.reset_n),
        .b_clk(plat_ifc.clocks.pClk.clk), .b_reset_n(plat_ifc.softReset_n),
        .a_joined_reset_n(core_reset_n));

    // Cross the PR freeze control into the application domain, initially asserted.
    ofs_plat_prim_clock_crossing_reg #(.WIDTH(1), .INITIAL_VALUE(1'b1)) freeze_cc (
        .clk_src(plat_ifc.clocks.pClk.clk), .clk_dst(core_clk),
        .r_in(plat_ifc.pr_freeze_to_afu_in), .r_out(core_freeze));

    // Native AXI LEN accommodates the controller's 64-beat commands. The
    // PIM-facing two-bit LEN caps packets at four full-width beats instead.
    ofs_plat_axi_mem_if #(`HOST_CHAN_AXI_MEM_PARAMS,
        .LOG_CLASS(ofs_plat_log_pkg::HOST_CHAN), .BURST_CNT_WIDTH(8)) host_mem();
    ofs_plat_axi_mem_if #(
        .ADDR_WIDTH(host_mem.ADDR_WIDTH), .DATA_WIDTH(host_mem.DATA_WIDTH),
        .MASKED_SYMBOL_WIDTH(host_mem.MASKED_SYMBOL_WIDTH),
        .RID_WIDTH(host_mem.RID_WIDTH), .WID_WIDTH(host_mem.WID_WIDTH),
        .USER_WIDTH(host_mem.USER_WIDTH), .BURST_CNT_WIDTH(2),
        .LOG_CLASS(ofs_plat_log_pkg::HOST_CHAN)) capped_mem();
    assign host_mem.clk = capped_mem.clk;
    assign host_mem.reset_n = capped_mem.reset_n;
    assign host_mem.instance_number = capped_mem.instance_number;
    ia840f_host_packet_cap packet_cap (.mem_source(host_mem), .mem_sink(capped_mem));

    // 64-bit AXI-Lite control and host DMA use the selected AFU clock/reset.
    ofs_plat_axi_mem_lite_if #(`HOST_CHAN_AXI_MMIO_PARAMS(64),
        .LOG_CLASS(ofs_plat_log_pkg::HOST_CHAN)) mmio();

    // Sorted read responses preserve stream order. Response buffering,
    // write-response sorting, timing registers and CDC are delegated to PIM.
    ofs_plat_host_chan_as_axi_mem_with_mmio #(
        .SORT_READ_RESPONSES(1), .SORT_WRITE_RESPONSES(1),
        .BUFFER_READ_RESPONSES(1), .ADD_CLOCK_CROSSING(1),
        .ADD_TIMING_REG_STAGES(2)) primary_axi (
        .to_fiu(plat_ifc.host_chan.ports[0]), .host_mem_to_afu(capped_mem),
        .mmio_to_afu(mmio), .afu_clk(core_clk), .afu_reset_n(core_reset_n));

    // Only host port zero is consumed by the application-facing adapter above.
    ofs_plat_if_tie_off_unused #(.HOST_CHAN_IN_USE_MASK(1)) tie_off(plat_ifc);
    ckks_native_top application (.mmio, .host_mem, .freeze(core_freeze));
endmodule
