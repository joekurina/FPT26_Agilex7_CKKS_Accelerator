cmake_minimum_required(VERSION 3.20)
project(ckks_native_benchmark LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
if(NOT TARGET ckks_native_wire)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." host-wire)
endif()
find_package(Threads REQUIRED)
include(cmake/Dependencies.cmake)

add_library(ckks_native_reference STATIC
    src/benchmark_vectors.cpp
    src/correctness_metrics.cpp
    src/seal_oracle.cpp
    src/input_preparation.cpp
    src/seal_embedded_bridge.c)
target_include_directories(ckks_native_reference PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(ckks_native_reference PUBLIC cxx_std_17)
set_target_properties(ckks_native_reference PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)
target_link_libraries(ckks_native_reference PUBLIC SEAL::seal seal_embedded m Threads::Threads)

# Preserve the reference arithmetic's separate multiply and add operations.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ckks_native_reference PRIVATE -mno-fma -ffp-contract=off)
endif()

add_library(ckks_native_benchmark_core STATIC benchmark.cpp)
target_include_directories(ckks_native_benchmark_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(ckks_native_benchmark_core PUBLIC cxx_std_17)
target_compile_options(ckks_native_benchmark_core PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(ckks_native_benchmark_core PUBLIC ckks_native_wire ckks_native_reference)

# The host and hardware take their UUID from the same AFU descriptor.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../../afu/afu.json" afu_json)
string(JSON CKKS_AFU_UUID GET "${afu_json}" afu-image accelerator-clusters 0 accelerator-type-uuid)
configure_file(ckks_afu_identity.hpp.in ckks_afu_identity.hpp @ONLY)

add_executable(ckks_native_benchmark opae_host.cpp)
target_compile_features(ckks_native_benchmark PRIVATE cxx_std_17)
target_include_directories(ckks_native_benchmark PRIVATE "${CKKS_OPAE_INCLUDE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_options(ckks_native_benchmark PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(ckks_native_benchmark PRIVATE ckks_native_benchmark_core "${CKKS_OPAE_LIBRARY}")

add_executable(ckks_generate_keys generate_keys.cpp)
target_compile_features(ckks_generate_keys PRIVATE cxx_std_17)
target_compile_options(ckks_generate_keys PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(ckks_generate_keys PRIVATE ckks_native_reference)
