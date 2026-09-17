cmake_minimum_required (VERSION 3.13)
project (wrapper_atb_app)

set(CMAKE_CXX_STANDARD 14)
# set by user as a hint
set (GMP_INC_PATH "" CACHE PATH "GMP include path (hint)")
set (GMP_LIB_PATH "" CACHE PATH "GMP library path (hint)")
set (MPFR_INC_PATH "" CACHE PATH "MPFR include path (hint)")
set (MPFR_LIB_PATH "" CACHE PATH "MPFR library path (hint)")

option(USE_GMP "Include and link against the GMP library for models that require arbitrary precision" ON)
option(USE_MPFR "Include and link against the MPFR library for models that require arbitrary precision floating point" OFF)

set(fhe_ifft_8k_4lanes_double_261_INC
    "fhe_ifft_8k_4lanes_double_261_sycl.hpp"
    "../ifft8k_base/cmodel/support/csl.h"
    "../ifft8k_base/cmodel/support/csl_impl.h"
    "../ifft8k_base/cmodel/support/csl_io.h"
)

set(fhe_ifft_8k_4lanes_double_261_SRC
    "fhe_ifft_8k_4lanes_double_261.cpp"
    "fhe_ifft_8k_4lanes_double_261_atb.cpp"
)
source_group(fhe_ifft_8k_4lanes_double_261 FILES ${fhe_ifft_8k_4lanes_double_261_INC} ${fhe_ifft_8k_4lanes_double_261_SRC})
set(cmodel_SRC ${fhe_ifft_8k_4lanes_double_261_INC} ${fhe_ifft_8k_4lanes_double_261_SRC})

add_executable(wrapper_atb_app ${cmodel_SRC})
target_compile_definitions(wrapper_atb_app PRIVATE WRITE_STM_FILES)
target_include_directories(wrapper_atb_app PRIVATE ../ifft8k_base/cmodel)
set_target_properties(wrapper_atb_app PROPERTIES UNITY_BUILD "ON")
add_definitions(-DFPGA_EMULATOR)
add_definitions(-DNO_SYCL)
if (WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
add_compile_options(
    $<$<CXX_COMPILER_ID:Clang>:-fno-slp-vectorize>
)
if (MSVC)
    add_compile_options(/bigobj)
else()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(USE_GMP)
    add_definitions(-DCSL_USE_GMP)
    find_path(GMP_INC
        NAMES gmp.h
        HINTS ${GMP_INC_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software"
    )
    find_library(GMP_LIB
        NAMES dspba_mpir gmp mpir
        HINTS ${GMP_LIB_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software/lib" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software/lib"
    )
    find_file(GMP_DLL
        NAMES dspba_mpir.dll libdspba_mpir.so gmp.dll mpir.dll libmpir.so libgmp.so
        PATHS ${GMP_LIB_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software/lib" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software/lib"
        NO_DEFAULT_PATH
    )

    target_include_directories(wrapper_atb_app PRIVATE ${GMP_INC})
    target_link_libraries(wrapper_atb_app PRIVATE ${GMP_LIB})

    add_custom_command(TARGET wrapper_atb_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GMP_DLL}"
        $<TARGET_FILE_DIR:wrapper_atb_app>)

endif(USE_GMP)

if(USE_MPFR)
    add_definitions(-DCSL_USE_MPFR)
    find_path(MPFR_INC
        NAMES mpfr.h
        HINTS ${MPFR_INC_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software"
    )
    find_library(MPFR_LIB
        NAMES mpfr dspba_mpfr
        HINTS ${MPFR_LIB_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software/lib" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software/lib"
    )
    find_file(MPFR_DLL
        NAMES mpfr.dll dspba_mpfr.dll libdspba_mpfr.so libmpfr.so
        PATHS ${MPFR_LIB_PATH} "$ENV{DSPBA_ROOTDIR}/Libraries/software/lib" "$ENV{DSPBA_ROOTDIR}/backend/Libraries/software/lib"
        NO_DEFAULT_PATH
    )

    target_include_directories(wrapper_atb_app PRIVATE ${MPFR_INC})
    target_link_libraries(wrapper_atb_app PRIVATE ${MPFR_LIB})

    add_custom_command(TARGET wrapper_atb_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MPFR_DLL}"
        $<TARGET_FILE_DIR:wrapper_atb_app>)

endif(USE_MPFR)

install(TARGETS wrapper_atb_app DESTINATION bin)
