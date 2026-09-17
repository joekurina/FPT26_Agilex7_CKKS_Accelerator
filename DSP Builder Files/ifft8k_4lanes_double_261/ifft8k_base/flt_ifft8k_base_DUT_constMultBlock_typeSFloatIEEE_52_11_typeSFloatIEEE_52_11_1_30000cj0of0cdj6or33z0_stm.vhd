-- ------------------------------------------------------------------------- 
-- High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
-- Quartus Prime development tool and MATLAB/Simulink Interface
-- 
-- Legal Notice: Copyright 2026 Altera Corporation.  All rights reserved.
-- Your use of Altera Corporation's  design tools,  logic functions and other
-- software and  tools, and  its AMPP partner logic functions, and any output
-- files any  of the  foregoing (including  device programming  or simulation
-- files), and  any associated  documentation  or  information  are expressly
-- subject to the terms and  conditions  of the  Altera FPGA Software License
-- Agreement, Altera MegaCore Function License Agreement, or other applicable
-- license agreement,  including,  without limitation,  that  your use is for
-- the  sole  purpose of  programming  logic devices  manufactured by  Altera
-- and  sold by Altera  or its authorized  distributors. Please refer  to the
-- applicable agreement for further details.
-- ---------------------------------------------------------------------------

-- VHDL created from flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_3w1cq5c31oy31o97pb726pa6vb8vn6063064663c61i64uc1d64d61ji4v612642i0860uq5ux0ao30cd06cj0of0cdj6or33z0
-- VHDL created on Tue Aug 25 13:21:30 2026


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;
use std.TextIO.all;
USE work.ifft8k_base_DUT_safe_path.all;
use work.dspba_sim_library_package.all;

entity flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_stm is
    port (
        in_0_stm : out std_logic_vector(63 downto 0);
        out_primWireOut_stm : out std_logic_vector(63 downto 0);
        clk : out std_logic;
        areset : out std_logic
    );
end flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_stm;

architecture normal of flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_stm is

    signal clk_stm_sig : std_logic := '0';
    signal clk_stm_sig_stop : std_logic := '0';
    signal clk_stm_sig_stopped : std_logic := '0';
    signal areset_stm_sig : std_logic := '0';

    function str_to_stdvec(inp: string) return std_logic_vector is
        variable temp: std_logic_vector(inp'range) := (others => 'X');
    begin
        for i in inp'range loop
            IF ((inp(i) = '1')) THEN
                temp(i) := '1';
            elsif (inp(i) = '0') then
                temp(i) := '0';
            END IF;
            end loop;
            return temp;
        end function str_to_stdvec;
        

    begin

    clk <= clk_stm_sig;
    clk_process: process 
    begin
        wait for 200 ps;
        clk_stm_sig <= not clk_stm_sig;
        wait for 633 ps;
        if (clk_stm_sig_stop = '1') then
            assert (false)
            report "Arrived at end of stimulus data on clk clk" severity NOTE;
            clk_stm_sig_stopped <= '1';
            wait;
        end if;
        wait for 200 ps;
        clk_stm_sig <= not clk_stm_sig;
        wait for 633 ps;
        if (clk_stm_sig_stop = '1') then
            assert (false)
            report "Arrived at end of stimulus data on clk clk" severity NOTE;
            clk_stm_sig_stopped <= '1';
            wait;
        end if;
    end process;

    areset <= areset_stm_sig;
    areset_process: process begin
        areset_stm_sig <= '0';
        wait for 1249 ps;
        wait for 1023*1666 ps; -- additional reset delay
        areset_stm_sig <= '1';
        wait;
    end process;

        end_of_sim_msg_p: process(clk_stm_sig_stopped)
        begin
            if (clk_stm_sig_stopped = '1') then
                if (report_mismatch_failure_detected) then
                    report "Simulation finished. Mismatches were detected between the Simulink and RTL simulations." severity NOTE;
                elsif (report_mismatch_warning_detected) then
                    report "Simulation finished. Mismatches defined as warnings were detected between the Simulink and RTL simulations, but no mismatches defined as errors were detected. Check signal mismatch messages above." severity NOTE;
                else
                    report "Simulation finished. No mismatches were detected between the Simulink and RTL simulations." severity NOTE;
                end if;
            end if;
        end process;
        
        -- Driving gnd for in_0 signals

        in_0_stm <= (others => '0');
        -- Driving gnd for out_primWireOut signals

        out_primWireOut_stm <= (others => '0');

    clk_stm_sig_stop <= '1';


    END normal;
