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

-- VHDL created from flt_ifft8k_base_DUT_subBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_addFpArchSoleDatapath_correctRounding_3m5cq5c35in4uia1u6737j47pg9pig2jg8vcexdqyfw8i063064663c61i64oc1764761di4p61v64vi1e64e61kc5363l60uq5ux0ao30cd06cj0of0cdj6of0cd16ok0ct30u
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
entity flt_ifft8k_base_DUT_subBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa00000cdj6of0cd16ok0ct30u is
    port (
        in_0 : in std_logic_vector(63 downto 0);  -- float64_m52
        in_1 : in std_logic_vector(63 downto 0);  -- float64_m52
        out_primWireOut : out std_logic_vector(63 downto 0);  -- float64_m52
        clk : in std_logic;
        areset : in std_logic
    );
end flt_ifft8k_base_DUT_subBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa00000cdj6of0cd16ok0ct30u;

architecture normal of flt_ifft8k_base_DUT_subBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa00000cdj6of0cd16ok0ct30u is

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
    signal invSigY_uid13_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal ypn_uid14_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal aSig_uid18_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal aSig_uid18_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal bSig_uid19_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal bSig_uid19_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal cstAllOWE_uid20_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal cstZeroWF_uid21_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal cstAllZWE_uid22_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal exp_aSig_uid23_block_rsrvd_fix_in : STD_LOGIC_VECTOR (62 downto 0);
    signal exp_aSig_uid23_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_aSig_uid24_block_rsrvd_fix_in : STD_LOGIC_VECTOR (51 downto 0);
    signal frac_aSig_uid24_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_aSig_uid18_uid25_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excZ_aSig_uid18_uid25_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid26_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid26_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid27_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid27_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid28_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_aSig_uid29_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_aSig_uid30_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_aSig_uid30_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid31_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid32_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_aSig_uid33_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal exp_bSig_uid37_block_rsrvd_fix_in : STD_LOGIC_VECTOR (62 downto 0);
    signal exp_bSig_uid37_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_bSig_uid38_block_rsrvd_fix_in : STD_LOGIC_VECTOR (51 downto 0);
    signal frac_bSig_uid38_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_bSig_uid19_uid39_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid40_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid40_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid41_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid41_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid42_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_bSig_uid43_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_bSig_uid44_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_bSig_uid44_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid45_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid46_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_bSig_uid47_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigA_uid52_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal sigB_uid53_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal effSub_uid54_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracBz_uid58_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal fracBz_uid58_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal oFracB_uid61_block_rsrvd_fix_q : STD_LOGIC_VECTOR (52 downto 0);
    signal expAmExpB_uid62_block_rsrvd_fix_a : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid62_block_rsrvd_fix_b : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid62_block_rsrvd_fix_o : STD_LOGIC_VECTOR (11 downto 0);
    signal expAmExpB_uid62_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal cWFP2_uid63_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal shiftedOut_uid65_block_rsrvd_fix_a : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid65_block_rsrvd_fix_b : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid65_block_rsrvd_fix_o : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid65_block_rsrvd_fix_c : STD_LOGIC_VECTOR (0 downto 0);
    signal padConst_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (53 downto 0);
    signal rightPaddedIn_uid67_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal iShiftedOut_uid69_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal alignFracBPostShiftOut_uid70_block_rsrvd_fix_b : STD_LOGIC_VECTOR (106 downto 0);
    signal alignFracBPostShiftOut_uid70_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (106 downto 0);
    signal alignFracBPostShiftOut_uid70_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invCmpEQ_stickyBits_cZwF_uid74_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal effSubInvSticky_uid76_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal zocst_uid78_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal fracAAddOp_uid79_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOp_uid82_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOpPostXor_uid83_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal fracBAddOpPostXor_uid83_block_rsrvd_fix_q : STD_LOGIC_VECTOR (55 downto 0);
    signal fracAddResult_uid84_block_rsrvd_fix_a : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid84_block_rsrvd_fix_b : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid84_block_rsrvd_fix_o : STD_LOGIC_VECTOR (56 downto 0);
    signal fracAddResult_uid84_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_in : STD_LOGIC_VECTOR (55 downto 0);
    signal rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal fracGRS_uid86_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal cAmA_uid88_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal aMinusA_uid89_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracPostNorm_uid91_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal oneCST_uid92_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal expInc_uid93_block_rsrvd_fix_a : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid93_block_rsrvd_fix_b : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid93_block_rsrvd_fix_o : STD_LOGIC_VECTOR (11 downto 0);
    signal expInc_uid93_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal expPostNorm_uid94_block_rsrvd_fix_a : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid94_block_rsrvd_fix_b : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid94_block_rsrvd_fix_o : STD_LOGIC_VECTOR (12 downto 0);
    signal expPostNorm_uid94_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal Sticky0_uid95_block_rsrvd_fix_in : STD_LOGIC_VECTOR (0 downto 0);
    signal Sticky0_uid95_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Sticky1_uid96_block_rsrvd_fix_in : STD_LOGIC_VECTOR (1 downto 0);
    signal Sticky1_uid96_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Round_uid97_block_rsrvd_fix_in : STD_LOGIC_VECTOR (2 downto 0);
    signal Round_uid97_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal Guard_uid98_block_rsrvd_fix_in : STD_LOGIC_VECTOR (3 downto 0);
    signal Guard_uid98_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal LSB_uid99_block_rsrvd_fix_in : STD_LOGIC_VECTOR (4 downto 0);
    signal LSB_uid99_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal rndBitCond_uid100_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal cRBit_uid101_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal rBi_uid102_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal rBi_uid102_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal roundBit_uid103_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracPostNormRndRange_uid104_block_rsrvd_fix_in : STD_LOGIC_VECTOR (54 downto 0);
    signal fracPostNormRndRange_uid104_block_rsrvd_fix_b : STD_LOGIC_VECTOR (52 downto 0);
    signal expFracR_uid105_block_rsrvd_fix_q : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExpFrac_uid106_block_rsrvd_fix_a : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid106_block_rsrvd_fix_b : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid106_block_rsrvd_fix_o : STD_LOGIC_VECTOR (66 downto 0);
    signal rndExpFrac_uid106_block_rsrvd_fix_q : STD_LOGIC_VECTOR (66 downto 0);
    signal wEP2AllOwE_uid107_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal rndExp_uid108_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExp_uid108_block_rsrvd_fix_b : STD_LOGIC_VECTOR (12 downto 0);
    signal rOvfEQMax_uid109_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rndExpFracOvfBits_uid111_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rndExpFracOvfBits_uid111_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rOvfExtraBits_uid112_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rOvf_uid113_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal wEP2AllZ_uid114_block_rsrvd_fix_q : STD_LOGIC_VECTOR (12 downto 0);
    signal rUdfEQMin_uid115_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rUdfExtraBit_uid116_block_rsrvd_fix_in : STD_LOGIC_VECTOR (65 downto 0);
    signal rUdfExtraBit_uid116_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal rUdf_uid117_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracRPreExc_uid118_block_rsrvd_fix_in : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPreExc_uid118_block_rsrvd_fix_b : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPreExc_uid119_block_rsrvd_fix_in : STD_LOGIC_VECTOR (63 downto 0);
    signal expRPreExc_uid119_block_rsrvd_fix_b : STD_LOGIC_VECTOR (10 downto 0);
    signal regInputs_uid120_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal regInputs_uid120_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRZeroVInC_uid121_block_rsrvd_fix_q : STD_LOGIC_VECTOR (4 downto 0);
    signal excRZero_uid122_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal rInfOvf_uid123_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRInfVInC_uid124_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal excRInf_uid125_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN2_uid126_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excAIBISub_uid127_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN_uid128_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN_uid128_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal concExc_uid129_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal excREnc_uid130_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal invAMinusA_uid131_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRReg_uid132_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigBBInf_uid133_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sigAAInf_uid134_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInf_uid135_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excAZBZSigASigB_uid136_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excBZARSigA_uid137_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRZero_uid138_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInfRZRReg_uid139_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal signRInfRZRReg_uid139_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExcRNaN_uid140_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRPostExc_uid141_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal oneFracRPostExc2_uid142_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal fracRPostExc_uid145_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostExc_uid145_block_rsrvd_fix_q : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPostExc_uid149_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal expRPostExc_uid149_block_rsrvd_fix_q : STD_LOGIC_VECTOR (10 downto 0);
    signal R_uid150_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal zs_uid152_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix_b : STD_LOGIC_VECTOR (31 downto 0);
    signal vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal mO_uid155_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (6 downto 0);
    signal vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_in : STD_LOGIC_VECTOR (24 downto 0);
    signal vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b : STD_LOGIC_VECTOR (24 downto 0);
    signal cStage_uid157_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (31 downto 0);
    signal zs_uid160_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (15 downto 0);
    signal vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (15 downto 0);
    signal zs_uid166_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (7 downto 0);
    signal vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (7 downto 0);
    signal zs_uid172_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (3 downto 0);
    signal vCount_uid174_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (3 downto 0);
    signal zs_uid178_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal vCount_uid180_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_s : STD_LOGIC_VECTOR (0 downto 0);
    signal vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (1 downto 0);
    signal rVStage_uid185_lzCountVal_uid87_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal vCount_uid186_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (0 downto 0);
    signal r_uid187_lzCountVal_uid87_block_rsrvd_fix_q : STD_LOGIC_VECTOR (5 downto 0);
    signal wIntCst_uid191_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (6 downto 0);
    signal shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_a : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_o : STD_LOGIC_VECTOR (13 downto 0);
    signal shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_n : STD_LOGIC_VECTOR (0 downto 0);
    signal rightShiftStage0Idx1Rng1_uid193_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (105 downto 0);
    signal rightShiftStage0Idx1_uid195_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage0Idx2Rng2_uid196_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (104 downto 0);
    signal rightShiftStage0Idx2_uid198_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage0Idx3Rng3_uid199_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (103 downto 0);
    signal rightShiftStage0Idx3Pad3_uid200_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (2 downto 0);
    signal rightShiftStage0Idx3_uid201_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_in : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx1Rng4_uid204_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (102 downto 0);
    signal rightShiftStage1Idx1_uid206_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx2Rng8_uid207_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (98 downto 0);
    signal rightShiftStage1Idx2_uid209_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage1Idx3Rng12_uid210_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (94 downto 0);
    signal rightShiftStage1Idx3Pad12_uid211_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (11 downto 0);
    signal rightShiftStage1Idx3_uid212_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_in : STD_LOGIC_VECTOR (3 downto 0);
    signal rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx1Rng16_uid215_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (90 downto 0);
    signal rightShiftStage2Idx1_uid217_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx2Rng32_uid218_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (74 downto 0);
    signal rightShiftStage2Idx2_uid220_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage2Idx3Rng48_uid221_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (58 downto 0);
    signal rightShiftStage2Idx3Pad48_uid222_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (47 downto 0);
    signal rightShiftStage2Idx3_uid223_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_in : STD_LOGIC_VECTOR (5 downto 0);
    signal rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStage3Idx1Rng64_uid226_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (42 downto 0);
    signal rightShiftStage3Idx1Pad64_uid227_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (63 downto 0);
    signal rightShiftStage3Idx1_uid228_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_in : STD_LOGIC_VECTOR (6 downto 0);
    signal rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b : STD_LOGIC_VECTOR (0 downto 0);
    signal zeroOutCst_uid231_alignmentShifter_uid66_block_rsrvd_fix_q : STD_LOGIC_VECTOR (106 downto 0);
    signal leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (40 downto 0);
    signal leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (40 downto 0);
    signal leftShiftStage0Idx1_uid238_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0Idx2_uid241_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (8 downto 0);
    signal leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (8 downto 0);
    signal leftShiftStage0Idx3_uid244_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (52 downto 0);
    signal leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (52 downto 0);
    signal leftShiftStage1Idx1_uid249_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (48 downto 0);
    signal leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (48 downto 0);
    signal leftShiftStage1Idx2_uid252_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (44 downto 0);
    signal leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (44 downto 0);
    signal leftShiftStage1Idx3_uid255_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (55 downto 0);
    signal leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (55 downto 0);
    signal leftShiftStage2Idx1_uid260_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (54 downto 0);
    signal leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (54 downto 0);
    signal leftShiftStage2Idx2_uid263_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_in : STD_LOGIC_VECTOR (53 downto 0);
    signal leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_b : STD_LOGIC_VECTOR (53 downto 0);
    signal leftShiftStage2Idx3_uid266_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_s : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q : STD_LOGIC_VECTOR (56 downto 0);
    signal stickyBits_uid71_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (51 downto 0);
    signal stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (54 downto 0);
    signal rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (15 downto 0);
    signal rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (15 downto 0);
    signal rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (7 downto 0);
    signal rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (7 downto 0);
    signal rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (3 downto 0);
    signal rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (3 downto 0);
    signal rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (1 downto 0);
    signal rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_b : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_c : STD_LOGIC_VECTOR (1 downto 0);
    signal leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_d : STD_LOGIC_VECTOR (1 downto 0);
    signal rightShiftStage3_uid230_alignmentShifter_uid66_block_rsrvd_fixinvSel_q : STD_LOGIC_VECTOR (0 downto 0);
    signal mergedMUXes0_opt_q : STD_LOGIC_VECTOR (106 downto 0);
    signal redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1_q : STD_LOGIC_VECTOR (15 downto 0);
    signal redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1_q : STD_LOGIC_VECTOR (15 downto 0);
    signal redist2_stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c_1_q : STD_LOGIC_VECTOR (54 downto 0);
    signal redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist4_rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (1 downto 0);
    signal redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (5 downto 0);
    signal redist6_vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist7_vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_q : STD_LOGIC_VECTOR (24 downto 0);
    signal redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_0 : STD_LOGIC_VECTOR (24 downto 0);
    signal redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_1 : STD_LOGIC_VECTOR (24 downto 0);
    signal redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist11_regInputs_uid120_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist12_expRPreExc_uid119_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist14_expFracR_uid105_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (65 downto 0);
    signal redist15_aMinusA_uid89_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist15_aMinusA_uid89_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (56 downto 0);
    signal redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (56 downto 0);
    signal redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_1 : STD_LOGIC_VECTOR (56 downto 0);
    signal redist17_rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (55 downto 0);
    signal redist18_cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist19_effSub_uid54_block_rsrvd_fix_q_6_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist20_sigB_uid53_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist21_sigB_uid53_block_rsrvd_fix_b_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigA_uid52_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigA_uid52_block_rsrvd_fix_b_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_2 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist24_InvExpXIsZero_uid46_block_rsrvd_fix_q_7_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist25_excN_bSig_uid44_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist28_expXIsMax_uid40_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist32_excN_aSig_uid30_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_1 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_delay_0 : STD_LOGIC_VECTOR (0 downto 0);
    signal redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_0 : STD_LOGIC_VECTOR (51 downto 0);
    signal redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_1 : STD_LOGIC_VECTOR (51 downto 0);
    signal redist38_sigY_uid12_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist39_expY_uid11_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist40_fracY_uid10_block_rsrvd_fix_b_1_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist41_in_0_in_0_1_q : STD_LOGIC_VECTOR (63 downto 0);
    signal redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0_q : STD_LOGIC_VECTOR (51 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_reset0 : std_logic;
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ia : STD_LOGIC_VECTOR (10 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_aa : STD_LOGIC_VECTOR (2 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ab : STD_LOGIC_VECTOR (2 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_iq : STD_LOGIC_VECTOR (10 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_q : STD_LOGIC_VECTOR (10 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_q : STD_LOGIC_VECTOR (2 downto 0);
    -- Initial-value here is arbitrary, but a resolved value is necessary for simulation.
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_i : UNSIGNED (2 downto 0) := "111";
    attribute preserve_syn_only : boolean;
    attribute preserve_syn_only of redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_i : signal is true;
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_offset_q : STD_LOGIC_VECTOR (2 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_a : STD_LOGIC_VECTOR (3 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_b : STD_LOGIC_VECTOR (3 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_o : STD_LOGIC_VECTOR (3 downto 0);
    signal redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_q : STD_LOGIC_VECTOR (3 downto 0);

begin


    -- cAmA_uid88_block_rsrvd_fix(CONSTANT,87)
    cAmA_uid88_block_rsrvd_fix_q <= "111001";

    -- zs_uid152_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,151)
    zs_uid152_lzCountVal_uid87_block_rsrvd_fix_q <= "00000000000000000000000000000000";

    -- sigY_uid12_block_rsrvd_fix(BITSELECT,11)@0
    sigY_uid12_block_rsrvd_fix_b <= in_1(63 downto 63);

    -- redist38_sigY_uid12_block_rsrvd_fix_b_1(DELAY,316)
    redist38_sigY_uid12_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist38_sigY_uid12_block_rsrvd_fix_b_1_q <= sigY_uid12_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- invSigY_uid13_block_rsrvd_fix(LOGICAL,12)@1
    invSigY_uid13_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist38_sigY_uid12_block_rsrvd_fix_b_1_q));

    -- expY_uid11_block_rsrvd_fix(BITSELECT,10)@0
    expY_uid11_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_1(62 downto 52));

    -- redist39_expY_uid11_block_rsrvd_fix_b_1(DELAY,317)
    redist39_expY_uid11_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist39_expY_uid11_block_rsrvd_fix_b_1_q <= expY_uid11_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- fracY_uid10_block_rsrvd_fix(BITSELECT,9)@0
    fracY_uid10_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(in_1(51 downto 0));

    -- redist40_fracY_uid10_block_rsrvd_fix_b_1(DELAY,318)
    redist40_fracY_uid10_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist40_fracY_uid10_block_rsrvd_fix_b_1_q <= fracY_uid10_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- ypn_uid14_block_rsrvd_fix(BITJOIN,13)@1
    ypn_uid14_block_rsrvd_fix_q <= invSigY_uid13_block_rsrvd_fix_q & redist39_expY_uid11_block_rsrvd_fix_b_1_q & redist40_fracY_uid10_block_rsrvd_fix_b_1_q;

    -- redist41_in_0_in_0_1(DELAY,319)
    redist41_in_0_in_0_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist41_in_0_in_0_1_q <= in_0;
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

    -- bSig_uid19_block_rsrvd_fix(MUX,18)@1
    bSig_uid19_block_rsrvd_fix_s <= xGTEy_uid9_block_rsrvd_fix_n;
    bSig_uid19_block_rsrvd_fix_combproc: PROCESS (bSig_uid19_block_rsrvd_fix_s, redist41_in_0_in_0_1_q, ypn_uid14_block_rsrvd_fix_q)
    BEGIN
        CASE (bSig_uid19_block_rsrvd_fix_s) IS
            WHEN "0" => bSig_uid19_block_rsrvd_fix_q <= redist41_in_0_in_0_1_q;
            WHEN "1" => bSig_uid19_block_rsrvd_fix_q <= ypn_uid14_block_rsrvd_fix_q;
            WHEN OTHERS => bSig_uid19_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- sigB_uid53_block_rsrvd_fix(BITSELECT,52)@1
    sigB_uid53_block_rsrvd_fix_b <= bSig_uid19_block_rsrvd_fix_q(63 downto 63);

    -- redist20_sigB_uid53_block_rsrvd_fix_b_4(DELAY,298)
    redist20_sigB_uid53_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(sigB_uid53_block_rsrvd_fix_b);
            redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_1 <= redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_0;
            redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_2 <= redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_1;
            redist20_sigB_uid53_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist20_sigB_uid53_block_rsrvd_fix_b_4_delay_2);
        END IF;
    END PROCESS;

    -- aSig_uid18_block_rsrvd_fix(MUX,17)@1
    aSig_uid18_block_rsrvd_fix_s <= xGTEy_uid9_block_rsrvd_fix_n;
    aSig_uid18_block_rsrvd_fix_combproc: PROCESS (aSig_uid18_block_rsrvd_fix_s, ypn_uid14_block_rsrvd_fix_q, redist41_in_0_in_0_1_q)
    BEGIN
        CASE (aSig_uid18_block_rsrvd_fix_s) IS
            WHEN "0" => aSig_uid18_block_rsrvd_fix_q <= ypn_uid14_block_rsrvd_fix_q;
            WHEN "1" => aSig_uid18_block_rsrvd_fix_q <= redist41_in_0_in_0_1_q;
            WHEN OTHERS => aSig_uid18_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- sigA_uid52_block_rsrvd_fix(BITSELECT,51)@1
    sigA_uid52_block_rsrvd_fix_b <= aSig_uid18_block_rsrvd_fix_q(63 downto 63);

    -- redist22_sigA_uid52_block_rsrvd_fix_b_4(DELAY,300)
    redist22_sigA_uid52_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(sigA_uid52_block_rsrvd_fix_b);
            redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_1 <= redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_0;
            redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_2 <= redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_1;
            redist22_sigA_uid52_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist22_sigA_uid52_block_rsrvd_fix_b_4_delay_2);
        END IF;
    END PROCESS;

    -- effSub_uid54_block_rsrvd_fix(LOGICAL,53)@5
    effSub_uid54_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist22_sigA_uid52_block_rsrvd_fix_b_4_q xor redist20_sigB_uid53_block_rsrvd_fix_b_4_q);

    -- exp_bSig_uid37_block_rsrvd_fix(BITSELECT,36)@1
    exp_bSig_uid37_block_rsrvd_fix_in <= bSig_uid19_block_rsrvd_fix_q(62 downto 0);
    exp_bSig_uid37_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(exp_bSig_uid37_block_rsrvd_fix_in(62 downto 52));

    -- exp_aSig_uid23_block_rsrvd_fix(BITSELECT,22)@1
    exp_aSig_uid23_block_rsrvd_fix_in <= aSig_uid18_block_rsrvd_fix_q(62 downto 0);
    exp_aSig_uid23_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(exp_aSig_uid23_block_rsrvd_fix_in(62 downto 52));

    -- expAmExpB_uid62_block_rsrvd_fix(SUB,61)@1 + 1
    expAmExpB_uid62_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & exp_aSig_uid23_block_rsrvd_fix_b));
    expAmExpB_uid62_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & exp_bSig_uid37_block_rsrvd_fix_b));
    expAmExpB_uid62_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expAmExpB_uid62_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expAmExpB_uid62_block_rsrvd_fix_a) - SIGNED(expAmExpB_uid62_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expAmExpB_uid62_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expAmExpB_uid62_block_rsrvd_fix_o(11 downto 0));

    -- cWFP2_uid63_block_rsrvd_fix(CONSTANT,62)
    cWFP2_uid63_block_rsrvd_fix_q <= "110110";

    -- shiftedOut_uid65_block_rsrvd_fix(COMPARE,64)@2 + 1
    shiftedOut_uid65_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("00000000" & cWFP2_uid63_block_rsrvd_fix_q);
    shiftedOut_uid65_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("00" & expAmExpB_uid62_block_rsrvd_fix_q);
    shiftedOut_uid65_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            shiftedOut_uid65_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(shiftedOut_uid65_block_rsrvd_fix_a) - UNSIGNED(shiftedOut_uid65_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    shiftedOut_uid65_block_rsrvd_fix_c(0) <= shiftedOut_uid65_block_rsrvd_fix_o(13);

    -- iShiftedOut_uid69_block_rsrvd_fix(LOGICAL,68)@3
    iShiftedOut_uid69_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (shiftedOut_uid65_block_rsrvd_fix_c));

    -- rightShiftStage2Idx3Pad48_uid222_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,221)
    rightShiftStage2Idx3Pad48_uid222_alignmentShifter_uid66_block_rsrvd_fix_q <= "000000000000000000000000000000000000000000000000";

    -- rightShiftStage2Idx3Rng48_uid221_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,220)@3
    rightShiftStage2Idx3Rng48_uid221_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 48));

    -- rightShiftStage2Idx3_uid223_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,222)@3
    rightShiftStage2Idx3_uid223_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage2Idx3Pad48_uid222_alignmentShifter_uid66_block_rsrvd_fix_q & rightShiftStage2Idx3Rng48_uid221_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- rightShiftStage2Idx2Rng32_uid218_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,217)@3
    rightShiftStage2Idx2Rng32_uid218_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 32));

    -- rightShiftStage2Idx2_uid220_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,219)@3
    rightShiftStage2Idx2_uid220_alignmentShifter_uid66_block_rsrvd_fix_q <= zs_uid152_lzCountVal_uid87_block_rsrvd_fix_q & rightShiftStage2Idx2Rng32_uid218_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- zs_uid160_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,159)
    zs_uid160_lzCountVal_uid87_block_rsrvd_fix_q <= "0000000000000000";

    -- rightShiftStage2Idx1Rng16_uid215_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,214)@3
    rightShiftStage2Idx1Rng16_uid215_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 16));

    -- rightShiftStage2Idx1_uid217_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,216)@3
    rightShiftStage2Idx1_uid217_alignmentShifter_uid66_block_rsrvd_fix_q <= zs_uid160_lzCountVal_uid87_block_rsrvd_fix_q & rightShiftStage2Idx1Rng16_uid215_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- rightShiftStage1Idx3Pad12_uid211_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,210)
    rightShiftStage1Idx3Pad12_uid211_alignmentShifter_uid66_block_rsrvd_fix_q <= "000000000000";

    -- rightShiftStage1Idx3Rng12_uid210_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,209)@2
    rightShiftStage1Idx3Rng12_uid210_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 12));

    -- rightShiftStage1Idx3_uid212_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,211)@2
    rightShiftStage1Idx3_uid212_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage1Idx3Pad12_uid211_alignmentShifter_uid66_block_rsrvd_fix_q & rightShiftStage1Idx3Rng12_uid210_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- zs_uid166_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,165)
    zs_uid166_lzCountVal_uid87_block_rsrvd_fix_q <= "00000000";

    -- rightShiftStage1Idx2Rng8_uid207_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,206)@2
    rightShiftStage1Idx2Rng8_uid207_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 8));

    -- rightShiftStage1Idx2_uid209_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,208)@2
    rightShiftStage1Idx2_uid209_alignmentShifter_uid66_block_rsrvd_fix_q <= zs_uid166_lzCountVal_uid87_block_rsrvd_fix_q & rightShiftStage1Idx2Rng8_uid207_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- zs_uid172_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,171)
    zs_uid172_lzCountVal_uid87_block_rsrvd_fix_q <= "0000";

    -- rightShiftStage1Idx1Rng4_uid204_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,203)@2
    rightShiftStage1Idx1Rng4_uid204_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 4));

    -- rightShiftStage1Idx1_uid206_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,205)@2
    rightShiftStage1Idx1_uid206_alignmentShifter_uid66_block_rsrvd_fix_q <= zs_uid172_lzCountVal_uid87_block_rsrvd_fix_q & rightShiftStage1Idx1Rng4_uid204_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- rightShiftStage0Idx3Pad3_uid200_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,199)
    rightShiftStage0Idx3Pad3_uid200_alignmentShifter_uid66_block_rsrvd_fix_q <= "000";

    -- rightShiftStage0Idx3Rng3_uid199_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,198)@2
    rightShiftStage0Idx3Rng3_uid199_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid67_block_rsrvd_fix_q(106 downto 3));

    -- rightShiftStage0Idx3_uid201_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,200)@2
    rightShiftStage0Idx3_uid201_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage0Idx3Pad3_uid200_alignmentShifter_uid66_block_rsrvd_fix_q & rightShiftStage0Idx3Rng3_uid199_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- zs_uid178_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,177)
    zs_uid178_lzCountVal_uid87_block_rsrvd_fix_q <= "00";

    -- rightShiftStage0Idx2Rng2_uid196_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,195)@2
    rightShiftStage0Idx2Rng2_uid196_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid67_block_rsrvd_fix_q(106 downto 2));

    -- rightShiftStage0Idx2_uid198_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,197)@2
    rightShiftStage0Idx2_uid198_alignmentShifter_uid66_block_rsrvd_fix_q <= zs_uid178_lzCountVal_uid87_block_rsrvd_fix_q & rightShiftStage0Idx2Rng2_uid196_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- rightShiftStage0Idx1Rng1_uid193_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,192)@2
    rightShiftStage0Idx1Rng1_uid193_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightPaddedIn_uid67_block_rsrvd_fix_q(106 downto 1));

    -- rightShiftStage0Idx1_uid195_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,194)@2
    rightShiftStage0Idx1_uid195_alignmentShifter_uid66_block_rsrvd_fix_q <= GND_q & rightShiftStage0Idx1Rng1_uid193_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- cstAllZWE_uid22_block_rsrvd_fix(CONSTANT,21)
    cstAllZWE_uid22_block_rsrvd_fix_q <= "00000000000";

    -- excZ_bSig_uid19_uid39_block_rsrvd_fix(LOGICAL,38)@1
    excZ_bSig_uid19_uid39_block_rsrvd_fix_q <= "1" WHEN exp_bSig_uid37_block_rsrvd_fix_b = cstAllZWE_uid22_block_rsrvd_fix_q ELSE "0";

    -- redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1(DELAY,307)
    redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1_q <= excZ_bSig_uid19_uid39_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- InvExpXIsZero_uid46_block_rsrvd_fix(LOGICAL,45)@2
    InvExpXIsZero_uid46_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1_q));

    -- cstZeroWF_uid21_block_rsrvd_fix(CONSTANT,20)
    cstZeroWF_uid21_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000000";

    -- frac_bSig_uid38_block_rsrvd_fix(BITSELECT,37)@1
    frac_bSig_uid38_block_rsrvd_fix_in <= bSig_uid19_block_rsrvd_fix_q(51 downto 0);
    frac_bSig_uid38_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(frac_bSig_uid38_block_rsrvd_fix_in(51 downto 0));

    -- fracBz_uid58_block_rsrvd_fix(MUX,57)@1 + 1
    fracBz_uid58_block_rsrvd_fix_s <= excZ_bSig_uid19_uid39_block_rsrvd_fix_q;
    fracBz_uid58_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (fracBz_uid58_block_rsrvd_fix_s) IS
                WHEN "0" => fracBz_uid58_block_rsrvd_fix_q <= frac_bSig_uid38_block_rsrvd_fix_b;
                WHEN "1" => fracBz_uid58_block_rsrvd_fix_q <= cstZeroWF_uid21_block_rsrvd_fix_q;
                WHEN OTHERS => fracBz_uid58_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- oFracB_uid61_block_rsrvd_fix(BITJOIN,60)@2
    oFracB_uid61_block_rsrvd_fix_q <= InvExpXIsZero_uid46_block_rsrvd_fix_q & fracBz_uid58_block_rsrvd_fix_q;

    -- padConst_uid66_block_rsrvd_fix(CONSTANT,65)
    padConst_uid66_block_rsrvd_fix_q <= "000000000000000000000000000000000000000000000000000000";

    -- rightPaddedIn_uid67_block_rsrvd_fix(BITJOIN,66)@2
    rightPaddedIn_uid67_block_rsrvd_fix_q <= oFracB_uid61_block_rsrvd_fix_q & padConst_uid66_block_rsrvd_fix_q;

    -- rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,201)@2
    rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_in <= expAmExpB_uid62_block_rsrvd_fix_q(1 downto 0);
    rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_in(1 downto 0));

    -- rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix(MUX,202)@2
    rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_s <= rightShiftStageSel0Dto0_uid202_alignmentShifter_uid66_block_rsrvd_fix_b;
    rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_combproc: PROCESS (rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_s, rightPaddedIn_uid67_block_rsrvd_fix_q, rightShiftStage0Idx1_uid195_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage0Idx2_uid198_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage0Idx3_uid201_alignmentShifter_uid66_block_rsrvd_fix_q)
    BEGIN
        CASE (rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_s) IS
            WHEN "00" => rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q <= rightPaddedIn_uid67_block_rsrvd_fix_q;
            WHEN "01" => rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage0Idx1_uid195_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN "10" => rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage0Idx2_uid198_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN "11" => rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage0Idx3_uid201_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN OTHERS => rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,212)@2
    rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_in <= expAmExpB_uid62_block_rsrvd_fix_q(3 downto 0);
    rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_in(3 downto 2));

    -- rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix(MUX,213)@2 + 1
    rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_s <= rightShiftStageSel2Dto2_uid213_alignmentShifter_uid66_block_rsrvd_fix_b;
    rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_s) IS
                WHEN "00" => rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage0_uid203_alignmentShifter_uid66_block_rsrvd_fix_q;
                WHEN "01" => rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage1Idx1_uid206_alignmentShifter_uid66_block_rsrvd_fix_q;
                WHEN "10" => rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage1Idx2_uid209_alignmentShifter_uid66_block_rsrvd_fix_q;
                WHEN "11" => rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage1Idx3_uid212_alignmentShifter_uid66_block_rsrvd_fix_q;
                WHEN OTHERS => rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,223)@2
    rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_in <= expAmExpB_uid62_block_rsrvd_fix_q(5 downto 0);
    rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_in(5 downto 4));

    -- redist4_rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b_1(DELAY,282)
    redist4_rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist4_rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b_1_q <= rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix(MUX,224)@3
    rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_s <= redist4_rightShiftStageSel4Dto4_uid224_alignmentShifter_uid66_block_rsrvd_fix_b_1_q;
    rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_combproc: PROCESS (rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_s, rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage2Idx1_uid217_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage2Idx2_uid220_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage2Idx3_uid223_alignmentShifter_uid66_block_rsrvd_fix_q)
    BEGIN
        CASE (rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_s) IS
            WHEN "00" => rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage1_uid214_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN "01" => rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage2Idx1_uid217_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN "10" => rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage2Idx2_uid220_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN "11" => rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage2Idx3_uid223_alignmentShifter_uid66_block_rsrvd_fix_q;
            WHEN OTHERS => rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rightShiftStage3_uid230_alignmentShifter_uid66_block_rsrvd_fixinvSel(LOGICAL,275)@3
    rightShiftStage3_uid230_alignmentShifter_uid66_block_rsrvd_fixinvSel_q <= not (redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_q);

    -- rightShiftStage3Idx1Pad64_uid227_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,226)
    rightShiftStage3Idx1Pad64_uid227_alignmentShifter_uid66_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000000000000000000";

    -- rightShiftStage3Idx1Rng64_uid226_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,225)@3
    rightShiftStage3Idx1Rng64_uid226_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q(106 downto 64));

    -- rightShiftStage3Idx1_uid228_alignmentShifter_uid66_block_rsrvd_fix(BITJOIN,227)@3
    rightShiftStage3Idx1_uid228_alignmentShifter_uid66_block_rsrvd_fix_q <= rightShiftStage3Idx1Pad64_uid227_alignmentShifter_uid66_block_rsrvd_fix_q & rightShiftStage3Idx1Rng64_uid226_alignmentShifter_uid66_block_rsrvd_fix_b;

    -- rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix(BITSELECT,228)@2
    rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_in <= expAmExpB_uid62_block_rsrvd_fix_q(6 downto 0);
    rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_in(6 downto 6));

    -- redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1(DELAY,281)
    redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_q <= rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- zeroOutCst_uid231_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,230)
    zeroOutCst_uid231_alignmentShifter_uid66_block_rsrvd_fix_q <= "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    -- wIntCst_uid191_alignmentShifter_uid66_block_rsrvd_fix(CONSTANT,190)
    wIntCst_uid191_alignmentShifter_uid66_block_rsrvd_fix_q <= "1101011";

    -- shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix(COMPARE,191)@2 + 1
    shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("00" & expAmExpB_uid62_block_rsrvd_fix_q);
    shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0000000" & wIntCst_uid191_alignmentShifter_uid66_block_rsrvd_fix_q);
    shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_a) - UNSIGNED(shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_n(0) <= not (shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_o(13));

    -- mergedMUXes0_opt(SELECTOR,277)@3
    mergedMUXes0_opt_combproc: PROCESS (shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_n, zeroOutCst_uid231_alignmentShifter_uid66_block_rsrvd_fix_q, redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_q, rightShiftStage3Idx1_uid228_alignmentShifter_uid66_block_rsrvd_fix_q, rightShiftStage3_uid230_alignmentShifter_uid66_block_rsrvd_fixinvSel_q, rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q, GND_q)
    BEGIN
        mergedMUXes0_opt_q <= STD_LOGIC_VECTOR((106 downto 1 => GND_q(0)) & GND_q);
        IF (rightShiftStage3_uid230_alignmentShifter_uid66_block_rsrvd_fixinvSel_q = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(rightShiftStage2_uid225_alignmentShifter_uid66_block_rsrvd_fix_q);
        END IF;
        IF (redist3_rightShiftStageSel6Dto6_uid229_alignmentShifter_uid66_block_rsrvd_fix_b_1_q = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(rightShiftStage3Idx1_uid228_alignmentShifter_uid66_block_rsrvd_fix_q);
        END IF;
        IF (shiftedOut_uid192_alignmentShifter_uid66_block_rsrvd_fix_n = "1") THEN
            mergedMUXes0_opt_q <= STD_LOGIC_VECTOR(zeroOutCst_uid231_alignmentShifter_uid66_block_rsrvd_fix_q);
        END IF;
    END PROCESS;

    -- alignFracBPostShiftOut_uid70_block_rsrvd_fix(LOGICAL,69)@3 + 1
    alignFracBPostShiftOut_uid70_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((106 downto 1 => iShiftedOut_uid69_block_rsrvd_fix_q(0)) & iShiftedOut_uid69_block_rsrvd_fix_q));
    alignFracBPostShiftOut_uid70_block_rsrvd_fix_qi <= mergedMUXes0_opt_q and alignFracBPostShiftOut_uid70_block_rsrvd_fix_b;
    alignFracBPostShiftOut_uid70_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 107, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => alignFracBPostShiftOut_uid70_block_rsrvd_fix_qi, xout => alignFracBPostShiftOut_uid70_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- stickyBits_uid71_block_rsrvd_fix_bit_select_merged(BITSELECT,269)@4
    stickyBits_uid71_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(alignFracBPostShiftOut_uid70_block_rsrvd_fix_q(51 downto 0));
    stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(alignFracBPostShiftOut_uid70_block_rsrvd_fix_q(106 downto 52));

    -- redist2_stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c_1(DELAY,280)
    redist2_stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist2_stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c_1_q <= stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c;
        END IF;
    END PROCESS;

    -- fracBAddOp_uid82_block_rsrvd_fix(BITJOIN,81)@5
    fracBAddOp_uid82_block_rsrvd_fix_q <= GND_q & redist2_stickyBits_uid71_block_rsrvd_fix_bit_select_merged_c_1_q;

    -- fracBAddOpPostXor_uid83_block_rsrvd_fix(LOGICAL,82)@5
    fracBAddOpPostXor_uid83_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((55 downto 1 => effSub_uid54_block_rsrvd_fix_q(0)) & effSub_uid54_block_rsrvd_fix_q));
    fracBAddOpPostXor_uid83_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(fracBAddOp_uid82_block_rsrvd_fix_q xor fracBAddOpPostXor_uid83_block_rsrvd_fix_b);

    -- zocst_uid78_block_rsrvd_fix(CONSTANT,77)
    zocst_uid78_block_rsrvd_fix_q <= "01";

    -- frac_aSig_uid24_block_rsrvd_fix(BITSELECT,23)@1
    frac_aSig_uid24_block_rsrvd_fix_in <= aSig_uid18_block_rsrvd_fix_q(51 downto 0);
    frac_aSig_uid24_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(frac_aSig_uid24_block_rsrvd_fix_in(51 downto 0));

    -- redist36_frac_aSig_uid24_block_rsrvd_fix_b_4(DELAY,314)
    redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_0 <= STD_LOGIC_VECTOR(frac_aSig_uid24_block_rsrvd_fix_b);
            redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_1 <= redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_0;
            redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_q <= STD_LOGIC_VECTOR(redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_delay_1);
        END IF;
    END PROCESS;

    -- redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0(DELAY,320)
    redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0_q <= redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_q;
        END IF;
    END PROCESS;

    -- cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix(LOGICAL,72)@4 + 1
    cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi <= "1" WHEN stickyBits_uid71_block_rsrvd_fix_bit_select_merged_b = cstZeroWF_uid21_block_rsrvd_fix_q ELSE "0";
    cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_qi, xout => cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- effSubInvSticky_uid76_block_rsrvd_fix(LOGICAL,75)@5
    effSubInvSticky_uid76_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(effSub_uid54_block_rsrvd_fix_q and cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q);

    -- fracAAddOp_uid79_block_rsrvd_fix(BITJOIN,78)@5
    fracAAddOp_uid79_block_rsrvd_fix_q <= zocst_uid78_block_rsrvd_fix_q & redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0_q & GND_q & effSubInvSticky_uid76_block_rsrvd_fix_q;

    -- fracAddResult_uid84_block_rsrvd_fix(ADD,83)@5
    fracAddResult_uid84_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & fracAAddOp_uid79_block_rsrvd_fix_q);
    fracAddResult_uid84_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0" & fracBAddOpPostXor_uid83_block_rsrvd_fix_q);
    fracAddResult_uid84_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(fracAddResult_uid84_block_rsrvd_fix_a) + UNSIGNED(fracAddResult_uid84_block_rsrvd_fix_b));
    fracAddResult_uid84_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(fracAddResult_uid84_block_rsrvd_fix_o(56 downto 0));

    -- rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix(BITSELECT,84)@5
    rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_in <= fracAddResult_uid84_block_rsrvd_fix_q(55 downto 0);
    rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_in(55 downto 0));

    -- redist17_rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b_1(DELAY,295)
    redist17_rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist17_rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b_1_q <= rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- redist18_cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q_2(DELAY,296)
    redist18_cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist18_cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q_2_q <= cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- invCmpEQ_stickyBits_cZwF_uid74_block_rsrvd_fix(LOGICAL,73)@6
    invCmpEQ_stickyBits_cZwF_uid74_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist18_cmpEQ_stickyBits_cZwF_uid73_block_rsrvd_fix_q_2_q));

    -- fracGRS_uid86_block_rsrvd_fix(BITJOIN,85)@6
    fracGRS_uid86_block_rsrvd_fix_q <= redist17_rangeFracAddResultMwfp3Dto0_uid85_block_rsrvd_fix_b_1_q & invCmpEQ_stickyBits_cZwF_uid74_block_rsrvd_fix_q;

    -- rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix(BITSELECT,152)@6
    rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracGRS_uid86_block_rsrvd_fix_q(56 downto 25));

    -- vCount_uid154_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,153)@6
    vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q <= "1" WHEN rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix_b = zs_uid152_lzCountVal_uid87_block_rsrvd_fix_q ELSE "0";

    -- redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2(DELAY,287)
    redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q);
            redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- vStage_uid156_lzCountVal_uid87_block_rsrvd_fix(BITSELECT,155)@6
    vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_in <= fracGRS_uid86_block_rsrvd_fix_q(24 downto 0);
    vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_in(24 downto 0));

    -- mO_uid155_lzCountVal_uid87_block_rsrvd_fix(CONSTANT,154)
    mO_uid155_lzCountVal_uid87_block_rsrvd_fix_q <= "1111111";

    -- cStage_uid157_lzCountVal_uid87_block_rsrvd_fix(BITJOIN,156)@6
    cStage_uid157_lzCountVal_uid87_block_rsrvd_fix_q <= vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b & mO_uid155_lzCountVal_uid87_block_rsrvd_fix_q;

    -- vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix(MUX,158)@6
    vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_s <= vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q;
    vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_combproc: PROCESS (vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_s, rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix_b, cStage_uid157_lzCountVal_uid87_block_rsrvd_fix_q)
    BEGIN
        CASE (vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid153_lzCountVal_uid87_block_rsrvd_fix_b;
            WHEN "1" => vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q <= cStage_uid157_lzCountVal_uid87_block_rsrvd_fix_q;
            WHEN OTHERS => vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged(BITSELECT,270)@6
    rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q(31 downto 16));
    rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid159_lzCountVal_uid87_block_rsrvd_fix_q(15 downto 0));

    -- vCount_uid162_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,161)@6 + 1
    vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_qi <= "1" WHEN rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b = zs_uid160_lzCountVal_uid87_block_rsrvd_fix_q ELSE "0";
    vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_qi, xout => vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist7_vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q_2(DELAY,285)
    redist7_vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist7_vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q_2_q <= vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1(DELAY,279)
    redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1_q <= rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c;
        END IF;
    END PROCESS;

    -- redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1(DELAY,278)
    redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1_q <= rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b;
        END IF;
    END PROCESS;

    -- vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix(MUX,164)@7
    vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_s <= vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q;
    vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_combproc: PROCESS (vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_s, redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1_q, redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1_q)
    BEGIN
        CASE (vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q <= redist0_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b_1_q;
            WHEN "1" => vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q <= redist1_rVStage_uid161_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c_1_q;
            WHEN OTHERS => vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged(BITSELECT,271)@7
    rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q(15 downto 8));
    rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid165_lzCountVal_uid87_block_rsrvd_fix_q(7 downto 0));

    -- vCount_uid168_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,167)@7
    vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q <= "1" WHEN rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b = zs_uid166_lzCountVal_uid87_block_rsrvd_fix_q ELSE "0";

    -- redist6_vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q_1(DELAY,284)
    redist6_vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist6_vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q_1_q <= vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix(MUX,170)@7 + 1
    vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_s <= vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q;
    vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_s) IS
                WHEN "0" => vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b;
                WHEN "1" => vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid167_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c;
                WHEN OTHERS => vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q <= (others => '0');
            END CASE;
        END IF;
    END PROCESS;

    -- rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged(BITSELECT,272)@8
    rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q(7 downto 4));
    rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid171_lzCountVal_uid87_block_rsrvd_fix_q(3 downto 0));

    -- vCount_uid174_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,173)@8
    vCount_uid174_lzCountVal_uid87_block_rsrvd_fix_q <= "1" WHEN rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b = zs_uid172_lzCountVal_uid87_block_rsrvd_fix_q ELSE "0";

    -- vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix(MUX,176)@8
    vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_s <= vCount_uid174_lzCountVal_uid87_block_rsrvd_fix_q;
    vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_combproc: PROCESS (vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_s, rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b, rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c)
    BEGIN
        CASE (vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b;
            WHEN "1" => vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid173_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c;
            WHEN OTHERS => vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged(BITSELECT,273)@8
    rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q(3 downto 2));
    rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(vStagei_uid177_lzCountVal_uid87_block_rsrvd_fix_q(1 downto 0));

    -- vCount_uid180_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,179)@8
    vCount_uid180_lzCountVal_uid87_block_rsrvd_fix_q <= "1" WHEN rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b = zs_uid178_lzCountVal_uid87_block_rsrvd_fix_q ELSE "0";

    -- vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix(MUX,182)@8
    vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_s <= vCount_uid180_lzCountVal_uid87_block_rsrvd_fix_q;
    vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_combproc: PROCESS (vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_s, rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b, rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c)
    BEGIN
        CASE (vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_s) IS
            WHEN "0" => vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_b;
            WHEN "1" => vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_q <= rVStage_uid179_lzCountVal_uid87_block_rsrvd_fix_bit_select_merged_c;
            WHEN OTHERS => vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- rVStage_uid185_lzCountVal_uid87_block_rsrvd_fix(BITSELECT,184)@8
    rVStage_uid185_lzCountVal_uid87_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(vStagei_uid183_lzCountVal_uid87_block_rsrvd_fix_q(1 downto 1));

    -- vCount_uid186_lzCountVal_uid87_block_rsrvd_fix(LOGICAL,185)@8
    vCount_uid186_lzCountVal_uid87_block_rsrvd_fix_q <= "1" WHEN rVStage_uid185_lzCountVal_uid87_block_rsrvd_fix_b = GND_q ELSE "0";

    -- r_uid187_lzCountVal_uid87_block_rsrvd_fix(BITJOIN,186)@8
    r_uid187_lzCountVal_uid87_block_rsrvd_fix_q <= redist9_vCount_uid154_lzCountVal_uid87_block_rsrvd_fix_q_2_q & redist7_vCount_uid162_lzCountVal_uid87_block_rsrvd_fix_q_2_q & redist6_vCount_uid168_lzCountVal_uid87_block_rsrvd_fix_q_1_q & vCount_uid174_lzCountVal_uid87_block_rsrvd_fix_q & vCount_uid180_lzCountVal_uid87_block_rsrvd_fix_q & vCount_uid186_lzCountVal_uid87_block_rsrvd_fix_q;

    -- redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1(DELAY,283)
    redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q <= r_uid187_lzCountVal_uid87_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- aMinusA_uid89_block_rsrvd_fix(LOGICAL,88)@9
    aMinusA_uid89_block_rsrvd_fix_q <= "1" WHEN redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q = cAmA_uid88_block_rsrvd_fix_q ELSE "0";

    -- invAMinusA_uid131_block_rsrvd_fix(LOGICAL,130)@9
    invAMinusA_uid131_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (aMinusA_uid89_block_rsrvd_fix_q));

    -- redist23_sigA_uid52_block_rsrvd_fix_b_8(DELAY,301)
    redist23_sigA_uid52_block_rsrvd_fix_b_8_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_0 <= STD_LOGIC_VECTOR(redist22_sigA_uid52_block_rsrvd_fix_b_4_q);
            redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_1 <= redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_0;
            redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_2 <= redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_1;
            redist23_sigA_uid52_block_rsrvd_fix_b_8_q <= STD_LOGIC_VECTOR(redist23_sigA_uid52_block_rsrvd_fix_b_8_delay_2);
        END IF;
    END PROCESS;

    -- cstAllOWE_uid20_block_rsrvd_fix(CONSTANT,19)
    cstAllOWE_uid20_block_rsrvd_fix_q <= "11111111111";

    -- expXIsMax_uid40_block_rsrvd_fix(LOGICAL,39)@1 + 1
    expXIsMax_uid40_block_rsrvd_fix_qi <= "1" WHEN exp_bSig_uid37_block_rsrvd_fix_b = cstAllOWE_uid20_block_rsrvd_fix_q ELSE "0";
    expXIsMax_uid40_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid40_block_rsrvd_fix_qi, xout => expXIsMax_uid40_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist28_expXIsMax_uid40_block_rsrvd_fix_q_8(DELAY,306)
    redist28_expXIsMax_uid40_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid40_block_rsrvd_fix_q, xout => redist28_expXIsMax_uid40_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- invExpXIsMax_uid45_block_rsrvd_fix(LOGICAL,44)@9
    invExpXIsMax_uid45_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist28_expXIsMax_uid40_block_rsrvd_fix_q_8_q));

    -- redist24_InvExpXIsZero_uid46_block_rsrvd_fix_q_7(DELAY,302)
    redist24_InvExpXIsZero_uid46_block_rsrvd_fix_q_7 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => InvExpXIsZero_uid46_block_rsrvd_fix_q, xout => redist24_InvExpXIsZero_uid46_block_rsrvd_fix_q_7_q, clk => clk, aclr => areset, ena => '1' );

    -- excR_bSig_uid47_block_rsrvd_fix(LOGICAL,46)@9
    excR_bSig_uid47_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist24_InvExpXIsZero_uid46_block_rsrvd_fix_q_7_q and invExpXIsMax_uid45_block_rsrvd_fix_q);

    -- redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_offset(CONSTANT,323)
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_offset_q <= "100";

    -- redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt(ADD,324)
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_a <= STD_LOGIC_VECTOR("0" & redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_q);
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_b <= STD_LOGIC_VECTOR("0" & redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_offset_q);
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_o <= STD_LOGIC_VECTOR(UNSIGNED(redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_a) + UNSIGNED(redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_b));
        END IF;
    END PROCESS;
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_q <= redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_o(3 downto 0);

    -- redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr(COUNTER,322)
    -- low=0, high=7, step=1, init=0
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_i <= redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_i + 1;
        END IF;
    END PROCESS;
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_q <= STD_LOGIC_VECTOR(RESIZE(redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_i, 3));

    -- redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem(DUALMEM,321)
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ia <= STD_LOGIC_VECTOR(exp_aSig_uid23_block_rsrvd_fix_b);
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_aa <= redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_wraddr_q;
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ab <= redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_rdcnt_q(2 downto 0);
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_dmem : altera_syncram
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
        address_a => redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_aa,
        data_a => redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ia,
        wren_a => VCC_q(0),
        address_b => redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_ab,
        q_b => redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_iq
    );
    redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_q <= STD_LOGIC_VECTOR(redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_iq(10 downto 0));

    -- expXIsMax_uid26_block_rsrvd_fix(LOGICAL,25)@8 + 1
    expXIsMax_uid26_block_rsrvd_fix_qi <= "1" WHEN redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_q = cstAllOWE_uid20_block_rsrvd_fix_q ELSE "0";
    expXIsMax_uid26_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => expXIsMax_uid26_block_rsrvd_fix_qi, xout => expXIsMax_uid26_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- invExpXIsMax_uid31_block_rsrvd_fix(LOGICAL,30)@9
    invExpXIsMax_uid31_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (expXIsMax_uid26_block_rsrvd_fix_q));

    -- excZ_aSig_uid18_uid25_block_rsrvd_fix(LOGICAL,24)@8 + 1
    excZ_aSig_uid18_uid25_block_rsrvd_fix_qi <= "1" WHEN redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_q = cstAllZWE_uid22_block_rsrvd_fix_q ELSE "0";
    excZ_aSig_uid18_uid25_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excZ_aSig_uid18_uid25_block_rsrvd_fix_qi, xout => excZ_aSig_uid18_uid25_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- InvExpXIsZero_uid32_block_rsrvd_fix(LOGICAL,31)@9
    InvExpXIsZero_uid32_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excZ_aSig_uid18_uid25_block_rsrvd_fix_q));

    -- excR_aSig_uid33_block_rsrvd_fix(LOGICAL,32)@9
    excR_aSig_uid33_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(InvExpXIsZero_uid32_block_rsrvd_fix_q and invExpXIsMax_uid31_block_rsrvd_fix_q);

    -- signRReg_uid132_block_rsrvd_fix(LOGICAL,131)@9
    signRReg_uid132_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excR_aSig_uid33_block_rsrvd_fix_q and excR_bSig_uid47_block_rsrvd_fix_q and redist23_sigA_uid52_block_rsrvd_fix_b_8_q and invAMinusA_uid131_block_rsrvd_fix_q);

    -- redist21_sigB_uid53_block_rsrvd_fix_b_8(DELAY,299)
    redist21_sigB_uid53_block_rsrvd_fix_b_8_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_0 <= STD_LOGIC_VECTOR(redist20_sigB_uid53_block_rsrvd_fix_b_4_q);
            redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_1 <= redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_0;
            redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_2 <= redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_1;
            redist21_sigB_uid53_block_rsrvd_fix_b_8_q <= STD_LOGIC_VECTOR(redist21_sigB_uid53_block_rsrvd_fix_b_8_delay_2);
        END IF;
    END PROCESS;

    -- redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8(DELAY,308)
    redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => redist29_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_1_q, xout => redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- excAZBZSigASigB_uid136_block_rsrvd_fix(LOGICAL,135)@9
    excAZBZSigASigB_uid136_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excZ_aSig_uid18_uid25_block_rsrvd_fix_q and redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8_q and redist23_sigA_uid52_block_rsrvd_fix_b_8_q and redist21_sigB_uid53_block_rsrvd_fix_b_8_q);

    -- excBZARSigA_uid137_block_rsrvd_fix(LOGICAL,136)@9
    excBZARSigA_uid137_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8_q and excR_aSig_uid33_block_rsrvd_fix_q and redist23_sigA_uid52_block_rsrvd_fix_b_8_q);

    -- signRZero_uid138_block_rsrvd_fix(LOGICAL,137)@9
    signRZero_uid138_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(excBZARSigA_uid137_block_rsrvd_fix_q or excAZBZSigASigB_uid136_block_rsrvd_fix_q);

    -- fracXIsZero_uid41_block_rsrvd_fix(LOGICAL,40)@1 + 1
    fracXIsZero_uid41_block_rsrvd_fix_qi <= "1" WHEN cstZeroWF_uid21_block_rsrvd_fix_q = frac_bSig_uid38_block_rsrvd_fix_b ELSE "0";
    fracXIsZero_uid41_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid41_block_rsrvd_fix_qi, xout => fracXIsZero_uid41_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8(DELAY,305)
    redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8 : dspba_delay
    GENERIC MAP ( width => 1, depth => 7, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid41_block_rsrvd_fix_q, xout => redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8_q, clk => clk, aclr => areset, ena => '1' );

    -- excI_bSig_uid43_block_rsrvd_fix(LOGICAL,42)@9
    excI_bSig_uid43_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist28_expXIsMax_uid40_block_rsrvd_fix_q_8_q and redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8_q);

    -- sigBBInf_uid133_block_rsrvd_fix(LOGICAL,132)@9
    sigBBInf_uid133_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist21_sigB_uid53_block_rsrvd_fix_b_8_q and excI_bSig_uid43_block_rsrvd_fix_q);

    -- fracXIsZero_uid27_block_rsrvd_fix(LOGICAL,26)@5 + 1
    fracXIsZero_uid27_block_rsrvd_fix_qi <= "1" WHEN cstZeroWF_uid21_block_rsrvd_fix_q = redist36_frac_aSig_uid24_block_rsrvd_fix_b_4_outputreg0_q ELSE "0";
    fracXIsZero_uid27_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => fracXIsZero_uid27_block_rsrvd_fix_qi, xout => fracXIsZero_uid27_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4(DELAY,312)
    redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_0 <= STD_LOGIC_VECTOR(fracXIsZero_uid27_block_rsrvd_fix_q);
            redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_1 <= redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_0;
            redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_q <= STD_LOGIC_VECTOR(redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_delay_1);
        END IF;
    END PROCESS;

    -- excI_aSig_uid29_block_rsrvd_fix(LOGICAL,28)@9
    excI_aSig_uid29_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expXIsMax_uid26_block_rsrvd_fix_q and redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_q);

    -- sigAAInf_uid134_block_rsrvd_fix(LOGICAL,133)@9
    sigAAInf_uid134_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist23_sigA_uid52_block_rsrvd_fix_b_8_q and excI_aSig_uid29_block_rsrvd_fix_q);

    -- signRInf_uid135_block_rsrvd_fix(LOGICAL,134)@9
    signRInf_uid135_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(sigAAInf_uid134_block_rsrvd_fix_q or sigBBInf_uid133_block_rsrvd_fix_q);

    -- signRInfRZRReg_uid139_block_rsrvd_fix(LOGICAL,138)@9 + 1
    signRInfRZRReg_uid139_block_rsrvd_fix_qi <= signRInf_uid135_block_rsrvd_fix_q or signRZero_uid138_block_rsrvd_fix_q or signRReg_uid132_block_rsrvd_fix_q;
    signRInfRZRReg_uid139_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => signRInfRZRReg_uid139_block_rsrvd_fix_qi, xout => signRInfRZRReg_uid139_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3(DELAY,288)
    redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(signRInfRZRReg_uid139_block_rsrvd_fix_q);
            redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_delay_0);
        END IF;
    END PROCESS;

    -- fracXIsNotZero_uid42_block_rsrvd_fix(LOGICAL,41)@9
    fracXIsNotZero_uid42_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist27_fracXIsZero_uid41_block_rsrvd_fix_q_8_q));

    -- excN_bSig_uid44_block_rsrvd_fix(LOGICAL,43)@9 + 1
    excN_bSig_uid44_block_rsrvd_fix_qi <= redist28_expXIsMax_uid40_block_rsrvd_fix_q_8_q and fracXIsNotZero_uid42_block_rsrvd_fix_q;
    excN_bSig_uid44_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excN_bSig_uid44_block_rsrvd_fix_qi, xout => excN_bSig_uid44_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist25_excN_bSig_uid44_block_rsrvd_fix_q_2(DELAY,303)
    redist25_excN_bSig_uid44_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist25_excN_bSig_uid44_block_rsrvd_fix_q_2_q <= excN_bSig_uid44_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- fracXIsNotZero_uid28_block_rsrvd_fix(LOGICAL,27)@9
    fracXIsNotZero_uid28_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (redist34_fracXIsZero_uid27_block_rsrvd_fix_q_4_q));

    -- excN_aSig_uid30_block_rsrvd_fix(LOGICAL,29)@9 + 1
    excN_aSig_uid30_block_rsrvd_fix_qi <= expXIsMax_uid26_block_rsrvd_fix_q and fracXIsNotZero_uid28_block_rsrvd_fix_q;
    excN_aSig_uid30_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excN_aSig_uid30_block_rsrvd_fix_qi, xout => excN_aSig_uid30_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist32_excN_aSig_uid30_block_rsrvd_fix_q_2(DELAY,310)
    redist32_excN_aSig_uid30_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist32_excN_aSig_uid30_block_rsrvd_fix_q_2_q <= excN_aSig_uid30_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- excRNaN2_uid126_block_rsrvd_fix(LOGICAL,125)@11
    excRNaN2_uid126_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist32_excN_aSig_uid30_block_rsrvd_fix_q_2_q or redist25_excN_bSig_uid44_block_rsrvd_fix_q_2_q);

    -- redist19_effSub_uid54_block_rsrvd_fix_q_6(DELAY,297)
    redist19_effSub_uid54_block_rsrvd_fix_q_6 : dspba_delay
    GENERIC MAP ( width => 1, depth => 6, reset_kind => "NONE", phase => 0, modulus => 1024, reset_high => '0' )
    PORT MAP ( xin => effSub_uid54_block_rsrvd_fix_q, xout => redist19_effSub_uid54_block_rsrvd_fix_q_6_q, clk => clk, aclr => areset, ena => '1' );

    -- redist26_excI_bSig_uid43_block_rsrvd_fix_q_2(DELAY,304)
    redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(excI_bSig_uid43_block_rsrvd_fix_q);
            redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- redist33_excI_aSig_uid29_block_rsrvd_fix_q_2(DELAY,311)
    redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(excI_aSig_uid29_block_rsrvd_fix_q);
            redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- excAIBISub_uid127_block_rsrvd_fix(LOGICAL,126)@11
    excAIBISub_uid127_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_q and redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_q and redist19_effSub_uid54_block_rsrvd_fix_q_6_q);

    -- excRNaN_uid128_block_rsrvd_fix(LOGICAL,127)@11 + 1
    excRNaN_uid128_block_rsrvd_fix_qi <= excAIBISub_uid127_block_rsrvd_fix_q or excRNaN2_uid126_block_rsrvd_fix_q;
    excRNaN_uid128_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => excRNaN_uid128_block_rsrvd_fix_qi, xout => excRNaN_uid128_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- invExcRNaN_uid140_block_rsrvd_fix(LOGICAL,139)@12
    invExcRNaN_uid140_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (excRNaN_uid128_block_rsrvd_fix_q));

    -- VCC(CONSTANT,1)
    VCC_q <= "1";

    -- signRPostExc_uid141_block_rsrvd_fix(LOGICAL,140)@12
    signRPostExc_uid141_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(invExcRNaN_uid140_block_rsrvd_fix_q and redist10_signRInfRZRReg_uid139_block_rsrvd_fix_q_3_q);

    -- cRBit_uid101_block_rsrvd_fix(CONSTANT,100)
    cRBit_uid101_block_rsrvd_fix_q <= "01000";

    -- leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,264)@9
    leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q(53 downto 0);
    leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_in(53 downto 0));

    -- leftShiftStage2Idx3_uid266_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,265)@9
    leftShiftStage2Idx3_uid266_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx3Rng3_uid265_fracPostNormExt_uid90_block_rsrvd_fix_b & rightShiftStage0Idx3Pad3_uid200_alignmentShifter_uid66_block_rsrvd_fix_q;

    -- leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,261)@9
    leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q(54 downto 0);
    leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_in(54 downto 0));

    -- leftShiftStage2Idx2_uid263_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,262)@9
    leftShiftStage2Idx2_uid263_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx2Rng2_uid262_fracPostNormExt_uid90_block_rsrvd_fix_b & zs_uid178_lzCountVal_uid87_block_rsrvd_fix_q;

    -- leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,258)@9
    leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q(55 downto 0);
    leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_in(55 downto 0));

    -- leftShiftStage2Idx1_uid260_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,259)@9
    leftShiftStage2Idx1_uid260_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx1Rng1_uid259_fracPostNormExt_uid90_block_rsrvd_fix_b & GND_q;

    -- leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,253)@9
    leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q(44 downto 0);
    leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_in(44 downto 0));

    -- leftShiftStage1Idx3_uid255_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,254)@9
    leftShiftStage1Idx3_uid255_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx3Rng12_uid254_fracPostNormExt_uid90_block_rsrvd_fix_b & rightShiftStage1Idx3Pad12_uid211_alignmentShifter_uid66_block_rsrvd_fix_q;

    -- leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,250)@9
    leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q(48 downto 0);
    leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_in(48 downto 0));

    -- leftShiftStage1Idx2_uid252_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,251)@9
    leftShiftStage1Idx2_uid252_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx2Rng8_uid251_fracPostNormExt_uid90_block_rsrvd_fix_b & zs_uid166_lzCountVal_uid87_block_rsrvd_fix_q;

    -- leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,247)@9
    leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_in <= leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q(52 downto 0);
    leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_in(52 downto 0));

    -- leftShiftStage1Idx1_uid249_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,248)@9
    leftShiftStage1Idx1_uid249_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx1Rng4_uid248_fracPostNormExt_uid90_block_rsrvd_fix_b & zs_uid172_lzCountVal_uid87_block_rsrvd_fix_q;

    -- leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,242)@9
    leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_in <= redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q(8 downto 0);
    leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_in(8 downto 0));

    -- leftShiftStage0Idx3_uid244_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,243)@9
    leftShiftStage0Idx3_uid244_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0Idx3Rng48_uid243_fracPostNormExt_uid90_block_rsrvd_fix_b & rightShiftStage2Idx3Pad48_uid222_alignmentShifter_uid66_block_rsrvd_fix_q;

    -- redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3(DELAY,286)
    redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_0 <= STD_LOGIC_VECTOR(vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b);
            redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_1 <= redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_0;
            redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_q <= STD_LOGIC_VECTOR(redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_delay_1);
        END IF;
    END PROCESS;

    -- leftShiftStage0Idx2_uid241_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,240)@9
    leftShiftStage0Idx2_uid241_fracPostNormExt_uid90_block_rsrvd_fix_q <= redist8_vStage_uid156_lzCountVal_uid87_block_rsrvd_fix_b_3_q & zs_uid152_lzCountVal_uid87_block_rsrvd_fix_q;

    -- leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix(BITSELECT,236)@9
    leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_in <= redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q(40 downto 0);
    leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_in(40 downto 0));

    -- leftShiftStage0Idx1_uid238_fracPostNormExt_uid90_block_rsrvd_fix(BITJOIN,237)@9
    leftShiftStage0Idx1_uid238_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0Idx1Rng16_uid237_fracPostNormExt_uid90_block_rsrvd_fix_b & zs_uid160_lzCountVal_uid87_block_rsrvd_fix_q;

    -- redist16_fracGRS_uid86_block_rsrvd_fix_q_3(DELAY,294)
    redist16_fracGRS_uid86_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(fracGRS_uid86_block_rsrvd_fix_q);
            redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_1 <= redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_0;
            redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist16_fracGRS_uid86_block_rsrvd_fix_q_3_delay_1);
        END IF;
    END PROCESS;

    -- leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix(MUX,245)@9
    leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_b;
    leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_combproc: PROCESS (leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_s, redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q, leftShiftStage0Idx1_uid238_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage0Idx2_uid241_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage0Idx3_uid244_fracPostNormExt_uid90_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q <= redist16_fracGRS_uid86_block_rsrvd_fix_q_3_q;
            WHEN "01" => leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0Idx1_uid238_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0Idx2_uid241_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0Idx3_uid244_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix(MUX,256)@9
    leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_c;
    leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_combproc: PROCESS (leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_s, leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage1Idx1_uid249_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage1Idx2_uid252_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage1Idx3_uid255_fracPostNormExt_uid90_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage0_uid246_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "01" => leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx1_uid249_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx2_uid252_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1Idx3_uid255_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged(BITSELECT,274)@9
    leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_b <= STD_LOGIC_VECTOR(redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q(5 downto 4));
    leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_c <= STD_LOGIC_VECTOR(redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q(3 downto 2));
    leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_d <= STD_LOGIC_VECTOR(redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q(1 downto 0));

    -- leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix(MUX,267)@9
    leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_s <= leftShiftStageSel0Dto4_uid245_fracPostNormExt_uid90_block_rsrvd_fix_bit_select_merged_d;
    leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_combproc: PROCESS (leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_s, leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage2Idx1_uid260_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage2Idx2_uid263_fracPostNormExt_uid90_block_rsrvd_fix_q, leftShiftStage2Idx3_uid266_fracPostNormExt_uid90_block_rsrvd_fix_q)
    BEGIN
        CASE (leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_s) IS
            WHEN "00" => leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage1_uid257_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "01" => leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx1_uid260_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "10" => leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx2_uid263_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN "11" => leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q <= leftShiftStage2Idx3_uid266_fracPostNormExt_uid90_block_rsrvd_fix_q;
            WHEN OTHERS => leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- LSB_uid99_block_rsrvd_fix(BITSELECT,98)@9
    LSB_uid99_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(4 downto 0));
    LSB_uid99_block_rsrvd_fix_b <= LSB_uid99_block_rsrvd_fix_in(4 downto 4);

    -- Guard_uid98_block_rsrvd_fix(BITSELECT,97)@9
    Guard_uid98_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(3 downto 0));
    Guard_uid98_block_rsrvd_fix_b <= Guard_uid98_block_rsrvd_fix_in(3 downto 3);

    -- Round_uid97_block_rsrvd_fix(BITSELECT,96)@9
    Round_uid97_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(2 downto 0));
    Round_uid97_block_rsrvd_fix_b <= Round_uid97_block_rsrvd_fix_in(2 downto 2);

    -- Sticky1_uid96_block_rsrvd_fix(BITSELECT,95)@9
    Sticky1_uid96_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(1 downto 0));
    Sticky1_uid96_block_rsrvd_fix_b <= Sticky1_uid96_block_rsrvd_fix_in(1 downto 1);

    -- Sticky0_uid95_block_rsrvd_fix(BITSELECT,94)@9
    Sticky0_uid95_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(0 downto 0));
    Sticky0_uid95_block_rsrvd_fix_b <= Sticky0_uid95_block_rsrvd_fix_in(0 downto 0);

    -- rndBitCond_uid100_block_rsrvd_fix(BITJOIN,99)@9
    rndBitCond_uid100_block_rsrvd_fix_q <= LSB_uid99_block_rsrvd_fix_b & Guard_uid98_block_rsrvd_fix_b & Round_uid97_block_rsrvd_fix_b & Sticky1_uid96_block_rsrvd_fix_b & Sticky0_uid95_block_rsrvd_fix_b;

    -- rBi_uid102_block_rsrvd_fix(LOGICAL,101)@9 + 1
    rBi_uid102_block_rsrvd_fix_qi <= "1" WHEN rndBitCond_uid100_block_rsrvd_fix_q = cRBit_uid101_block_rsrvd_fix_q ELSE "0";
    rBi_uid102_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => rBi_uid102_block_rsrvd_fix_qi, xout => rBi_uid102_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- roundBit_uid103_block_rsrvd_fix(LOGICAL,102)@10
    roundBit_uid103_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(not (rBi_uid102_block_rsrvd_fix_q));

    -- oneCST_uid92_block_rsrvd_fix(CONSTANT,91)
    oneCST_uid92_block_rsrvd_fix_q <= "00000000001";

    -- expInc_uid93_block_rsrvd_fix(ADD,92)@8 + 1
    expInc_uid93_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & redist37_exp_aSig_uid23_block_rsrvd_fix_b_7_mem_q);
    expInc_uid93_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("0" & oneCST_uid92_block_rsrvd_fix_q);
    expInc_uid93_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            expInc_uid93_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(expInc_uid93_block_rsrvd_fix_a) + UNSIGNED(expInc_uid93_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    expInc_uid93_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expInc_uid93_block_rsrvd_fix_o(11 downto 0));

    -- expPostNorm_uid94_block_rsrvd_fix(SUB,93)@9
    expPostNorm_uid94_block_rsrvd_fix_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & expInc_uid93_block_rsrvd_fix_q));
    expPostNorm_uid94_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0000000" & redist5_r_uid187_lzCountVal_uid87_block_rsrvd_fix_q_1_q));
    expPostNorm_uid94_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(SIGNED(expPostNorm_uid94_block_rsrvd_fix_a) - SIGNED(expPostNorm_uid94_block_rsrvd_fix_b));
    expPostNorm_uid94_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(expPostNorm_uid94_block_rsrvd_fix_o(12 downto 0));

    -- fracPostNorm_uid91_block_rsrvd_fix(BITSELECT,90)@9
    fracPostNorm_uid91_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(leftShiftStage2_uid268_fracPostNormExt_uid90_block_rsrvd_fix_q(56 downto 1));

    -- fracPostNormRndRange_uid104_block_rsrvd_fix(BITSELECT,103)@9
    fracPostNormRndRange_uid104_block_rsrvd_fix_in <= fracPostNorm_uid91_block_rsrvd_fix_b(54 downto 0);
    fracPostNormRndRange_uid104_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracPostNormRndRange_uid104_block_rsrvd_fix_in(54 downto 2));

    -- expFracR_uid105_block_rsrvd_fix(BITJOIN,104)@9
    expFracR_uid105_block_rsrvd_fix_q <= expPostNorm_uid94_block_rsrvd_fix_q & fracPostNormRndRange_uid104_block_rsrvd_fix_b;

    -- redist14_expFracR_uid105_block_rsrvd_fix_q_1(DELAY,292)
    redist14_expFracR_uid105_block_rsrvd_fix_q_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist14_expFracR_uid105_block_rsrvd_fix_q_1_q <= expFracR_uid105_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- rndExpFrac_uid106_block_rsrvd_fix(ADD,105)@10 + 1
    rndExpFrac_uid106_block_rsrvd_fix_a <= STD_LOGIC_VECTOR("0" & redist14_expFracR_uid105_block_rsrvd_fix_q_1_q);
    rndExpFrac_uid106_block_rsrvd_fix_b <= STD_LOGIC_VECTOR("000000000000000000000000000000000000000000000000000000000000000000" & roundBit_uid103_block_rsrvd_fix_q);
    rndExpFrac_uid106_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            rndExpFrac_uid106_block_rsrvd_fix_o <= STD_LOGIC_VECTOR(UNSIGNED(rndExpFrac_uid106_block_rsrvd_fix_a) + UNSIGNED(rndExpFrac_uid106_block_rsrvd_fix_b));
        END IF;
    END PROCESS;
    rndExpFrac_uid106_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rndExpFrac_uid106_block_rsrvd_fix_o(66 downto 0));

    -- expRPreExc_uid119_block_rsrvd_fix(BITSELECT,118)@11
    expRPreExc_uid119_block_rsrvd_fix_in <= rndExpFrac_uid106_block_rsrvd_fix_q(63 downto 0);
    expRPreExc_uid119_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(expRPreExc_uid119_block_rsrvd_fix_in(63 downto 53));

    -- redist12_expRPreExc_uid119_block_rsrvd_fix_b_1(DELAY,290)
    redist12_expRPreExc_uid119_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist12_expRPreExc_uid119_block_rsrvd_fix_b_1_q <= expRPreExc_uid119_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- rndExpFracOvfBits_uid111_block_rsrvd_fix(BITSELECT,110)@11
    rndExpFracOvfBits_uid111_block_rsrvd_fix_in <= rndExpFrac_uid106_block_rsrvd_fix_q(65 downto 0);
    rndExpFracOvfBits_uid111_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rndExpFracOvfBits_uid111_block_rsrvd_fix_in(65 downto 64));

    -- rOvfExtraBits_uid112_block_rsrvd_fix(LOGICAL,111)@11
    rOvfExtraBits_uid112_block_rsrvd_fix_q <= "1" WHEN rndExpFracOvfBits_uid111_block_rsrvd_fix_b = zocst_uid78_block_rsrvd_fix_q ELSE "0";

    -- wEP2AllOwE_uid107_block_rsrvd_fix(CONSTANT,106)
    wEP2AllOwE_uid107_block_rsrvd_fix_q <= "0011111111111";

    -- rndExp_uid108_block_rsrvd_fix(BITSELECT,107)@11
    rndExp_uid108_block_rsrvd_fix_in <= rndExpFrac_uid106_block_rsrvd_fix_q(65 downto 0);
    rndExp_uid108_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(rndExp_uid108_block_rsrvd_fix_in(65 downto 53));

    -- rOvfEQMax_uid109_block_rsrvd_fix(LOGICAL,108)@11
    rOvfEQMax_uid109_block_rsrvd_fix_q <= "1" WHEN rndExp_uid108_block_rsrvd_fix_b = wEP2AllOwE_uid107_block_rsrvd_fix_q ELSE "0";

    -- rOvf_uid113_block_rsrvd_fix(LOGICAL,112)@11
    rOvf_uid113_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rOvfEQMax_uid109_block_rsrvd_fix_q or rOvfExtraBits_uid112_block_rsrvd_fix_q);

    -- regInputs_uid120_block_rsrvd_fix(LOGICAL,119)@9 + 1
    regInputs_uid120_block_rsrvd_fix_qi <= excR_aSig_uid33_block_rsrvd_fix_q and excR_bSig_uid47_block_rsrvd_fix_q;
    regInputs_uid120_block_rsrvd_fix_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "NONE", phase => 0, modulus => 1, reset_high => '0' )
    PORT MAP ( xin => regInputs_uid120_block_rsrvd_fix_qi, xout => regInputs_uid120_block_rsrvd_fix_q, clk => clk, aclr => areset, ena => '1' );

    -- redist11_regInputs_uid120_block_rsrvd_fix_q_2(DELAY,289)
    redist11_regInputs_uid120_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist11_regInputs_uid120_block_rsrvd_fix_q_2_q <= regInputs_uid120_block_rsrvd_fix_q;
        END IF;
    END PROCESS;

    -- rInfOvf_uid123_block_rsrvd_fix(LOGICAL,122)@11
    rInfOvf_uid123_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(redist11_regInputs_uid120_block_rsrvd_fix_q_2_q and rOvf_uid113_block_rsrvd_fix_q);

    -- excRInfVInC_uid124_block_rsrvd_fix(BITJOIN,123)@11
    excRInfVInC_uid124_block_rsrvd_fix_q <= rInfOvf_uid123_block_rsrvd_fix_q & redist25_excN_bSig_uid44_block_rsrvd_fix_q_2_q & redist32_excN_aSig_uid30_block_rsrvd_fix_q_2_q & redist26_excI_bSig_uid43_block_rsrvd_fix_q_2_q & redist33_excI_aSig_uid29_block_rsrvd_fix_q_2_q & redist19_effSub_uid54_block_rsrvd_fix_q_6_q;

    -- excRInf_uid125_block_rsrvd_fix(LOOKUP,124)@11 + 1
    excRInf_uid125_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (excRInfVInC_uid124_block_rsrvd_fix_q) IS
                WHEN "000000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "000001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "000010" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "000011" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "000100" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "000101" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "000110" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "000111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "001111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "010111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "011111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100000" => excRInf_uid125_block_rsrvd_fix_q <= "1";
                WHEN "100001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "100111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "101111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "110111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111000" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111001" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111010" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111011" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111100" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111101" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111110" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN "111111" => excRInf_uid125_block_rsrvd_fix_q <= "0";
                WHEN OTHERS => -- unreachable
                               excRInf_uid125_block_rsrvd_fix_q <= (others => '-');
            END CASE;
        END IF;
    END PROCESS;

    -- redist15_aMinusA_uid89_block_rsrvd_fix_q_2(DELAY,293)
    redist15_aMinusA_uid89_block_rsrvd_fix_q_2_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist15_aMinusA_uid89_block_rsrvd_fix_q_2_delay_0 <= STD_LOGIC_VECTOR(aMinusA_uid89_block_rsrvd_fix_q);
            redist15_aMinusA_uid89_block_rsrvd_fix_q_2_q <= STD_LOGIC_VECTOR(redist15_aMinusA_uid89_block_rsrvd_fix_q_2_delay_0);
        END IF;
    END PROCESS;

    -- rUdfExtraBit_uid116_block_rsrvd_fix(BITSELECT,115)@11
    rUdfExtraBit_uid116_block_rsrvd_fix_in <= STD_LOGIC_VECTOR(rndExpFrac_uid106_block_rsrvd_fix_q(65 downto 0));
    rUdfExtraBit_uid116_block_rsrvd_fix_b <= rUdfExtraBit_uid116_block_rsrvd_fix_in(65 downto 65);

    -- wEP2AllZ_uid114_block_rsrvd_fix(CONSTANT,113)
    wEP2AllZ_uid114_block_rsrvd_fix_q <= "0000000000000";

    -- rUdfEQMin_uid115_block_rsrvd_fix(LOGICAL,114)@11
    rUdfEQMin_uid115_block_rsrvd_fix_q <= "1" WHEN rndExp_uid108_block_rsrvd_fix_b = wEP2AllZ_uid114_block_rsrvd_fix_q ELSE "0";

    -- rUdf_uid117_block_rsrvd_fix(LOGICAL,116)@11
    rUdf_uid117_block_rsrvd_fix_q <= STD_LOGIC_VECTOR(rUdfEQMin_uid115_block_rsrvd_fix_q or rUdfExtraBit_uid116_block_rsrvd_fix_b);

    -- redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10(DELAY,309)
    redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_delay_0 <= STD_LOGIC_VECTOR(redist30_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_8_q);
            redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_q <= STD_LOGIC_VECTOR(redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_delay_0);
        END IF;
    END PROCESS;

    -- redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3(DELAY,313)
    redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_delay_0 <= STD_LOGIC_VECTOR(excZ_aSig_uid18_uid25_block_rsrvd_fix_q);
            redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_q <= STD_LOGIC_VECTOR(redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_delay_0);
        END IF;
    END PROCESS;

    -- excRZeroVInC_uid121_block_rsrvd_fix(BITJOIN,120)@11
    excRZeroVInC_uid121_block_rsrvd_fix_q <= redist15_aMinusA_uid89_block_rsrvd_fix_q_2_q & rUdf_uid117_block_rsrvd_fix_q & redist11_regInputs_uid120_block_rsrvd_fix_q_2_q & redist31_excZ_bSig_uid19_uid39_block_rsrvd_fix_q_10_q & redist35_excZ_aSig_uid18_uid25_block_rsrvd_fix_q_3_q;

    -- excRZero_uid122_block_rsrvd_fix(LOOKUP,121)@11 + 1
    excRZero_uid122_block_rsrvd_fix_clkproc: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            CASE (excRZeroVInC_uid121_block_rsrvd_fix_q) IS
                WHEN "00000" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00001" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00010" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00011" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "00100" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00101" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00110" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "00111" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01000" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01001" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01010" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01011" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "01100" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "01101" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01110" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "01111" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10000" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10001" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10010" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10011" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "10100" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "10101" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10110" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "10111" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11000" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11001" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11010" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11011" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "11100" => excRZero_uid122_block_rsrvd_fix_q <= "1";
                WHEN "11101" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11110" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN "11111" => excRZero_uid122_block_rsrvd_fix_q <= "0";
                WHEN OTHERS => -- unreachable
                               excRZero_uid122_block_rsrvd_fix_q <= (others => '-');
            END CASE;
        END IF;
    END PROCESS;

    -- concExc_uid129_block_rsrvd_fix(BITJOIN,128)@12
    concExc_uid129_block_rsrvd_fix_q <= excRNaN_uid128_block_rsrvd_fix_q & excRInf_uid125_block_rsrvd_fix_q & excRZero_uid122_block_rsrvd_fix_q;

    -- excREnc_uid130_block_rsrvd_fix(LOOKUP,129)@12
    excREnc_uid130_block_rsrvd_fix_combproc: PROCESS (concExc_uid129_block_rsrvd_fix_q)
    BEGIN
        -- Begin reserved scope level
        CASE (concExc_uid129_block_rsrvd_fix_q) IS
            WHEN "000" => excREnc_uid130_block_rsrvd_fix_q <= "01";
            WHEN "001" => excREnc_uid130_block_rsrvd_fix_q <= "00";
            WHEN "010" => excREnc_uid130_block_rsrvd_fix_q <= "10";
            WHEN "011" => excREnc_uid130_block_rsrvd_fix_q <= "10";
            WHEN "100" => excREnc_uid130_block_rsrvd_fix_q <= "11";
            WHEN "101" => excREnc_uid130_block_rsrvd_fix_q <= "11";
            WHEN "110" => excREnc_uid130_block_rsrvd_fix_q <= "11";
            WHEN "111" => excREnc_uid130_block_rsrvd_fix_q <= "11";
            WHEN OTHERS => -- unreachable
                           excREnc_uid130_block_rsrvd_fix_q <= (others => '-');
        END CASE;
        -- End reserved scope level
    END PROCESS;

    -- expRPostExc_uid149_block_rsrvd_fix(MUX,148)@12
    expRPostExc_uid149_block_rsrvd_fix_s <= excREnc_uid130_block_rsrvd_fix_q;
    expRPostExc_uid149_block_rsrvd_fix_combproc: PROCESS (expRPostExc_uid149_block_rsrvd_fix_s, cstAllZWE_uid22_block_rsrvd_fix_q, redist12_expRPreExc_uid119_block_rsrvd_fix_b_1_q, cstAllOWE_uid20_block_rsrvd_fix_q)
    BEGIN
        CASE (expRPostExc_uid149_block_rsrvd_fix_s) IS
            WHEN "00" => expRPostExc_uid149_block_rsrvd_fix_q <= cstAllZWE_uid22_block_rsrvd_fix_q;
            WHEN "01" => expRPostExc_uid149_block_rsrvd_fix_q <= redist12_expRPreExc_uid119_block_rsrvd_fix_b_1_q;
            WHEN "10" => expRPostExc_uid149_block_rsrvd_fix_q <= cstAllOWE_uid20_block_rsrvd_fix_q;
            WHEN "11" => expRPostExc_uid149_block_rsrvd_fix_q <= cstAllOWE_uid20_block_rsrvd_fix_q;
            WHEN OTHERS => expRPostExc_uid149_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- oneFracRPostExc2_uid142_block_rsrvd_fix(CONSTANT,141)
    oneFracRPostExc2_uid142_block_rsrvd_fix_q <= "0000000000000000000000000000000000000000000000000001";

    -- fracRPreExc_uid118_block_rsrvd_fix(BITSELECT,117)@11
    fracRPreExc_uid118_block_rsrvd_fix_in <= rndExpFrac_uid106_block_rsrvd_fix_q(52 downto 0);
    fracRPreExc_uid118_block_rsrvd_fix_b <= STD_LOGIC_VECTOR(fracRPreExc_uid118_block_rsrvd_fix_in(52 downto 1));

    -- redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1(DELAY,291)
    redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1_clkproc_0: PROCESS (clk)
    BEGIN
        IF (clk'EVENT AND clk = '1') THEN
            redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1_q <= fracRPreExc_uid118_block_rsrvd_fix_b;
        END IF;
    END PROCESS;

    -- fracRPostExc_uid145_block_rsrvd_fix(MUX,144)@12
    fracRPostExc_uid145_block_rsrvd_fix_s <= excREnc_uid130_block_rsrvd_fix_q;
    fracRPostExc_uid145_block_rsrvd_fix_combproc: PROCESS (fracRPostExc_uid145_block_rsrvd_fix_s, cstZeroWF_uid21_block_rsrvd_fix_q, redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1_q, oneFracRPostExc2_uid142_block_rsrvd_fix_q)
    BEGIN
        CASE (fracRPostExc_uid145_block_rsrvd_fix_s) IS
            WHEN "00" => fracRPostExc_uid145_block_rsrvd_fix_q <= cstZeroWF_uid21_block_rsrvd_fix_q;
            WHEN "01" => fracRPostExc_uid145_block_rsrvd_fix_q <= redist13_fracRPreExc_uid118_block_rsrvd_fix_b_1_q;
            WHEN "10" => fracRPostExc_uid145_block_rsrvd_fix_q <= cstZeroWF_uid21_block_rsrvd_fix_q;
            WHEN "11" => fracRPostExc_uid145_block_rsrvd_fix_q <= oneFracRPostExc2_uid142_block_rsrvd_fix_q;
            WHEN OTHERS => fracRPostExc_uid145_block_rsrvd_fix_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- R_uid150_block_rsrvd_fix(BITJOIN,149)@12
    R_uid150_block_rsrvd_fix_q <= signRPostExc_uid141_block_rsrvd_fix_q & expRPostExc_uid149_block_rsrvd_fix_q & fracRPostExc_uid145_block_rsrvd_fix_q;

    -- out_primWireOut(GPOUT,5)@12
    out_primWireOut <= R_uid150_block_rsrvd_fix_q;

END normal;
