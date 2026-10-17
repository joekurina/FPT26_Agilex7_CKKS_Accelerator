# Native CKKS benchmark

The preparation, vector generation, numerical verification and key-loading sources are included here. The build compiles SEAL and SEAL-Embedded from pinned public submodules and links directly to the installed OPAE SDK library.

`InputPreparer::prepare(vector, seeds)` prepares one input: its complex embedding, error samples, coefficient-domain secret-key limbs and C1 limbs. The private `src/seal_embedded_bridge.c` adapter owns SEAL-Embedded state and writes the sampled polynomials directly into the C++ result buffers. It checks the library's moduli against `benchmark_config.hpp` once during creation.

## Build

From `Accelerator Pipeline/`, on x86-64 Linux with CMake 3.20 or newer, C/C++17 compilers, and the OPAE 2.14.0-3 development headers and library installed:

```bash
git submodule update --init --recursive
cmake -S ckks_afu/host/benchmark -B build-host -DCMAKE_BUILD_TYPE=Release
cmake --build build-host --target ckks_native_benchmark ckks_generate_keys --parallel 4
```

For an OPAE SDK outside the system search paths, add `-DOPAE_ROOT=/absolute/sdk/prefix` to the CMake configure command. CMake resolves both the headers and `libopae-c` from that prefix.

The submodule revisions select Microsoft SEAL 3.7.2 and SEAL-Embedded 1.1.0. Their source notices and licenses remain in the submodules. Upstream examples, tests and benchmarks are not built. SEAL compression and optional acceleration dependencies are disabled, so this build uses uncompressed key files.

SEAL-Embedded uses its pinned default host configuration: dynamic allocation, 32-bit residues, a persistent computed index map, and no external precomputed-data files. CMake removes the upstream memory-address printing block from a build-tree copy of `ckks_sym.c`. The submodule and its arithmetic remain unchanged.

## Generate matching keys

```bash
build-host/ckks_generate_keys "$(pwd)/benchmark-keys"
```

This creates `secret-key.seal` and `secret-key.compact` from the same randomly generated SEAL key. The generator verifies the pair, creates private files, and refuses an existing output directory. These filenames are ignored by Git. Keep them private.

The context uses N=8192, the six ordered data primes in `benchmark_config.hpp`, a 38-bit special prime, and scale 2^25. No supplied private key or captured input is required.

## Run on the FPGA host

The device host needs the compatible programmed CKKS image and OFS platform, the matching OPAE 2.14 runtime with `libopae-v.so`, the accelerator VF bound to VFIO, and appropriate device permissions. Building the host executable does not program or open the FPGA.

The included `opae-ckks.cfg` is the VFIO profile used by the supported platform. Its PCI identity is `8086:bccf`, subsystem `8086:1771`. The profile name is inherited from that platform. A different platform requires its own compatible configuration.

For a non-system OPAE installation, set `OPAE_ROOT` to the SDK prefix used at build time and expose its runtime libraries:

```bash
export LD_LIBRARY_PATH="$OPAE_ROOT/lib64:$OPAE_ROOT/lib:$OPAE_ROOT/lib64/opae:$OPAE_ROOT/lib/opae${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
```

Set `CKKS_PCI_BDF` to the accelerator VF's exact domain:bus:device.function address. Select the VFIO configuration before launching the program:

```bash
unset OPAE_EXPLICIT_INITIALIZE WITH_ASE
export LIBOPAE_CFGFILE="$(pwd)/ckks_afu/host/benchmark/opae-ckks.cfg"
build-host/ckks_native_benchmark "$CKKS_PCI_BDF" \
  "$(pwd)/benchmark-keys/secret-key.compact" \
  "$(pwd)/benchmark-keys/secret-key.seal" 4096 3
```

The optional final arguments are frames per timed trial and the number of trials. OPAE initializes automatically before `main()` using `LIBOPAE_CFGFILE` or its system configuration, and finalizes at process exit. The application checks device cleanup before reporting completion. Install the matching OPAE SDK/runtime as part of the FPGA platform environment. The pinned OPAE sources remain available under `third_party/opae-sdk` for reference.

The benchmark uses a separately qualified FPGA image. Each run prepares 16 real, partial and complex cases, warms up, and times complete-ciphertext delivery. The timed boundary includes native submission/completion, C0 decoding and C0/C1 materialization. After each trial, the retained first, middle and last outputs are decrypted and compared across all 4096 slots. Numerical coverage is limited to those retained samples, and the summary reports `qualification_frames=0`. The program reports numerical failures and retains DMA ownership when completion is uncertain.

Seeds are deterministic for repeatable benchmark inputs. This executable is a benchmark, not a production encryption service.

## Qualification boundary

Compile/link and hardware validation of the directly linked host remain pending. Published hardware measurements remain bound to the preserved pre-cleanup FPGA image.
