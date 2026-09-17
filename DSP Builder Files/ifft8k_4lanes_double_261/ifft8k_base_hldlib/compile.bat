@echo off
:: Read more: https://www.intel.com/content/www/us/en/programmable/documentation/mwh1391807965224.html#owr1568230510943
fpga_crossgen -Xsv -Xsv fhe_ifft_8k_4lanes_double_261.xml --cpp_model fhe_ifft_8k_4lanes_double_261.cpp -o fhe_ifft_8k_4lanes_double_261.obj -w -I. -I../ifft8k_base/cmodel -DFPGA_EMULATOR -DCSL_SYCL
if %ERRORLEVEL% NEQ 0 echo "Error: fpga_crossgen failed" && exit /B %ERRORLEVEL%
:: The command below can be modified as needed if combining multiple object files into a single library.
fpga_libtool fhe_ifft_8k_4lanes_double_261.obj --create fhe_ifft_8k_4lanes_double_261.lib
if %ERRORLEVEL% NEQ 0 echo "Error: fpga_libtool failed" && exit /B %ERRORLEVEL%
