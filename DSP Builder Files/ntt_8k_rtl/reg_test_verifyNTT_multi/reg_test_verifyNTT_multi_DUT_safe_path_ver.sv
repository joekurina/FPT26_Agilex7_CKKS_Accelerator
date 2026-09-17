// safe_path_ver for reg_test_verifyNTT_multi_DUT given rtl dir is ./ntt_8k_rtl (quartus)

package reg_test_verifyNTT_multi_DUT_safe_path_ver;

    typedef logic[8*512-1:0] mystring;
    function mystring safe_path_ver(mystring path);
        `ifndef SYNTHESIS
            safe_path_ver = path;
            for(int i=0; i < 4096-$bits("./ntt_8k_rtl/"); i = i+8) begin
               if(path[i+:8] == 0) begin
                  safe_path_ver[i+:$bits("./ntt_8k_rtl/")] = "./ntt_8k_rtl/";
                  break;
               end
            end
        `else
            safe_path_ver = path;
        `endif

    endfunction

endpackage
