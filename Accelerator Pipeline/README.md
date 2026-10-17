# CKKS AHLS AFU on IA-840F

Publication sources for the CKKS encode/encrypt implementation. The hardware uses pipelined admission, tile-based input parsing, a shared IFFT with paired errors, blocking fan-out, twelve NTTs, and fenced C0 output. C1 is retained by the host for complete ciphertext construction.

- [Application layout and dependencies](ckks_afu/README.md)
- [AHLS pipeline and IP generation](ckks_afu/hls/README.md)
- [Host build, key generation and benchmark](ckks_afu/host/benchmark/README.md)

The application sources contain one hardware implementation, its required transport modules, and the publication benchmark with numerical verification and DMA safety checks. Experimental application variants, standalone tests, debug counters, and development artifacts are excluded. Third-party submodules retain their upstream contents, with only the required libraries built.

The original transform archives remain under `ckks_afu/hls/libraries/`. Public SEAL, SEAL-Embedded and OPAE sources are pinned under `third_party/`. Run `git submodule update --init --recursive` after cloning. The native host links the installed OPAE SDK library. The FPGA build and execution still require the matching AHLS/Quartus installation, a compatible fixed OFS platform export, generated HLS output and an installed OPAE runtime. Generated FPGA images and native build outputs are not supplied by this checkout.
