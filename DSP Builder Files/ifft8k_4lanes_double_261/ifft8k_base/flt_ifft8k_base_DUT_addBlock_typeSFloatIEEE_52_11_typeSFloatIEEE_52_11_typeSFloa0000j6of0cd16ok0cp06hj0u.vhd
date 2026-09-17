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

-- VHDL created from flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_0_0_addFpArchSoleDatapath_correctRounding_3m1iq5c35in4uia1u6737j47pg9pig2jg8vcemhqnd3wi063064663c61i64oc1764761di4p61v64vi1e64e61kc3k65k63961r60uq5ux0ao30cd06cj0of0cdj6of0cd16ok0cp06hj0u
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
entity flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u is
    port (
        in_0 : in std_logic_vector(63 downto 0);  -- float64_m52
        in_1 : in std_logic_vector(63 downto 0);  -- float64_m52
        out_primWireOut : out std_logic_vector(63 downto 0);  -- float64_m52
        clk : in std_logic;
        areset : in std_logic
    );
end flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u;

architecture normal of flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u is

    attribute altera_attribute : string;
    attribute altera_attribute of normal : architecture is "-name AUTO_SHIFT_REGISTER_RECOGNITION OFF; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 10037; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 15400; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 12020; -name MESSAGE_DISABLE 12030; -name MESSAGE_DISABLE 12010; -name MESSAGE_DISABLE 12110; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 13410; -name MESSAGE_DISABLE 113007";
    
    signal GND_q : STD_LOGIC_VECTOR (0 downto 0);
    signal VCC_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expFracX_uid7_block_rsrvd_fix_b : STD_LOGIC_VECTOR (62 downto 0);
    signal expFracY_uid8_block_rsrvd_fix_b : STD_LOGIC_VECTOR (62 downto 0);
    signal xGTEy_uid9_block_rsrvd_fix_a : STD_LOGIC_VECTOR (64 downto 0);
    signal xGTEy_uid9_block_rsrvd_fix_b : STD_LOGIC_VECTOR (64 downto 0);
    signal xGTEy_uid9_block_rsrvd_fix_o : STD_LOGIC_VECTOR (64 downto 0);
    signal xGTEy_uid9_block_rsrvd_fix_n : STD_LOGIC_VECTOR (0 downto 0);
    signal fracY_uid10_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal expY_uid11_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal sigY_uid12_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal ypn_uid13_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal aSig_uid17_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal aSig_uid17_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal bSig_uid18_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal bSig_uid18_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal cstAllOWE_uid19_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal cstZeroWF_uid20_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal cstAllZWE_uid21_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal exp_aSig_uid22_block_rsrvd_fix_in : STD_LOGIC_VECTOR (62 downto 0);
    signal exp_aSig_uid22_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_aSig_uid23_block_rsrvd_fix_in : STD_LOGIC_VECTOR (51 downto 0);
    signal frac_aSig_uid23_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_aSig_uid17_uid24_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excZ_aSig_uid17_uid24_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid25_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid25_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid26_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid26_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid27_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_aSig_uid28_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_aSig_uid29_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_aSig_uid29_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid30_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid31_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_aSig_uid32_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal exp_bSig_uid36_block_rsrvd_fix_in : STD_LOGIC_VECTOR (62 downto 0);
    signal exp_bSig_uid36_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_bSig_uid37_block_rsrvd_fix_in : STD_LOGIC_VECTOR (51 downto 0);
    signal frac_bSig_uid37_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_bSig_uid18_uid38_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid39_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid39_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid40_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid40_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid41_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_bSig_uid42_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_bSig_uid43_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_bSig_uid43_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid44_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid45_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_bSig_uid46_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigA_uid51_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal sigB_uid52_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal effSub_uid53_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracBz_uid57_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal fracBz_uid57_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal oFracB_uid60_block_rsrvd_fix_q : STD_LOGIC_VECTOR (52 downto 0);
    signal expAmExpB_uid61_block_rsrvd_fix_a : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid61_block_rsrvd_fix_b : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid61_block_rsrvd_fix_o : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid61_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal cWFP2_uid62_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal shiftedOut_uid64_block_rsrvd_fix_a : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid64_block_rsrvd_fix_b : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid64_block_rsrvd_fix_o : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid64_block_rsrvd_fix_c : STD_LOGIC_VECTOR (0 downto 0);
    signal padConst_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (53 downto 0);
    signal rightPaddedIn_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal iShiftedOut_uid68_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal alignFracBPostShiftOut_uid69_block_rsrvd_fix_b : STD_LOGIC_VECTOR (106 downto 0);
    signal alignFracBPostShiftOut_uid69_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (106 downto 0);
    signal alignFracBPostShiftOut_uid69_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal effSubInvSticky_uid75_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal zocst_uid77_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal fracAAddOp_uid78_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOp_uid81_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOpPostXor_uid82_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOpPostXor_uid82_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracAddResult_uid83_block_rsrvd_fix_a : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid83_block_rsrvd_fix_b : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid83_block_rsrvd_fix_o : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid83_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_in : STD_LOGIC_VECTOR (55 downto 0);
    signal rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal fracGRS_uid85_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal cAmA_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal aMinusA_uid88_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracPostNorm_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal oneCST_uid91_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal expInc_uid92_block_rsrvd_fix_a : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid92_block_rsrvd_fix_b : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid92_block_rsrvd_fix_o : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid92_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal expPostNorm_uid93_block_rsrvd_fix_a : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid93_block_rsrvd_fix_b : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid93_block_rsrvd_fix_o : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid93_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal Sticky0_uid94_block_rsrvd_fix_in : STD_LOGIC_VECTOR (0 downto 0);
    signal Sticky0_uid94_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Sticky1_uid95_block_rsrvd_fix_in : STD_LOGIC_VECTOR (1 downto 0);
    signal Sticky1_uid95_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Round_uid96_block_rsrvd_fix_in : STD_LOGIC_VECTOR (2 downto 0);
    signal Round_uid96_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Guard_uid97_block_rsrvd_fix_in : STD_LOGIC_VECTOR (3 downto 0);
    signal Guard_uid97_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal LSB_uid98_block_rsrvd_fix_in : STD_LOGIC_VECTOR (4 downto 0);
    signal LSB_uid98_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal rndBitCond_uid99_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal cRBit_uid100_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal rBi_uid101_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal rBi_uid101_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal roundBit_uid102_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracPostNormRndRange_uid103_block_rsrvd_fix_in : STD_LOGIC_VECTOR (54 downto 0);
    signal fracPostNormRndRange_uid103_block_rsrvd_fix_b : STD_LOGIC_VECTOR (52 downto 0);
    signal expFracR_uid104_block_rsrvd_fix_q : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExpFrac_uid105_block_rsrvd_fix_a : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid105_block_rsrvd_fix_b : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid105_block_rsrvd_fix_o : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid105_block_rsrvd_fix_q : STD_LOGIC_VECTOR (66 downto 0);
    signal wEP2AllOwE_uid106_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal rndExp_uid107_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExp_uid107_block_rsrvd_fix_b : STD_LOGIC_VECTOR (12 downto 0);
    signal rOvfEQMax_uid108_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rndExpFracOvfBits_uid110_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExpFracOvfBits_uid110_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rOvfExtraBits_uid111_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rOvf_uid112_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal wEP2AllZ_uid113_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal rUdfEQMin_uid114_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rUdfExtraBit_uid115_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rUdfExtraBit_uid115_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal rUdf_uid116_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracRPreExc_uid117_block_rsrvd_fix_in : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPreExc_uid117_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPreExc_uid118_block_rsrvd_fix_in : STD_LOGIC_VECTOR (63 downto 0);
    signal expRPreExc_uid118_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal regInputs_uid119_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal regInputs_uid119_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRZeroVInC_uid120_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal excRZero_uid121_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rInfOvf_uid122_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRInfVInC_uid123_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal excRInf_uid124_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN2_uid125_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excAIBISub_uid126_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN_uid127_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal concExc_uid128_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal excREnc_uid129_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal invAMinusA_uid130_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRReg_uid131_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigBBInf_uid132_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigAAInf_uid133_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInf_uid134_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excAZBZSigASigB_uid135_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excBZARSigA_uid136_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRZero_uid137_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInfRZRReg_uid138_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInfRZRReg_uid138_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExcRNaN_uid139_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRPostExc_uid140_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal signRPostExc_uid140_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal oneFracRPostExc2_uid141_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal fracRPostExc_uid144_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostExc_uid144_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPostExc_uid148_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal expRPostExc_uid148_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal R_uid149_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal zs_uid151_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix_b : STD_LOGIC_VECTOR (31 downto 0);
    signal vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal mO_uid154_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (6 downto 0);
    signal vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_in : STD_LOGIC_VECTOR (24 downto 0);
    signal vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b : STD_LOGIC_VECTOR (24 downto 0);
    signal cStage_uid156_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal zs_uid159_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (15 downto 0);
    signal vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (15 downto 0);
    signal zs_uid165_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (7 downto 0);
    signal vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (7 downto 0);
    signal zs_uid171_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (3 downto 0);
    signal vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (3 downto 0);
    signal zs_uid177_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal vCount_uid185_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal r_uid186_lzCountVal_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal wIntCst_uid190_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (6 downto 0);
    signal shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_a : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_o : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_n : STD_LOGIC_VECTOR (0 downto 0);
    signal rightShiftStage0Idx1Rng1_uid192_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (105 downto 0);
    signal rightShiftStage0Idx1_uid194_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage0Idx2Rng2_uid195_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (104 downto 0);
    signal rightShiftStage0Idx2_uid197_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage0Idx3Rng3_uid198_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (103 downto 0);
    signal rightShiftStage0Idx3Pad3_uid199_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal rightShiftStage0Idx3_uid200_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_in : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx1Rng4_uid203_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (102 downto 0);
    signal rightShiftStage1Idx1_uid205_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx2Rng8_uid206_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (98 downto 0);
    signal rightShiftStage1Idx2_uid208_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx3Rng12_uid209_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (94 downto 0);
    signal rightShiftStage1Idx3Pad12_uid210_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal rightShiftStage1Idx3_uid211_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_in : STD_LOGIC_VECTOR (3 downto 0);
    signal rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx1Rng16_uid214_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (90 downto 0);
    signal rightShiftStage2Idx1_uid216_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx2Rng32_uid217_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (74 downto 0);
    signal rightShiftStage2Idx2_uid219_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx3Rng48_uid220_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (58 downto 0);
    signal rightShiftStage2Idx3Pad48_uid221_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (47 downto 0);
    signal rightShiftStage2Idx3_uid222_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_in : STD_LOGIC_VECTOR (5 downto 0);
    signal rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage3Idx1Rng64_uid225_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (42 downto 0);
    signal rightShiftStage3Idx1Pad64_uid226_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal rightShiftStage3Idx1_uid227_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_in : STD_LOGIC_VECTOR (6 downto 0);
    signal rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal zeroOutCst_uid230_alignmentShifter_uid65_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (40 downto 0);
    signal leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (40 downto 0);
    signal leftShiftStage0Idx1_uid237_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0Idx2_uid240_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (8 downto 0);
    signal leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (8 downto 0);
    signal leftShiftStage0Idx3_uid243_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (52 downto 0);
    signal leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (52 downto 0);
    signal leftShiftStage1Idx1_uid248_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (48 downto 0);
    signal leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (48 downto 0);
    signal leftShiftStage1Idx2_uid251_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (44 downto 0);
    signal leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (44 downto 0);
    signal leftShiftStage1Idx3_uid254_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (55 downto 0);
    signal leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal leftShiftStage2Idx1_uid259_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (54 downto 0);
    signal leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (54 downto 0);
    signal leftShiftStage2Idx2_uid262_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_in : STD_LOGIC_VECTOR (53 downto 0);
    signal leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_b : STD_LOGIC_VECTOR (53 downto 0);
    signal leftShiftStage2Idx3_uid265_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal stickyBits_uid70_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (51 downto 0);
    signal stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (54 downto 0);
    signal rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (15 downto 0);
    signal rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (15 downto 0);
    signal rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (7 downto 0);
    signal rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (7 downto 0);
    signal rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (3 downto 0);
    signal rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (3 downto 0);
    signal rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_d : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage3_uid229_alignmentShifter_uid65_block_rsrvd_fixinvSel_q : STD_LOGIC_VECTOR (0 downto 0);
    signal mergedMUXes0_opt_q : STD_LOGIC_VECTOR (106 downto 0);
    signal redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1_q : STD_LOGIC_VECTOR (15 downto 0);
    signal redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1_q : STD_LOGIC_VECTOR (15 downto 0);
    signal redist2_stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c_1_q : STD_LOGIC_VECTOR (54 downto 0);
    signal redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist4_rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (1 downto 0);
    signal redist5_rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist6_vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist7_vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_q : STD_LOGIC_VECTOR (24 downto 0);
    signal redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_0 : STD_LOGIC_VECTOR (24 downto 0);
    signal redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_1 : STD_LOGIC_VECTOR (24 downto 0);
    signal redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist12_signRInfRZRReg_uid138_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist13_excRNaN_uid127_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist14_regInputs_uid119_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist15_expRPreExc_uid118_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist17_expFracR_uid104_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (65 downto 0);
    signal redist18_aMinusA_uid88_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist18_aMinusA_uid88_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (56 downto 0);
    signal redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (56 downto 0);
    signal redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_1 : STD_LOGIC_VECTOR (56 downto 0);
    signal redist20_rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (55 downto 0);
    signal redist21_effSub_uid53_block_rsrvd_fix_q_6_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigB_uid52_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigB_uid52_block_rsrvd_fix_b_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist24_sigA_uid51_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist25_sigA_uid51_block_rsrvd_fix_b_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist26_InvExpXIsZero_uid45_block_rsrvd_fix_q_7_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist27_excN_bSig_uid43_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist30_expXIsMax_uid39_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist34_excN_aSig_uid29_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (51 downto 0);
    signal redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (51 downto 0);
    signal redist40_sigY_uid12_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist41_expY_uid11_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist42_fracY_uid10_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist43_in_0_in_0_1_q : STD_LOGIC_VECTOR (63 downto 0);
    signal redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_reset0 : std_logic;
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ia : STD_LOGIC_VECTOR (10 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_aa : STD_LOGIC_VECTOR (2 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ab : STD_LOGIC_VECTOR (2 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_iq : STD_LOGIC_VECTOR (10 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_q : STD_LOGIC_VECTOR (2 downto 0);
    -- Initial-value here is arbitrary, but a resolved value is necessary for simulation.
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_i : UNSIGNED (2 downto 0) := "111";
    attribute preserve_syn_only : boolean;
    attribute preserve_syn_only of redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_i : signal is true;
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_offset_q : STD_LOGIC_VECTOR (2 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_a : STD_LOGIC_VECTOR (3 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_b : STD_LOGIC_VECTOR (3 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_o : STD_LOGIC_VECTOR (3 downto 0);
    signal redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_q : STD_LOGIC_VECTOR (3 downto 0);

begin


    -- cAmA_uid87_block_rsrvd_fix(CONSTANT,86)
    cAmA_uid87_block_rsrvd_fix_q <= "111001";

    -- zs_uid151_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,150)
    zs_uid151_lzCountVal_uid86_block_rsrvd_fix_q <= "00000000000000000000000000000000";

    -- sigY_uid12_block_rsrvd_fix(BITSELECT,11)@0
    sigY_uid12_block_rsrvd_fix_b <= in_1(63 downto 63);

    -- redist40_sigY_uid12_block_rsrvd_fix_b_1(DELAY,317)
    redist40_sigY_uid12_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist40_sigY_uid12_block_rsrvd_fix_b_1_q <= sigY_uid12_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- expY_uid11_block_rsrvd_fix(BITSELECT,10)@0
    expY_uid11_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_1(62 downto 52));

    -- redist41_expY_uid11_block_rsrvd_fix_b_1(DELAY,318)
    redist41_expY_uid11_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist41_expY_uid11_block_rsrvd_fix_b_1_q <= expY_uid11_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- fracY_uid10_block_rsrvd_fix(BITSELECT,9)@0
    fracY_uid10_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_1(51 downto 0));

    -- redist42_fracY_uid10_block_rsrvd_fix_b_1(DELAY,319)
    redist42_fracY_uid10_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist42_fracY_uid10_block_rsrvd_fix_b_1_q <= fracY_uid10_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- ypn_uid13_block_rsrvd_fix(BITJOIN,12)@1
    ypn_uid13_block_rsrvd_fix_q <= redist40_sigY_uid12_block_rsrvd_fix_b_1_q & redist41_expY_uid11_block_rsrvd_fix_b_1_q & redist42_fracY_uid10_block_rsrvd_fix_b_1_q;

    -- redist43_in_0_in_0_1(DELAY,320)
    redist43_in_0_in_0_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist43_in_0_in_0_1_q <= in_0;
        END IF;
    END PROCESS;

    -- GND(CONSTANT,0)
    GND_q <= "0";

    -- expFracY_uid8_block_rsrvd_fix(BITSELECT,7)@0
    expFracY_uid8_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_1(62 downto 0));

    -- expFracX_uid7_block_rsrvd_fix(BITSELECT,6)@0
    expFracX_uid7_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_0(62 downto 0));

    -- xGTEy_uid9_block_rsrvd_fix(COMPARE,8)@0 + 1
    xGTEy_uid9_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("00" & expFracX_uid7_block_rsrvd_fix_b);
    xGTEy_uid9_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("00" & expFracY_uid8_block_rsrvd_fix_b);
    xGTEy_uid9_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            xGTEy_uid9_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(xGTEy_uid9_block_rsrvd_fix_a) - UNSIGNED(xGTEy_uid9_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    xGTEy_uid9_block_rsrvd_fix_n(0) <= not (xGTEy_uid9_block_rsrvd_fix_o(64));

    -- bSig_uid18_block_rsrvd_fix(MUX,17)@1
    bSig_uid18_block_rsrvd_fix_s <= xGTEy_uid9_block_rsrvd_fix_n;
    bSig_uid18_block_rsrvd_fix_combproc: PROCESS (bSig_uid18_block_rsrvd_fix_s, redist43_in_0_in_0_1_q, ypn_uid13_block_rsrvd_fix_q)
    BEGIN
        CASE (bSig_uid18_block_rsrvd_fix_s) IS
            WHEN "0" => bSig_uid18_block_rsrvd_fix_q <= redist43_in_0_in_0_1_q;
            WHEN "1" => bSig_uid18_block_rsrvd_fix_q <= ypn_uid13_block_rsrvd_fix_q;
            WHEN OTHERS => bSig_uid18_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- sigB_uid52_block_rsrvd_fix(BITSELECT,51)@1
    sigB_uid52_block_rsrvd_fix_b <= bSig_uid18_block_rsrvd_fix_q(63 downto 63);

    -- redist22_sigB_uid52_block_rsrvd_fix_b_4(DELAY,299)
    redist22_sigB_uid52_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(sigB_uid52_block_rsrvd_fix_b);
            redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_1 <= redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_0;
            redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_2 <= redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_1;
            redist22_sigB_uid52_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist22_sigB_uid52_block_rsrvd_fix_b_4_delay_2);
        END IF;
    END PROCESS;

    -- aSig_uid17_block_rsrvd_fix(MUX,16)@1
    aSig_uid17_block_rsrvd_fix_s <= xGTEy_uid9_block_rsrvd_fix_n;
    aSig_uid17_block_rsrvd_fix_combproc: PROCESS (aSig_uid17_block_rsrvd_fix_s, ypn_uid13_block_rsrvd_fix_q, redist43_in_0_in_0_1_q)
    BEGIN
        CASE (aSig_uid17_block_rsrvd_fix_s) IS
            WHEN "0" => aSig_uid17_block_rsrvd_fix_q <= ypn_uid13_block_rsrvd_fix_q;
            WHEN "1" => aSig_uid17_block_rsrvd_fix_q <= redist43_in_0_in_0_1_q;
            WHEN OTHERS => aSig_uid17_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- sigA_uid51_block_rsrvd_fix(BITSELECT,50)@1
    sigA_uid51_block_rsrvd_fix_b <= aSig_uid17_block_rsrvd_fix_q(63 downto 63);

    -- redist24_sigA_uid51_block_rsrvd_fix_b_4(DELAY,301)
    redist24_sigA_uid51_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(sigA_uid51_block_rsrvd_fix_b);
            redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_1 <= redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_0;
            redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_2 <= redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_1;
            redist24_sigA_uid51_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist24_sigA_uid51_block_rsrvd_fix_b_4_delay_2);
        END IF;
    END PROCESS;

    -- effSub_uid53_block_rsrvd_fix(LOGICAL,52)@5
    effSub_uid53_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist24_sigA_uid51_block_rsrvd_fix_b_4_q xor redist22_sigB_uid52_block_rsrvd_fix_b_4_q);

    -- exp_bSig_uid36_block_rsrvd_fix(BITSELECT,35)@1
    exp_bSig_uid36_block_rsrvd_fix_in <= bSig_uid18_block_rsrvd_fix_q(62 downto 0);
    exp_bSig_uid36_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(exp_bSig_uid36_block_rsrvd_fix_in(62 downto 52));

    -- exp_aSig_uid22_block_rsrvd_fix(BITSELECT,21)@1
    exp_aSig_uid22_block_rsrvd_fix_in <= aSig_uid17_block_rsrvd_fix_q(62 downto 0);
    exp_aSig_uid22_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(exp_aSig_uid22_block_rsrvd_fix_in(62 downto 52));

    -- expAmExpB_uid61_block_rsrvd_fix(SUB,60)@1 + 1
    expAmExpB_uid61_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & exp_aSig_uid22_block_rsrvd_fix_b));
    expAmExpB_uid61_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & exp_bSig_uid36_block_rsrvd_fix_b));
    expAmExpB_uid61_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expAmExpB_uid61_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expAmExpB_uid61_block_rsrvd_fix_a) - SIGNED(expAmExpB_uid61_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expAmExpB_uid61_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expAmExpB_uid61_block_rsrvd_fix_o(11 downto 0));

    -- cWFP2_uid62_block_rsrvd_fix(CONSTANT,61)
    cWFP2_uid62_block_rsrvd_fix_q <= "110110";

    -- shiftedOut_uid64_block_rsrvd_fix(COMPARE,63)@2 + 1
    shiftedOut_uid64_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("00000000" & cWFP2_uid62_block_rsrvd_fix_q);
    shiftedOut_uid64_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("00" & expAmExpB_uid61_block_rsrvd_fix_q);
    shiftedOut_uid64_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            shiftedOut_uid64_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(shiftedOut_uid64_block_rsrvd_fix_a) - UNSIGNED(shiftedOut_uid64_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    shiftedOut_uid64_block_rsrvd_fix_c(0) <= shiftedOut_uid64_block_rsrvd_fix_o(13);

    -- iShiftedOut_uid68_block_rsrvd_fix(LOGICAL,67)@3
    iShiftedOut_uid68_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (shiftedOut_uid64_block_rsrvd_fix_c));

    -- rightShiftStage2Idx3Pad48_uid221_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,220)
    rightShiftStage2Idx3Pad48_uid221_alignmentShifter_uid65_block_rsrvd_fix_q <= "000000000000000000000000000000000000000000000000";

    -- rightShiftStage2Idx3Rng48_uid220_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,219)@3
    rightShiftStage2Idx3Rng48_uid220_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 48));

    -- rightShiftStage2Idx3_uid222_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,221)@3
    rightShiftStage2Idx3_uid222_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage2Idx3Pad48_uid221_alignmentShifter_uid65_block_rsrvd_fix_q & rightShiftStage2Idx3Rng48_uid220_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- rightShiftStage2Idx2Rng32_uid217_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,216)@3
    rightShiftStage2Idx2Rng32_uid217_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 32));

    -- rightShiftStage2Idx2_uid219_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,218)@3
    rightShiftStage2Idx2_uid219_alignmentShifter_uid65_block_rsrvd_fix_q <= zs_uid151_lzCountVal_uid86_block_rsrvd_fix_q & rightShiftStage2Idx2Rng32_uid217_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- zs_uid159_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,158)
    zs_uid159_lzCountVal_uid86_block_rsrvd_fix_q <= "0000000000000000";

    -- rightShiftStage2Idx1Rng16_uid214_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,213)@3
    rightShiftStage2Idx1Rng16_uid214_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 16));

    -- rightShiftStage2Idx1_uid216_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,215)@3
    rightShiftStage2Idx1_uid216_alignmentShifter_uid65_block_rsrvd_fix_q <= zs_uid159_lzCountVal_uid86_block_rsrvd_fix_q & rightShiftStage2Idx1Rng16_uid214_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- rightShiftStage1Idx3Pad12_uid210_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,209)
    rightShiftStage1Idx3Pad12_uid210_alignmentShifter_uid65_block_rsrvd_fix_q <= "000000000000";

    -- rightShiftStage1Idx3Rng12_uid209_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,208)@2
    rightShiftStage1Idx3Rng12_uid209_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 12));

    -- rightShiftStage1Idx3_uid211_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,210)@2
    rightShiftStage1Idx3_uid211_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage1Idx3Pad12_uid210_alignmentShifter_uid65_block_rsrvd_fix_q & rightShiftStage1Idx3Rng12_uid209_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- zs_uid165_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,164)
    zs_uid165_lzCountVal_uid86_block_rsrvd_fix_q <= "00000000";

    -- rightShiftStage1Idx2Rng8_uid206_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,205)@2
    rightShiftStage1Idx2Rng8_uid206_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 8));

    -- rightShiftStage1Idx2_uid208_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,207)@2
    rightShiftStage1Idx2_uid208_alignmentShifter_uid65_block_rsrvd_fix_q <= zs_uid165_lzCountVal_uid86_block_rsrvd_fix_q & rightShiftStage1Idx2Rng8_uid206_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- zs_uid171_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,170)
    zs_uid171_lzCountVal_uid86_block_rsrvd_fix_q <= "0000";

    -- rightShiftStage1Idx1Rng4_uid203_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,202)@2
    rightShiftStage1Idx1Rng4_uid203_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 4));

    -- rightShiftStage1Idx1_uid205_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,204)@2
    rightShiftStage1Idx1_uid205_alignmentShifter_uid65_block_rsrvd_fix_q <= zs_uid171_lzCountVal_uid86_block_rsrvd_fix_q & rightShiftStage1Idx1Rng4_uid203_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- rightShiftStage0Idx3Pad3_uid199_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,198)
    rightShiftStage0Idx3Pad3_uid199_alignmentShifter_uid65_block_rsrvd_fix_q <= "000";

    -- rightShiftStage0Idx3Rng3_uid198_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,197)@2
    rightShiftStage0Idx3Rng3_uid198_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid66_block_rsrvd_fix_q(106 downto 3));

    -- rightShiftStage0Idx3_uid200_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,199)@2
    rightShiftStage0Idx3_uid200_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage0Idx3Pad3_uid199_alignmentShifter_uid65_block_rsrvd_fix_q & rightShiftStage0Idx3Rng3_uid198_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- zs_uid177_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,176)
    zs_uid177_lzCountVal_uid86_block_rsrvd_fix_q <= "00";

    -- rightShiftStage0Idx2Rng2_uid195_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,194)@2
    rightShiftStage0Idx2Rng2_uid195_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid66_block_rsrvd_fix_q(106 downto 2));

    -- rightShiftStage0Idx2_uid197_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,196)@2
    rightShiftStage0Idx2_uid197_alignmentShifter_uid65_block_rsrvd_fix_q <= zs_uid177_lzCountVal_uid86_block_rsrvd_fix_q & rightShiftStage0Idx2Rng2_uid195_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- rightShiftStage0Idx1Rng1_uid192_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,191)@2
    rightShiftStage0Idx1Rng1_uid192_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid66_block_rsrvd_fix_q(106 downto 1));

    -- rightShiftStage0Idx1_uid194_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,193)@2
    rightShiftStage0Idx1_uid194_alignmentShifter_uid65_block_rsrvd_fix_q <= GND_q & rightShiftStage0Idx1Rng1_uid192_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- cstAllZWE_uid21_block_rsrvd_fix(CONSTANT,20)
    cstAllZWE_uid21_block_rsrvd_fix_q <= "00000000000";

    -- excZ_bSig_uid18_uid38_block_rsrvd_fix(LOGICAL,37)@1
    excZ_bSig_uid18_uid38_block_rsrvd_fix_q <= "1" WHEN exp_bSig_uid36_block_rsrvd_fix_b = cstAllZWE_uid21_block_rsrvd_fix_q ELSE "0";

    -- redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1(DELAY,308)
    redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1_q <= excZ_bSig_uid18_uid38_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- InvExpXIsZero_uid45_block_rsrvd_fix(LOGICAL,44)@2
    InvExpXIsZero_uid45_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1_q));

    -- cstZeroWF_uid20_block_rsrvd_fix(CONSTANT,19)
    cstZeroWF_uid20_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000000";

    -- frac_bSig_uid37_block_rsrvd_fix(BITSELECT,36)@1
    frac_bSig_uid37_block_rsrvd_fix_in <= bSig_uid18_block_rsrvd_fix_q(51 downto 0);
    frac_bSig_uid37_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(frac_bSig_uid37_block_rsrvd_fix_in(51 downto 0));

    -- fracBz_uid57_block_rsrvd_fix(MUX,56)@1 + 1
    fracBz_uid57_block_rsrvd_fix_s <= excZ_bSig_uid18_uid38_block_rsrvd_fix_q;
    fracBz_uid57_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (fracBz_uid57_block_rsrvd_fix_s) IS
                WHEN "0" => fracBz_uid57_block_rsrvd_fix_q <= frac_bSig_uid37_block_rsrvd_fix_b;
                WHEN "1" => fracBz_uid57_block_rsrvd_fix_q <= cstZeroWF_uid20_block_rsrvd_fix_q;
                WHEN OTHERS => fracBz_uid57_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- oFracB_uid60_block_rsrvd_fix(BITJOIN,59)@2
    oFracB_uid60_block_rsrvd_fix_q <= InvExpXIsZero_uid45_block_rsrvd_fix_q & fracBz_uid57_block_rsrvd_fix_q;

    -- padConst_uid65_block_rsrvd_fix(CONSTANT,64)
    padConst_uid65_block_rsrvd_fix_q <= "000000000000000000000000000000000000000000000000000000";

    -- rightPaddedIn_uid66_block_rsrvd_fix(BITJOIN,65)@2
    rightPaddedIn_uid66_block_rsrvd_fix_q <= oFracB_uid60_block_rsrvd_fix_q & padConst_uid65_block_rsrvd_fix_q;

    -- rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,200)@2
    rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_in <= expAmExpB_uid61_block_rsrvd_fix_q(1 downto 0);
    rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_in(1 downto 0));

    -- rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix(MUX,201)@2
    rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_s <= rightShiftStageSel0Dto0_uid201_alignmentShifter_uid65_block_rsrvd_fix_b;
    rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_combproc: PROCESS (rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_s, rightPaddedIn_uid66_block_rsrvd_fix_q, rightShiftStage0Idx1_uid194_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage0Idx2_uid197_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage0Idx3_uid200_alignmentShifter_uid65_block_rsrvd_fix_q)
    BEGIN
        CASE (rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_s) IS
            WHEN "00" => rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q <= rightPaddedIn_uid66_block_rsrvd_fix_q;
            WHEN "01" => rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage0Idx1_uid194_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN "10" => rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage0Idx2_uid197_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN "11" => rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage0Idx3_uid200_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN OTHERS => rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,211)@2
    rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_in <= expAmExpB_uid61_block_rsrvd_fix_q(3 downto 0);
    rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_in(3 downto 2));

    -- rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix(MUX,212)@2 + 1
    rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_s <= rightShiftStageSel2Dto2_uid212_alignmentShifter_uid65_block_rsrvd_fix_b;
    rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_s) IS
                WHEN "00" => rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage0_uid202_alignmentShifter_uid65_block_rsrvd_fix_q;
                WHEN "01" => rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage1Idx1_uid205_alignmentShifter_uid65_block_rsrvd_fix_q;
                WHEN "10" => rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage1Idx2_uid208_alignmentShifter_uid65_block_rsrvd_fix_q;
                WHEN "11" => rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage1Idx3_uid211_alignmentShifter_uid65_block_rsrvd_fix_q;
                WHEN OTHERS => rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,222)@2
    rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_in <= expAmExpB_uid61_block_rsrvd_fix_q(5 downto 0);
    rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_in(5 downto 4));

    -- redist4_rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b_1(DELAY,281)
    redist4_rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist4_rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b_1_q <= rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix(MUX,223)@3
    rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_s <= redist4_rightShiftStageSel4Dto4_uid223_alignmentShifter_uid65_block_rsrvd_fix_b_1_q;
    rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_combproc: PROCESS (rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_s, rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage2Idx1_uid216_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage2Idx2_uid219_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage2Idx3_uid222_alignmentShifter_uid65_block_rsrvd_fix_q)
    BEGIN
        CASE (rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_s) IS
            WHEN "00" => rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage1_uid213_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN "01" => rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage2Idx1_uid216_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN "10" => rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage2Idx2_uid219_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN "11" => rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage2Idx3_uid222_alignmentShifter_uid65_block_rsrvd_fix_q;
            WHEN OTHERS => rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rightShiftStage3_uid229_alignmentShifter_uid65_block_rsrvd_fixinvSel(LOGICAL,274)@3
    rightShiftStage3_uid229_alignmentShifter_uid65_block_rsrvd_fixinvSel_q <= not (redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_q);

    -- rightShiftStage3Idx1Pad64_uid226_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,225)
    rightShiftStage3Idx1Pad64_uid226_alignmentShifter_uid65_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000000000000000000";

    -- rightShiftStage3Idx1Rng64_uid225_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,224)@3
    rightShiftStage3Idx1Rng64_uid225_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q(106 downto 64));

    -- rightShiftStage3Idx1_uid227_alignmentShifter_uid65_block_rsrvd_fix(BITJOIN,226)@3
    rightShiftStage3Idx1_uid227_alignmentShifter_uid65_block_rsrvd_fix_q <= rightShiftStage3Idx1Pad64_uid226_alignmentShifter_uid65_block_rsrvd_fix_q & rightShiftStage3Idx1Rng64_uid225_alignmentShifter_uid65_block_rsrvd_fix_b;

    -- rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix(BITSELECT,227)@2
    rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_in <= expAmExpB_uid61_block_rsrvd_fix_q(6 downto 0);
    rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_in(6 downto 6));

    -- redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1(DELAY,280)
    redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_q <= rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- zeroOutCst_uid230_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,229)
    zeroOutCst_uid230_alignmentShifter_uid65_block_rsrvd_fix_q <= "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    -- wIntCst_uid190_alignmentShifter_uid65_block_rsrvd_fix(CONSTANT,189)
    wIntCst_uid190_alignmentShifter_uid65_block_rsrvd_fix_q <= "1101011";

    -- shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix(COMPARE,190)@2 + 1
    shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("00" & expAmExpB_uid61_block_rsrvd_fix_q);
    shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0000000" & wIntCst_uid190_alignmentShifter_uid65_block_rsrvd_fix_q);
    shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_a) - UNSIGNED(shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_n(0) <= not (shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_o(13));

    -- mergedMUXes0_opt(SELECTOR,276)@3
    mergedMUXes0_opt_combproc: PROCESS (shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_n, zeroOutCst_uid230_alignmentShifter_uid65_block_rsrvd_fix_q, redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_q, rightShiftStage3Idx1_uid227_alignmentShifter_uid65_block_rsrvd_fix_q, rightShiftStage3_uid229_alignmentShifter_uid65_block_rsrvd_fixinvSel_q, rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q, GND_q)
    BEGIN
        mergedMUXes0_opt_q <= STD_LOGIC_VECTOR((106 downto 1 => GND_q(0)) & GND_q);
        IF (rightShiftStage3_uid229_alignmentShifter_uid65_block_rsrvd_fixinvSel_q = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(rightShiftStage2_uid224_alignmentShifter_uid65_block_rsrvd_fix_q);
        END IF;
        IF (redist3_rightShiftStageSel6Dto6_uid228_alignmentShifter_uid65_block_rsrvd_fix_b_1_q = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(rightShiftStage3Idx1_uid227_alignmentShifter_uid65_block_rsrvd_fix_q);
        END IF;
        IF (shiftedOut_uid191_alignmentShifter_uid65_block_rsrvd_fix_n = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(zeroOutCst_uid230_alignmentShifter_uid65_block_rsrvd_fix_q);
        END IF;
    END PROCESS;

    -- alignFracBPostShiftOut_uid69_block_rsrvd_fix(LOGICAL,68)@3 + 1
    alignFracBPostShiftOut_uid69_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((106 downto 1 => iShiftedOut_uid68_block_rsrvd_fix_q(0)) & iShiftedOut_uid68_block_rsrvd_fix_q));
    alignFracBPostShiftOut_uid69_block_rsrvd_fix_qi <= mergedMUXes0_opt_q and alignFracBPostShiftOut_uid69_block_rsrvd_fix_b;
    alignFracBPostShiftOut_uid69_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 107, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => alignFracBPostShiftOut_uid69_block_rsrvd_fix_qi, xout => alignFracBPostShiftOut_uid69_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- stickyBits_uid70_block_rsrvd_fix_bit_select_merged(BITSELECT,268)@4
    stickyBits_uid70_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(alignFracBPostShiftOut_uid69_block_rsrvd_fix_q(51 downto 0));
    stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(alignFracBPostShiftOut_uid69_block_rsrvd_fix_q(106 downto 52));

    -- redist2_stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c_1(DELAY,279)
    redist2_stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist2_stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c_1_q <= stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c;
        END IF;
    END PROCESS;

    -- fracBAddOp_uid81_block_rsrvd_fix(BITJOIN,80)@5
    fracBAddOp_uid81_block_rsrvd_fix_q <= GND_q & redist2_stickyBits_uid70_block_rsrvd_fix_bit_select_merged_c_1_q;

    -- fracBAddOpPostXor_uid82_block_rsrvd_fix(LOGICAL,81)@5
    fracBAddOpPostXor_uid82_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((55 downto 1 => effSub_uid53_block_rsrvd_fix_q(0)) & effSub_uid53_block_rsrvd_fix_q));
    fracBAddOpPostXor_uid82_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(fracBAddOp_uid81_block_rsrvd_fix_q xor fracBAddOpPostXor_uid82_block_rsrvd_fix_b);

    -- zocst_uid77_block_rsrvd_fix(CONSTANT,76)
    zocst_uid77_block_rsrvd_fix_q <= "01";

    -- frac_aSig_uid23_block_rsrvd_fix(BITSELECT,22)@1
    frac_aSig_uid23_block_rsrvd_fix_in <= aSig_uid17_block_rsrvd_fix_q(51 downto 0);
    frac_aSig_uid23_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(frac_aSig_uid23_block_rsrvd_fix_in(51 downto 0));

    -- redist38_frac_aSig_uid23_block_rsrvd_fix_b_4(DELAY,315)
    redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(frac_aSig_uid23_block_rsrvd_fix_b);
            redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_1 <= redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_0;
            redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_delay_1);
        END IF;
    END PROCESS;

    -- redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0(DELAY,321)
    redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0_q <= redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_q;
        END IF;
    END PROCESS;

    -- cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix(LOGICAL,71)@4 + 1
    cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_qi <= "1" WHEN stickyBits_uid70_block_rsrvd_fix_bit_select_merged_b = cstZeroWF_uid20_block_rsrvd_fix_q ELSE "0";
    cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_qi, xout => cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- effSubInvSticky_uid75_block_rsrvd_fix(LOGICAL,74)@5
    effSubInvSticky_uid75_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(effSub_uid53_block_rsrvd_fix_q and cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_q);

    -- fracAAddOp_uid78_block_rsrvd_fix(BITJOIN,77)@5
    fracAAddOp_uid78_block_rsrvd_fix_q <= zocst_uid77_block_rsrvd_fix_q & redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0_q & GND_q & effSubInvSticky_uid75_block_rsrvd_fix_q;

    -- fracAddResult_uid83_block_rsrvd_fix(ADD,82)@5
    fracAddResult_uid83_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & fracAAddOp_uid78_block_rsrvd_fix_q);
    fracAddResult_uid83_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0" & fracBAddOpPostXor_uid82_block_rsrvd_fix_q);
    fracAddResult_uid83_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(fracAddResult_uid83_block_rsrvd_fix_a) + UNSIGNED(fracAddResult_uid83_block_rsrvd_fix_b));
    fracAddResult_uid83_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(fracAddResult_uid83_block_rsrvd_fix_o(56 downto 0));

    -- rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix(BITSELECT,83)@5
    rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_in <= fracAddResult_uid83_block_rsrvd_fix_q(55 downto 0);
    rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_in(55 downto 0));

    -- redist20_rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b_1(DELAY,297)
    redist20_rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist20_rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b_1_q <= rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix(LOGICAL,72)@5 + 1
    invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi <= not (cmpEQ_stickyBits_cZwF_uid72_block_rsrvd_fix_q);
    invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi, xout => invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- fracGRS_uid85_block_rsrvd_fix(BITJOIN,84)@6
    fracGRS_uid85_block_rsrvd_fix_q <= redist20_rangeFracAddResultMwfp3Dto0_uid84_block_rsrvd_fix_b_1_q & invCmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q;

    -- rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix(BITSELECT,151)@6
    rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracGRS_uid85_block_rsrvd_fix_q(56 downto 25));

    -- vCount_uid153_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,152)@6
    vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q <= "1" WHEN rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix_b = zs_uid151_lzCountVal_uid86_block_rsrvd_fix_q ELSE "0";

    -- redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3(DELAY,288)
    redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q);
            redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_1 <= redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0;
            redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_1);
        END IF;
    END PROCESS;

    -- vStage_uid155_lzCountVal_uid86_block_rsrvd_fix(BITSELECT,154)@6
    vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_in <= fracGRS_uid85_block_rsrvd_fix_q(24 downto 0);
    vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_in(24 downto 0));

    -- mO_uid154_lzCountVal_uid86_block_rsrvd_fix(CONSTANT,153)
    mO_uid154_lzCountVal_uid86_block_rsrvd_fix_q <= "1111111";

    -- cStage_uid156_lzCountVal_uid86_block_rsrvd_fix(BITJOIN,155)@6
    cStage_uid156_lzCountVal_uid86_block_rsrvd_fix_q <= vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b & mO_uid154_lzCountVal_uid86_block_rsrvd_fix_q;

    -- vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix(MUX,157)@6
    vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_s <= vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q;
    vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_combproc: PROCESS (vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_s, rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix_b, cStage_uid156_lzCountVal_uid86_block_rsrvd_fix_q)
    BEGIN
        CASE (vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid152_lzCountVal_uid86_block_rsrvd_fix_b;
            WHEN "1" => vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q <= cStage_uid156_lzCountVal_uid86_block_rsrvd_fix_q;
            WHEN OTHERS => vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged(BITSELECT,269)@6
    rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q(31 downto 16));
    rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid158_lzCountVal_uid86_block_rsrvd_fix_q(15 downto 0));

    -- vCount_uid161_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,160)@6 + 1
    vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_qi <= "1" WHEN rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b = zs_uid159_lzCountVal_uid86_block_rsrvd_fix_q ELSE "0";
    vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_qi, xout => vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3(DELAY,286)
    redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q);
            redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_delay_0);
        END IF;
    END PROCESS;

    -- redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1(DELAY,278)
    redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1_q <= rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c;
        END IF;
    END PROCESS;

    -- redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1(DELAY,277)
    redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1_q <= rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b;
        END IF;
    END PROCESS;

    -- vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix(MUX,163)@7
    vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_s <= vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q;
    vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_combproc: PROCESS (vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_s, redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1_q, redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1_q)
    BEGIN
        CASE (vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q <= redist0_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b_1_q;
            WHEN "1" => vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q <= redist1_rVStage_uid160_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c_1_q;
            WHEN OTHERS => vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged(BITSELECT,270)@7
    rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q(15 downto 8));
    rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid164_lzCountVal_uid86_block_rsrvd_fix_q(7 downto 0));

    -- vCount_uid167_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,166)@7
    vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q <= "1" WHEN rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b = zs_uid165_lzCountVal_uid86_block_rsrvd_fix_q ELSE "0";

    -- redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2(DELAY,285)
    redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q);
            redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix(MUX,169)@7 + 1
    vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_s <= vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q;
    vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_s) IS
                WHEN "0" => vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b;
                WHEN "1" => vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid166_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c;
                WHEN OTHERS => vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged(BITSELECT,271)@8
    rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q(7 downto 4));
    rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid170_lzCountVal_uid86_block_rsrvd_fix_q(3 downto 0));

    -- vCount_uid173_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,172)@8
    vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q <= "1" WHEN rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b = zs_uid171_lzCountVal_uid86_block_rsrvd_fix_q ELSE "0";

    -- redist7_vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q_1(DELAY,284)
    redist7_vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist7_vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q_1_q <= vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix(MUX,175)@8
    vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_s <= vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q;
    vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_combproc: PROCESS (vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_s, rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b, rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c)
    BEGIN
        CASE (vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b;
            WHEN "1" => vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid172_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c;
            WHEN OTHERS => vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged(BITSELECT,272)@8
    rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q(3 downto 2));
    rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid176_lzCountVal_uid86_block_rsrvd_fix_q(1 downto 0));

    -- vCount_uid179_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,178)@8
    vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q <= "1" WHEN rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b = zs_uid177_lzCountVal_uid86_block_rsrvd_fix_q ELSE "0";

    -- redist6_vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q_1(DELAY,283)
    redist6_vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist6_vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q_1_q <= vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix(MUX,181)@8
    vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_s <= vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q;
    vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_combproc: PROCESS (vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_s, rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b, rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c)
    BEGIN
        CASE (vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_b;
            WHEN "1" => vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_q <= rVStage_uid178_lzCountVal_uid86_block_rsrvd_fix_bit_select_merged_c;
            WHEN OTHERS => vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix(BITSELECT,183)@8
    rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(vStagei_uid182_lzCountVal_uid86_block_rsrvd_fix_q(1 downto 1));

    -- redist5_rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b_1(DELAY,282)
    redist5_rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist5_rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b_1_q <= rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- vCount_uid185_lzCountVal_uid86_block_rsrvd_fix(LOGICAL,184)@9
    vCount_uid185_lzCountVal_uid86_block_rsrvd_fix_q <= "1" WHEN redist5_rVStage_uid184_lzCountVal_uid86_block_rsrvd_fix_b_1_q = GND_q ELSE "0";

    -- r_uid186_lzCountVal_uid86_block_rsrvd_fix(BITJOIN,185)@9
    r_uid186_lzCountVal_uid86_block_rsrvd_fix_q <= redist11_vCount_uid153_lzCountVal_uid86_block_rsrvd_fix_q_3_q & redist9_vCount_uid161_lzCountVal_uid86_block_rsrvd_fix_q_3_q & redist8_vCount_uid167_lzCountVal_uid86_block_rsrvd_fix_q_2_q & redist7_vCount_uid173_lzCountVal_uid86_block_rsrvd_fix_q_1_q & redist6_vCount_uid179_lzCountVal_uid86_block_rsrvd_fix_q_1_q & vCount_uid185_lzCountVal_uid86_block_rsrvd_fix_q;

    -- aMinusA_uid88_block_rsrvd_fix(LOGICAL,87)@9
    aMinusA_uid88_block_rsrvd_fix_q <= "1" WHEN r_uid186_lzCountVal_uid86_block_rsrvd_fix_q = cAmA_uid87_block_rsrvd_fix_q ELSE "0";

    -- invAMinusA_uid130_block_rsrvd_fix(LOGICAL,129)@9
    invAMinusA_uid130_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (aMinusA_uid88_block_rsrvd_fix_q));

    -- redist25_sigA_uid51_block_rsrvd_fix_b_8(DELAY,302)
    redist25_sigA_uid51_block_rsrvd_fix_b_8_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_0 <= STD_LOGIC_VECTOR(redist24_sigA_uid51_block_rsrvd_fix_b_4_q);
            redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_1 <= redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_0;
            redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_2 <= redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_1;
            redist25_sigA_uid51_block_rsrvd_fix_b_8_q <= STD_LOGIC_VECTOR(redist25_sigA_uid51_block_rsrvd_fix_b_8_delay_2);
        END IF;
    END PROCESS;

    -- cstAllOWE_uid19_block_rsrvd_fix(CONSTANT,18)
    cstAllOWE_uid19_block_rsrvd_fix_q <= "11111111111";

    -- expXIsMax_uid39_block_rsrvd_fix(LOGICAL,38)@1 + 1
    expXIsMax_uid39_block_rsrvd_fix_qi <= "1" WHEN exp_bSig_uid36_block_rsrvd_fix_b = cstAllOWE_uid19_block_rsrvd_fix_q ELSE "0";
    expXIsMax_uid39_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid39_block_rsrvd_fix_qi, xout => expXIsMax_uid39_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist30_expXIsMax_uid39_block_rsrvd_fix_q_8(DELAY,307)
    redist30_expXIsMax_uid39_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid39_block_rsrvd_fix_q, xout => redist30_expXIsMax_uid39_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- invExpXIsMax_uid44_block_rsrvd_fix(LOGICAL,43)@9
    invExpXIsMax_uid44_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist30_expXIsMax_uid39_block_rsrvd_fix_q_8_q));

    -- redist26_InvExpXIsZero_uid45_block_rsrvd_fix_q_7(DELAY,303)
    redist26_InvExpXIsZero_uid45_block_rsrvd_fix_q_7 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => InvExpXIsZero_uid45_block_rsrvd_fix_q, xout => redist26_InvExpXIsZero_uid45_block_rsrvd_fix_q_7_q, clk => clk, aclr => areset, ena => '1' );

    -- excR_bSig_uid46_block_rsrvd_fix(LOGICAL,45)@9
    excR_bSig_uid46_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist26_InvExpXIsZero_uid45_block_rsrvd_fix_q_7_q and invExpXIsMax_uid44_block_rsrvd_fix_q);

    -- redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_offset(CONSTANT,324)
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_offset_q <= "100";

    -- redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt(ADD,325)
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_a <= STD_LOGIC_VECTOR("0" & redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_q);
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_b <= STD_LOGIC_VECTOR("0" & redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_offset_q);
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_o <= STD_LOGIC_VECTOR(UNSIGNED(redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_a) + UNSIGNED(redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_b));
        END IF;
    END PROCESS;
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_q <= redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_o(3 downto 0);

    -- redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr(COUNTER,323)
    -- low=0, high=7, step=1, init=0
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_i <= redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_i + 1;
        END IF;
    END PROCESS;
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_q <= STD_LOGIC_VECTOR(RESIZE(redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_i, 3));

    -- redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem(DUALMEM,322)
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ia <= STD_LOGIC_VECTOR(exp_aSig_uid22_block_rsrvd_fix_b);
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_aa <= redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_wraddr_q;
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ab <= redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_rdcnt_q(2 downto 0);
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_dmem : altera_syncram
    GENERIC MAP (
        ram_block_type => "MLAB",
        operation_mode => "DUAL_PORT",
        width_a => 11,
        widthad_a => 3,
        numwords_a => 8,
        width_b => 11,
        widthad_b => 3,
        numwords_b => 8,
        lpm_type => "altera_syncram",
        width_byteena_a => 1,
        address_reg_b => "CLOCK0",
        indata_reg_b => "CLOCK0",
        rdcontrol_reg_b => "CLOCK0",
        byteena_reg_b => "CLOCK0",
        outdata_reg_b => "CLOCK0",
        outdata_sclr_b => "NONE",
        clock_enable_input_a => "NORMAL",
        clock_enable_input_b => "NORMAL",
        clock_enable_output_b => "NORMAL",
        read_during_write_mode_mixed_ports => "DONT_CARE",
        power_up_uninitialized => "TRUE",
        intended_device_family => "Agilex 7"
    )
    PORT MAP (
        clocken0 => '1',
        clock0 => clk,
        address_a => redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_aa,
        data_a => redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ia,
        wren_a => VCC_q(0),
        address_b => redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_ab,
        q_b => redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_iq
    );
    redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_q <= STD_LOGIC_VECTOR(redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_iq(10 downto 0));

    -- expXIsMax_uid25_block_rsrvd_fix(LOGICAL,24)@8 + 1
    expXIsMax_uid25_block_rsrvd_fix_qi <= "1" WHEN redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_q = cstAllOWE_uid19_block_rsrvd_fix_q ELSE "0";
    expXIsMax_uid25_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid25_block_rsrvd_fix_qi, xout => expXIsMax_uid25_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- invExpXIsMax_uid30_block_rsrvd_fix(LOGICAL,29)@9
    invExpXIsMax_uid30_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (expXIsMax_uid25_block_rsrvd_fix_q));

    -- excZ_aSig_uid17_uid24_block_rsrvd_fix(LOGICAL,23)@8 + 1
    excZ_aSig_uid17_uid24_block_rsrvd_fix_qi <= "1" WHEN redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_q = cstAllZWE_uid21_block_rsrvd_fix_q ELSE "0";
    excZ_aSig_uid17_uid24_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excZ_aSig_uid17_uid24_block_rsrvd_fix_qi, xout => excZ_aSig_uid17_uid24_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- InvExpXIsZero_uid31_block_rsrvd_fix(LOGICAL,30)@9
    InvExpXIsZero_uid31_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excZ_aSig_uid17_uid24_block_rsrvd_fix_q));

    -- excR_aSig_uid32_block_rsrvd_fix(LOGICAL,31)@9
    excR_aSig_uid32_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(InvExpXIsZero_uid31_block_rsrvd_fix_q and invExpXIsMax_uid30_block_rsrvd_fix_q);

    -- signRReg_uid131_block_rsrvd_fix(LOGICAL,130)@9
    signRReg_uid131_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excR_aSig_uid32_block_rsrvd_fix_q and excR_bSig_uid46_block_rsrvd_fix_q and redist25_sigA_uid51_block_rsrvd_fix_b_8_q and invAMinusA_uid130_block_rsrvd_fix_q);

    -- redist23_sigB_uid52_block_rsrvd_fix_b_8(DELAY,300)
    redist23_sigB_uid52_block_rsrvd_fix_b_8_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_0 <= STD_LOGIC_VECTOR(redist22_sigB_uid52_block_rsrvd_fix_b_4_q);
            redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_1 <= redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_0;
            redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_2 <= redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_1;
            redist23_sigB_uid52_block_rsrvd_fix_b_8_q <= STD_LOGIC_VECTOR(redist23_sigB_uid52_block_rsrvd_fix_b_8_delay_2);
        END IF;
    END PROCESS;

    -- redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8(DELAY,309)
    redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => redist31_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_1_q, xout => redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- excAZBZSigASigB_uid135_block_rsrvd_fix(LOGICAL,134)@9
    excAZBZSigASigB_uid135_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excZ_aSig_uid17_uid24_block_rsrvd_fix_q and redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8_q and redist25_sigA_uid51_block_rsrvd_fix_b_8_q and redist23_sigB_uid52_block_rsrvd_fix_b_8_q);

    -- excBZARSigA_uid136_block_rsrvd_fix(LOGICAL,135)@9
    excBZARSigA_uid136_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8_q and excR_aSig_uid32_block_rsrvd_fix_q and redist25_sigA_uid51_block_rsrvd_fix_b_8_q);

    -- signRZero_uid137_block_rsrvd_fix(LOGICAL,136)@9
    signRZero_uid137_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excBZARSigA_uid136_block_rsrvd_fix_q or excAZBZSigASigB_uid135_block_rsrvd_fix_q);

    -- fracXIsZero_uid40_block_rsrvd_fix(LOGICAL,39)@1 + 1
    fracXIsZero_uid40_block_rsrvd_fix_qi <= "1" WHEN cstZeroWF_uid20_block_rsrvd_fix_q = frac_bSig_uid37_block_rsrvd_fix_b ELSE "0";
    fracXIsZero_uid40_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid40_block_rsrvd_fix_qi, xout => fracXIsZero_uid40_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8(DELAY,306)
    redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid40_block_rsrvd_fix_q, xout => redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- excI_bSig_uid42_block_rsrvd_fix(LOGICAL,41)@9
    excI_bSig_uid42_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist30_expXIsMax_uid39_block_rsrvd_fix_q_8_q and redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8_q);

    -- sigBBInf_uid132_block_rsrvd_fix(LOGICAL,131)@9
    sigBBInf_uid132_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist23_sigB_uid52_block_rsrvd_fix_b_8_q and excI_bSig_uid42_block_rsrvd_fix_q);

    -- fracXIsZero_uid26_block_rsrvd_fix(LOGICAL,25)@5 + 1
    fracXIsZero_uid26_block_rsrvd_fix_qi <= "1" WHEN cstZeroWF_uid20_block_rsrvd_fix_q = redist38_frac_aSig_uid23_block_rsrvd_fix_b_4_outputreg0_q ELSE "0";
    fracXIsZero_uid26_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid26_block_rsrvd_fix_qi, xout => fracXIsZero_uid26_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4(DELAY,313)
    redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_0 <= STD_LOGIC_VECTOR(fracXIsZero_uid26_block_rsrvd_fix_q);
            redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_1 <= redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_0;
            redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_q <= STD_LOGIC_VECTOR(redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_delay_1);
        END IF;
    END PROCESS;

    -- excI_aSig_uid28_block_rsrvd_fix(LOGICAL,27)@9
    excI_aSig_uid28_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expXIsMax_uid25_block_rsrvd_fix_q and redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_q);

    -- sigAAInf_uid133_block_rsrvd_fix(LOGICAL,132)@9
    sigAAInf_uid133_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist25_sigA_uid51_block_rsrvd_fix_b_8_q and excI_aSig_uid28_block_rsrvd_fix_q);

    -- signRInf_uid134_block_rsrvd_fix(LOGICAL,133)@9
    signRInf_uid134_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(sigAAInf_uid133_block_rsrvd_fix_q or sigBBInf_uid132_block_rsrvd_fix_q);

    -- signRInfRZRReg_uid138_block_rsrvd_fix(LOGICAL,137)@9 + 1
    signRInfRZRReg_uid138_block_rsrvd_fix_qi <= signRInf_uid134_block_rsrvd_fix_q or signRZero_uid137_block_rsrvd_fix_q or signRReg_uid131_block_rsrvd_fix_q;
    signRInfRZRReg_uid138_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => signRInfRZRReg_uid138_block_rsrvd_fix_qi, xout => signRInfRZRReg_uid138_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist12_signRInfRZRReg_uid138_block_rsrvd_fix_q_2(DELAY,289)
    redist12_signRInfRZRReg_uid138_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist12_signRInfRZRReg_uid138_block_rsrvd_fix_q_2_q <= signRInfRZRReg_uid138_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- fracXIsNotZero_uid41_block_rsrvd_fix(LOGICAL,40)@9
    fracXIsNotZero_uid41_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist29_fracXIsZero_uid40_block_rsrvd_fix_q_8_q));

    -- excN_bSig_uid43_block_rsrvd_fix(LOGICAL,42)@9 + 1
    excN_bSig_uid43_block_rsrvd_fix_qi <= redist30_expXIsMax_uid39_block_rsrvd_fix_q_8_q and fracXIsNotZero_uid41_block_rsrvd_fix_q;
    excN_bSig_uid43_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excN_bSig_uid43_block_rsrvd_fix_qi, xout => excN_bSig_uid43_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist27_excN_bSig_uid43_block_rsrvd_fix_q_2(DELAY,304)
    redist27_excN_bSig_uid43_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist27_excN_bSig_uid43_block_rsrvd_fix_q_2_q <= excN_bSig_uid43_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- fracXIsNotZero_uid27_block_rsrvd_fix(LOGICAL,26)@9
    fracXIsNotZero_uid27_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist36_fracXIsZero_uid26_block_rsrvd_fix_q_4_q));

    -- excN_aSig_uid29_block_rsrvd_fix(LOGICAL,28)@9 + 1
    excN_aSig_uid29_block_rsrvd_fix_qi <= expXIsMax_uid25_block_rsrvd_fix_q and fracXIsNotZero_uid27_block_rsrvd_fix_q;
    excN_aSig_uid29_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excN_aSig_uid29_block_rsrvd_fix_qi, xout => excN_aSig_uid29_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist34_excN_aSig_uid29_block_rsrvd_fix_q_2(DELAY,311)
    redist34_excN_aSig_uid29_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist34_excN_aSig_uid29_block_rsrvd_fix_q_2_q <= excN_aSig_uid29_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- excRNaN2_uid125_block_rsrvd_fix(LOGICAL,124)@11
    excRNaN2_uid125_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist34_excN_aSig_uid29_block_rsrvd_fix_q_2_q or redist27_excN_bSig_uid43_block_rsrvd_fix_q_2_q);

    -- redist21_effSub_uid53_block_rsrvd_fix_q_6(DELAY,298)
    redist21_effSub_uid53_block_rsrvd_fix_q_6 : dspba_delay
    GENERIC MAP ( width => 1, depth => 6, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => effSub_uid53_block_rsrvd_fix_q, xout => redist21_effSub_uid53_block_rsrvd_fix_q_6_q, clk => clk, aclr => areset, ena => '1' );

    -- redist28_excI_bSig_uid42_block_rsrvd_fix_q_2(DELAY,305)
    redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(excI_bSig_uid42_block_rsrvd_fix_q);
            redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- redist35_excI_aSig_uid28_block_rsrvd_fix_q_2(DELAY,312)
    redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(excI_aSig_uid28_block_rsrvd_fix_q);
            redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- excAIBISub_uid126_block_rsrvd_fix(LOGICAL,125)@11
    excAIBISub_uid126_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_q and redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_q and redist21_effSub_uid53_block_rsrvd_fix_q_6_q);

    -- excRNaN_uid127_block_rsrvd_fix(LOGICAL,126)@11
    excRNaN_uid127_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excAIBISub_uid126_block_rsrvd_fix_q or excRNaN2_uid125_block_rsrvd_fix_q);

    -- invExcRNaN_uid139_block_rsrvd_fix(LOGICAL,138)@11
    invExcRNaN_uid139_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excRNaN_uid127_block_rsrvd_fix_q));

    -- VCC(CONSTANT,1)
    VCC_q <= "1";

    -- signRPostExc_uid140_block_rsrvd_fix(LOGICAL,139)@11 + 1
    signRPostExc_uid140_block_rsrvd_fix_qi <= invExcRNaN_uid139_block_rsrvd_fix_q and redist12_signRInfRZRReg_uid138_block_rsrvd_fix_q_2_q;
    signRPostExc_uid140_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => signRPostExc_uid140_block_rsrvd_fix_qi, xout => signRPostExc_uid140_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- cRBit_uid100_block_rsrvd_fix(CONSTANT,99)
    cRBit_uid100_block_rsrvd_fix_q <= "01000";

    -- leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,263)@9
    leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q(53 downto 0);
    leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_in(53 downto 0));

    -- leftShiftStage2Idx3_uid265_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,264)@9
    leftShiftStage2Idx3_uid265_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx3Rng3_uid264_fracPostNormExt_uid89_block_rsrvd_fix_b & rightShiftStage0Idx3Pad3_uid199_alignmentShifter_uid65_block_rsrvd_fix_q;

    -- leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,260)@9
    leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q(54 downto 0);
    leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_in(54 downto 0));

    -- leftShiftStage2Idx2_uid262_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,261)@9
    leftShiftStage2Idx2_uid262_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx2Rng2_uid261_fracPostNormExt_uid89_block_rsrvd_fix_b & zs_uid177_lzCountVal_uid86_block_rsrvd_fix_q;

    -- leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,257)@9
    leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q(55 downto 0);
    leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_in(55 downto 0));

    -- leftShiftStage2Idx1_uid259_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,258)@9
    leftShiftStage2Idx1_uid259_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx1Rng1_uid258_fracPostNormExt_uid89_block_rsrvd_fix_b & GND_q;

    -- leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,252)@9
    leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q(44 downto 0);
    leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_in(44 downto 0));

    -- leftShiftStage1Idx3_uid254_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,253)@9
    leftShiftStage1Idx3_uid254_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx3Rng12_uid253_fracPostNormExt_uid89_block_rsrvd_fix_b & rightShiftStage1Idx3Pad12_uid210_alignmentShifter_uid65_block_rsrvd_fix_q;

    -- leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,249)@9
    leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q(48 downto 0);
    leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_in(48 downto 0));

    -- leftShiftStage1Idx2_uid251_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,250)@9
    leftShiftStage1Idx2_uid251_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx2Rng8_uid250_fracPostNormExt_uid89_block_rsrvd_fix_b & zs_uid165_lzCountVal_uid86_block_rsrvd_fix_q;

    -- leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,246)@9
    leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_in <= leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q(52 downto 0);
    leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_in(52 downto 0));

    -- leftShiftStage1Idx1_uid248_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,247)@9
    leftShiftStage1Idx1_uid248_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx1Rng4_uid247_fracPostNormExt_uid89_block_rsrvd_fix_b & zs_uid171_lzCountVal_uid86_block_rsrvd_fix_q;

    -- leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,241)@9
    leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_in <= redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q(8 downto 0);
    leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_in(8 downto 0));

    -- leftShiftStage0Idx3_uid243_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,242)@9
    leftShiftStage0Idx3_uid243_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0Idx3Rng48_uid242_fracPostNormExt_uid89_block_rsrvd_fix_b & rightShiftStage2Idx3Pad48_uid221_alignmentShifter_uid65_block_rsrvd_fix_q;

    -- redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3(DELAY,287)
    redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_0 <= STD_LOGIC_VECTOR(vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b);
            redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_1 <= redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_0;
            redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_q <= STD_LOGIC_VECTOR(redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_delay_1);
        END IF;
    END PROCESS;

    -- leftShiftStage0Idx2_uid240_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,239)@9
    leftShiftStage0Idx2_uid240_fracPostNormExt_uid89_block_rsrvd_fix_q <= redist10_vStage_uid155_lzCountVal_uid86_block_rsrvd_fix_b_3_q & zs_uid151_lzCountVal_uid86_block_rsrvd_fix_q;

    -- leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix(BITSELECT,235)@9
    leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_in <= redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q(40 downto 0);
    leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_in(40 downto 0));

    -- leftShiftStage0Idx1_uid237_fracPostNormExt_uid89_block_rsrvd_fix(BITJOIN,236)@9
    leftShiftStage0Idx1_uid237_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0Idx1Rng16_uid236_fracPostNormExt_uid89_block_rsrvd_fix_b & zs_uid159_lzCountVal_uid86_block_rsrvd_fix_q;

    -- redist19_fracGRS_uid85_block_rsrvd_fix_q_3(DELAY,296)
    redist19_fracGRS_uid85_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(fracGRS_uid85_block_rsrvd_fix_q);
            redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_1 <= redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_0;
            redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist19_fracGRS_uid85_block_rsrvd_fix_q_3_delay_1);
        END IF;
    END PROCESS;

    -- leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix(MUX,244)@9
    leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_b;
    leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_combproc: PROCESS (leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_s, redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q, leftShiftStage0Idx1_uid237_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage0Idx2_uid240_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage0Idx3_uid243_fracPostNormExt_uid89_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q <= redist19_fracGRS_uid85_block_rsrvd_fix_q_3_q;
            WHEN "01" => leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0Idx1_uid237_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0Idx2_uid240_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0Idx3_uid243_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix(MUX,255)@9
    leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_c;
    leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_combproc: PROCESS (leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_s, leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage1Idx1_uid248_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage1Idx2_uid251_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage1Idx3_uid254_fracPostNormExt_uid89_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage0_uid245_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "01" => leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx1_uid248_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx2_uid251_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1Idx3_uid254_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged(BITSELECT,273)@9
    leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(r_uid186_lzCountVal_uid86_block_rsrvd_fix_q(5 downto 4));
    leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(r_uid186_lzCountVal_uid86_block_rsrvd_fix_q(3 downto 2));
    leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_d <= STD_LOGIC_VECTOR(r_uid186_lzCountVal_uid86_block_rsrvd_fix_q(1 downto 0));

    -- leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix(MUX,266)@9
    leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid244_fracPostNormExt_uid89_block_rsrvd_fix_bit_select_merged_d;
    leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_combproc: PROCESS (leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_s, leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage2Idx1_uid259_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage2Idx2_uid262_fracPostNormExt_uid89_block_rsrvd_fix_q, leftShiftStage2Idx3_uid265_fracPostNormExt_uid89_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage1_uid256_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "01" => leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx1_uid259_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx2_uid262_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q <= leftShiftStage2Idx3_uid265_fracPostNormExt_uid89_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- LSB_uid98_block_rsrvd_fix(BITSELECT,97)@9
    LSB_uid98_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(4 downto 0));
    LSB_uid98_block_rsrvd_fix_b <= LSB_uid98_block_rsrvd_fix_in(4 downto 4);

    -- Guard_uid97_block_rsrvd_fix(BITSELECT,96)@9
    Guard_uid97_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(3 downto 0));
    Guard_uid97_block_rsrvd_fix_b <= Guard_uid97_block_rsrvd_fix_in(3 downto 3);

    -- Round_uid96_block_rsrvd_fix(BITSELECT,95)@9
    Round_uid96_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(2 downto 0));
    Round_uid96_block_rsrvd_fix_b <= Round_uid96_block_rsrvd_fix_in(2 downto 2);

    -- Sticky1_uid95_block_rsrvd_fix(BITSELECT,94)@9
    Sticky1_uid95_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(1 downto 0));
    Sticky1_uid95_block_rsrvd_fix_b <= Sticky1_uid95_block_rsrvd_fix_in(1 downto 1);

    -- Sticky0_uid94_block_rsrvd_fix(BITSELECT,93)@9
    Sticky0_uid94_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(0 downto 0));
    Sticky0_uid94_block_rsrvd_fix_b <= Sticky0_uid94_block_rsrvd_fix_in(0 downto 0);

    -- rndBitCond_uid99_block_rsrvd_fix(BITJOIN,98)@9
    rndBitCond_uid99_block_rsrvd_fix_q <= LSB_uid98_block_rsrvd_fix_b & Guard_uid97_block_rsrvd_fix_b & Round_uid96_block_rsrvd_fix_b & Sticky1_uid95_block_rsrvd_fix_b & Sticky0_uid94_block_rsrvd_fix_b;

    -- rBi_uid101_block_rsrvd_fix(LOGICAL,100)@9 + 1
    rBi_uid101_block_rsrvd_fix_qi <= "1" WHEN rndBitCond_uid99_block_rsrvd_fix_q = cRBit_uid100_block_rsrvd_fix_q ELSE "0";
    rBi_uid101_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => rBi_uid101_block_rsrvd_fix_qi, xout => rBi_uid101_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- roundBit_uid102_block_rsrvd_fix(LOGICAL,101)@10
    roundBit_uid102_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (rBi_uid101_block_rsrvd_fix_q));

    -- oneCST_uid91_block_rsrvd_fix(CONSTANT,90)
    oneCST_uid91_block_rsrvd_fix_q <= "00000000001";

    -- expInc_uid92_block_rsrvd_fix(ADD,91)@8 + 1
    expInc_uid92_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & redist39_exp_aSig_uid22_block_rsrvd_fix_b_7_mem_q);
    expInc_uid92_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0" & oneCST_uid91_block_rsrvd_fix_q);
    expInc_uid92_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expInc_uid92_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(expInc_uid92_block_rsrvd_fix_a) + UNSIGNED(expInc_uid92_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expInc_uid92_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expInc_uid92_block_rsrvd_fix_o(11 downto 0));

    -- expPostNorm_uid93_block_rsrvd_fix(SUB,92)@9
    expPostNorm_uid93_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & expInc_uid92_block_rsrvd_fix_q));
    expPostNorm_uid93_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0000000" & r_uid186_lzCountVal_uid86_block_rsrvd_fix_q));
    expPostNorm_uid93_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expPostNorm_uid93_block_rsrvd_fix_a) - SIGNED(expPostNorm_uid93_block_rsrvd_fix_b));
    expPostNorm_uid93_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expPostNorm_uid93_block_rsrvd_fix_o(12 downto 0));

    -- fracPostNorm_uid90_block_rsrvd_fix(BITSELECT,89)@9
    fracPostNorm_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2_uid267_fracPostNormExt_uid89_block_rsrvd_fix_q(56 downto 1));

    -- fracPostNormRndRange_uid103_block_rsrvd_fix(BITSELECT,102)@9
    fracPostNormRndRange_uid103_block_rsrvd_fix_in <= fracPostNorm_uid90_block_rsrvd_fix_b(54 downto 0);
    fracPostNormRndRange_uid103_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracPostNormRndRange_uid103_block_rsrvd_fix_in(54 downto 2));

    -- expFracR_uid104_block_rsrvd_fix(BITJOIN,103)@9
    expFracR_uid104_block_rsrvd_fix_q <= expPostNorm_uid93_block_rsrvd_fix_q & fracPostNormRndRange_uid103_block_rsrvd_fix_b;

    -- redist17_expFracR_uid104_block_rsrvd_fix_q_1(DELAY,294)
    redist17_expFracR_uid104_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist17_expFracR_uid104_block_rsrvd_fix_q_1_q <= expFracR_uid104_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- rndExpFrac_uid105_block_rsrvd_fix(ADD,104)@10 + 1
    rndExpFrac_uid105_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & redist17_expFracR_uid104_block_rsrvd_fix_q_1_q);
    rndExpFrac_uid105_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("000000000000000000000000000000000000000000000000000000000000000000" & roundBit_uid102_block_rsrvd_fix_q);
    rndExpFrac_uid105_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            rndExpFrac_uid105_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(rndExpFrac_uid105_block_rsrvd_fix_a) + UNSIGNED(rndExpFrac_uid105_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    rndExpFrac_uid105_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rndExpFrac_uid105_block_rsrvd_fix_o(66 downto 0));

    -- expRPreExc_uid118_block_rsrvd_fix(BITSELECT,117)@11
    expRPreExc_uid118_block_rsrvd_fix_in <= rndExpFrac_uid105_block_rsrvd_fix_q(63 downto 0);
    expRPreExc_uid118_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(expRPreExc_uid118_block_rsrvd_fix_in(63 downto 53));

    -- redist15_expRPreExc_uid118_block_rsrvd_fix_b_1(DELAY,292)
    redist15_expRPreExc_uid118_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist15_expRPreExc_uid118_block_rsrvd_fix_b_1_q <= expRPreExc_uid118_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- redist13_excRNaN_uid127_block_rsrvd_fix_q_1(DELAY,290)
    redist13_excRNaN_uid127_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist13_excRNaN_uid127_block_rsrvd_fix_q_1_q <= excRNaN_uid127_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- rndExpFracOvfBits_uid110_block_rsrvd_fix(BITSELECT,109)@11
    rndExpFracOvfBits_uid110_block_rsrvd_fix_in <= rndExpFrac_uid105_block_rsrvd_fix_q(65 downto 0);
    rndExpFracOvfBits_uid110_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rndExpFracOvfBits_uid110_block_rsrvd_fix_in(65 downto 64));

    -- rOvfExtraBits_uid111_block_rsrvd_fix(LOGICAL,110)@11
    rOvfExtraBits_uid111_block_rsrvd_fix_q <= "1" WHEN rndExpFracOvfBits_uid110_block_rsrvd_fix_b = zocst_uid77_block_rsrvd_fix_q ELSE "0";

    -- wEP2AllOwE_uid106_block_rsrvd_fix(CONSTANT,105)
    wEP2AllOwE_uid106_block_rsrvd_fix_q <= "0011111111111";

    -- rndExp_uid107_block_rsrvd_fix(BITSELECT,106)@11
    rndExp_uid107_block_rsrvd_fix_in <= rndExpFrac_uid105_block_rsrvd_fix_q(65 downto 0);
    rndExp_uid107_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rndExp_uid107_block_rsrvd_fix_in(65 downto 53));

    -- rOvfEQMax_uid108_block_rsrvd_fix(LOGICAL,107)@11
    rOvfEQMax_uid108_block_rsrvd_fix_q <= "1" WHEN rndExp_uid107_block_rsrvd_fix_b = wEP2AllOwE_uid106_block_rsrvd_fix_q ELSE "0";

    -- rOvf_uid112_block_rsrvd_fix(LOGICAL,111)@11
    rOvf_uid112_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rOvfEQMax_uid108_block_rsrvd_fix_q or rOvfExtraBits_uid111_block_rsrvd_fix_q);

    -- regInputs_uid119_block_rsrvd_fix(LOGICAL,118)@9 + 1
    regInputs_uid119_block_rsrvd_fix_qi <= excR_aSig_uid32_block_rsrvd_fix_q and excR_bSig_uid46_block_rsrvd_fix_q;
    regInputs_uid119_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => regInputs_uid119_block_rsrvd_fix_qi, xout => regInputs_uid119_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist14_regInputs_uid119_block_rsrvd_fix_q_2(DELAY,291)
    redist14_regInputs_uid119_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist14_regInputs_uid119_block_rsrvd_fix_q_2_q <= regInputs_uid119_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- rInfOvf_uid122_block_rsrvd_fix(LOGICAL,121)@11
    rInfOvf_uid122_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist14_regInputs_uid119_block_rsrvd_fix_q_2_q and rOvf_uid112_block_rsrvd_fix_q);

    -- excRInfVInC_uid123_block_rsrvd_fix(BITJOIN,122)@11
    excRInfVInC_uid123_block_rsrvd_fix_q <= rInfOvf_uid122_block_rsrvd_fix_q & redist27_excN_bSig_uid43_block_rsrvd_fix_q_2_q & redist34_excN_aSig_uid29_block_rsrvd_fix_q_2_q & redist28_excI_bSig_uid42_block_rsrvd_fix_q_2_q & redist35_excI_aSig_uid28_block_rsrvd_fix_q_2_q & redist21_effSub_uid53_block_rsrvd_fix_q_6_q;

    -- excRInf_uid124_block_rsrvd_fix(LOOKUP,123)@11 + 1
    excRInf_uid124_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (excRInfVInC_uid123_block_rsrvd_fix_q) IS
                WHEN "000000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "000001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "000010" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "000011" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "000100" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "000101" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "000110" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "000111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "001111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "010111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "011111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100000" => excRInf_uid124_block_rsrvd_fix_q <= "1";
                WHEN "100001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "100111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "101111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "110111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111000" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111001" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111010" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111011" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111100" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111101" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111110" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN "111111" => excRInf_uid124_block_rsrvd_fix_q <= "0";
                WHEN OTHERS => -- unreachable
                               excRInf_uid124_block_rsrvd_fix_q <= (others => '-');
            END CASE;
        END IF;
    END PROCESS;

    -- redist18_aMinusA_uid88_block_rsrvd_fix_q_2(DELAY,295)
    redist18_aMinusA_uid88_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist18_aMinusA_uid88_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(aMinusA_uid88_block_rsrvd_fix_q);
            redist18_aMinusA_uid88_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist18_aMinusA_uid88_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- rUdfExtraBit_uid115_block_rsrvd_fix(BITSELECT,114)@11
    rUdfExtraBit_uid115_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(rndExpFrac_uid105_block_rsrvd_fix_q(65 downto 0));
    rUdfExtraBit_uid115_block_rsrvd_fix_b <= rUdfExtraBit_uid115_block_rsrvd_fix_in(65 downto 65);

    -- wEP2AllZ_uid113_block_rsrvd_fix(CONSTANT,112)
    wEP2AllZ_uid113_block_rsrvd_fix_q <= "0000000000000";

    -- rUdfEQMin_uid114_block_rsrvd_fix(LOGICAL,113)@11
    rUdfEQMin_uid114_block_rsrvd_fix_q <= "1" WHEN rndExp_uid107_block_rsrvd_fix_b = wEP2AllZ_uid113_block_rsrvd_fix_q ELSE "0";

    -- rUdf_uid116_block_rsrvd_fix(LOGICAL,115)@11
    rUdf_uid116_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rUdfEQMin_uid114_block_rsrvd_fix_q or rUdfExtraBit_uid115_block_rsrvd_fix_b);

    -- redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10(DELAY,310)
    redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_delay_0 <= STD_LOGIC_VECTOR(redist32_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_8_q);
            redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_q <= STD_LOGIC_VECTOR(redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_delay_0);
        END IF;
    END PROCESS;

    -- redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3(DELAY,314)
    redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(excZ_aSig_uid17_uid24_block_rsrvd_fix_q);
            redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_delay_0);
        END IF;
    END PROCESS;

    -- excRZeroVInC_uid120_block_rsrvd_fix(BITJOIN,119)@11
    excRZeroVInC_uid120_block_rsrvd_fix_q <= redist18_aMinusA_uid88_block_rsrvd_fix_q_2_q & rUdf_uid116_block_rsrvd_fix_q & redist14_regInputs_uid119_block_rsrvd_fix_q_2_q & redist33_excZ_bSig_uid18_uid38_block_rsrvd_fix_q_10_q & redist37_excZ_aSig_uid17_uid24_block_rsrvd_fix_q_3_q;

    -- excRZero_uid121_block_rsrvd_fix(LOOKUP,120)@11 + 1
    excRZero_uid121_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (excRZeroVInC_uid120_block_rsrvd_fix_q) IS
                WHEN "00000" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00001" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00010" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00011" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "00100" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00101" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00110" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "00111" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01000" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01001" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01010" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01011" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "01100" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "01101" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01110" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "01111" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10000" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10001" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10010" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10011" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "10100" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "10101" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10110" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "10111" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11000" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11001" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11010" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11011" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "11100" => excRZero_uid121_block_rsrvd_fix_q <= "1";
                WHEN "11101" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11110" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN "11111" => excRZero_uid121_block_rsrvd_fix_q <= "0";
                WHEN OTHERS => -- unreachable
                               excRZero_uid121_block_rsrvd_fix_q <= (others => '-');
            END CASE;
        END IF;
    END PROCESS;

    -- concExc_uid128_block_rsrvd_fix(BITJOIN,127)@12
    concExc_uid128_block_rsrvd_fix_q <= redist13_excRNaN_uid127_block_rsrvd_fix_q_1_q & excRInf_uid124_block_rsrvd_fix_q & excRZero_uid121_block_rsrvd_fix_q;

    -- excREnc_uid129_block_rsrvd_fix(LOOKUP,128)@12
    excREnc_uid129_block_rsrvd_fix_combproc: PROCESS (concExc_uid128_block_rsrvd_fix_q)
    BEGIN
        -- Begin reserved scope level
        CASE (concExc_uid128_block_rsrvd_fix_q) IS
            WHEN "000" => excREnc_uid129_block_rsrvd_fix_q <= "01";
            WHEN "001" => excREnc_uid129_block_rsrvd_fix_q <= "00";
            WHEN "010" => excREnc_uid129_block_rsrvd_fix_q <= "10";
            WHEN "011" => excREnc_uid129_block_rsrvd_fix_q <= "10";
            WHEN "100" => excREnc_uid129_block_rsrvd_fix_q <= "11";
            WHEN "101" => excREnc_uid129_block_rsrvd_fix_q <= "11";
            WHEN "110" => excREnc_uid129_block_rsrvd_fix_q <= "11";
            WHEN "111" => excREnc_uid129_block_rsrvd_fix_q <= "11";
            WHEN OTHERS => -- unreachable
                           excREnc_uid129_block_rsrvd_fix_q <= (others => '-');
        END CASE;
        -- End reserved scope level
    END PROCESS;

    -- expRPostExc_uid148_block_rsrvd_fix(MUX,147)@12
    expRPostExc_uid148_block_rsrvd_fix_s <= excREnc_uid129_block_rsrvd_fix_q;
    expRPostExc_uid148_block_rsrvd_fix_combproc: PROCESS (expRPostExc_uid148_block_rsrvd_fix_s, cstAllZWE_uid21_block_rsrvd_fix_q, redist15_expRPreExc_uid118_block_rsrvd_fix_b_1_q, cstAllOWE_uid19_block_rsrvd_fix_q)
    BEGIN
        CASE (expRPostExc_uid148_block_rsrvd_fix_s) IS
            WHEN "00" => expRPostExc_uid148_block_rsrvd_fix_q <= cstAllZWE_uid21_block_rsrvd_fix_q;
            WHEN "01" => expRPostExc_uid148_block_rsrvd_fix_q <= redist15_expRPreExc_uid118_block_rsrvd_fix_b_1_q;
            WHEN "10" => expRPostExc_uid148_block_rsrvd_fix_q <= cstAllOWE_uid19_block_rsrvd_fix_q;
            WHEN "11" => expRPostExc_uid148_block_rsrvd_fix_q <= cstAllOWE_uid19_block_rsrvd_fix_q;
            WHEN OTHERS => expRPostExc_uid148_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- oneFracRPostExc2_uid141_block_rsrvd_fix(CONSTANT,140)
    oneFracRPostExc2_uid141_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000001";

    -- fracRPreExc_uid117_block_rsrvd_fix(BITSELECT,116)@11
    fracRPreExc_uid117_block_rsrvd_fix_in <= rndExpFrac_uid105_block_rsrvd_fix_q(52 downto 0);
    fracRPreExc_uid117_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracRPreExc_uid117_block_rsrvd_fix_in(52 downto 1));

    -- redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1(DELAY,293)
    redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1_q <= fracRPreExc_uid117_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- fracRPostExc_uid144_block_rsrvd_fix(MUX,143)@12
    fracRPostExc_uid144_block_rsrvd_fix_s <= excREnc_uid129_block_rsrvd_fix_q;
    fracRPostExc_uid144_block_rsrvd_fix_combproc: PROCESS (fracRPostExc_uid144_block_rsrvd_fix_s, cstZeroWF_uid20_block_rsrvd_fix_q, redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1_q, oneFracRPostExc2_uid141_block_rsrvd_fix_q)
    BEGIN
        CASE (fracRPostExc_uid144_block_rsrvd_fix_s) IS
            WHEN "00" => fracRPostExc_uid144_block_rsrvd_fix_q <= cstZeroWF_uid20_block_rsrvd_fix_q;
            WHEN "01" => fracRPostExc_uid144_block_rsrvd_fix_q <= redist16_fracRPreExc_uid117_block_rsrvd_fix_b_1_q;
            WHEN "10" => fracRPostExc_uid144_block_rsrvd_fix_q <= cstZeroWF_uid20_block_rsrvd_fix_q;
            WHEN "11" => fracRPostExc_uid144_block_rsrvd_fix_q <= oneFracRPostExc2_uid141_block_rsrvd_fix_q;
            WHEN OTHERS => fracRPostExc_uid144_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- R_uid149_block_rsrvd_fix(BITJOIN,148)@12
    R_uid149_block_rsrvd_fix_q <= signRPostExc_uid140_block_rsrvd_fix_q & expRPostExc_uid148_block_rsrvd_fix_q & fracRPostExc_uid144_block_rsrvd_fix_q;

    -- out_primWireOut(GPOUT,5)@12
    out_primWireOut <= R_uid149_block_rsrvd_fix_q;

END normal;
