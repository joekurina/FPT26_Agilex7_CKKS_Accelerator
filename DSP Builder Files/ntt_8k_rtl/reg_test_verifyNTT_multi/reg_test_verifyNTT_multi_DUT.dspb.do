# This is the Run ModelSim file list for 'reg_test_verifyNTT_multi_DUT'

if {![info exist use_own_safe_path] || ![string equal -nocase $use_own_safe_path true]} {
    vlog -sv -quiet $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_safe_path_msim_ver.sv
}
if {![info exist use_own_safe_path] || ![string equal -nocase $use_own_safe_path true]} {
    vcom -93 -quiet $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_safe_path_msim.vhd
}
vlog -sv -quiet $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT.sv
