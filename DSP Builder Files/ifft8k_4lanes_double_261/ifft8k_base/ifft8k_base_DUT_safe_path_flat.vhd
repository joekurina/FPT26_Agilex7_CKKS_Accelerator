-- safe_path for ifft8k_base_DUT given rtl dir is ./ifft8k_4lanes_double_261 (flat)
LIBRARY ieee;
USE ieee.std_logic_1164.all;

PACKAGE ifft8k_base_DUT_safe_path is
	FUNCTION safe_path( path: string ) RETURN string;
END ifft8k_base_DUT_safe_path;

PACKAGE body ifft8k_base_DUT_safe_path IS
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
END ifft8k_base_DUT_safe_path;
