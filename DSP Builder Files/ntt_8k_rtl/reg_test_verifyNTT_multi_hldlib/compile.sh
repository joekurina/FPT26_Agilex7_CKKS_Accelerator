#!/bin/sh
check_error() {
    result=$?
    if [ $result -ne 0 ]; then
        echo "Error: $1"
        exit $result
    fi
}

# Read more: https://docs.altera.com/r/docs/683846/current
fpga_crossgen -Xsv -Xsv the_nwc_8k_ntt.xml --cpp_model the_nwc_8k_ntt.cpp -o the_nwc_8k_ntt.o -w -I. -I../reg_test_verifyNTT_multi/cmodel -DFPGA_EMULATOR -DCSL_SYCL
check_error "fpga_crossgen command failed"
# The command below can be modified as needed if combining multiple object files into a single library.
fpga_libtool the_nwc_8k_ntt.o --create the_nwc_8k_ntt.a
check_error "fpga_libtool command failed"
