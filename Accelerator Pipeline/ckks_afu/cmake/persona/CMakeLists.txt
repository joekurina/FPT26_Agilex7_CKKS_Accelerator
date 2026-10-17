# Native PR-persona stages using an existing OFS static FIM export and AHLS IP.
# LANGUAGES NONE keeps this entry point focused on native tool commands.
cmake_minimum_required(VERSION 3.20)
project(ckks_native_persona LANGUAGES NONE)

# Caller-selected tool, export, generated-IP, and prepared-project locations.
set(QUARTUS_ROOT "/opt/altera/26.1.1/quartus" CACHE PATH "Quartus Pro 26.1.1 installation")
set(CKKS_HLS_PROJECT "" CACHE PATH "Generated ckks_pipeline.report.prj")
set(OFS_PLATFORM_LIB "" CACHE PATH "Matching OFS 2026.1-1 export hw/lib")
set(AFU_SOURCES "" CACHE FILEPATH "Prepared CKKS AFU source list; generated from the current sources when empty")
set(PERSONA_TARGET "" CACHE PATH "New afu_synth_setup output directory")
set(PERSONA_PROJECT "" CACHE PATH "Prepared native persona synthesis directory")
# Setup prepares a new project. Implementation uses an already-prepared one.
set(CKKS_NATIVE_PHASE "setup" CACHE STRING "Native stage: setup or implementation")
set_property(CACHE CKKS_NATIVE_PHASE PROPERTY STRINGS setup implementation)

# Check absolute input paths and their expected file/directory kind at configure time.
function(require_input name kind)
    if(NOT IS_ABSOLUTE "${${name}}" OR NOT EXISTS "${${name}}")
        message(FATAL_ERROR "${name} must name an existing absolute ${kind}")
    endif()
    if(kind STREQUAL "directory" AND NOT IS_DIRECTORY "${${name}}")
        message(FATAL_ERROR "${name} is not a directory")
    elseif(kind STREQUAL "file" AND IS_DIRECTORY "${${name}}")
        message(FATAL_ERROR "${name} is not a file")
    endif()
endfunction()
require_input(QUARTUS_ROOT directory)

# Prepare the native source list unless the caller supplies an explicit list.
if(CKKS_NATIVE_PHASE STREQUAL "setup")
    require_input(OFS_PLATFORM_LIB directory)
    if(NOT AFU_SOURCES)
        require_input(CKKS_HLS_PROJECT directory)
        # Include the generated arithmetic component through its QIP dependency list.
        set(CKKS_HLS_QIP "${CKKS_HLS_PROJECT}/kernel_system.qip")
        require_input(CKKS_HLS_QIP file)
        get_filename_component(CKKS_APP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
        set(AFU_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/ckks_sources.txt")
        configure_file("${CKKS_APP_ROOT}/afu/sources.txt.in" "${AFU_SOURCES}" @ONLY)
    endif()
    require_input(AFU_SOURCES file)
    # Require the export identity file and a fresh destination for project setup.
    if(NOT EXISTS "${OFS_PLATFORM_LIB}/fme-ifc-id.txt")
        message(FATAL_ERROR "OFS_PLATFORM_LIB is missing its exported FIM interface identity")
    endif()
    if(NOT IS_ABSOLUTE "${PERSONA_TARGET}" OR EXISTS "${PERSONA_TARGET}")
        message(FATAL_ERROR "PERSONA_TARGET must be a new absolute output path")
    endif()
# Project preparation is invoked explicitly through this build target.
add_custom_target(ckks_afu_setup
    COMMAND afu_synth_setup --lib "${OFS_PLATFORM_LIB}"
        --sources "${AFU_SOURCES}" "${PERSONA_TARGET}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM USES_TERMINAL)

elseif(CKKS_NATIVE_PHASE STREQUAL "implementation")
    # Reuse the prepared PR revision and static partition database.
    require_input(PERSONA_PROJECT directory)
    if(NOT EXISTS "${PERSONA_PROJECT}/ofs_pr_afu.qsf" OR
       NOT EXISTS "${PERSONA_PROJECT}/ofs_top.qdb")
        message(FATAL_ERROR "PERSONA_PROJECT is missing its prepared PR revision or static QDB")
    endif()
    # Full revision compile, followed by individually invocable native stages.
    # These targets remain independent so the caller selects the stage sequence.
    add_custom_target(ckks_afu_compile
        COMMAND "${QUARTUS_ROOT}/bin/quartus_sh"
            --flow compile ofs_top -c ofs_pr_afu
        WORKING_DIRECTORY "${PERSONA_PROJECT}" VERBATIM USES_TERMINAL)
    add_custom_target(ckks_afu_synthesis
        COMMAND "${QUARTUS_ROOT}/bin/quartus_syn"
            --read_settings_files=on --write_settings_files=off ofs_top -c ofs_pr_afu
        WORKING_DIRECTORY "${PERSONA_PROJECT}" VERBATIM USES_TERMINAL)
    add_custom_target(ckks_afu_fit
        COMMAND "${QUARTUS_ROOT}/bin/quartus_fit"
            --read_settings_files=on --write_settings_files=off ofs_top -c ofs_pr_afu
        WORKING_DIRECTORY "${PERSONA_PROJECT}" VERBATIM USES_TERMINAL)
    # Request final-snapshot, multi-corner timing and CDC reports for review.
    add_custom_target(ckks_afu_timing
        COMMAND "${QUARTUS_ROOT}/bin/quartus_sta"
            ofs_top -c ofs_pr_afu --snapshot=final --multicorner=on
            --do_report_timing --do_report_cdc_viewer
        WORKING_DIRECTORY "${PERSONA_PROJECT}" VERBATIM USES_TERMINAL)
    # Assembly consumes existing implementation outputs. Review preceding stages separately.
    add_custom_target(ckks_afu_assembly
        COMMAND "${QUARTUS_ROOT}/bin/quartus_asm"
            --read_settings_files=on ofs_top -c ofs_pr_afu
        WORKING_DIRECTORY "${PERSONA_PROJECT}" VERBATIM USES_TERMINAL)
else()
    message(FATAL_ERROR "CKKS_NATIVE_PHASE must be setup or implementation")
endif()
