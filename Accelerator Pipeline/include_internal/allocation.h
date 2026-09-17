#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <new>
#include <stdexcept>
#include <sycl/sycl.hpp>

namespace ckks {
// Queue/context outlive this object. No queue-wide wait: persistent RTL
// services never complete. Destruction is
// permitted only before submission or after all bounded users have completed.
// Persistent pipe services do not capture these pointers. A failed session must
// establish bounded-command quiescence before destroying its slots.
class SlotAllocation {
public:
    SlotAllocation(sycl::queue &queue, size_t input_bytes,
                   size_t c0_bytes, size_t alignment) : queue_(queue)
    {
        if (!input_bytes || !c0_bytes || alignment < 64 ||
            (alignment & (alignment - 1)))
            throw std::invalid_argument("invalid USM allocation extent/alignment");
        try {
            for (size_t i = 0; i < allocations_.size(); ++i) {
                const size_t bytes = i < 2 ? input_bytes : c0_bytes;
                allocations_[i] = i % 2 != 0
                    ? sycl::aligned_alloc_device(alignment, bytes, queue_)
                    : sycl::aligned_alloc_host(alignment, bytes, queue_);
                if (!allocations_[i]) throw std::bad_alloc();
                if (reinterpret_cast<uintptr_t>(allocations_[i]) % alignment)
                    throw std::runtime_error("USM allocator returned misaligned memory");
            }
        } catch (...) {
            release();
            throw;
        }
    }
    ~SlotAllocation() { release(); }
    SlotAllocation(const SlotAllocation &) = delete;
    SlotAllocation &operator=(const SlotAllocation &) = delete;
    SlotAllocation(SlotAllocation &&) = delete;
    SlotAllocation &operator=(SlotAllocation &&) = delete;
    void *host_input() const { return allocations_[0]; }
    void *device_input() const { return allocations_[1]; }
    void *host_c0() const { return allocations_[2]; }
    void *device_c0() const { return allocations_[3]; }
private:
    void release() noexcept {
        for (size_t i = allocations_.size(); i != 0; --i) {
            // The session guarantees a live context and USM provenance.
            if (allocations_[i-1]) sycl::free(allocations_[i-1], queue_.get_context());
            allocations_[i-1] = nullptr;
        }
    }
    sycl::queue &queue_;
    std::array<void *, 4> allocations_{};
};
} // namespace ckks
