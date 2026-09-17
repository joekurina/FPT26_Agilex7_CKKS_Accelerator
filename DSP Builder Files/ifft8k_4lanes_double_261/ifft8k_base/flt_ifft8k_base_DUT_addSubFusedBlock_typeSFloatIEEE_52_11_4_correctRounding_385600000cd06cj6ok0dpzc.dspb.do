# This is the Run ModelSim file list for 'flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc'

if {![info exist use_own_safe_path] || ![string equal -nocase $use_own_safe_path true]} {
    vcom -93 -quiet $base_dir/ifft8k_base/ifft8k_base_DUT_safe_path_msim.vhd
}
vcom -93 -quiet $base_dir/ifft8k_base/flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc.vhd
