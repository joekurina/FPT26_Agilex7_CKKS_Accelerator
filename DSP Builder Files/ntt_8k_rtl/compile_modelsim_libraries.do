echo "Starting library check for Agilex 7..."
quietly set start_time [clock milliseconds]
clock format [clock seconds] -format "%Y-%m-%d %H:%M:%S"
if ![info exists base_dir] {
quietly set base_dir ./ntt_8k_rtl
}
echo "Current directory: [pwd]"
echo "Changing directory to '$base_dir'"
quietly set orig_dir [pwd]
quietly set ll ""
quietly set script_success 0
quietly cd $base_dir
if [info exists ::env(QUARTUS_ROOTDIR_OVERRIDE)] {
    printenv QUARTUS_ROOTDIR_OVERRIDE
    quietly set quartus_dir $::env(QUARTUS_ROOTDIR_OVERRIDE)
} else {
    quietly set quartus_dir $::env(QUARTUS_ROOTDIR)
}


proc checkDepends {dst src} {
    if {! [file exists $dst]} { return 1 }
    if {[file mtime $dst] < [file mtime $src]} { return 1 }
    return 0
}

quietly set compile_lib(altera_mf_ver) 0
quietly set using_lib(altera_mf_ver) 0
if {$script_success == 0} {
    onerror {
        echo "Library altera_mf_ver not found, compiling from source..."
        quietly set compile_lib(altera_mf_ver) 1
        resume
    }
    echo "Checking if library altera_mf_ver exists..."
    quietly vdir -lib altera_mf_ver
    quietly set using_lib(altera_mf_ver) 1
    if {[file exist altera_mf_ver/_info]} {
        if {[checkDepends altera_mf_ver/_info "$quartus_dir/eda/sim_lib/altera_mf.v"]        } {
            echo "Library altera_mf_ver out of date, removing old library and recompiling from source..."
            vdel -all -lib altera_mf_ver
            quietly set compile_lib(altera_mf_ver) 1
            quietly set using_lib(altera_mf_ver) 0
        }
    }
}
onerror {
    echo "Error compiling library altera_mf_ver. Please compile library manually."
    vmap -del altera_mf_ver
    vdel -all -lib altera_mf_ver
}
if {$compile_lib(altera_mf_ver)} {
    if {[file exist $quartus_dir/eda/sim_lib/altera_mf.v]} {
        vlib altera_mf_ver
        vmap altera_mf_ver altera_mf_ver
        vlog -quiet -work altera_mf_ver "$quartus_dir/eda/sim_lib/altera_mf.v"
        quietly set using_lib(altera_mf_ver) 1
    } else {
        echo "Cannot find source files to compile library altera_mf_ver."    }
}
if {$using_lib(altera_mf_ver)} {
    quietly set ll "-L altera_mf_ver $ll"
}
quietly set compile_lib(altera_lnsim) 0
quietly set using_lib(altera_lnsim) 0
if {$script_success == 0} {
    onerror {
        echo "Library altera_lnsim not found, compiling from source..."
        quietly set compile_lib(altera_lnsim) 1
        resume
    }
    echo "Checking if library altera_lnsim exists..."
    quietly vdir -lib altera_lnsim
    quietly set using_lib(altera_lnsim) 1
    if {[file exist altera_lnsim/_info]} {
        if {[checkDepends altera_lnsim/_info "$quartus_dir/eda/sim_lib/altera_lnsim_components.vhd"] || [checkDepends altera_lnsim/_info "$quartus_dir/eda/sim_lib/altera_lnsim.sv"]        } {
            echo "Library altera_lnsim out of date, removing old library and recompiling from source..."
            vdel -all -lib altera_lnsim
            quietly set compile_lib(altera_lnsim) 1
            quietly set using_lib(altera_lnsim) 0
        }
    }
}
onerror {
    echo "Error compiling library altera_lnsim. Please compile library manually."
    vmap -del altera_lnsim
    vdel -all -lib altera_lnsim
}
if {$compile_lib(altera_lnsim)} {
    if {[file exist $quartus_dir/eda/sim_lib/altera_lnsim_components.vhd] && [file exist $quartus_dir/eda/sim_lib/altera_lnsim.sv]} {
        vlib altera_lnsim
        vmap altera_lnsim altera_lnsim
        vcom -93 -quiet -work altera_lnsim "$quartus_dir/eda/sim_lib/altera_lnsim_components.vhd"
        vlog -sv -quiet -work altera_lnsim "$quartus_dir/eda/sim_lib/altera_lnsim.sv"
        quietly set using_lib(altera_lnsim) 1
    } else {
        echo "Cannot find source files to compile library altera_lnsim."    }
}
if {$using_lib(altera_lnsim)} {
    quietly set ll "-L altera_lnsim $ll"
}
quietly set compile_lib(tennm) 0
quietly set using_lib(tennm) 0
if {$script_success == 0} {
    onerror {
        echo "Library tennm not found, compiling from source..."
        quietly set compile_lib(tennm) 1
        resume
    }
    echo "Checking if library tennm exists..."
    quietly vdir -lib tennm
    quietly set using_lib(tennm) 1
    if {[file exist tennm/_info]} {
        if {[checkDepends tennm/_info "$quartus_dir/eda/sim_lib/tennm_atoms.vhd"] || [checkDepends tennm/_info "$quartus_dir/eda/sim_lib/tennm_components.vhd"] || [checkDepends tennm/_info "$quartus_dir/eda/sim_lib/mentor/tennm_atoms_ncrypt.sv"]        } {
            echo "Library tennm out of date, removing old library and recompiling from source..."
            vdel -all -lib tennm
            quietly set compile_lib(tennm) 1
            quietly set using_lib(tennm) 0
        }
    }
}
onerror {
    echo "Error compiling library tennm. Please compile library manually."
    vmap -del tennm
    vdel -all -lib tennm
}
if {$compile_lib(tennm)} {
    if {[file exist $quartus_dir/eda/sim_lib/tennm_atoms.vhd] && [file exist $quartus_dir/eda/sim_lib/tennm_components.vhd] && [file exist $quartus_dir/eda/sim_lib/mentor/tennm_atoms_ncrypt.sv]} {
        vlib tennm
        vmap tennm tennm
        vcom -93 -quiet -work tennm "$quartus_dir/eda/sim_lib/tennm_atoms.vhd"
        vcom -93 -quiet -work tennm "$quartus_dir/eda/sim_lib/tennm_components.vhd"
        vlog -sv -quiet -work tennm "$quartus_dir/eda/sim_lib/mentor/tennm_atoms_ncrypt.sv"
        quietly set using_lib(tennm) 1
    } else {
        echo "Cannot find source files to compile library tennm."    }
}
if {$using_lib(tennm)} {
    quietly set ll "-L tennm $ll"
}
quietly cd $orig_dir
echo "Finished library checks."
quietly set elapsed_time [expr {[clock milliseconds] - $start_time}]
echo "Elapsed time: $elapsed_time ms"
