# Generate the arithmetic component. Native persona and host builds have separate entry points.
cmake_minimum_required(VERSION 3.20)

# Select AHLS before project() discovers the compiler, unless one was supplied.
if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER ahls)
endif()

project(ckks_ahls LANGUAGES CXX)

# The part is fixed for this application.
# The clock value is an AHLS scheduling target.
set(FPGA_DEVICE "AGFB027R25A2E2V" CACHE STRING "FPGA part for CKKS IP generation")
set(CKKS_HLS_CLOCK "2ns" CACHE STRING "AHLS scheduling target")

if(NOT FPGA_DEVICE STREQUAL "AGFB027R25A2E2V")
    message(FATAL_ERROR "The selected IA-840F part is AGFB027R25A2E2V")
endif()


# Import the supplied transform archives and publish their generated headers.
add_subdirectory(libraries)

# The complete pipeline, including the original transforms imported through AHLS.
# Keep stage definitions before the final pipeline-instantiation source.
set(ckks_pipeline_sources
    src/ingress.cpp
    src/ifft.cpp
    src/ntt.cpp
    src/poly_add_mult.cpp
    src/egress.cpp
    src/ckks_pipeline.cpp)

# IP generation is an explicitly requested build target.
add_executable(ckks_pipeline_ip EXCLUDE_FROM_ALL ${ckks_pipeline_sources})

# Keep stage-template definitions visible to task_sequence in one AHLS unit.
set_target_properties(ckks_pipeline_ip PROPERTIES UNITY_BUILD ON UNITY_BUILD_MODE GROUP)
set_source_files_properties(${ckks_pipeline_sources} PROPERTIES UNITY_GROUP ckks_pipeline)

# Share the packed host wire definitions with the HLS stages.
target_include_directories(ckks_pipeline_ip PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../host/include")
target_compile_features(ckks_pipeline_ip PRIVATE cxx_std_17)

# Apply the existing floating-point policy at compile and link stages, and
# keep device code together.
target_compile_options(ckks_pipeline_ip PRIVATE -Wall -mno-fma -ffp-model=precise
    -fsycl-device-code-split=off)
target_link_options(ckks_pipeline_ip PRIVATE -mno-fma -ffp-model=precise
    -fsycl-device-code-split=off)

# Compile the hardware-only pipeline.
target_compile_definitions(ckks_pipeline_ip PRIVATE FPGA_HARDWARE)
target_compile_options(ckks_pipeline_ip PRIVATE -Wno-return-type-c-linkage)

# Early device linking generates AHLS report/IP collateral for the persona flow.
target_link_options(ckks_pipeline_ip PRIVATE -Xshardware "-Xstarget=${FPGA_DEVICE}"
    "-Xsclock=${CKKS_HLS_CLOCK}" -fsycl-link=early)

# The supplied DSP Builder archives share host-side logging symbols.
# GNU ld keeps the first definition. The allowance covers all duplicates in
# this executable link, while leaving the supplied archives unchanged.
target_link_options(ckks_pipeline_ip PRIVATE "LINKER:--allow-multiple-definition")
target_link_libraries(ckks_pipeline_ip PRIVATE ckks_transforms)

# The persona entry point consumes the matching ckks_pipeline.report.prj tree.
set_target_properties(ckks_pipeline_ip PROPERTIES OUTPUT_NAME "ckks_pipeline.report")
add_custom_target(ckks_ahls_ip DEPENDS ckks_pipeline_ip)
