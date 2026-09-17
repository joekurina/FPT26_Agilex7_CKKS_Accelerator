# CKKS accelerator library

This directory builds the CKKS FPGA accelerator: N=8192, six ordered
moduli, four frames per enqueue, and two host slots.

## Build and install

Use an FPGA-capable Intel oneAPI **2025.0** environment, its compatible FPGA
backend/Quartus installation and licenses, and the installed IA-840F BSP. Source
the site's oneAPI environment setup and configure the BSP/Quartus environment
before these commands. Run from this directory on the build machine:

```sh
cmake -S . -B build \
  -DCMAKE_CXX_COMPILER=icpx \
  -DCKKS_FPGA_TARGET=ia840f:ofs_ia840f_usm \
  -DCMAKE_INSTALL_PREFIX="$PWD/install" \
  -DCMAKE_INSTALL_LIBDIR=lib
cmake --build build --target ckks_hw_image
cmake --install build
```

`CKKS_FPGA_TARGET` is required: substitute the installed BSP path/name and exact
variant if different. The hardware target is explicit (not in the default build)
because it performs a potentially multi-hour full FPGA compilation. Installation
does not build it; build `ckks_hw_image` first. Use a fresh install prefix for this
two-file package; installation does not remove headers from older installations.

Build outputs:

- `build/hardware/libckks_accelerator.a`
- `build/include/ckks_accelerator.h`

With the settings above, installation delivers:

- `install/lib/libckks_accelerator.a`
- `install/include/ckks_accelerator.h`

## Link another program

Include `#include <ckks_accelerator.h>` and compile the caller as normal host code.
For example, with `PREFIX` pointing to the installed package:

```sh
c++ -std=c++17 -I"$PREFIX/include" -c app.cpp -o app.o
icpx -fsycl -fintelfpga app.o \
  "$PREFIX/lib/libckks_accelerator.a" -pthread -o app
```

For C callers, compile the caller with a C99-or-later compiler instead; use the
same oneAPI C++ final link. Keep a compatible host ABI (including the header's
existing C `double complex` / C++ `std::complex<double>` representation). Do not
pass `-Xshardware`, `-Xstarget` or `-fsycl-link=image` on this consumer link: the
archive already contains the FPGA image. Use the FPGA-capable oneAPI toolchain
compatible with the archive; a generic host linker alone is not sufficient.
The in-tree imported CMake target `ckks_hardware` carries the packaged include
path, Threads dependency and final-link flags; no installed CMake config is
provided.

The package is not a standalone runtime distribution. Execution still needs the
compatible oneAPI SYCL/FPGA runtime, board support/driver stack, and configured
IA-840F hardware for the selected image.

Use the header's `ckks_accelerator` create/enqueue/poll/collect-next/drain/
close API. Externally serialize calls, enqueue exactly four frames (encoding vectors), collect in
FIFO order, and collect all outputs before closing. Only one accelerator may be
created per process. Closing does not restart persistent services. A drain timeout
stops the accelerator and retains storage. Use an external watchdog because a
driver call can block despite the cooperative deadline.
