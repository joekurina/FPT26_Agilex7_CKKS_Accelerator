// safe_path_ver for reg_test_verifyNTT_multi_DUT given rtl dir is ./ntt_8k_rtl (flat)

package reg_test_verifyNTT_multi_DUT_safe_path_ver;

    typedef logic[8*512-1:0] mystring;
    function mystring safe_path_ver(mystring path);
        safe_path_ver = path;
        for (int i =0; i < 4096; i = i+8 ) begin
            if( path[i+:8] == "/") begin
                for (int j = i; j < 4096; j = j+8 ) begin
                    safe_path_ver[j+:8] = 0;
                end
                return safe_path_ver;
           end
        end
        return safe_path_ver;
    endfunction

endpackage
