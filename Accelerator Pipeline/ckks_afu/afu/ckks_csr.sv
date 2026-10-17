// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: MIT
// AXI-Lite request/response registers follow the OFS copy-engine CSR frontend.
// MMIO register bank for command staging and one-frame completion status.
// Register-access checks live here. Descriptor admission and matching
// completion release belong to ckks_frame_control_pipelined.

`include "ofs_plat_if.vh"
`include "afu_json_info.vh"

module ckks_csr (
    ofs_plat_axi_mem_lite_if.to_source mmio,

    // Live controller status: busy also gates mutable command/config writes.
    input logic busy,
    input logic done_valid,
    input logic [63:0] done_sequence,
    input logic [31:0] frame_errors,
    input logic [31:0] admin_error,

    // Registered memory windows and the eight-word command image for GO.
    output logic cfg_locked,
    output logic [63:0] cfg_input_iova,
    output logic [63:0] cfg_output_iova,
    output logic [31:0] cfg_input_capacity,
    output logic [31:0] cfg_output_capacity,
    output logic [63:0] command_words [8],

    // One-cycle notifications: RELEASE carries a sequence for ownership checks.
    output logic go_valid,
    output logic release_valid,
    output logic [63:0] release_sequence
);

    wire clk = mmio.clk;
    wire reset_n = mmio.reset_n;
    localparam logic [127:0] AFU_ID = `AFU_ACCEL_UUID;

    // Independent one-entry AR, AW and W storage permits separate arrival
    // of write address and data. Responses block new same-direction requests.
    ofs_plat_axi_mem_lite_if #(`OFS_PLAT_AXI_MEM_LITE_IF_REPLICATE_PARAMS(mmio)) saved();
    wire read_request = saved.arvalid;
    wire write_request = saved.awvalid && saved.wvalid;
    logic [31:0] csr_error;

    assign mmio.arready = !saved.arvalid && !saved.rvalid;
    assign mmio.awready = !saved.awvalid && !saved.bvalid;
    assign mmio.wready = !saved.wvalid && !saved.bvalid;
    assign mmio.rvalid = saved.rvalid;
    assign mmio.r = saved.r;
    assign mmio.bvalid = saved.bvalid;
    assign mmio.b = saved.b;

    always_ff @(posedge clk) begin
        if (read_request) saved.arvalid <= 1'b0;
        else if (mmio.arvalid && mmio.arready) begin
            saved.arvalid <= 1'b1;
            saved.ar <= mmio.ar;
        end
        if (write_request) begin
            saved.awvalid <= 1'b0;
            saved.wvalid <= 1'b0;
        end else begin
            if (mmio.awvalid && mmio.awready) begin
                saved.awvalid <= 1'b1;
                saved.aw <= mmio.aw;
            end
            if (mmio.wvalid && mmio.wready) begin
                saved.wvalid <= 1'b1;
                saved.w <= mmio.w;
            end
        end
        if (!reset_n) begin
            saved.arvalid <= 1'b0;
            saved.awvalid <= 1'b0;
            saved.wvalid <= 1'b0;
        end
    end

    // Capture read data once and hold RVALID until the host accepts it.
    // Undefined addresses return zero with SLVERR.
    always_ff @(posedge clk) begin
        if (read_request) begin
            saved.rvalid <= 1'b1;
            saved.r <= '0;
            saved.r.id <= saved.ar.id;
            saved.r.user <= saved.ar.user;

            // Decode the full byte address for control CSRs.
            case (saved.ar.addr)
                'h000: saved.r.data <= 64'h1000010000000000;
                'h008: saved.r.data <= AFU_ID[63:0];
                'h010: saved.r.data <= AFU_ID[127:64];
                'h018, 'h020: saved.r.data <= 0;
                'h028: saved.r.data <= 64'h434b4b534e415431; // CKKSNAT1
                'h030: saved.r.data <= {32'd1, 16'd1, 16'd1}; // MMIO completion, capacity one, ABI one

                // The sequence is a completion identifier only while done_valid is set.
                'h038: saved.r.data <= done_sequence;
                'h080: saved.r.data <= {frame_errors, 30'd0, done_valid, busy};
                'h088: saved.r.data <= {csr_error, admin_error};
                'h100: saved.r.data <= cfg_input_iova;
                'h108: saved.r.data <= cfg_output_iova;
                'h110: saved.r.data <= {cfg_output_capacity, cfg_input_capacity};
                'h118: saved.r.data <= {63'd0, cfg_locked};

                // Fixed payload sizes are packed as output bytes above input bytes.
                'h120: saved.r.data <= {32'd196608, 32'd540672};

                default: begin
                    saved.r.data <= 0;
                    saved.r.resp <= 2'b10;
                end
            endcase
        end else if (mmio.rready) saved.rvalid <= 1'b0;
        if (!reset_n) saved.rvalid <= 1'b0;
    end

    // GO/RELEASE pulses are independent of how long the AXI B response stalls.
    always_ff @(posedge clk) begin
        go_valid <= 1'b0;
        release_valid <= 1'b0;

        if (write_request) begin
            saved.bvalid <= 1'b1;
            saved.b <= '0;
            saved.b.id <= saved.aw.id;
            saved.b.user <= saved.aw.user;

            // Require aligned, full-width 64-bit writes with every byte strobe set.
            if (saved.w.strb != '1 || saved.aw.addr[2:0] != 0) begin
                saved.b.resp <= 2'b10;
                csr_error <= 32'd1;

            end else begin
                case (saved.aw.addr)
                    'h040, 'h048, 'h050, 'h058, 'h060, 'h068, 'h070, 'h078: begin
                        if (!busy) command_words[(saved.aw.addr - 'h040) >> 3] <= saved.w.data;
                        else begin saved.b.resp <= 2'b10; csr_error <= 32'd2; end
                    end

                    // GO must repeat command word 0. CSR acceptance requests
                    // descriptor admission through the controller's staged validation.
                    'h080: begin
                        if (!busy && saved.w.data == command_words[0]) go_valid <= 1'b1;
                        else begin saved.b.resp <= 2'b10; csr_error <= 32'd3; end
                    end

                    // Forward RELEASE even while busy. Only the controller
                    // can validate DONE ownership and the matching sequence.
                    'h090: begin
                        release_sequence <= saved.w.data;
                        release_valid <= 1'b1;
                    end

                    // Pinned-window bases/capacities are mutable only while
                    // idle and unlocked. The lock itself is software controlled.
                    'h100: begin
                        if (!busy && !cfg_locked) cfg_input_iova <= saved.w.data;
                        else begin saved.b.resp <= 2'b10; csr_error <= 32'd4; end
                    end

                    'h108: begin
                        if (!busy && !cfg_locked) cfg_output_iova <= saved.w.data;
                        else begin saved.b.resp <= 2'b10; csr_error <= 32'd4; end
                    end

                    'h110: begin
                        if (!busy && !cfg_locked) begin
                            cfg_input_capacity <= saved.w.data[31:0];
                            cfg_output_capacity <= saved.w.data[63:32];
                        end else begin saved.b.resp <= 2'b10; csr_error <= 32'd4; end
                    end

                    'h118: begin
                        if (!busy && saved.w.data[63:1] == 0) cfg_locked <= saved.w.data[0];
                        else begin saved.b.resp <= 2'b10; csr_error <= 32'd4; end
                    end

                    // Clear only CSR access errors. Other successful accesses
                    // leave csr_error intact.
                    'h088: begin
                        if (!busy && saved.w.data == 0) csr_error <= 0;
                        else saved.b.resp <= 2'b10;
                    end

                    default: begin saved.b.resp <= 2'b10; csr_error <= 32'd5; end
                endcase
            end

        end else if (mmio.bready) saved.bvalid <= 1'b0;

        if (!reset_n) begin
            saved.bvalid <= 1'b0;
            cfg_locked <= 0;
            cfg_input_iova <= 0;
            cfg_output_iova <= 0;
            cfg_input_capacity <= 0;
            cfg_output_capacity <= 0;
            csr_error <= 0;
            go_valid <= 0;
            release_valid <= 0;
            release_sequence <= 0;
            for (int i = 0; i < 8; i = i + 1) command_words[i] <= 0;
        end
    end

endmodule
