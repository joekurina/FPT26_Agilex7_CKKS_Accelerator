// CPU-only serialization between logical frame arrays and the native DMA payloads.

#include "ckks_native.h"
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

namespace ckks_native_detail {
// Keep the shared packed record ABI and raw C0 plane layout fixed at compile time.
static_assert(sizeof(ckks_native_complex64) == 16, "Complex input is two doubles");
static_assert(sizeof(ckks_native_input_record) == 264, "Input record size");
static_assert(offsetof(ckks_native_input_record, encoding) == 0, "Encoding field position");
static_assert(offsetof(ckks_native_input_record, error) == 64, "Error field position");
static_assert(offsetof(ckks_native_input_record, secret_key) == 68, "Key field position");
static_assert(offsetof(ckks_native_input_record, c1) == 164, "C1 field position");
static_assert(offsetof(ckks_native_input_record, reserved) == 260, "Reserved field position");
static_assert(sizeof(ckks_native_c0_frame) == CKKS_NATIVE_C0_BYTES, "C0 buffer size");

// Inspect the first object byte with memcpy to determine host byte order.
inline bool host_is_little_endian() {
    const uint16_t word = 1;
    uint8_t first_byte = 0;
    std::memcpy(&first_byte, &word, 1);
    return first_byte == 1;
}

// Reverse a scalar's bytes in place, preserving its width and field position.
inline void reverse_bytes(void *value, size_t count) {
    auto *bytes = static_cast<uint8_t *>(value);
    for (size_t i = 0; i < count / 2; ++i) {
        const uint8_t saved = bytes[i];
        bytes[i] = bytes[count - 1 - i];
        bytes[count - 1 - i] = saved;
    }
}

/* Apply in either direction: reversing the bytes twice restores the value. */
// Convert multi-byte fields, preserving coefficient, lane and modulus order.
// Signed error samples retain their single-byte representation.
inline void convert_record_byte_order(ckks_native_input_record &record) {
    if (host_is_little_endian()) return;
    for (size_t lane = 0; lane < CKKS_NATIVE_LANES; ++lane) {
        reverse_bytes(&record.encoding[lane].real, sizeof(double));
        reverse_bytes(&record.encoding[lane].imag, sizeof(double));
        for (size_t p = 0; p < CKKS_NATIVE_NUM_MODULI; ++p) {
            reverse_bytes(&record.secret_key[p][lane], sizeof(uint32_t));
            reverse_bytes(&record.c1[p][lane], sizeof(uint32_t));
        }
    }
    reverse_bytes(&record.reserved, sizeof(record.reserved));
}

// Assemble an unsigned little-endian scalar from individual bytes.
template <typename T> inline T load_le(const uint8_t *in) {
    static_assert(std::is_unsigned<T>::value, "unsigned wire scalar");
    T value = 0;
    for (size_t j = 0; j < sizeof(T); ++j)
        value |= static_cast<T>(in[j]) << (8 * j);
    return value;
}

// Copy the binary64 representation.
inline uint64_t double_bits(double value) {
    uint64_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}
// An all-ones binary64 exponent identifies both infinities and NaNs.
inline bool finite_bits(uint64_t bits) {
    return (bits & 0x7ff0000000000000ULL) != 0x7ff0000000000000ULL;
}

// Shared preflight order: null pointers, exact wire length, address wrap, overlap.
// Callers supply accessible memory with fixed nonzero object/payload sizes.
// Preflight checks use pointer values and sizes.
inline ckks_native_wire_result buffer_contract(
                                        const void *object,
                                        size_t object_bytes,
                                        const void *wire,
                                        size_t wire_bytes,
                                        size_t required_bytes)
{
    if (!object || !wire) {
        return CKKS_NATIVE_WIRE_INVALID_ARGUMENT;
    }

    if (wire_bytes != required_bytes) {
        return CKKS_NATIVE_WIRE_BAD_LENGTH;
    }

    const uintptr_t a = reinterpret_cast<uintptr_t>(object);
    const uintptr_t b = reinterpret_cast<uintptr_t>(wire);
    const uintptr_t max = std::numeric_limits<uintptr_t>::max();

    // Check inclusive endpoints for address wrap before addition and overlap checks.
    if (object_bytes - 1 > max - a || wire_bytes - 1 > max - b) {
        return CKKS_NATIVE_WIRE_ADDRESS_RANGE;
    }

    const uintptr_t a_last = a + object_bytes - 1;
    const uintptr_t b_last = b + wire_bytes - 1;

    if (a <= b_last && b <= a_last) {
        return CKKS_NATIVE_WIRE_OVERLAPPING_MEMORY;
    }

    return CKKS_NATIVE_WIRE_OK;
}

} // namespace ckks_native_detail

using namespace ckks_native_detail;

// Gather consecutive coefficient indices into records only after all checks pass.
extern "C" ckks_native_wire_result ckks_native_wire_encode_input(
    const ckks_native_input_frame *frame, uint8_t *wire, size_t wire_bytes) {
    auto result = buffer_contract(frame, sizeof(*frame), wire, wire_bytes, CKKS_NATIVE_INPUT_BYTES);
    if (result != CKKS_NATIVE_WIRE_OK) return result;

    // Check every value before changing the output buffer.
    for (size_t i = 0; i < CKKS_NATIVE_POLY_N; ++i)
        if (!finite_bits(double_bits(frame->encoding[i].real)) ||
            !finite_bits(double_bits(frame->encoding[i].imag)))
            return CKKS_NATIVE_WIRE_NONFINITE_ENCODING;

    uint8_t *output = wire;

    // Each record interleaves one lane block with the same indices from every modulus.
    for (size_t block = 0; block < CKKS_NATIVE_BLOCKS_PER_FRAME; ++block) {
        alignas(8) ckks_native_input_record record{};
        for (size_t lane = 0; lane < CKKS_NATIVE_LANES; ++lane) {
            const size_t i = block * CKKS_NATIVE_LANES + lane;
            record.encoding[lane] = frame->encoding[i];
            record.error[lane] = frame->error[i];
            for (size_t p = 0; p < CKKS_NATIVE_NUM_MODULI; ++p) {
                record.secret_key[p][lane] = frame->secret_key[p][i];
                record.c1[p][lane] = frame->c1[p][i];
            }
        }
        record.reserved = 0;

        // Convert the local record, then copy bytes to an arbitrarily aligned wire buffer.
        convert_record_byte_order(record);
        std::memcpy(output, &record, sizeof(record));
        output += sizeof(record);
    }
    return CKKS_NATIVE_WIRE_OK;
}

// C0 is already modulus-major on the wire, matching the host array order.
// Decoding checks buffer contracts only.
extern "C" ckks_native_wire_result ckks_native_wire_decode_c0(
    const uint8_t *wire, size_t wire_bytes, ckks_native_c0_frame *frame) {
    auto result = buffer_contract(frame, sizeof(*frame), wire, wire_bytes, CKKS_NATIVE_C0_BYTES);
    if (result != CKKS_NATIVE_WIRE_OK) return result;

    // The little-endian layout permits one copy. Other hosts assemble each scalar.
    if (host_is_little_endian()) {
        std::memcpy(frame, wire, sizeof(*frame));
    } else {
        const uint8_t *input = wire;
        for (auto &plane : frame->coefficients)
            for (uint32_t &value : plane) {
                value = load_le<uint32_t>(input);
                input += sizeof(value);
            }
    }
    return CKKS_NATIVE_WIRE_OK;
}
