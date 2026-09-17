# pass in -Gquit_at_end=true to make vsim call exit at the end. Useful for running standalone.
quietly set quit_at_end 0
if {[lsearch $argv -Gquit_at_end=true] != -1} {
    quietly set quit_at_end 1
}

if {$argc > 0} {
    quietly set base_dir $1
} else {
    quietly set base_dir "././ntt_8k_rtl"
    echo The current directory is: [pwd]
}
quietly set base_dir [file normalize $base_dir]
echo Creating the project under $base_dir

do $base_dir/compile_modelsim_libraries.do
onerror {resume}

if { [string compare [project env] ""] != 0 } {
    quit -sim
    project close
}

if {! [file exists $base_dir/reg_test_verifyNTT_multi_DUT]} {
    file delete -force $base_dir/reg_test_verifyNTT_multi_DUT
}

project new $base_dir reg_test_verifyNTT_multi_DUT
if {! [file exists $base_dir/work/_info]} {
    file delete -force $base_dir/work
    vlib work
}
quietly vmap work $base_dir/work

do "$base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_fpc.do"


quietly set vcomfailed 0
onerror {
    quietly set vcomfailed 1
    resume
}

project addfile $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_safe_path_msim_ver.sv systemverilog
project addfile $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_safe_path_msim.vhd vhdl
project addfile $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT.sv systemverilog
puts {Note: Process variables may be optimized out of top-level testbench. Re-compile with the following command to disable optimizations:}
puts {vcom -quiet -O0 $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_atb.vhd}
project addfile $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_atb.vhd vhdl
project addfile $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_stm.vhd vhdl
project calculateorder

onerror {resume}

proc report_mismatch {signal cycle} {
    puts "Mismatch in ${signal} at system clock cycle ${cycle}"
    set modelsimvalue [examine ${signal}_dut];
    set stmvalue [examine ${signal}_stm];
    puts "\t${signal} (ModelSim):\t${modelsimvalue}"
    puts "\t${signal} (Simulink):\t${stmvalue}"
}

if {$vcomfailed == 0} {
    onbreak {
        quietly set my_tb [string trim [tb]];
        quietly set regOK [regexp {(.*) ([0-9]+) ([\[address]*) ([.]*)} $my_tb \ match atbfile linenum ignore_this];
        if {$regOK == 1} {
            quietly set simtime [expr $now - 200];
            quietly set cyclenum [expr int($simtime / 1818.181818)];
            if { [catch {exa mismatch_Out_V_s} mismatch] == 0 && $mismatch } {
                report_mismatch Out_V_s $cyclenum
            }
            if { [catch {exa mismatch_Out_C_s} mismatch] == 0 && $mismatch } {
                report_mismatch Out_C_s $cyclenum
            }
            if { [catch {exa mismatch_Out_Q_0} mismatch] == 0 && $mismatch } {
                report_mismatch Out_Q_0 $cyclenum
            }
            if { [catch {exa mismatch_Out_Q_1} mismatch] == 0 && $mismatch } {
                report_mismatch Out_Q_1 $cyclenum
            }
            if { [catch {exa mismatch_Out_Q_2} mismatch] == 0 && $mismatch } {
                report_mismatch Out_Q_2 $cyclenum
            }
            if { [catch {exa mismatch_Out_Q_3} mismatch] == 0 && $mismatch } {
                report_mismatch Out_Q_3 $cyclenum
            }
        } else {
            puts "Signal mismatch detected at $my_tb";
        }
        if {$quit_at_end == 1} {
            quit -code 1;
        }
    }
    eval vsim -quiet -suppress 14408 -error 3473 -msgmode both -voptargs="+acc" -t ps reg_test_verifyNTT_multi_DUT_atb $ll
    do $base_dir/reg_test_verifyNTT_multi/reg_test_verifyNTT_multi_DUT_atb.wav.do
# Disable some warnings that occur at the very start of simulation
    quietly set StdArithNoWarnings 1
    run 0ns
    quietly set StdArithNoWarnings 0
    run -all
} else {
    echo At least one module failed to compile, not starting simulation
}

if {$quit_at_end == 1} {
    exit
}
