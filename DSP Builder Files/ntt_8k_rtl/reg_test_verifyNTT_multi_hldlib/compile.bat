@echo off
:: Read more: https://docs.altera.com/r/docs/683846/current
fpga_crossgen -Xsv -Xsv the_nwc_8k_ntt.xml --cpp_model the_nwc_8k_ntt.cpp -o the_nwc_8k_ntt.obj -w -I. -I../reg_test_verifyNTT_multi/cmodel -DFPGA_EMULATOR -DCSL_SYCL
if %ERRORLEVEL% NEQ 0 echo "Error: fpga_crossgen failed" && exit /B %ERRORLEVEL%
:: The command below can be modified as needed if combining multiple object files into a single library.
fpga_libtool the_nwc_8k_ntt.obj --create the_nwc_8k_ntt.lib
if %ERRORLEVEL% NEQ 0 echo "Error: fpga_libtool failed" && exit /B %ERRORLEVEL%
