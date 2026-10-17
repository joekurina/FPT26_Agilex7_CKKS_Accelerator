# CKKS AHLS pipeline

This directory contains the SYCL implementation of the accelerator pipeline.

## Source layout

Headers are in `include/` and implementations are in `src/`.

- `ingress`: assemble packed DMA words into input records and distribute their fields.
- `ifft`: call the shared IFFT, scale and round its real output, add the corresponding error, and fan out signed coefficient blocks.
- `ntt`: call the key and message transforms, with signed Barrett reduction in the message-input adapter.
- `poly_add_mult`: compute each C0 modulus plane from the two NTT outputs and supplied C1.
- `egress`: pack C0 planes into the DMA output stream.
- `ckks_pipeline`: instantiate the tasks and order their starts and completion waits.
- `streaming_pipes.hpp`: payload types, external AXI stream properties, and `ModulusPipes<P>`.
- `parameters.hpp` and `arithmetic.hpp`: fixed geometry, moduli, and reduction operations.
- `libraries/`: supplied DSP Builder archives and matching generated interfaces.

The parser groups eight 264-byte records into 33 input words.
All records are forwarded in order, and nonzero reserved fields are reported through the status stream after the tasks finish.

The IFFT task pairs each encoding input with one error block. Its output conversion applies scale, round, signed 64-bit conversion, and error addition in that order. AHLS may schedule the error read later than its source position. The signed output FIFO and blocking fan-out remain separate stages.

Each modulus has independent key and message NTT tasks. A completed imported return is forwarded through a blocking pipe write. The import transaction handshake and downstream backpressure remain active. The host retains C1 and combines it with the returned C0 planes.

## IP generation

Use AHLS 2026.1.0 in the selected AHLS Apptainer environment with Quartus Pro 26.1.1. Set `CKKS_SOURCE` to the `ckks_afu` directory and `CKKS_BUILD` to an external build directory.

```bash
cmake -S "$CKKS_SOURCE/hls" -B "$CKKS_BUILD/hls" \
  -DCMAKE_CXX_COMPILER=ahls \
  -DFPGA_DEVICE=AGFB027R25A2E2V \
  -DCKKS_HLS_CLOCK=2ns \
  -DCKKS_DSP_LIBRARY_DIR="$CKKS_SOURCE/hls/libraries"
cmake --build "$CKKS_BUILD/hls" --target ckks_ahls_ip
```

CMake places the stage implementations before `ckks_pipeline.cpp` in one unity group so template definitions are visible at task instantiation. The target generates `ckks_pipeline.report.prj/` for the native persona flow. The 2 ns setting is a scheduling target, not a measured operating clock.

The supplied transform archives link directly, followed by GMP. The executable uses `--allow-multiple-definition` for duplicate host-model logging symbols. The supplied archives and generated headers are unchanged.
