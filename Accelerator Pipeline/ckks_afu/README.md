# CKKS AHLS AFU

The accelerator uses pipelined admission, tile-based parsing with compiler-default clustering, and a blocking input distributor. The accelerator has a fixed shape of N=8192, 6 prime moduli, coefficients grouped in blocks of 4 lanes, binary64 and scale `0x1p25`, with one active operation. C0 output is combined with host-retained C1 to produce a complete ciphertext.

## Source layout

- [`hls/`](hls/README.md): the SYCL implementation of the accelerator pipeline.
- `hls/libraries/`: Exported DSP Builder IFFT/NTT archives and headers.
- `afu/`: OFS/PIM bindings, CSR frontend, and accelerator pipeline controller.
- `afu/transport/`: host-memory read/write engines, command types, counter and packet cap.
- `host/`: wire serialization and validation. `host/benchmark/` is the benchmark executable.
- `cmake/persona/`: native AFU setup and implementation using the generated HLS QIP.

## Build dependencies

The selected environment is Altera HLS IP Gen Compiler (AHLS) v2026.1.0, Quartus Pro 26.1.1 Build 130 and OPAE 2.14.0-3, with the established AHLS Apptainer and compatible fixed platform export. The host builds its included preparation and oracle sources with the pinned SEAL and SEAL-Embedded submodules, and links the installed OPAE SDK library. [Host build and run instructions](host/benchmark/README.md) include key generation and the VFIO configuration.

`CKKS_HLS_CLOCK` defaults to `2ns`. This is a compiler scheduling request, not a measured runtime clock. The arithmetic and parser selections are fixed in the source. Native CMake defaults to `CKKS_NATIVE_PHASE=setup`. When `AFU_SOURCES` is omitted, it requires `CKKS_HLS_PROJECT` and configures `afu/sources.txt.in` with the application paths and generated `kernel_system.qip`. The pipelined controller is listed directly alongside the other RTL. An explicitly prepared source list remains supported, and the implementation phase uses the prepared native project.
