/** 
 * csl.h - C++ Software model Support Library
 * 
 * This header provides the implementation for DSPBA software models.
 * It is used by generated code and is not intended to be called by
 * user-written code.
 *
 * CSL is header-only for maximum compatibility with user build 
 * systems and to enable inlining of performance-critical paths.
 *
 * Include generated model headers (which include this) in a single 
 * translation unit to optimize compile times.
 */
#pragma once

#ifndef CSL_CSL_H
#define CSL_CSL_H

#include <cmath>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <new>

#if _MSC_VER
#if _MSVC_LANG < 201402L
#error "The software model code requires C++14 or later."
#endif
#else
#if __cplusplus < 201402L
#error "The software model code requires C++14 or later."
#endif
#endif

/**
 * Multi-precision integer support via GMP/MPFR libraries.
 * Define CSL_USE_GMP/CSL_USE_MPFR and link against GMP/MPFR
 * as required.
 * DSPBA-generated build scripts will define these automatically.
 */
#ifdef CSL_USE_GMP
#include "gmp.h"
#endif
#ifdef CSL_USE_MPFR
#include "mpfr.h"
#endif

/**
 * Functions may be marked CSL_FORCE_INLINE where compilers have been 
 * observed to make poor inlining choices for performance-critical code.
 *
 * Conversely, some functions are marked CSL_NO_INLINE - for extremely 
 * large models this can notably improve compile times by removing the 
 * inlining decision from the compiler.
 *
 * CSL_NO_INLINE is disabled for GCC8 due to a compiler bug. 
 */
#ifdef _MSC_VER
#define CSL_FORCE_INLINE __forceinline
#define CSL_NO_INLINE __declspec(noinline) inline
#else
#define CSL_FORCE_INLINE inline __attribute__((always_inline))
#if defined(__GNUC__) && __GNUC__ == 8
#define CSL_NO_INLINE inline
#else
#define CSL_NO_INLINE __attribute__((noinline)) inline
#endif
#endif
#ifndef CSL_EXTERNAL
#define CSL_EXTERNAL extern
#endif

namespace csl
{

#ifdef CSL_USE_GMP
struct mp_temp_allocator;
#endif

/**
 * User-Implemented Functions
 * 
 * Applications must implement these three functions to link successfully.
 * The generated model code uses these for logging and error reporting.
 *
 * - info(const char* msg)  - Log information messages
 * - error(const char* msg) - Log recoverable errors
 * - fatal(const char* msg) - Handle fatal errors (MUST NOT RETURN - use exit/terminate/throw)
 *
 * Example implementation:
 *   void info(const char* msg) { printf("[INFO] %s\n", msg); }
 *   void error(const char* msg) { fprintf(stderr, "[ERROR] %s\n", msg); }
 *   [[noreturn]] void fatal(const char* msg) { 
 *       fprintf(stderr, "[FATAL] %s\n", msg); 
 *       exit(1); 
 *   }
 */
CSL_EXTERNAL void info(const char* msg);
CSL_EXTERNAL void error(const char* msg);
[[noreturn]] CSL_EXTERNAL void fatal(const char* msg);

/** 
 * Utility functions for native types
 */
constexpr bool is_zero(int64_t& value) noexcept;
constexpr bool is_one(int64_t& value) noexcept;
constexpr void negate(int64_t& result, int64_t v) noexcept;
constexpr void complement(int64_t& result, int64_t v) noexcept;
constexpr uint64_t bit_mask_u64(size_t amount) noexcept;
constexpr int64_t bit_mask_i64(size_t amount) noexcept;
constexpr void mask_lower(int64_t& result, int64_t value, size_t width) noexcept;
constexpr bool test_bit(size_t bit_position, int64_t value) noexcept;
constexpr void mask(int64_t& result, int64_t v, size_t bit_width) noexcept;
constexpr void set_upper(int64_t& value, size_t bit_width) noexcept;
/**
 * Sign- or zero-extend `q` to `bit_width` bits in place. When `is_signed`
 * is true and bit `bit_width - 1` is set, sets every bit at position
 * >= bit_width - 1 (sign-extends). Otherwise clears every bit at position
 * >= bit_width (zero-extends).
 */
constexpr void sign_or_zero_extend(int64_t& q, size_t bit_width, bool is_signed) noexcept;
constexpr void not_n(int64_t& result, int64_t value, int bit_width) noexcept;
constexpr void boolean_complement(int64_t& result, int64_t v) noexcept;
constexpr void set_bit(int64_t& result, size_t position, bool value) noexcept;
constexpr void ld_exp(int64_t& result, int64_t value, int exp2) noexcept;
constexpr int64_t abs(int64_t value) noexcept;
constexpr int64_t pow2(int64_t value) noexcept;
constexpr int64_t to_i64(int64_t v) noexcept;
constexpr uint64_t to_u64(int64_t value) noexcept;
/**
 * Sign-extend the low `bit_width` bits of `value` to fill the full
 * int64_t. `bit_width` must be in `[0, 64]`. At 0 the function is a
 * no-op (returns `value` unchanged); at 64 it is also a no-op (the
 * value already fills the int64). Intermediate widths sign-extend
 * bit `bit_width - 1` outward.
 */
constexpr int64_t sign_extend(int64_t value, int bit_width) noexcept;

/** Subtraction (workaround for GCC 8.x/9.x compiler bug for int64_t) */
constexpr void safe_sub(int64_t& result, int64_t a, int64_t b) noexcept;
/** Flushes denormalized floats to zero */
float flush_subnormals(float f) noexcept;
/** Sets NaN value to canonical form for DSP blocks */
float canonicalize_nan(float f) noexcept;

/**
 * Fill algorithm (avoids including <algorithm> header).
 */
template <class It, class T>
It fill_n(It first, size_t count, const T& value) noexcept
{
    for (size_t i = 0; i < count; i++)
    {
        *first++ = value;
    }
    return first;
}

/** Returns the minimum of a and b */
template <class T>
const T& min(const T& a, const T& b) noexcept
{
    return (b < a) ? b : a;
}

/** Returns the array value if it is in bounds, else 0 */
template <class T, size_t N>
T checked_array_value(const T (&values)[N], int64_t index) noexcept
{
    return ((index < static_cast<int64_t>(N)) && (index >= 0)) ? values[index] : T(0);
}

/**
 * Wrapper around mpz_t to automate lifetime management
 * and provide conversion functions.
 */
#ifdef CSL_USE_GMP

static_assert(sizeof(mpir_ui) == sizeof(uint64_t), "Expected mpir_ui to be size of uint64_t");
static_assert(sizeof(mpir_si) == sizeof(int64_t), "Expected mpir_si to be size of int64_t");

struct mp_int_info
{
    uint32_t offset;
    uint16_t count;
    char sign;
};

/**
 * RAII wrapper for GMP mpz_t integers.
 * Copy + move constructors and move-assignment are deleted to prevent
 * unintended allocations or buffer transfers; use copy-assignment
 * (operator=) for explicit copies.
 */
class mp_int
{
public:
    mp_int();
    mp_int(const mp_int& other) = delete;
    mp_int(mp_int&& other) = delete;
    ~mp_int() noexcept;

    /**
     * Returns the value of mpz as a string,
     * e.g. returns "2" if the underlying value is 2
     */
    void str(char* dst, size_t max_size) const noexcept;
    /**
     * Returns the binary value of mpz as a string,
     * e.g. returns "10" if the underlying value is 2
     */
    void str_bin(char* dst, size_t max_size) const noexcept;
    /**
     * Sets the value from a little-endian uint32 array, interpreted as a
     * bit_width-bit two's-complement signed integer.
     *
     * @param array        The packed magnitude. array[0] is the LSB word.
     * @param n            Number of words to read from array. May be larger
     *                     than strictly needed to cover bit_width bits;
     *                     any bits above position bit_width - 1 are
     *                     correctly handled.
     * @param bit_width    The signed width of the value. The bit at
     *                     position bit_width - 1 is the sign bit.
     * @param alloc        Used only when the sign bit is set; pushes one
     *                     allocator frame.
     */
    void set_from_uint_array(const uint32_t* array, size_t n, size_t bit_width, mp_temp_allocator& alloc) noexcept;
    /**
     * Gets the value of this mp int as an array of integers
     */
    void get_as_uint_array(uint32_t* array, size_t n, mp_temp_allocator& alloc) const noexcept;
    /**
     * Sets the value from a string with a given radix 
     */
    void set_from_str(const char* str, int radix);

    mp_int& operator=(const mp_int& other) noexcept;
    mp_int& operator=(mp_int&& other) = delete;
    mp_int& operator=(const mpf_t val) noexcept;
    mp_int& operator=(const mpz_t val) noexcept;
    mp_int& operator=(int64_t i) noexcept;
    mp_int& operator=(uint64_t i) noexcept;
    mp_int& operator=(int32_t i) noexcept;
    mp_int& operator=(uint32_t i) noexcept;

    /** Get the underlying gmp type */
    constexpr mpz_t& get() noexcept;
    constexpr const mpz_t& get() const noexcept;

private:
    mpz_t m_value;
};

void fill_mpz_data(mp_int& dst, const uint64_t* words, uint16_t count, int8_t sign);
void fill_mpz_data(mp_int& dst, const uint64_t* words, const mp_int_info* infos, size_t index);

/**
 * Conversion functions
 */
int64_t to_i64(const mp_int& value) noexcept;
uint64_t to_u64(const mp_int& value) noexcept;
int32_t to_i32(const mp_int& value) noexcept;
uint32_t to_u32(const mp_int& value) noexcept;

/**
 * Inline operators
 */
bool operator==(const mp_int& a, const mp_int& b) noexcept;
bool operator==(const mp_int& a, int32_t b) noexcept;
bool operator==(const mp_int& a, uint32_t b) noexcept;
bool operator==(const mp_int& a, int64_t b) noexcept;
bool operator==(const mp_int& a, uint64_t b) noexcept;
bool operator==(int32_t a, const mp_int& b) noexcept;
bool operator==(uint32_t a, const mp_int& b) noexcept;
bool operator==(int64_t a, const mp_int& b) noexcept;
bool operator==(uint64_t a, const mp_int& b) noexcept;
bool operator!=(const mp_int& a, const mp_int& b) noexcept;
bool operator!=(const mp_int& a, int64_t b) noexcept;
bool operator!=(const mp_int& a, uint64_t b) noexcept;
bool operator!=(const mp_int& a, int32_t b) noexcept;
bool operator!=(const mp_int& a, uint32_t b) noexcept;
bool operator!=(int32_t a, const mp_int& b) noexcept;
bool operator!=(int64_t a, const mp_int& b) noexcept;
bool operator!=(uint32_t a, const mp_int& b) noexcept;
bool operator!=(uint64_t a, const mp_int& b) noexcept;
bool operator<(const mp_int& a, const mp_int& b) noexcept;
bool operator<(const mp_int& a, int64_t b) noexcept;
bool operator>(const mp_int& a, const mp_int& b) noexcept;
bool operator>(const mp_int& a, int64_t b) noexcept;
bool operator<=(const mp_int& a, const mp_int& b) noexcept;
bool operator<=(const mp_int& a, int64_t b) noexcept;
bool operator>=(const mp_int& a, const mp_int& b) noexcept;
bool operator>=(const mp_int& a, int64_t b) noexcept;

mp_int& operator%=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator+=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator-=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator*=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator|=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator&=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator^=(mp_int& a, const mp_int& b) noexcept;
mp_int& operator<<=(mp_int& num, mp_bitcnt_t amount) noexcept;
mp_int& operator>>=(mp_int& num, mp_bitcnt_t amount) noexcept;
mp_int& operator%=(mp_int& a, int64_t b) noexcept;
mp_int& operator+=(mp_int& a, int64_t b) noexcept;
mp_int& operator-=(mp_int& a, int64_t b) noexcept;
mp_int& operator*=(mp_int& a, int64_t b) noexcept;

/**
 * Utility functions for multi-precision types
 */
#ifdef CSL_MP_ALLOCATOR_OVERRIDES
void set_default_mp_allocators() noexcept;
void set_no_grow_mp_allocators() noexcept;
#endif

bool is_zero(const mp_int& value) noexcept;
bool is_one(const mp_int& value) noexcept;
void negate(mp_int& result, const mp_int& v) noexcept;
void complement(mp_int& result, const mp_int& v) noexcept;

void bit_mask_mp_int(mp_int& result, size_t amount) noexcept;
uint64_t to_u64(const mp_int& value) noexcept;
void mask(mp_int& result, const mp_int& v, size_t bit_width) noexcept;
void mask_lower(mp_int& result, const mp_int& value, size_t width) noexcept;
bool test_bit(size_t bit_position, const mp_int& value) noexcept;
void ld_exp(mp_int& result, const mp_int& value, int exp2) noexcept;
void set_upper(mp_int& value, size_t bit_width) noexcept;
/** mp_int overload of sign_or_zero_extend; see the int64 decl in csl.h. */
void sign_or_zero_extend(mp_int& q, size_t bit_width, bool is_signed) noexcept;
/**
 * Flips the lower `bit_width` bits of `value` into `result`, leaving
 * bits at position >= bit_width unchanged. `value` is treated as a raw
 * bit pattern, not a sign-extended signed integer.
 */
void not_n(mp_int& result, const mp_int& value, int bit_width, mp_temp_allocator& alloc) noexcept;
void boolean_complement(mp_int& result, const mp_int& v) noexcept;
void set_bit(mp_int& result, size_t position, bool value) noexcept;

/** Returns array value or zero if index out of bounds */
template <class T, size_t N>
T checked_array_value(const T (&values)[N], const mp_int& index) noexcept
{
    int64_t index_i64 = to_i64(index);
    return ((index_i64 < static_cast<int64_t>(N)) && (index_i64 >= 0)) ? values[index_i64] : T(0);
}

#endif

#ifdef CSL_USE_MPFR
struct mp_float_init_token
{};

/**
 * RAII wrapper for MPFR mpfr_t floats.
 * Copy/move constructors disabled to prevent unintended allocations.
 * Use assignment operator for explicit copies if needed.
 */
struct mp_float
{
    mp_float(mp_prec_t precision);
    mp_float(mp_float_init_token);
    mp_float(const mp_float& other) = delete;
    mp_float(mp_float&& other) = delete;
    ~mp_float() noexcept;

    mp_float& operator=(const mp_float& x) noexcept;
    mp_float& operator=(mp_float&& x) = delete;

    constexpr mpfr_t& get() noexcept;
    constexpr const mpfr_t& get() const noexcept;

private:
    mpfr_t m_value;
};

/**
 * Flush subnormals and canonicalize NaN values 
 */
float sanitize_f32(float value) noexcept;
float sanitize_f32(const mp_int& value) noexcept;
float sanitize_f32(int64_t value) noexcept;

int64_t f32_to_i64(float value) noexcept;
void set(mp_float& dst, int64_t src) noexcept;
void set(mp_float& dst, const mp_int& src) noexcept;

void flush_bad_values(int exponent_width, mpfr_t& o) noexcept;
void mult_fp16_extend(mpfr_t& o, mpfr_t& a, mpfr_t& b) noexcept;
void transfer_fp(int exponent_width, int mantissa_width, mp_float& dst, int64_t src) noexcept;
void transfer_fp(int exponent_width, int mantissa_width, mp_float& dst, const mp_int& src) noexcept;
#ifdef CSL_USE_GMP
void float_pack_bits_default(mpfr_t& ref, int w_exp, int w_frac, mpz_t& z0, bool subnormals_to_zero) noexcept;
#endif

#endif

#ifdef CSL_USE_GMP
/**
 * Stack-based allocator for temporary multi-precision values.
 * Avoids dynamic allocation during model execution for performance.
 * The capacity is set statically to be slightly larger than any construct
 * in the generated software models will require.
 */
struct mp_temp_allocator
{
    mp_temp_allocator() noexcept
    {
#ifdef CSL_USE_MPFR
        for (size_t i = 0; i < capacity; ++i)
        {
            new (get_floats() + i) mp_float(24);
        }
#endif
    }

    ~mp_temp_allocator() noexcept
    {
#ifdef CSL_USE_MPFR
        for (size_t i = 0; i < capacity; ++i)
        {
            get_floats()[i].~mp_float();
        }
#endif
    }
    mp_temp_allocator(const mp_temp_allocator&) = delete;
    mp_temp_allocator(mp_temp_allocator&&) = delete;
    mp_temp_allocator& operator=(const mp_temp_allocator&) = delete;
    mp_temp_allocator& operator=(mp_temp_allocator&&) = delete;

    void reset() noexcept
    {
        m_stack_pos = 0;
        m_stack[0] = {};
    }

    void push() noexcept
    {
        if (m_stack_pos >= max_stack_pos)
        {
            fatal("Multi-precision temporary stack exhausted");
        }
        m_stack[m_stack_pos + 1] = m_stack[m_stack_pos];
        m_stack_pos++;
    }

    void pop() noexcept
    {
        if (m_stack_pos == 0)
        {
            fatal("Multi-precision temporary allocator stack pop() called when at bottom");
        }
        m_stack_pos--;
    }

    mp_int& alloc_int() noexcept
    {
        if (m_stack[m_stack_pos].int_offset >= capacity)
        {
            fatal("Multi-precision temporary allocator exhausted");
        }
        return m_ints[m_stack[m_stack_pos].int_offset++];
    }

#ifdef CSL_USE_MPFR
    mp_float& alloc_float(mp_prec_t prec) noexcept
    {
        if (m_stack[m_stack_pos].float_offset >= capacity)
        {
            fatal("Multi-precision temporary allocator exhausted");
        }
        mp_float& result = get_floats()[m_stack[m_stack_pos].float_offset++];
        mpfr_set_prec(result.get(), prec);
        return result;
    }
#endif

private:
#ifdef CSL_USE_MPFR
    CSL_FORCE_INLINE mp_float* get_floats() noexcept
    {
        return reinterpret_cast<mp_float*>(m_floats_storage);
    }
#endif

    static constexpr size_t capacity = 10;
    static constexpr size_t stack_depth = 3;
    static constexpr size_t max_stack_pos = stack_depth - 1;

    uint32_t m_stack_pos = 0;
    struct StackFrame
    {
        uint16_t int_offset;
        uint16_t float_offset;
    };
    StackFrame m_stack[stack_depth] = {};

    mp_int m_ints[capacity];
#ifdef CSL_USE_MPFR
    alignas(mp_float) unsigned char m_floats_storage[capacity * sizeof(mp_float)];
#endif
};
#endif

/** FIFO configuration used by generated step_fifo calls */
struct fifo_params
{
    /** Total capacity of the FIFO in words */
    int depth;
    /** Number of words in FIFO before 'filled' flag is asserted */
    int fill_threshold;
    /** Number of words in FIFO before 'full' flag is asserted */
    int full_threshold;
    /** Write latency in clock cycles */
    int write_latency;
    /** User synchronous clear control signal */
    int user_sclr;
    /** Base index offset for FIFO addressing */
    int base_index;
};

/** Configuration parameters for the enable generator step. */
struct enable_gen_params
{
    int decim;
    int interp;
    int n_chans;
    int compute_cycle_length;
    int adder_width;
    int valid_inc;
    int ena_inc;
    int last_enable_inc;
    int num_forced_zeros;
    bool use_sequencer_disable;
    bool use_delay_disable;
};

/** Configuration parameters for the chain multiply-add (CMA) step. */
struct cma_add_params
{
    int pipeline_depth;
    int systolic_region_count;
    int systolic_region_size;
    int systolic_region_latency;
    int n_mults;
};

#ifdef CSL_USE_GMP
void safe_sub(mp_int& result, int64_t a, int64_t b, mp_temp_allocator& alloc) noexcept;
void safe_sub(mp_int& result, const mp_int& a, int64_t b, mp_temp_allocator& alloc) noexcept;
void safe_sub(mp_int& result, int64_t a, const mp_int& b, mp_temp_allocator& alloc) noexcept;
void safe_sub(mp_int& result, const mp_int& a, const mp_int& b, mp_temp_allocator& alloc) noexcept;
void safe_sub(int64_t& result, const mp_int& a, int64_t b, mp_temp_allocator& alloc) noexcept;
void safe_sub(int64_t& result, int64_t a, const mp_int& b, mp_temp_allocator& alloc) noexcept;
void safe_sub(int64_t& result, const mp_int& a, const mp_int& b, mp_temp_allocator& alloc) noexcept;
#endif

/**
 * Returns true if the given address is valid within the size
 * of the memory
 */
constexpr bool dual_mem_is_valid_address(int size, int addr) noexcept;
/**
 * Gets a word from the memory.
 * If the given address is invalid, sets the output value to 0xcdcdcdcd.
 */
void dual_mem_get_word(int index, int size, uint32_t byte_width, int64_t* store, int64_t& word, int64_t uaddr, int word_size) noexcept;
/**
 * Puts a word to the memory.
 * Returns true if successful (always unless address is invalid)
 */
bool dual_mem_put_word(int index, int size, uint32_t byte_width, int64_t* store, const int64_t& word, int64_t uaddr,
                       int word_size) noexcept;

#ifdef CSL_USE_GMP
void dual_mem_get_word(int index, int size, uint32_t byte_width, mp_int* store, mp_int& word, int64_t uaddr, int word_size,
                       mp_temp_allocator& alloc) noexcept;
bool dual_mem_put_word(int index, int size, uint32_t byte_width, mp_int* store, const mp_int& word, int64_t uaddr, int word_size,
                       mp_temp_allocator& alloc) noexcept;
#endif

#if defined(CSL_USE_GMP) && defined(CSL_USE_MPFR)
/**
 * IEEE-754 single-precision multiply that handles subnormal rounding
 * via MPFR.
 */
float fp_mul_impl(const float& a, const float& b, mp_temp_allocator& alloc) noexcept;
#endif

/**
 * Utility for buffering model outputs of type T with latency N.
 * 
 * This delay buffer models pipeline latency in hardware by buffering
 * values for N clock cycles. The output at any cycle is the input
 * from N cycles ago.
 * 
 * Usage:
 *   delay_correction<int64_t, 3> delay_buf; // Initialized to zeros
 *   int64_t result = delay_buf.delay(input_value);
 *   // result contains the input from 3 cycles ago
 * 
 * @tparam T Value type to buffer (int64_t, mp_int, etc.)
 * @tparam N Number of cycles of latency (pipeline depth)
 */
template <typename T, size_t N>
struct delay_correction
{
    /** Type used for return values (by-value for fundamentals, by-const-ref for complex types) */
    using value_type = typename std::conditional<std::is_fundamental<T>::value, T, const T&>::type;

    delay_correction() noexcept
    {
        reset();
    }

    void reset() noexcept
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_buffer[i] = 0;
        }
        m_curr = 0;
    }

    value_type delay(int64_t value) noexcept;
#ifdef CSL_USE_GMP
    value_type delay(const mp_int& value) noexcept;
#endif

    constexpr const T& get() const noexcept
    {
        return m_curr;
    }

private:
    size_t m_offset = 0;
    T m_curr;
    T m_buffer[N];
};

/**
 * Utility for buffering model outputs of type T with latency N.
 * 
 * Similar to [[delay_correction]], but operates on arrays of values rather
 * than single values.
 * 
 * Usage:
 *   delay_correction_array<int64_t, 3, 4> delay_buf;
 *   int64_t inputs[4] = {1, 2, 3, 4};
 *   int64_t* outputs = delay_buf.delay(inputs);
 *   // outputs contains inputs from 3 cycles ago for all 4 values
 * 
 * @tparam T Value type for each array element
 * @tparam N Number of cycles of latency
 * @tparam COUNT Number of elements in each array
 */
template <typename T, size_t N, size_t COUNT>
struct delay_correction_array
{
    constexpr delay_correction_array() noexcept
    {
        reset();
    }

    constexpr void reset() noexcept
    {
        for (size_t i = 0; i < COUNT; ++i)
        {
            fill_n(m_buffer[i], N, T(0));
        }
    }

    template <unsigned int ARR_COUNT>
    constexpr T* delay(const T (&values)[ARR_COUNT]) noexcept
    {
        static_assert(ARR_COUNT == COUNT, "Input array size did not match internal array size");
        for (size_t i = 0; i < COUNT; ++i)
        {
            m_output[i] = m_buffer[i][m_offset];
            m_buffer[i][m_offset] = values[i];
        }
        m_offset = (m_offset + 1) % N;
        return m_output;
    }

private:
    size_t m_offset = 0;
    T m_buffer[COUNT][N];
    T m_output[COUNT];
};

/** Generated steps begin */
// Revision: 13

void step_logical_finalize(int64_t& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out) noexcept;
void step_logical_finalize_inv(int64_t& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out) noexcept;
void step_add(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_mul(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_sub(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_addsub(int64_t ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_subadd(int64_t ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_and(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_or(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_xor(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_reducing_or(int64_t& iq, int64_t ia) noexcept;
void step_reducing_nor(int64_t& iq, int64_t ia) noexcept;
void step_reducing_and(int64_t& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept;
void step_ld_exp(int64_t& iq, int64_t ia, int64_t ib, bool reverse) noexcept;
void step_equal(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_nequal(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_reducing_nand(int64_t& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept;
void step_reducing_xor(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_reducing_nxor(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_bit_extract(int64_t& iq, int64_t ia, size_t width, bool signed_extend, int bit_pos) noexcept;
void step_biased_round(int64_t& iq, int64_t ia, int bit) noexcept;
void step_unbiased_round(int64_t& iq, int64_t ia, int bit) noexcept;
void step_bit_reverse(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_sign_bit(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_nsign_bit(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_shift_right(int64_t& iq, int64_t ia, size_t amount) noexcept;
void step_shift_left(int64_t& iq, int64_t ia, size_t amount) noexcept;
void step_test_bit(int64_t& iq, int64_t ia, size_t bit_position) noexcept;
void step_set_bit(int64_t& iq, int64_t ia, size_t bit_position) noexcept;
void step_not(int64_t& iq, int64_t ia, int bit_width) noexcept;
void step_not_signed(int64_t& iq, int64_t ia, int bit_width) noexcept;
void step_sequencer(int64_t& state, int64_t& iq, int64_t ia, size_t offset, int64_t mod, int64_t cross) noexcept;
void step_reduce(int64_t& iq, int64_t ia, size_t bit_width) noexcept;
void step_counter(int64_t& counter, int64_t& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_bit_combine(int64_t& iq, int64_t ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos,
                      size_t next_bit_pos) noexcept;
bool get_lookup_value(const int64_t* values, uint64_t n, uint64_t key, int64_t& out) noexcept;
void step_lookup(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, int64_t ia_in) noexcept;
void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, int64_t& ivalid, int64_t ia_in) noexcept;
void step_lookup_hash(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, int64_t ia_in) noexcept;
void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, int64_t& ivalid,
                                 int64_t ia_in) noexcept;
void step_decode(int64_t& iq0, int64_t ia, int64_t ib, int32_t low, int32_t high, int32_t decode) noexcept;
void step_decode(int64_t& iq0, int64_t& iq1, int64_t ia, int64_t ib, int32_t low, int32_t high, int32_t decode) noexcept;
void step_loadable_counter(int64_t& state_counter, int64_t& state_mod, int64_t& state_inc, int64_t& iq, int64_t ienable, int64_t iload,
                           int64_t load_count, int64_t load_mod, int64_t load_inc) noexcept;
void step_enable_generator(const enable_gen_params& params, int64_t valid, int64_t enable_in, int64_t& enable_out, int64_t& count,
                           int64_t& en_count, int64_t& zero_force_count, int64_t& enable,
                           int64_t& enable_zero_forcing_sequencer) noexcept;
void step_cma_add(const int64_t* const prod_arr, int64_t* const sums_arr, const cma_add_params& params, int64_t sub_ctrl,
                  int64_t neg_ctrl, int64_t& region_sum) noexcept;
void step_fifo(int64_t* store, const fifo_params& params, int64_t& data, int64_t write_en, int64_t read_en, int64_t flush) noexcept;

#ifdef CSL_USE_MPFR

void step_fp_add(int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_fp_sub(int64_t& iq, int64_t ia, int64_t ib) noexcept;

#endif // CSL_USE_MPFR

#ifdef CSL_USE_GMP

void step_logical_finalize(mp_int& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out) noexcept;
void step_logical_finalize_inv(mp_int& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out,
                               mp_temp_allocator& alloc) noexcept;
void step_add(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_add(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_add(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_add(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_add(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_add(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_add(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_mul(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_mul(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_mul(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_mul(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_mul(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_mul(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_mul(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_sub(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_sub(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_sub(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_sub(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_sub(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_sub(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_sub(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_addsub(int64_t ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(int64_t ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_addsub(const mp_int& ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_addsub(const mp_int& ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_addsub(const mp_int& ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_subadd(int64_t ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(int64_t ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept;
void step_subadd(const mp_int& ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_subadd(const mp_int& ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_subadd(const mp_int& ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_and(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_and(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_and(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_and(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_and(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_and(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_and(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_or(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_or(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_or(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_or(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_or(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_or(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_or(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_xor(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_xor(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_xor(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_xor(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_xor(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_xor(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_xor(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_reducing_or(int64_t& iq, const mp_int& ia) noexcept;
void step_reducing_or(mp_int& iq, int64_t ia) noexcept;
void step_reducing_or(mp_int& iq, const mp_int& ia) noexcept;
void step_reducing_nor(int64_t& iq, const mp_int& ia) noexcept;
void step_reducing_nor(mp_int& iq, int64_t ia) noexcept;
void step_reducing_nor(mp_int& iq, const mp_int& ia) noexcept;
void step_reducing_and(mp_int& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept;
void step_reducing_and(int64_t& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept;
void step_reducing_and(mp_int& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept;
void step_ld_exp(int64_t& iq, const mp_int& ia, int64_t ib, bool reverse, mp_temp_allocator& alloc) noexcept;
void step_ld_exp(mp_int& iq, int64_t ia, int64_t ib, bool reverse) noexcept;
void step_ld_exp(mp_int& iq, const mp_int& ia, int64_t ib, bool reverse, mp_temp_allocator& alloc) noexcept;
void step_ld_exp(int64_t& iq, int64_t ia, const mp_int& ib, bool reverse) noexcept;
void step_ld_exp(int64_t& iq, const mp_int& ia, const mp_int& ib, bool reverse, mp_temp_allocator& alloc) noexcept;
void step_ld_exp(mp_int& iq, int64_t ia, const mp_int& ib, bool reverse) noexcept;
void step_ld_exp(mp_int& iq, const mp_int& ia, const mp_int& ib, bool reverse, mp_temp_allocator& alloc) noexcept;
void step_equal(int64_t& iq, int64_t ia, const mp_int& ib) noexcept;
void step_equal(int64_t& iq, const mp_int& ia, int64_t ib) noexcept;
void step_equal(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_equal(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_equal(mp_int& iq, int64_t ia, const mp_int& ib) noexcept;
void step_equal(mp_int& iq, const mp_int& ia, int64_t ib) noexcept;
void step_equal(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_nequal(int64_t& iq, int64_t ia, const mp_int& ib) noexcept;
void step_nequal(int64_t& iq, const mp_int& ia, int64_t ib) noexcept;
void step_nequal(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_nequal(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_nequal(mp_int& iq, int64_t ia, const mp_int& ib) noexcept;
void step_nequal(mp_int& iq, const mp_int& ia, int64_t ib) noexcept;
void step_nequal(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_reducing_nand(int64_t& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept;
void step_reducing_nand(mp_int& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept;
void step_reducing_nand(mp_int& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept;
void step_reducing_xor(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_reducing_xor(mp_int& iq, int64_t ia, size_t bit_width) noexcept;
void step_reducing_xor(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_reducing_nxor(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_reducing_nxor(mp_int& iq, int64_t ia, size_t bit_width) noexcept;
void step_reducing_nxor(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_bit_extract(int64_t& iq, const mp_int& ia, size_t width, bool signed_extend, int bit_pos, mp_temp_allocator& alloc) noexcept;
void step_bit_extract(mp_int& iq, int64_t ia, size_t width, bool signed_extend, int bit_pos) noexcept;
void step_bit_extract(mp_int& iq, const mp_int& ia, size_t width, bool signed_extend, int bit_pos, mp_temp_allocator& alloc) noexcept;
void step_biased_round(int64_t& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept;
void step_biased_round(mp_int& iq, int64_t ia, int bit) noexcept;
void step_biased_round(mp_int& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept;
void step_unbiased_round(int64_t& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept;
void step_unbiased_round(mp_int& iq, int64_t ia, int bit) noexcept;
void step_unbiased_round(mp_int& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept;
void step_bit_reverse(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_bit_reverse(mp_int& iq, int64_t ia, size_t bit_width) noexcept;
void step_bit_reverse(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_sign_bit(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_sign_bit(mp_int& iq, int64_t ia, size_t bit_width) noexcept;
void step_sign_bit(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_nsign_bit(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_nsign_bit(mp_int& iq, int64_t ia, size_t bit_width) noexcept;
void step_nsign_bit(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept;
void step_shift_right(int64_t& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_shift_right(mp_int& iq, int64_t ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_shift_right(mp_int& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_shift_left(int64_t& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_shift_left(mp_int& iq, int64_t ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_shift_left(mp_int& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept;
void step_test_bit(int64_t& iq, const mp_int& ia, size_t bit_position) noexcept;
void step_test_bit(mp_int& iq, int64_t ia, size_t bit_position) noexcept;
void step_test_bit(mp_int& iq, const mp_int& ia, size_t bit_position) noexcept;
void step_set_bit(int64_t& iq, const mp_int& ia, size_t bit_position) noexcept;
void step_set_bit(mp_int& iq, int64_t ia, size_t bit_position) noexcept;
void step_set_bit(mp_int& iq, const mp_int& ia, size_t bit_position) noexcept;
void step_not(int64_t& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept;
void step_not(mp_int& iq, int64_t ia, int bit_width) noexcept;
void step_not(mp_int& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept;
void step_not_signed(int64_t& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept;
void step_not_signed(mp_int& iq, int64_t ia, int bit_width) noexcept;
void step_not_signed(mp_int& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept;
void step_sequencer(mp_int& state, mp_int& iq, const mp_int& ia, size_t offset, int64_t mod, int64_t cross) noexcept;
void step_reduce(int64_t& iq, const mp_int& ia, size_t bit_width, mp_temp_allocator& alloc) noexcept;
void step_reduce(mp_int& iq, int64_t ia, size_t bit_width, mp_temp_allocator& alloc) noexcept;
void step_reduce(mp_int& iq, const mp_int& ia, size_t bit_width, mp_temp_allocator& alloc) noexcept;
void step_counter(int64_t& counter, int64_t& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(int64_t& counter, mp_int& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(int64_t& counter, mp_int& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(mp_int& counter, int64_t& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(mp_int& counter, int64_t& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(mp_int& counter, mp_int& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_counter(mp_int& counter, mp_int& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept;
void step_bit_combine(int64_t& iq, int64_t ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                      mp_temp_allocator& alloc) noexcept;
void step_bit_combine(int64_t& iq, const mp_int& ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                      mp_temp_allocator& alloc) noexcept;
void step_bit_combine(int64_t& iq, const mp_int& ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                      size_t next_bit_pos, mp_temp_allocator& alloc) noexcept;
void step_bit_combine(mp_int& iq, int64_t ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                      mp_temp_allocator& alloc) noexcept;
void step_bit_combine(mp_int& iq, int64_t ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                      mp_temp_allocator& alloc) noexcept;
void step_bit_combine(mp_int& iq, const mp_int& ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                      mp_temp_allocator& alloc) noexcept;
void step_bit_combine(mp_int& iq, const mp_int& ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                      size_t next_bit_pos, mp_temp_allocator& alloc) noexcept;
bool get_lookup_value(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t key, mp_int& out) noexcept;
void step_lookup(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, int64_t ia_in) noexcept;
void step_lookup(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq, int64_t ia_in,
                 mp_temp_allocator& alloc) noexcept;
void step_lookup(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq, int64_t ia_in,
                 mp_temp_allocator& alloc) noexcept;
void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, mp_int& ivalid, int64_t ia_in) noexcept;
void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, int64_t& ivalid, int64_t ia_in) noexcept;
void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, mp_int& ivalid, int64_t ia_in) noexcept;
void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq,
                            int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq, mp_int& ivalid,
                            int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq, int64_t& ivalid,
                            int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq, mp_int& ivalid,
                            int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_hash(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, int64_t ia_in) noexcept;
void step_lookup_hash(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, int64_t& iq, int64_t ia_in,
                      mp_temp_allocator& alloc) noexcept;
void step_lookup_hash(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq, int64_t ia_in,
                      mp_temp_allocator& alloc) noexcept;
void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, mp_int& ivalid,
                                 int64_t ia_in) noexcept;
void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, int64_t& ivalid,
                                 int64_t ia_in) noexcept;
void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, mp_int& ivalid, int64_t ia_in) noexcept;
void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, int64_t& iq,
                                 int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, int64_t& iq,
                                 mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq,
                                 int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq,
                                 mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept;
void step_decode(mp_int& iq0, const mp_int& ia, const mp_int& ib, int32_t low, int32_t high, int32_t decode,
                 mp_temp_allocator& alloc) noexcept;
void step_decode(mp_int& iq0, mp_int& iq1, const mp_int& ia, const mp_int& ib, int32_t low, int32_t high, int32_t decode,
                 mp_temp_allocator& alloc) noexcept;
void step_loadable_counter(int64_t& state_counter, int64_t& state_mod, int64_t& state_inc, mp_int& iq, int64_t ienable, int64_t iload,
                           int64_t load_count, int64_t load_mod, int64_t load_inc) noexcept;
void step_loadable_counter(mp_int& state_counter, mp_int& state_mod, mp_int& state_inc, int64_t& iq, const mp_int& ienable,
                           const mp_int& iload, const mp_int& load_count, const mp_int& load_mod, const mp_int& load_inc) noexcept;
void step_loadable_counter(mp_int& state_counter, mp_int& state_mod, mp_int& state_inc, mp_int& iq, const mp_int& ienable,
                           const mp_int& iload, const mp_int& load_count, const mp_int& load_mod, const mp_int& load_inc) noexcept;
void step_cma_add(const mp_int* const prod_arr, mp_int* const sums_arr, const cma_add_params& params, int64_t sub_ctrl,
                  int64_t neg_ctrl, mp_int& region_sum) noexcept;
void step_fifo(mp_int* store, const fifo_params& params, mp_int& data, int64_t write_en, int64_t read_en, int64_t flush) noexcept;

#ifdef CSL_USE_MPFR

void step_fp_add(int64_t& iq, int64_t ia, const mp_int& ib) noexcept;
void step_fp_add(int64_t& iq, const mp_int& ia, int64_t ib) noexcept;
void step_fp_add(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_fp_add(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_fp_add(mp_int& iq, int64_t ia, const mp_int& ib) noexcept;
void step_fp_add(mp_int& iq, const mp_int& ia, int64_t ib) noexcept;
void step_fp_add(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_fp_sub(int64_t& iq, int64_t ia, const mp_int& ib) noexcept;
void step_fp_sub(int64_t& iq, const mp_int& ia, int64_t ib) noexcept;
void step_fp_sub(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_fp_sub(mp_int& iq, int64_t ia, int64_t ib) noexcept;
void step_fp_sub(mp_int& iq, int64_t ia, const mp_int& ib) noexcept;
void step_fp_sub(mp_int& iq, const mp_int& ia, int64_t ib) noexcept;
void step_fp_sub(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept;
void step_fp_mul(int64_t& iq, int64_t ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(mp_int& iq, int64_t ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mul(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept;
void step_fp_mult_acc(int64_t& iacc, int64_t control, int64_t& iq, int64_t ix, int64_t iy, mp_temp_allocator& alloc) noexcept;
void step_fp_mult_acc(mp_int& iacc, int64_t control, int64_t& iq, int64_t ix, int64_t iy, mp_temp_allocator& alloc) noexcept;

#endif // CSL_USE_MPFR

#endif // CSL_USE_GMP
/** Generated steps end */
} // namespace csl

/**
 * csl_impl.h contains the implementation details for the functions
 * defined in this header.
 */
#include "csl_impl.h"

#endif // CSL_CSL_H
