#pragma once

#include "common.h"
#include "pipes.h"
#include "data_types.h"
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {

// Submit each persistent service once. Competing consumers share its pipes.
// Never wait on service events or the queue. Finite feeders/drainers own completion.

class IFFTFanoutKernelTask;

class IFFTFanoutKernel {
public:
    void operator()(sycl::handler& h) const {
        h.single_task<IFFTFanoutKernelTask>([=]() [[intel::kernel_args_restrict]] {
            encoding_block output_block{};
            unsigned pending = 0;
            // Retry only unaccepted destinations. Do not read ahead or duplicate writes.
            [[intel::initiation_interval(1)]]
            while (true) {
                if (pending == 0) {
                    bool valid = false;
                    encoding_block next = IFFTRawOutputPipe::read(valid);
                    if (valid) {
                        output_block = next;
                        pending = 0x3fu;
                    }
                }
                if (pending != 0) {
                    if (pending & (1u << 0)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<0>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 0);
                    }
                    if (pending & (1u << 1)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<1>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 1);
                    }
                    if (pending & (1u << 2)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<2>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 2);
                    }
                    if (pending & (1u << 3)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<3>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 3);
                    }
                    if (pending & (1u << 4)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<4>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 4);
                    }
                    if (pending & (1u << 5)) {
                        bool accepted = false;
                        IFFTToScaleReducePipes::PipeAt<5>::write(output_block, accepted);
                        if (accepted) pending &= ~(1u << 5);
                    }
                }
            }
        });
    }
};

template <int P>
class ScaleAndReduceKernelTask;

template <int P>
class ScaleAndReduceKernel {
private:
    const double scale;
    const uint32_t mod_value;
    const uint32_t const_ratio[2];

public:
    static_assert(P >= 0 && P < NUM_MODULI, "invalid physical pipeline");
    ScaleAndReduceKernel(double s, uint32_t mod, const uint32_t* cr)
        : scale(s), mod_value(mod), const_ratio{cr[0], cr[1]}
    {}

    void operator()(sycl::handler& h) const {
        double kernel_scale = scale;
        uint32_t kernel_mod = mod_value;
        uint32_t kernel_cr0 = const_ratio[0];
        uint32_t kernel_cr1 = const_ratio[1];

        h.single_task<ScaleAndReduceKernelTask<P>>([=]() [[intel::kernel_args_restrict]] {
            using Pipes = PipeSet<P>;
            double n_inv = kernel_scale / static_cast<double>(POLY_N);

            [[intel::initiation_interval(1)]]
            while (true) {
                encoding_block enc = IFFTToScaleReducePipes::PipeAt<P>::read();
                i8x4 err = ErrorToScaleReducePipes::PipeAt<P>::read();

                double scaled0 = sycl::round(enc.element0.real() * n_inv);
                double scaled1 = sycl::round(enc.element1.real() * n_inv);
                double scaled2 = sycl::round(enc.element2.real() * n_inv);
                double scaled3 = sycl::round(enc.element3.real() * n_inv);

                int64_t int_val0 = static_cast<int64_t>(scaled0) + err.element0;
                int64_t int_val1 = static_cast<int64_t>(scaled1) + err.element1;
                int64_t int_val2 = static_cast<int64_t>(scaled2) + err.element2;
                int64_t int_val3 = static_cast<int64_t>(scaled3) + err.element3;

                u32x4 out;
                out.element0 = barrett_reduce_64_core(int_val0, kernel_mod, kernel_cr0, kernel_cr1, false);
                out.element1 = barrett_reduce_64_core(int_val1, kernel_mod, kernel_cr0, kernel_cr1, false);
                out.element2 = barrett_reduce_64_core(int_val2, kernel_mod, kernel_cr0, kernel_cr1, false);
                out.element3 = barrett_reduce_64_core(int_val3, kernel_mod, kernel_cr0, kernel_cr1, false);

                Pipes::ScaleReduceToNTTBPipe::write(out);
            }
        });
    }
};

template <int P>
class PolyMultNegAddKernelTask;

template <int P>
class PolyMultNegAddKernel {
private:
    const uint32_t mod_value;
    const uint32_t const_ratio[2];

public:
    static_assert(P >= 0 && P < NUM_MODULI, "invalid physical pipeline");
    PolyMultNegAddKernel(uint32_t mod, const uint32_t* cr)
        : mod_value(mod), const_ratio{cr[0], cr[1]}
    {}

    void operator()(sycl::handler& h) const {
        uint32_t kernel_mod = mod_value;
        uint32_t kernel_cr0 = const_ratio[0];
        uint32_t kernel_cr1 = const_ratio[1];

        h.single_task<PolyMultNegAddKernelTask<P>>([=]() [[intel::kernel_args_restrict]] {
            using Pipes = PipeSet<P>;

            [[intel::initiation_interval(1)]]
            while (true) {
                u32x4 ntt_s = Pipes::NTTAToPolyMultNegPipe::read();
                u32x4 c1 = Pipes::EntryToPolyMultNegPipe::read();
                u32x4 ntt_pte = Pipes::NTTBToPolyAddPipe::read();

                uint64_t prod0 = static_cast<uint64_t>(ntt_s.element0) * static_cast<uint64_t>(c1.element0);
                uint64_t prod1 = static_cast<uint64_t>(ntt_s.element1) * static_cast<uint64_t>(c1.element1);
                uint64_t prod2 = static_cast<uint64_t>(ntt_s.element2) * static_cast<uint64_t>(c1.element2);
                uint64_t prod3 = static_cast<uint64_t>(ntt_s.element3) * static_cast<uint64_t>(c1.element3);

                uint32_t red0 = barrett_reduce_u64_core(prod0, kernel_mod, kernel_cr0, kernel_cr1);
                uint32_t red1 = barrett_reduce_u64_core(prod1, kernel_mod, kernel_cr0, kernel_cr1);
                uint32_t red2 = barrett_reduce_u64_core(prod2, kernel_mod, kernel_cr0, kernel_cr1);
                uint32_t red3 = barrett_reduce_u64_core(prod3, kernel_mod, kernel_cr0, kernel_cr1);

                uint32_t neg0 = mod_neg(red0, kernel_mod);
                uint32_t neg1 = mod_neg(red1, kernel_mod);
                uint32_t neg2 = mod_neg(red2, kernel_mod);
                uint32_t neg3 = mod_neg(red3, kernel_mod);

                u32x4 out;
                out.element0 = mod_add(neg0, ntt_pte.element0, kernel_mod);
                out.element1 = mod_add(neg1, ntt_pte.element1, kernel_mod);
                out.element2 = mod_add(neg2, ntt_pte.element2, kernel_mod);
                out.element3 = mod_add(neg3, ntt_pte.element3, kernel_mod);

                Pipes::PolyAddToExitPipe::write(out);
            }
        });
    }
};

} // namespace ckks
