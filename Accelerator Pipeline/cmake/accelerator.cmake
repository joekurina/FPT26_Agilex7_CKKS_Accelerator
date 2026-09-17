# Native full no-main FPGA image
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
  message(FATAL_ERROR "Configure with FPGA-capable oneAPI 2025.0 icpx")
endif()
find_package(Threads REQUIRED)
set(CKKS_FPGA_TARGET "" CACHE STRING "Installed IA840f BSP path:variant")
if(NOT CKKS_FPGA_TARGET)
  message(FATAL_ERROR "Set CKKS_FPGA_TARGET to the installed BSP:variant")
endif()
set(_rtl "${PROJECT_SOURCE_DIR}/rtl/the_nwc_8k_ntt.a" "${PROJECT_SOURCE_DIR}/rtl/fhe_ifft_8k_4lanes_double_261.a")
file(GLOB_RECURSE _headers CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h" "${PROJECT_SOURCE_DIR}/include_internal/*.h" "${PROJECT_SOURCE_DIR}/include_internal/*.hpp" "${PROJECT_SOURCE_DIR}/rtl/*.hpp")
set(CKKS_HW_IMAGE "${PROJECT_BINARY_DIR}/hardware/ckks_accelerator_hw.a")
add_custom_command(OUTPUT "${CKKS_HW_IMAGE}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${PROJECT_BINARY_DIR}/hardware"
  COMMAND "${CMAKE_CXX_COMPILER}" -v -fsycl -fintelfpga -std=c++17 -O3
    -Rno-debug-disables-optimization -DCSL_USE_GMP -DCSL_SYCL -Wno-return-type-c-linkage -qactypes
    "-I${PROJECT_SOURCE_DIR}" "-I${PROJECT_SOURCE_DIR}/include" "-I${PROJECT_SOURCE_DIR}/include_internal" "-I${PROJECT_SOURCE_DIR}/rtl"
    -DFPGA_HARDWARE=1 -Xshardware "-Xstarget=${CKKS_FPGA_TARGET}" -fsycl-link=image
    -o "${CKKS_HW_IMAGE}" "${PROJECT_SOURCE_DIR}/src/ckks_accelerator.cpp" ${_rtl}
  DEPENDS "${PROJECT_SOURCE_DIR}/src/ckks_accelerator.cpp" ${_headers} ${_rtl} "${CMAKE_CURRENT_LIST_FILE}"
  COMMENT "Fresh F4 hardware image from current refactored source" VERBATIM)
add_custom_target(ckks_hw_image DEPENDS "${CKKS_HW_IMAGE}")
add_library(ckks_hardware STATIC IMPORTED GLOBAL)
set_target_properties(ckks_hardware PROPERTIES IMPORTED_LOCATION "${CKKS_HW_IMAGE}"
 INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include"
 INTERFACE_LINK_LIBRARIES "Threads::Threads" INTERFACE_LINK_OPTIONS "-fsycl;-fintelfpga")
add_dependencies(ckks_hardware ckks_hw_image)
