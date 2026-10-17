# Link the supplied DSP Builder archives and expose their generated interfaces.
# Fresh configurations use this directory. An explicit or cached override is retained.
set(CKKS_DSP_LIBRARY_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE PATH "DSP Builder transform archives and generated headers")
get_filename_component(CKKS_DSP_LIBRARY_DIR "${CKKS_DSP_LIBRARY_DIR}" ABSOLUTE)

set(ifft_archive "${CKKS_DSP_LIBRARY_DIR}/fhe_ifft_8k_4lanes_double_261.a")
set(ntt_archive "${CKKS_DSP_LIBRARY_DIR}/the_nwc_8k_ntt.a")
# Check that both archives and the expected interface-header filenames exist.
foreach(required IN ITEMS "${ifft_archive}" "${ntt_archive}"
    "${CKKS_DSP_LIBRARY_DIR}/fhe_ifft_8k_4lanes_double_261_sycl.hpp"
    "${CKKS_DSP_LIBRARY_DIR}/the_nwc_8k_ntt_sycl.hpp")
    if(NOT EXISTS "${required}")
        message(FATAL_ERROR "Missing supplied DSP Builder file: ${required}")
    endif()
endforeach()

# The supplied host-model objects require GMP at link time.
find_library(CKKS_GMP_LIBRARY NAMES gmp libgmp.so.10 REQUIRED)

# Import the supplied archives directly. Duplicate host symbols are handled
# by the HLS executable's linker options.
# Imported targets describe already-built files.
foreach(transform IN ITEMS ifft ntt)
    add_library(ckks_${transform}_rtl STATIC IMPORTED GLOBAL)
    set_target_properties(ckks_${transform}_rtl PROPERTIES
        IMPORTED_LOCATION "${${transform}_archive}")
endforeach()

# This aggregate propagates include and link requirements.
add_library(ckks_transforms INTERFACE)
target_include_directories(ckks_transforms INTERFACE "${CKKS_DSP_LIBRARY_DIR}")
# Preserve archive order because the executable permits duplicate host definitions.
target_link_libraries(ckks_transforms INTERFACE ckks_ifft_rtl ckks_ntt_rtl "${CKKS_GMP_LIBRARY}")
