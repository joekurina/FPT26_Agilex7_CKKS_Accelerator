-- safe_path for reg_test_verifyNTT_multi_DUT given rtl dir is ./ntt_8k_rtl (quartus)
LIBRARY ieee;
USE ieee.std_logic_1164.all;

PACKAGE reg_test_verifyNTT_multi_DUT_safe_path is
	FUNCTION safe_path( path: string ) RETURN string;
END reg_test_verifyNTT_multi_DUT_safe_path;

PACKAGE body reg_test_verifyNTT_multi_DUT_safe_path IS
	FUNCTION safe_path( path: string )
		RETURN string IS
	BEGIN
		return string'("./ntt_8k_rtl/") & path;
	END FUNCTION safe_path;
END reg_test_verifyNTT_multi_DUT_safe_path;
