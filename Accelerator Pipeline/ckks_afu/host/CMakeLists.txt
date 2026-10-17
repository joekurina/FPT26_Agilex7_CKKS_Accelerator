# Build the CPU wire codec, with an optional native-device benchmark executable.
cmake_minimum_required(VERSION 3.20)
project(ckks_native_wire LANGUAGES C CXX)

# CPU serialization library. The OPAE backend is a separate target.
option(CKKS_REAL_DEVICE "Build the real CKKS OPAE backend" OFF)

# Consumers inherit the public headers
# and C++ language requirement through this library target.
add_library(ckks_native_wire STATIC EXCLUDE_FROM_ALL
    src/wire.cpp)
target_include_directories(ckks_native_wire PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(ckks_native_wire PUBLIC cxx_std_17)
# Use standard C++17 and enable supported warnings.
set_target_properties(ckks_native_wire PROPERTIES CXX_EXTENSIONS OFF)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ckks_native_wire PRIVATE -Wall -Wextra -Wpedantic)
endif()

# The hardware executable is opt-in.
if(CKKS_REAL_DEVICE)
    add_subdirectory(benchmark)
endif()
