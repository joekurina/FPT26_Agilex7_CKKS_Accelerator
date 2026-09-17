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
use work.dspba_sim_library_package.all;
entity flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_atb is
end;

architecture normal of flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_atb is

component flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0 is
    port (
        in_0 : in std_logic_vector(63 downto 0);  -- float64_m52
        out_primWireOut : out std_logic_vector(63 downto 0);  -- float64_m52
        clk : in std_logic;
        areset : in std_logic
    );
end component;

component flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_stm is
    port (
        in_0_stm : out std_logic_vector(63 downto 0);
        out_primWireOut_stm : out std_logic_vector(63 downto 0);
        clk : out std_logic;
        areset : out std_logic
    );
end component;

signal in_0_stm : STD_LOGIC_VECTOR (63 downto 0);
signal out_primWireOut_stm : STD_LOGIC_VECTOR (63 downto 0);
signal in_0_dut : STD_LOGIC_VECTOR (63 downto 0);
signal out_primWireOut_dut : STD_LOGIC_VECTOR (63 downto 0);
        signal clk : std_logic;
        signal areset : std_logic;

begin

-- General Purpose data in real output
checkin_0 : process (clk, areset, in_0_dut, in_0_stm)
variable in_0_real : REAL := 0.0;
variable in_0_stm_real : REAL := 0.0;
begin
 in_0_real := vIEEE_2_real(in_0_dut, 11, 52, false);
 in_0_stm_real := vIEEE_2_real(in_0_stm, 11, 52, false);
END PROCESS;


dut : flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0 port map (
    in_0_stm,
    out_primWireOut_dut,
        clk,
        areset
);

sim : flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0_stm port map (
    in_0_stm,
    out_primWireOut_stm,
        clk,
        areset
);

end normal;
