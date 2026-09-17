// safe_path_ver for reg_test_verifyNTT_multi_DUT given rtl dir is ./ntt_8k_rtl (modelsim)

package reg_test_verifyNTT_multi_DUT_safe_path_ver;

    typedef logic[8*512-1:0] mystring;
    function mystring safe_path_ver(mystring path);
                safe_path_ver = path;

    endfunction

endpackage
