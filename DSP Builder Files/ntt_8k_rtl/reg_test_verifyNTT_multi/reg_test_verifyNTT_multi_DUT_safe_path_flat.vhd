-- safe_path for reg_test_verifyNTT_multi_DUT given rtl dir is ./ntt_8k_rtl (flat)
LIBRARY ieee;
USE ieee.std_logic_1164.all;

PACKAGE reg_test_verifyNTT_multi_DUT_safe_path is
	FUNCTION safe_path( path: string ) RETURN string;
END reg_test_verifyNTT_multi_DUT_safe_path;

PACKAGE body reg_test_verifyNTT_multi_DUT_safe_path IS
	FUNCTION safe_path( path: string )
		RETURN string IS
	BEGIN
		FOR i IN path'reverse_range loop
			IF (path(i) = '/') THEN
				RETURN path(i+1 to path'right);
			END IF;
		END LOOP;
		RETURN path;
	END FUNCTION safe_path;
END reg_test_verifyNTT_multi_DUT_safe_path;
