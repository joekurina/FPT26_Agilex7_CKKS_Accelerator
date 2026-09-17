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
-- VHDL created on Tue Aug 25 13:21:28 2026


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;
use IEEE.MATH_REAL.all;
use std.TextIO.all;
use work.dspba_library_package.all;

LIBRARY altera_mf;
USE altera_mf.altera_mf_components.all;
LIBRARY altera_lnsim;
USE altera_lnsim.altera_lnsim_components.altera_syncram;

library tennm;
use tennm.tennm_components.tennm_mac;
use tennm.tennm_components.tennm_fp_mac;

USE work.ifft8k_base_DUT_safe_path.all;
entity flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0 is
    port (
        in_0 : in std_logic_vector(63 downto 0);  -- float64_m52
        out_primWireOut : out std_logic_vector(63 downto 0);  -- float64_m52
        clk : in std_logic;
        areset : in std_logic
    );
end flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0;

architecture normal of flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0 is

    attribute altera_attribute : string;
    attribute altera_attribute of normal : architecture is "-name AUTO_SHIFT_REGISTER_RECOGNITION OFF; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 10037; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 15400; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 12020; -name MESSAGE_DISABLE 12030; -name MESSAGE_DISABLE 12010; -name MESSAGE_DISABLE 12110; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 13410; -name MESSAGE_DISABLE 113007";
    
    signal GND_q : STD_LOGIC_VECTOR (0 downto 0);
    signal VCC_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expX_uid6_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal cstAllOWE_uid7_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal cstZeroWF_uid8_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal cstAllZWE_uid9_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_x_uid11_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_x_uid12_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excZ_x_uid12_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid13_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid13_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid14_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid14_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid15_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_x_uid16_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_x_uid17_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid18_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid19_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_x_uid20_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal oFracX_uid23_block_rsrvd_fix_q : STD_LOGIC_VECTOR (52 downto 0);
    signal normFracLow_uid28_block_rsrvd_fix_in : STD_LOGIC_VECTOR (114 downto 0);
    signal normFracLow_uid28_block_rsrvd_fix_b : STD_LOGIC_VECTOR (52 downto 0);
    signal twoZeros_uid30_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal zeroExtendedExp_uid31_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal fracRPostNorm1dto0_uid41_block_rsrvd_fix_in : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostNorm1dto0_uid41_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal lrs_uid42_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal roundBitDetectionConstant_uid43_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal roundBitDetectionPattern_uid44_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal roundBit_uid45_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expFracPreRound_uid46_block_rsrvd_fix_q : STD_LOGIC_VECTOR (65 downto 0);
    signal roundBitAndNormalizationOp_uid48_block_rsrvd_fix_q : STD_LOGIC_VECTOR (54 downto 0);
    signal expRPreExcExt_uid50_block_rsrvd_fix_b : STD_LOGIC_VECTOR (13 downto 0);
    signal fracRPreExcExt_uid51_block_rsrvd_fix_in : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPreExcExt_uid51_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal expUdf_uid52_block_rsrvd_fix_a : STD_LOGIC_VECTOR (15 downto 0);
    signal expUdf_uid52_block_rsrvd_fix_b : STD_LOGIC_VECTOR (15 downto 0);
    signal expUdf_uid52_block_rsrvd_fix_o : STD_LOGIC_VECTOR (15 downto 0);
    signal expUdf_uid52_block_rsrvd_fix_n : STD_LOGIC_VECTOR (0 downto 0);
    signal expOvf_uid54_block_rsrvd_fix_a : STD_LOGIC_VECTOR (15 downto 0);
    signal expOvf_uid54_block_rsrvd_fix_b : STD_LOGIC_VECTOR (15 downto 0);
    signal expOvf_uid54_block_rsrvd_fix_o : STD_LOGIC_VECTOR (15 downto 0);
    signal expOvf_uid54_block_rsrvd_fix_n : STD_LOGIC_VECTOR (0 downto 0);
    signal signX_uid55_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal InvSignX_uid56_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expRPreExc_uid57_block_rsrvd_fix_in : STD_LOGIC_VECTOR (10 downto 0);
    signal expRPreExc_uid57_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal regInputAndOverflow_uid58_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRInf_uid59_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal regInputAndUnderflow_uid60_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRZero_uid61_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal concExc_uid62_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal excREnc_uid63_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal oneFracRPostExc2_uid64_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal fracRPostExc_uid67_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostExc_uid67_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPostExc_uid71_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal expRPostExc_uid71_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal invExcXN_uid72_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sRPostExc_uid73_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal constMultR_uid74_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal sR_bottomExtension_uid83_fxpFracProd_uid25_block_rsrvd_fix_q : STD_LOGIC_VECTOR (62 downto 0);
    signal sR_mergedSignalTMB_uid85_fxpFracProd_uid25_block_rsrvd_fix_q : STD_LOGIC_VECTOR (116 downto 0);
    signal expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_in : STD_LOGIC_VECTOR (66 downto 0);
    signal expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_b : STD_LOGIC_VECTOR (62 downto 0);
    signal expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_in : STD_LOGIC_VECTOR (66 downto 0);
    signal expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_b : STD_LOGIC_VECTOR (0 downto 0);
    signal expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_join_q : STD_LOGIC_VECTOR (66 downto 0);
    signal redist0_expRPreExc_uid57_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist1_signX_uid55_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (51 downto 0);

begin


    -- frac_x_uid11_block_rsrvd_fix(BITSELECT,10)@0
    frac_x_uid11_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_0(51 downto 0));

    -- cstZeroWF_uid8_block_rsrvd_fix(CONSTANT,7)
    cstZeroWF_uid8_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000000";

    -- fracXIsZero_uid14_block_rsrvd_fix(LOGICAL,13)@0 + 1
    fracXIsZero_uid14_block_rsrvd_fix_qi <= "1" WHEN cstZeroWF_uid8_block_rsrvd_fix_q = frac_x_uid11_block_rsrvd_fix_b ELSE "0";
    fracXIsZero_uid14_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid14_block_rsrvd_fix_qi, xout => fracXIsZero_uid14_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- fracXIsNotZero_uid15_block_rsrvd_fix(LOGICAL,14)@1
    fracXIsNotZero_uid15_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (fracXIsZero_uid14_block_rsrvd_fix_q));

    -- cstAllOWE_uid7_block_rsrvd_fix(CONSTANT,6)
    cstAllOWE_uid7_block_rsrvd_fix_q <= "11111111111";

    -- expX_uid6_block_rsrvd_fix(BITSELECT,5)@0
    expX_uid6_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_0(62 downto 52));

    -- expXIsMax_uid13_block_rsrvd_fix(LOGICAL,12)@0 + 1
    expXIsMax_uid13_block_rsrvd_fix_qi <= "1" WHEN expX_uid6_block_rsrvd_fix_b = cstAllOWE_uid7_block_rsrvd_fix_q ELSE "0";
    expXIsMax_uid13_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid13_block_rsrvd_fix_qi, xout => expXIsMax_uid13_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- excN_x_uid17_block_rsrvd_fix(LOGICAL,16)@1
    excN_x_uid17_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expXIsMax_uid13_block_rsrvd_fix_q and fracXIsNotZero_uid15_block_rsrvd_fix_q);

    -- invExcXN_uid72_block_rsrvd_fix(LOGICAL,71)@1
    invExcXN_uid72_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excN_x_uid17_block_rsrvd_fix_q));

    -- signX_uid55_block_rsrvd_fix(BITSELECT,54)@0
    signX_uid55_block_rsrvd_fix_b <= in_0(63 downto 63);

    -- redist1_signX_uid55_block_rsrvd_fix_b_1(DELAY,178)
    redist1_signX_uid55_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist1_signX_uid55_block_rsrvd_fix_b_1_q <= signX_uid55_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- InvSignX_uid56_block_rsrvd_fix(LOGICAL,55)@1
    InvSignX_uid56_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist1_signX_uid55_block_rsrvd_fix_b_1_q));

    -- VCC(CONSTANT,1)
    VCC_q <= "1";

    -- sRPostExc_uid73_block_rsrvd_fix(LOGICAL,72)@1
    sRPostExc_uid73_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(InvSignX_uid56_block_rsrvd_fix_q and invExcXN_uid72_block_rsrvd_fix_q);

    -- GND(CONSTANT,0)
    GND_q <= "0";

    -- twoZeros_uid30_block_rsrvd_fix(CONSTANT,29)
    twoZeros_uid30_block_rsrvd_fix_q <= "00";

    -- zeroExtendedExp_uid31_block_rsrvd_fix(BITJOIN,30)@0
    zeroExtendedExp_uid31_block_rsrvd_fix_q <= twoZeros_uid30_block_rsrvd_fix_q & expX_uid6_block_rsrvd_fix_b;

    -- oFracX_uid23_block_rsrvd_fix(BITJOIN,22)@0
    oFracX_uid23_block_rsrvd_fix_q <= VCC_q & frac_x_uid11_block_rsrvd_fix_b;

    -- sR_bottomExtension_uid83_fxpFracProd_uid25_block_rsrvd_fix(CONSTANT,82)
    sR_bottomExtension_uid83_fxpFracProd_uid25_block_rsrvd_fix_q <= "000000000000000000000000000000000000000000000000000000000000000";

    -- sR_mergedSignalTMB_uid85_fxpFracProd_uid25_block_rsrvd_fix(BITJOIN,84)@0
    sR_mergedSignalTMB_uid85_fxpFracProd_uid25_block_rsrvd_fix_q <= GND_q & oFracX_uid23_block_rsrvd_fix_q & sR_bottomExtension_uid83_fxpFracProd_uid25_block_rsrvd_fix_q;

    -- normFracLow_uid28_block_rsrvd_fix(BITSELECT,27)@0
    normFracLow_uid28_block_rsrvd_fix_in <= sR_mergedSignalTMB_uid85_fxpFracProd_uid25_block_rsrvd_fix_q(114 downto 0);
    normFracLow_uid28_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(normFracLow_uid28_block_rsrvd_fix_in(114 downto 62));

    -- expFracPreRound_uid46_block_rsrvd_fix(BITJOIN,45)@0
    expFracPreRound_uid46_block_rsrvd_fix_q <= zeroExtendedExp_uid31_block_rsrvd_fix_q & normFracLow_uid28_block_rsrvd_fix_b;

    -- expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a(BITSELECT,174)@0
    expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_in <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((66 downto 66 => expFracPreRound_uid46_block_rsrvd_fix_q(65)) & expFracPreRound_uid46_block_rsrvd_fix_q));
    expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_b <= expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_in(63 downto 1);

    -- roundBitDetectionConstant_uid43_block_rsrvd_fix(CONSTANT,42)
    roundBitDetectionConstant_uid43_block_rsrvd_fix_q <= "010";

    -- fracRPostNorm1dto0_uid41_block_rsrvd_fix(BITSELECT,40)@0
    fracRPostNorm1dto0_uid41_block_rsrvd_fix_in <= normFracLow_uid28_block_rsrvd_fix_b(1 downto 0);
    fracRPostNorm1dto0_uid41_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracRPostNorm1dto0_uid41_block_rsrvd_fix_in(1 downto 0));

    -- lrs_uid42_block_rsrvd_fix(BITJOIN,41)@0
    lrs_uid42_block_rsrvd_fix_q <= fracRPostNorm1dto0_uid41_block_rsrvd_fix_b & GND_q;

    -- roundBitDetectionPattern_uid44_block_rsrvd_fix(LOGICAL,43)@0
    roundBitDetectionPattern_uid44_block_rsrvd_fix_q <= "1" WHEN lrs_uid42_block_rsrvd_fix_q = roundBitDetectionConstant_uid43_block_rsrvd_fix_q ELSE "0";

    -- roundBit_uid45_block_rsrvd_fix(LOGICAL,44)@0
    roundBit_uid45_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (roundBitDetectionPattern_uid44_block_rsrvd_fix_q));

    -- roundBitAndNormalizationOp_uid48_block_rsrvd_fix(BITJOIN,47)@0
    roundBitAndNormalizationOp_uid48_block_rsrvd_fix_q <= GND_q & GND_q & cstZeroWF_uid8_block_rsrvd_fix_q & roundBit_uid45_block_rsrvd_fix_q;

    -- expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b(BITSELECT,175)@0
    expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_in <= STD_LOGIC_VECTOR("000000000000" & roundBitAndNormalizationOp_uid48_block_rsrvd_fix_q);
    expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_b <= STD_LOGIC_VECTOR(expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_in(0 downto 0));

    -- expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_join(BITJOIN,176)@0
    expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_join_q <= GND_q & GND_q & GND_q & expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_a_b & expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_BitSelect_for_b_b;

    -- expRPreExcExt_uid50_block_rsrvd_fix(BITSELECT,49)@0
    expRPreExcExt_uid50_block_rsrvd_fix_b <= expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_join_q(66 downto 53);

    -- expRPreExc_uid57_block_rsrvd_fix(BITSELECT,56)@0
    expRPreExc_uid57_block_rsrvd_fix_in <= expRPreExcExt_uid50_block_rsrvd_fix_b(10 downto 0);
    expRPreExc_uid57_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(expRPreExc_uid57_block_rsrvd_fix_in(10 downto 0));

    -- redist0_expRPreExc_uid57_block_rsrvd_fix_b_1(DELAY,177)
    redist0_expRPreExc_uid57_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist0_expRPreExc_uid57_block_rsrvd_fix_b_1_q <= expRPreExc_uid57_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- cstAllZWE_uid9_block_rsrvd_fix(CONSTANT,8)
    cstAllZWE_uid9_block_rsrvd_fix_q <= "00000000000";

    -- expOvf_uid54_block_rsrvd_fix(COMPARE,53)@0 + 1
    expOvf_uid54_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((15 downto 14 => expRPreExcExt_uid50_block_rsrvd_fix_b(13)) & expRPreExcExt_uid50_block_rsrvd_fix_b));
    expOvf_uid54_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("00000" & cstAllOWE_uid7_block_rsrvd_fix_q));
    expOvf_uid54_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expOvf_uid54_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expOvf_uid54_block_rsrvd_fix_a) - SIGNED(expOvf_uid54_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expOvf_uid54_block_rsrvd_fix_n(0) <= not (expOvf_uid54_block_rsrvd_fix_o(15));

    -- invExpXIsMax_uid18_block_rsrvd_fix(LOGICAL,17)@1
    invExpXIsMax_uid18_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (expXIsMax_uid13_block_rsrvd_fix_q));

    -- excZ_x_uid12_block_rsrvd_fix(LOGICAL,11)@0 + 1
    excZ_x_uid12_block_rsrvd_fix_qi <= "1" WHEN expX_uid6_block_rsrvd_fix_b = cstAllZWE_uid9_block_rsrvd_fix_q ELSE "0";
    excZ_x_uid12_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excZ_x_uid12_block_rsrvd_fix_qi, xout => excZ_x_uid12_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- InvExpXIsZero_uid19_block_rsrvd_fix(LOGICAL,18)@1
    InvExpXIsZero_uid19_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excZ_x_uid12_block_rsrvd_fix_q));

    -- excR_x_uid20_block_rsrvd_fix(LOGICAL,19)@1
    excR_x_uid20_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(InvExpXIsZero_uid19_block_rsrvd_fix_q and invExpXIsMax_uid18_block_rsrvd_fix_q);

    -- regInputAndOverflow_uid58_block_rsrvd_fix(LOGICAL,57)@1
    regInputAndOverflow_uid58_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excR_x_uid20_block_rsrvd_fix_q and expOvf_uid54_block_rsrvd_fix_n);

    -- excI_x_uid16_block_rsrvd_fix(LOGICAL,15)@1
    excI_x_uid16_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expXIsMax_uid13_block_rsrvd_fix_q and fracXIsZero_uid14_block_rsrvd_fix_q);

    -- excRInf_uid59_block_rsrvd_fix(LOGICAL,58)@1
    excRInf_uid59_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excI_x_uid16_block_rsrvd_fix_q or regInputAndOverflow_uid58_block_rsrvd_fix_q);

    -- expUdf_uid52_block_rsrvd_fix(COMPARE,51)@0 + 1
    expUdf_uid52_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("000000000000000" & GND_q));
    expUdf_uid52_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((15 downto 14 => expRPreExcExt_uid50_block_rsrvd_fix_b(13)) & expRPreExcExt_uid50_block_rsrvd_fix_b));
    expUdf_uid52_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expUdf_uid52_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expUdf_uid52_block_rsrvd_fix_a) - SIGNED(expUdf_uid52_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expUdf_uid52_block_rsrvd_fix_n(0) <= not (expUdf_uid52_block_rsrvd_fix_o(15));

    -- regInputAndUnderflow_uid60_block_rsrvd_fix(LOGICAL,59)@1
    regInputAndUnderflow_uid60_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excR_x_uid20_block_rsrvd_fix_q and expUdf_uid52_block_rsrvd_fix_n);

    -- excRZero_uid61_block_rsrvd_fix(LOGICAL,60)@1
    excRZero_uid61_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excZ_x_uid12_block_rsrvd_fix_q or regInputAndUnderflow_uid60_block_rsrvd_fix_q);

    -- concExc_uid62_block_rsrvd_fix(BITJOIN,61)@1
    concExc_uid62_block_rsrvd_fix_q <= excN_x_uid17_block_rsrvd_fix_q & excRInf_uid59_block_rsrvd_fix_q & excRZero_uid61_block_rsrvd_fix_q;

    -- excREnc_uid63_block_rsrvd_fix(LOOKUP,62)@1
    excREnc_uid63_block_rsrvd_fix_combproc: PROCESS (concExc_uid62_block_rsrvd_fix_q)
    BEGIN
        -- Begin reserved scope level
        CASE (concExc_uid62_block_rsrvd_fix_q) IS
            WHEN "000" => excREnc_uid63_block_rsrvd_fix_q <= "01";
            WHEN "001" => excREnc_uid63_block_rsrvd_fix_q <= "00";
            WHEN "010" => excREnc_uid63_block_rsrvd_fix_q <= "10";
            WHEN "011" => excREnc_uid63_block_rsrvd_fix_q <= "00";
            WHEN "100" => excREnc_uid63_block_rsrvd_fix_q <= "11";
            WHEN "101" => excREnc_uid63_block_rsrvd_fix_q <= "00";
            WHEN "110" => excREnc_uid63_block_rsrvd_fix_q <= "00";
            WHEN "111" => excREnc_uid63_block_rsrvd_fix_q <= "00";
            WHEN OTHERS => -- unreachable
                           excREnc_uid63_block_rsrvd_fix_q <= (others => '-');
        END CASE;
        -- End reserved scope level
    END PROCESS;

    -- expRPostExc_uid71_block_rsrvd_fix(MUX,70)@1
    expRPostExc_uid71_block_rsrvd_fix_s <= excREnc_uid63_block_rsrvd_fix_q;
    expRPostExc_uid71_block_rsrvd_fix_combproc: PROCESS (expRPostExc_uid71_block_rsrvd_fix_s, cstAllZWE_uid9_block_rsrvd_fix_q, redist0_expRPreExc_uid57_block_rsrvd_fix_b_1_q, cstAllOWE_uid7_block_rsrvd_fix_q)
    BEGIN
        CASE (expRPostExc_uid71_block_rsrvd_fix_s) IS
            WHEN "00" => expRPostExc_uid71_block_rsrvd_fix_q <= cstAllZWE_uid9_block_rsrvd_fix_q;
            WHEN "01" => expRPostExc_uid71_block_rsrvd_fix_q <= redist0_expRPreExc_uid57_block_rsrvd_fix_b_1_q;
            WHEN "10" => expRPostExc_uid71_block_rsrvd_fix_q <= cstAllOWE_uid7_block_rsrvd_fix_q;
            WHEN "11" => expRPostExc_uid71_block_rsrvd_fix_q <= cstAllOWE_uid7_block_rsrvd_fix_q;
            WHEN OTHERS => expRPostExc_uid71_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- oneFracRPostExc2_uid64_block_rsrvd_fix(CONSTANT,63)
    oneFracRPostExc2_uid64_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000001";

    -- fracRPreExcExt_uid51_block_rsrvd_fix(BITSELECT,50)@0
    fracRPreExcExt_uid51_block_rsrvd_fix_in <= expFracRPostRounding_uid49_block_rsrvd_fix_replace_or_join_q(52 downto 0);
    fracRPreExcExt_uid51_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracRPreExcExt_uid51_block_rsrvd_fix_in(52 downto 1));

    -- redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1(DELAY,179)
    redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1_q <= fracRPreExcExt_uid51_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- fracRPostExc_uid67_block_rsrvd_fix(MUX,66)@1
    fracRPostExc_uid67_block_rsrvd_fix_s <= excREnc_uid63_block_rsrvd_fix_q;
    fracRPostExc_uid67_block_rsrvd_fix_combproc: PROCESS (fracRPostExc_uid67_block_rsrvd_fix_s, cstZeroWF_uid8_block_rsrvd_fix_q, redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1_q, oneFracRPostExc2_uid64_block_rsrvd_fix_q)
    BEGIN
        CASE (fracRPostExc_uid67_block_rsrvd_fix_s) IS
            WHEN "00" => fracRPostExc_uid67_block_rsrvd_fix_q <= cstZeroWF_uid8_block_rsrvd_fix_q;
            WHEN "01" => fracRPostExc_uid67_block_rsrvd_fix_q <= redist2_fracRPreExcExt_uid51_block_rsrvd_fix_b_1_q;
            WHEN "10" => fracRPostExc_uid67_block_rsrvd_fix_q <= cstZeroWF_uid8_block_rsrvd_fix_q;
            WHEN "11" => fracRPostExc_uid67_block_rsrvd_fix_q <= oneFracRPostExc2_uid64_block_rsrvd_fix_q;
            WHEN OTHERS => fracRPostExc_uid67_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- constMultR_uid74_block_rsrvd_fix(BITJOIN,73)@1
    constMultR_uid74_block_rsrvd_fix_q <= sRPostExc_uid73_block_rsrvd_fix_q & expRPostExc_uid71_block_rsrvd_fix_q & fracRPostExc_uid67_block_rsrvd_fix_q;

    -- out_primWireOut(GPOUT,4)@1
    out_primWireOut <= constMultR_uid74_block_rsrvd_fix_q;

END normal;
