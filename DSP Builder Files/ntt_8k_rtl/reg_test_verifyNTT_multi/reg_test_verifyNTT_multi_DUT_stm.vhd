-- ------------------------------------------------------------------------- 
-- High Level Design Compiler for Altera(R) FPGAs Version 2026.3 (Release Build #847757300c)
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

-- VHDL created from reg_test_verifyNTT_multi_DUT
-- VHDL created on Wed Aug 26 10:03:58 2026


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;
use std.TextIO.all;
USE work.reg_test_verifyNTT_multi_DUT_safe_path.all;
use work.dspba_sim_library_package.all;

entity reg_test_verifyNTT_multi_DUT_stm is
    port (
        In_V_s_stm : out std_logic_vector(0 downto 0);
        In_C_s_stm : out std_logic_vector(7 downto 0);
        X_in_0_stm : out std_logic_vector(63 downto 0);
        X_in_1_stm : out std_logic_vector(63 downto 0);
        X_in_2_stm : out std_logic_vector(63 downto 0);
        X_in_3_stm : out std_logic_vector(63 downto 0);
        Out_V_s_stm : out std_logic_vector(0 downto 0);
        Out_C_s_stm : out std_logic_vector(7 downto 0);
        Out_Q_0_stm : out std_logic_vector(63 downto 0);
        Out_Q_1_stm : out std_logic_vector(63 downto 0);
        Out_Q_2_stm : out std_logic_vector(63 downto 0);
        Out_Q_3_stm : out std_logic_vector(63 downto 0);
        clk : out std_logic;
        areset : out std_logic
    );
end reg_test_verifyNTT_multi_DUT_stm;

architecture normal of reg_test_verifyNTT_multi_DUT_stm is

    signal clk_stm_sig : std_logic := '0';
    signal clk_stm_sig_stop : std_logic := '0';
    signal clk_stm_sig_stopped : std_logic := '0';
    signal areset_stm_sig : std_logic := '1';
    signal clk_ChannelIn_vunroll_x_stm_sig_stop : std_logic := '0';
    signal clk_ChannelOut_vunroll_x_stm_sig_stop : std_logic := '0';

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
        wait for 709 ps;
        if (clk_stm_sig_stop = '1') then
            assert (false)
            report "Arrived at end of stimulus data on clk clk" severity NOTE;
            clk_stm_sig_stopped <= '1';
            wait;
        end if;
        wait for 200 ps;
        clk_stm_sig <= not clk_stm_sig;
        wait for 709 ps;
        if (clk_stm_sig_stop = '1') then
            assert (false)
            report "Arrived at end of stimulus data on clk clk" severity NOTE;
            clk_stm_sig_stopped <= '1';
            wait;
        end if;
    end process;

    areset <= areset_stm_sig;
    areset_process: process begin
        areset_stm_sig <= '1';
        wait for 1363 ps;
        wait for 1023*1818 ps; -- additional reset delay
        areset_stm_sig <= '0';
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
        

        -- Generating stimulus for ChannelIn_vunroll_x
        ChannelIn_vunroll_x_stm_init_p: process

            variable L : line;
            variable dummy_int : Integer;
            file data_file_ChannelIn_vunroll_x : text open read_mode is safe_path("reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_ChannelIn_vunroll_x.stm");
            variable In_V_s_int_0 : Integer;
            variable In_V_s_temp : std_logic_vector(0 downto 0);
            variable In_C_s_int_0 : Integer;
            variable In_C_s_temp : std_logic_vector(7 downto 0);
            variable X_in_0_int_0 : Integer;
            variable X_in_0_int_1 : Integer;
            variable X_in_0_temp : std_logic_vector(63 downto 0);
            variable X_in_1_int_0 : Integer;
            variable X_in_1_int_1 : Integer;
            variable X_in_1_temp : std_logic_vector(63 downto 0);
            variable X_in_2_int_0 : Integer;
            variable X_in_2_int_1 : Integer;
            variable X_in_2_temp : std_logic_vector(63 downto 0);
            variable X_in_3_int_0 : Integer;
            variable X_in_3_int_1 : Integer;
            variable X_in_3_temp : std_logic_vector(63 downto 0);

        begin
            -- initialize all outputs to 0
            In_V_s_stm <= (others => '0');
            In_C_s_stm <= (others => '0');
            X_in_0_stm <= (others => '0');
            X_in_1_stm <= (others => '0');
            X_in_2_stm <= (others => '0');
            X_in_3_stm <= (others => '0');

            wait for 201 ps; -- wait delay
            
            for tick in 1 to 1023 loop
            
                wait for 1818 ps; -- additional reset delay
                
                In_V_s_stm <= (others => '0');
                In_C_s_stm <= (others => '0');
                X_in_0_stm <= (others => '0');
                X_in_1_stm <= (others => '0');
                X_in_2_stm <= (others => '0');
                X_in_3_stm <= (others => '0');
            end loop;
            while true loop
            
                IF (endfile(data_file_ChannelIn_vunroll_x)) THEN
                    clk_ChannelIn_vunroll_x_stm_sig_stop <= '1';
                    wait;
                ELSE
                    readline(data_file_ChannelIn_vunroll_x, L);
                    
                    read(L, In_V_s_int_0);
                    In_V_s_temp(0 downto 0) := std_logic_vector(to_unsigned(In_V_s_int_0, 1));
                    In_V_s_stm <= In_V_s_temp;
                    read(L, In_C_s_int_0);
                    In_C_s_temp(7 downto 0) := std_logic_vector(to_unsigned(In_C_s_int_0, 8));
                    In_C_s_stm <= In_C_s_temp;
                    read(L, X_in_0_int_0);
                    X_in_0_temp(31 downto 0) := std_logic_vector(to_signed(X_in_0_int_0, 32));
                    read(L, X_in_0_int_1);
                    X_in_0_temp(63 downto 32) := std_logic_vector(to_signed(X_in_0_int_1, 32));
                    X_in_0_stm <= X_in_0_temp;
                    read(L, X_in_1_int_0);
                    X_in_1_temp(31 downto 0) := std_logic_vector(to_signed(X_in_1_int_0, 32));
                    read(L, X_in_1_int_1);
                    X_in_1_temp(63 downto 32) := std_logic_vector(to_signed(X_in_1_int_1, 32));
                    X_in_1_stm <= X_in_1_temp;
                    read(L, X_in_2_int_0);
                    X_in_2_temp(31 downto 0) := std_logic_vector(to_signed(X_in_2_int_0, 32));
                    read(L, X_in_2_int_1);
                    X_in_2_temp(63 downto 32) := std_logic_vector(to_signed(X_in_2_int_1, 32));
                    X_in_2_stm <= X_in_2_temp;
                    read(L, X_in_3_int_0);
                    X_in_3_temp(31 downto 0) := std_logic_vector(to_signed(X_in_3_int_0, 32));
                    read(L, X_in_3_int_1);
                    X_in_3_temp(63 downto 32) := std_logic_vector(to_signed(X_in_3_int_1, 32));
                    X_in_3_stm <= X_in_3_temp;

                    deallocate(L);
                END IF;
                -- -- wait for rising edge to pass (assert signals just after rising edge)
                wait until clk_stm_sig'EVENT and clk_stm_sig = '1';
                wait for 1 ps; -- wait delay
                
                end loop;
            wait;
        END PROCESS;

        -- Generating stimulus for ChannelOut_vunroll_x
        ChannelOut_vunroll_x_stm_init_p: process

            variable L : line;
            variable dummy_int : Integer;
            file data_file_ChannelOut_vunroll_x : text open read_mode is safe_path("reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_ChannelOut_vunroll_x.stm");
            variable Out_V_s_int_0 : Integer;
            variable Out_V_s_temp : std_logic_vector(0 downto 0);
            variable Out_C_s_int_0 : Integer;
            variable Out_C_s_temp : std_logic_vector(7 downto 0);
            variable Out_Q_0_int_0 : Integer;
            variable Out_Q_0_int_1 : Integer;
            variable Out_Q_0_temp : std_logic_vector(63 downto 0);
            variable Out_Q_1_int_0 : Integer;
            variable Out_Q_1_int_1 : Integer;
            variable Out_Q_1_temp : std_logic_vector(63 downto 0);
            variable Out_Q_2_int_0 : Integer;
            variable Out_Q_2_int_1 : Integer;
            variable Out_Q_2_temp : std_logic_vector(63 downto 0);
            variable Out_Q_3_int_0 : Integer;
            variable Out_Q_3_int_1 : Integer;
            variable Out_Q_3_temp : std_logic_vector(63 downto 0);

        begin
            -- initialize all outputs to 0
            Out_V_s_stm <= (others => '0');
            Out_C_s_stm <= (others => '0');
            Out_Q_0_stm <= (others => '0');
            Out_Q_1_stm <= (others => '0');
            Out_Q_2_stm <= (others => '0');
            Out_Q_3_stm <= (others => '0');

            wait for 201 ps; -- wait delay
            
            wait for 1023*1818 ps; -- additional reset delay
            
            while true loop
            
                IF (endfile(data_file_ChannelOut_vunroll_x)) THEN
                    clk_ChannelOut_vunroll_x_stm_sig_stop <= '1';
                    wait;
                ELSE
                    readline(data_file_ChannelOut_vunroll_x, L);
                    
                    read(L, Out_V_s_int_0);
                    Out_V_s_temp(0 downto 0) := std_logic_vector(to_unsigned(Out_V_s_int_0, 1));
                    Out_V_s_stm <= Out_V_s_temp;
                    read(L, Out_C_s_int_0);
                    Out_C_s_temp(7 downto 0) := std_logic_vector(to_unsigned(Out_C_s_int_0, 8));
                    Out_C_s_stm <= Out_C_s_temp;
                    read(L, Out_Q_0_int_0);
                    Out_Q_0_temp(31 downto 0) := std_logic_vector(to_signed(Out_Q_0_int_0, 32));
                    read(L, Out_Q_0_int_1);
                    Out_Q_0_temp(63 downto 32) := std_logic_vector(to_signed(Out_Q_0_int_1, 32));
                    Out_Q_0_stm <= Out_Q_0_temp;
                    read(L, Out_Q_1_int_0);
                    Out_Q_1_temp(31 downto 0) := std_logic_vector(to_signed(Out_Q_1_int_0, 32));
                    read(L, Out_Q_1_int_1);
                    Out_Q_1_temp(63 downto 32) := std_logic_vector(to_signed(Out_Q_1_int_1, 32));
                    Out_Q_1_stm <= Out_Q_1_temp;
                    read(L, Out_Q_2_int_0);
                    Out_Q_2_temp(31 downto 0) := std_logic_vector(to_signed(Out_Q_2_int_0, 32));
                    read(L, Out_Q_2_int_1);
                    Out_Q_2_temp(63 downto 32) := std_logic_vector(to_signed(Out_Q_2_int_1, 32));
                    Out_Q_2_stm <= Out_Q_2_temp;
                    read(L, Out_Q_3_int_0);
                    Out_Q_3_temp(31 downto 0) := std_logic_vector(to_signed(Out_Q_3_int_0, 32));
                    read(L, Out_Q_3_int_1);
                    Out_Q_3_temp(63 downto 32) := std_logic_vector(to_signed(Out_Q_3_int_1, 32));
                    Out_Q_3_stm <= Out_Q_3_temp;

                    deallocate(L);
                END IF;
                -- -- wait for rising edge to pass (assert signals just after rising edge)
                wait until clk_stm_sig'EVENT and clk_stm_sig = '1';
                wait for 1 ps; -- wait delay
                
                end loop;
            wait;
        END PROCESS;

    clk_stm_sig_stop <= clk_ChannelIn_vunroll_x_stm_sig_stop OR clk_ChannelOut_vunroll_x_stm_sig_stop OR '0';


    END normal;
