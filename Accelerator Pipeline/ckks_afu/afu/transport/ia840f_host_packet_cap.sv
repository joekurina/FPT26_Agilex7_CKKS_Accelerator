// IA-840F AFU-side packet cap.
`include "ofs_plat_if.vh"

// Split original DMA command bursts into PIM-sized packets.
module ia840f_host_packet_cap
   (
    // Application-facing original bursts and PIM-facing capped packets share
    // full-width data and a clock domain. ofs_plat_afu configures PIM's CDC.
    ofs_plat_axi_mem_if.to_source mem_source,
    ofs_plat_axi_mem_if.to_sink mem_sink
    );

    // The standard host flags occupy bits 0..3 in the bound release.
    // PIM returns AFU-private bit 4 in USER metadata for this mapper's
    // reply suppression. HC_AXI_UFLAG_NO_REPLY is standard host flag bit 0.
    localparam PRIVATE_NO_REPLY = ofs_plat_host_chan_axi_mem_pkg::HC_AXI_UFLAG_WIDTH;

    // The public mapper splits address/length, fixup_wlast reconstructs
    // fragment WLASTs, and the private flag suppresses intermediate B and
    // intermediate RLAST while forwarding all read data. Full-width accesses
    // and linear/aligned WRAP ranges are required.
    // With the bound two-bit sink LEN, fragments are at most four 64-byte
    // beats. Returned B responses and RLAST correspond to original commands,
    // so frame-control credits count original 4 KiB DMA commands.
    // Reconstruction relies on PIM returning the private USER metadata and
    // on the configured response ordering. The source-side write-error
    // indication reflects only the forwarded final-fragment BRESP.
    ofs_plat_axi_mem_if_map_bursts
      #(
        .UFLAG_NO_REPLY(PRIVATE_NO_REPLY),
        .PAGE_SIZE(4096),
        .NATURAL_ALIGNMENT(0)
        )
      packet_mapper
       (
        .mem_source,
        .mem_sink
        );

endmodule
