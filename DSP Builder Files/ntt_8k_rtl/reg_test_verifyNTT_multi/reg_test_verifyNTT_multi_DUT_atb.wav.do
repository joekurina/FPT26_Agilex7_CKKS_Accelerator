onerror {resume}

# obtain Modelsim version and extract the NN.Nc part after vsim
quietly set vsim_ver [regexp -inline {vsim (\d+\.\d+)(\w?)} [vsim -version]]
quietly set has_fixpt_radix 0
if {[lindex $vsim_ver 1] == 10.2} {
    if {[lindex $vsim_ver 2] >= "d"} {
        quietly set has_fixpt_radix 1
    }
} elseif {[lindex $vsim_ver 1] > 10.2} {
    quietly set has_fixpt_radix 1
}

proc add_fixpt_wave {name width frac_width signed} {
    global has_fixpt_radix
    if {$frac_width > 0 && $has_fixpt_radix} {
        set type "[string index $signed 0]fix${width}_En${frac_width}"
        if {[lsearch [radix names] $type] < 0} {
            if {$signed == "signed"} {
                radix define $type -fixed -signed -fraction $frac_width
            } else {
                radix define $type -fixed -fraction $frac_width
            }
        }
        add wave -noupdate -format Literal -radix $type $name
    } else {
        add wave -noupdate -format Literal -radix $signed $name
    }
}

add wave -noupdate -divider {Input Ports}
add wave -noupdate -format Logic /reg_test_verifyNTT_multi_DUT_atb/dut/clk
add wave -noupdate -format Logic /reg_test_verifyNTT_multi_DUT_atb/dut/areset
add wave -noupdate -format Logical /reg_test_verifyNTT_multi_DUT_atb/sim/In_V_s_stm
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/In_C_s_stm 8 0 unsigned
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/X_in_0_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/X_in_1_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/X_in_2_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/X_in_3_stm 64 0 signed
add wave -noupdate -divider {Output Ports}
add wave -noupdate -format Logical /reg_test_verifyNTT_multi_DUT_atb/dut/Out_V_s
add wave -noupdate -format Logical /reg_test_verifyNTT_multi_DUT_atb/sim/Out_V_s_stm
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/dut/Out_C_s 8 0 unsigned
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/Out_C_s_stm 8 0 unsigned
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/dut/Out_Q_0 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/Out_Q_0_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/dut/Out_Q_1 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/Out_Q_1_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/dut/Out_Q_2 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/Out_Q_2_stm 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/dut/Out_Q_3 64 0 signed
add_fixpt_wave /reg_test_verifyNTT_multi_DUT_atb/sim/Out_Q_3_stm 64 0 signed
TreeUpdate [SetDefaultTree]
