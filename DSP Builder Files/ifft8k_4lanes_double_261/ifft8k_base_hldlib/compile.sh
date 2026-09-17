#!/bin/sh
check_error() {
    result=$?
    if [ $result -ne 0 ]; then
        echo "Error: $1"
        exit $result
    fi
}

# Read more: https://www.intel.com/content/www/us/en/programmable/documentation/mwh1391807965224.html#owr1568230510943
fpga_crossgen -Xsv -Xsv fhe_ifft_8k_4lanes_double_261.xml --cpp_model fhe_ifft_8k_4lanes_double_261.cpp -o fhe_ifft_8k_4lanes_double_261.o -w -I. -I../ifft8k_base/cmodel -DFPGA_EMULATOR -DCSL_SYCL
check_error "fpga_crossgen command failed"
# The command below can be modified as needed if combining multiple object files into a single library.
fpga_libtool fhe_ifft_8k_4lanes_double_261.o --create fhe_ifft_8k_4lanes_double_261.a
check_error "fpga_libtool command failed"
