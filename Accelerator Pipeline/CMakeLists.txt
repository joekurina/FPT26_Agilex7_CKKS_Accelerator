cmake_minimum_required(VERSION 3.20)
project(sycl_ckks_accelerator VERSION 0.3.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(cmake/accelerator.cmake)

# Package one header without modifying the source API or its shared type header.
# Track both inputs so a normal build regenerates it after either is edited.
set(_api_header "${PROJECT_SOURCE_DIR}/include/sycl_ckks_accelerator/ckks_accelerator.h")
set(_types_header "${PROJECT_SOURCE_DIR}/include/sycl_ckks_accelerator/ckks_types.h")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${_api_header}" "${_types_header}")
file(READ "${_api_header}" _public_api)
file(READ "${_types_header}" _public_types)
string(REGEX REPLACE "^#pragma once\n" "" _public_types "${_public_types}")
string(REPLACE "#include \"sycl_ckks_accelerator/ckks_types.h\""
    "${_public_types}" _public_header "${_public_api}")
file(GENERATE OUTPUT "${PROJECT_BINARY_DIR}/include/ckks_accelerator.h"
    CONTENT "${_public_header}")

# Installation requires the explicit ckks_hw_image build first.
install(FILES "${CKKS_HW_IMAGE}" DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(FILES "${PROJECT_BINARY_DIR}/include/ckks_accelerator.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
