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
use work.dspba_sim_library_package.all;
entity reg_test_verifyNTT_multi_DUT_atb is
end;

architecture normal of reg_test_verifyNTT_multi_DUT_atb is

component reg_test_verifyNTT_multi_DUT is
    port (
        In_V_s : in std_logic_vector(0 downto 0);  -- ufix1
        In_C_s : in std_logic_vector(7 downto 0);  -- ufix8
        X_in_0 : in std_logic_vector(63 downto 0);  -- sfix64
        X_in_1 : in std_logic_vector(63 downto 0);  -- sfix64
        X_in_2 : in std_logic_vector(63 downto 0);  -- sfix64
        X_in_3 : in std_logic_vector(63 downto 0);  -- sfix64
        Out_V_s : out std_logic_vector(0 downto 0);  -- ufix1
        Out_C_s : out std_logic_vector(7 downto 0);  -- ufix8
        Out_Q_0 : out std_logic_vector(63 downto 0);  -- sfix64
        Out_Q_1 : out std_logic_vector(63 downto 0);  -- sfix64
        Out_Q_2 : out std_logic_vector(63 downto 0);  -- sfix64
        Out_Q_3 : out std_logic_vector(63 downto 0);  -- sfix64
        clk : in std_logic;
        areset : in std_logic
    );
end component;

component reg_test_verifyNTT_multi_DUT_stm is
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
end component;

signal In_V_s_stm : STD_LOGIC_VECTOR (0 downto 0);
signal In_C_s_stm : STD_LOGIC_VECTOR (7 downto 0);
signal X_in_0_stm : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_1_stm : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_2_stm : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_3_stm : STD_LOGIC_VECTOR (63 downto 0);
signal Out_V_s_stm : STD_LOGIC_VECTOR (0 downto 0);
signal Out_C_s_stm : STD_LOGIC_VECTOR (7 downto 0);
signal Out_Q_0_stm : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_1_stm : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_2_stm : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_3_stm : STD_LOGIC_VECTOR (63 downto 0);
signal In_V_s_dut : STD_LOGIC_VECTOR (0 downto 0);
signal In_C_s_dut : STD_LOGIC_VECTOR (7 downto 0);
signal X_in_0_dut : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_1_dut : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_2_dut : STD_LOGIC_VECTOR (63 downto 0);
signal X_in_3_dut : STD_LOGIC_VECTOR (63 downto 0);
signal Out_V_s_dut : STD_LOGIC_VECTOR (0 downto 0);
signal Out_C_s_dut : STD_LOGIC_VECTOR (7 downto 0);
signal Out_Q_0_dut : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_1_dut : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_2_dut : STD_LOGIC_VECTOR (63 downto 0);
signal Out_Q_3_dut : STD_LOGIC_VECTOR (63 downto 0);
        signal clk : std_logic;
        signal areset : std_logic;

begin

-- Channelized data in real output
checkChannelIn_vunroll_x : process (clk, areset, X_in_0_dut, X_in_0_stm, X_in_1_dut, X_in_1_stm, X_in_2_dut, X_in_2_stm, X_in_3_dut, X_in_3_stm)
begin
END PROCESS;


-- Channelized data out check
checkChannelOut_vunroll_x : process (clk, areset, Out_Q_0_dut, Out_Q_0_stm, Out_Q_1_dut, Out_Q_1_stm, Out_Q_2_dut, Out_Q_2_stm, Out_Q_3_dut, Out_Q_3_stm)
variable mismatch_Out_V_s : BOOLEAN := FALSE;
variable mismatch_Out_C_s : BOOLEAN := FALSE;
variable mismatch_Out_Q_0 : BOOLEAN := FALSE;
variable mismatch_Out_Q_1 : BOOLEAN := FALSE;
variable mismatch_Out_Q_2 : BOOLEAN := FALSE;
variable mismatch_Out_Q_3 : BOOLEAN := FALSE;
variable ok : BOOLEAN := TRUE;
begin
    IF ((areset = '1')) THEN
        -- do nothing during reset
    ELSIF (clk'EVENT AND clk = '0') THEN -- falling clock edge to avoid transitions
        ok := TRUE;
        mismatch_Out_V_s := FALSE;
        mismatch_Out_C_s := FALSE;
        mismatch_Out_Q_0 := FALSE;
        mismatch_Out_Q_1 := FALSE;
        mismatch_Out_Q_2 := FALSE;
        mismatch_Out_Q_3 := FALSE;
        IF ( (Out_V_s_dut /= Out_V_s_stm)) THEN
            mismatch_Out_V_s := TRUE;
            report "mismatch in Out_V_s signal" severity Failure;
        END IF;
        IF ((Out_V_s_dut = "1")) THEN
            IF ( (Out_C_s_dut /= Out_C_s_stm)) THEN
                mismatch_Out_C_s := TRUE;
                report "mismatch in Out_C_s signal" severity Warning;
            END IF;
            IF ( (Out_Q_0_dut /= Out_Q_0_stm)) THEN
                mismatch_Out_Q_0 := TRUE;
                report "mismatch in Out_Q_0 signal" severity Warning;
            END IF;
            IF ( (Out_Q_1_dut /= Out_Q_1_stm)) THEN
                mismatch_Out_Q_1 := TRUE;
                report "mismatch in Out_Q_1 signal" severity Warning;
            END IF;
            IF ( (Out_Q_2_dut /= Out_Q_2_stm)) THEN
                mismatch_Out_Q_2 := TRUE;
                report "mismatch in Out_Q_2 signal" severity Warning;
            END IF;
            IF ( (Out_Q_3_dut /= Out_Q_3_stm)) THEN
                mismatch_Out_Q_3 := TRUE;
                report "mismatch in Out_Q_3 signal" severity Warning;
            END IF;
        END IF;
        IF (mismatch_Out_V_s = TRUE or mismatch_Out_C_s = TRUE or mismatch_Out_Q_0 = TRUE or mismatch_Out_Q_1 = TRUE or mismatch_Out_Q_2 = TRUE or mismatch_Out_Q_3 = TRUE) THEN
            ok := FALSE;
            report_mismatch_failure_detected := TRUE;
        END IF;
        IF (ok = FALSE) THEN
            report "Mismatch detected" severity Failure;
        END IF;
    END IF;
END PROCESS;


dut : reg_test_verifyNTT_multi_DUT port map (
    In_V_s_stm,
    In_C_s_stm,
    X_in_0_stm,
    X_in_1_stm,
    X_in_2_stm,
    X_in_3_stm,
    Out_V_s_dut,
    Out_C_s_dut,
    Out_Q_0_dut,
    Out_Q_1_dut,
    Out_Q_2_dut,
    Out_Q_3_dut,
        clk,
        areset
);

sim : reg_test_verifyNTT_multi_DUT_stm port map (
    In_V_s_stm,
    In_C_s_stm,
    X_in_0_stm,
    X_in_1_stm,
    X_in_2_stm,
    X_in_3_stm,
    Out_V_s_stm,
    Out_C_s_stm,
    Out_Q_0_stm,
    Out_Q_1_stm,
    Out_Q_2_stm,
    Out_Q_3_stm,
        clk,
        areset
);

end normal;
