get_filename_component(ckks_repository "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE)
set(ckks_third_party "${ckks_repository}/third_party")
foreach(required IN ITEMS SEAL/CMakeLists.txt SEAL-Embedded/device/CMakeLists.txt)
    if(NOT EXISTS "${ckks_third_party}/${required}")
        message(FATAL_ERROR "Initialize dependencies with: git submodule update --init --recursive")
    endif()
endforeach()

# Build only the libraries needed by preparation and verification.
set(SEAL_BUILD_DEPS OFF CACHE BOOL "Build additional SEAL dependencies" FORCE)
set(SEAL_USE_MSGSL OFF CACHE BOOL "Use Microsoft GSL" FORCE)
set(SEAL_USE_ZLIB OFF CACHE BOOL "Enable compressed SEAL serialization" FORCE)
set(SEAL_USE_ZSTD OFF CACHE BOOL "Enable Zstandard SEAL serialization" FORCE)
set(SEAL_USE_INTEL_HEXL OFF CACHE BOOL "Use Intel HEXL" FORCE)
set(SEAL_BUILD_EXAMPLES OFF CACHE BOOL "Build SEAL examples" FORCE)
set(SEAL_BUILD_TESTS OFF CACHE BOOL "Build SEAL tests" FORCE)
set(SEAL_BUILD_BENCH OFF CACHE BOOL "Build SEAL benchmarks" FORCE)
add_subdirectory("${ckks_third_party}/SEAL" "${CMAKE_CURRENT_BINARY_DIR}/seal")

set(SE_BUILD_LOCAL ON CACHE BOOL "Build SEAL-Embedded for the host" FORCE)
set(SE_BUILD_TYPE Lib CACHE STRING "SEAL-Embedded library build" FORCE)
add_subdirectory("${ckks_third_party}/SEAL-Embedded/device" "${CMAKE_CURRENT_BINARY_DIR}/seal-embedded")

# Omit upstream address dumps in a build-tree copy, preserving the submodule.
set(ckks_sym_original "${ckks_third_party}/SEAL-Embedded/device/lib/ckks_sym.c")
file(READ "${ckks_sym_original}" ckks_sym_source)
set(ckks_address_dump [=[    // -- Debugging: print all adresses
#ifdef SE_USE_MALLOC
    se_print_addresses(mempool, se_ptrs, n, 1);
    se_print_relative_positions(mempool, se_ptrs, n, 1);
#else
    se_print_addresses(mempool, se_ptrs);
    se_print_relative_positions(mempool, se_ptrs);
#endif
]=])
string(FIND "${ckks_sym_source}" "${ckks_address_dump}" ckks_address_dump_offset)
if(ckks_address_dump_offset EQUAL -1)
    message(FATAL_ERROR "Unexpected SEAL-Embedded source. Restore the pinned submodule revision.")
endif()
string(REPLACE "${ckks_address_dump}" "" ckks_sym_source "${ckks_sym_source}")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(ckks_sym_quiet "${CMAKE_CURRENT_BINARY_DIR}/generated/ckks_sym.c")
file(WRITE "${ckks_sym_quiet}" "${ckks_sym_source}")
get_target_property(ckks_embedded_sources seal_embedded SOURCES)
list(REMOVE_ITEM ckks_embedded_sources "${ckks_sym_original}")
list(APPEND ckks_embedded_sources "${ckks_sym_quiet}")
set_property(TARGET seal_embedded PROPERTY SOURCES "${ckks_embedded_sources}")

# Locate the installed OPAE SDK used by the native host.
set(OPAE_ROOT "" CACHE PATH "Installed OPAE SDK prefix, or empty for system search paths")
unset(CKKS_OPAE_INCLUDE_DIR CACHE)
unset(CKKS_OPAE_LIBRARY CACHE)
if(OPAE_ROOT)
    find_path(CKKS_OPAE_INCLUDE_DIR NAMES opae/fpga.h
        PATHS "${OPAE_ROOT}/include" NO_DEFAULT_PATH REQUIRED)
    find_library(CKKS_OPAE_LIBRARY NAMES opae-c
        PATHS "${OPAE_ROOT}/lib64" "${OPAE_ROOT}/lib" NO_DEFAULT_PATH REQUIRED)
else()
    find_path(CKKS_OPAE_INCLUDE_DIR NAMES opae/fpga.h REQUIRED)
    find_library(CKKS_OPAE_LIBRARY NAMES opae-c REQUIRED)
endif()
