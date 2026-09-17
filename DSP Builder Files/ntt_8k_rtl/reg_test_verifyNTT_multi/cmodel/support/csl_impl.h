namespace csl
{

constexpr inline bool is_zero(int64_t& value) noexcept
{
    return (value == 0);
}

constexpr inline bool is_one(int64_t& value) noexcept
{
    return (value == 1);
}

constexpr inline void negate(int64_t& result, int64_t v) noexcept
{
    result = -v;
}

constexpr inline void complement(int64_t& result, int64_t v) noexcept
{
    result = ~v;
}

inline constexpr void safe_sub(int64_t& result, int64_t a, int64_t b) noexcept
{
    // casting to u64 works around inlining issue in gcc8.x and gcc9.x
    result = (int64_t)(a - (uint64_t)b);
}

inline constexpr int64_t to_i64(int64_t v) noexcept
{
    return v;
}

inline constexpr uint64_t bit_mask_u64(size_t amount) noexcept
{
    return (amount < 64) ? (1ull << amount) - 1 : 0xFFFFFFFFFFFFFFFFull;
}

inline constexpr int64_t bit_mask_i64(size_t amount) noexcept
{
    return (amount < 64) ? (1ll << amount) - 1 : 0xFFFFFFFFFFFFFFFFll;
}

inline constexpr void mask_lower(int64_t& result, int64_t value, size_t width) noexcept
{
    result = value & bit_mask_i64(width);
}

template <typename TQ, typename TA>
inline std::enable_if_t<std::is_fundamental<TQ>::value && std::is_integral<TA>::value && std::is_signed<TA>::value>
mask_lower(TQ& result, TA ia, size_t width) noexcept
{
    // sign extend first for smaller signed int types
    int64_t i64 = static_cast<int64_t>(ia);
    uint64_t u64 = static_cast<uint64_t>(i64);
    uint64_t mask = (width >= 64) ? ~uint64_t(0) : ((uint64_t(1) << width) - 1);
    uint64_t tmp = u64 & mask;
    std::memcpy(&result, &tmp, sizeof(result));
}

template <typename TQ, typename TA>
inline std::enable_if_t<std::is_fundamental<TQ>::value && std::is_fundamental<TA>::value
                        && (!std::is_integral<TA>::value || std::is_unsigned<TA>::value)>
mask_lower(TQ& result, TA ia, size_t width) noexcept
{
    // for non-signed types, treat as raw bits
    uint64_t u64 = 0;
    std::memcpy(&u64, &ia, sizeof(ia));
    uint64_t mask = (width >= 64) ? ~uint64_t(0) : ((uint64_t(1) << width) - 1);
    uint64_t tmp = u64 & mask;
    std::memcpy(&result, &tmp, sizeof(result));
}

inline constexpr bool test_bit(size_t bit_position, int64_t value) noexcept
{
    if (bit_position > 63)
    {
        // sign extend
        return value < 0;
    }
    else
    {
        uint64_t mask = (1ull << bit_position);
        uint64_t result = (value & mask);
        return result != 0;
    }
}

inline constexpr void mask(int64_t& result, int64_t v, size_t bit_width) noexcept
{
    result = v & bit_mask_i64(bit_width);
}

inline constexpr void set_upper(int64_t& value, size_t bit_width) noexcept
{
    value = ~value;
    mask_lower(value, value, bit_width);
    value = ~value;
}

inline constexpr void sign_or_zero_extend(int64_t& q, size_t bit_width, bool is_signed) noexcept
{
    // Shared body for step_logical_finalize / _inv / step_not_signed.
    if (is_signed && csl::test_bit(bit_width - 1, q))
    {
        csl::set_upper(q, bit_width);
    }
    else
    {
        csl::mask_lower(q, q, bit_width);
    }
}

inline constexpr void not_n(int64_t& result, int64_t value, int bit_width) noexcept
{
    // Flips the lower `bit_width` bits of `value`, leaving bits at
    // position >= bit_width unchanged. `value` is treated as a raw bit
    // pattern, not as a sign-extended signed integer.
    result = value ^ bit_mask_i64(bit_width);
}

inline constexpr void boolean_complement(int64_t& result, int64_t v) noexcept
{
    result = ~v & 1;
}

inline constexpr void set_bit(int64_t& result, size_t position, bool value) noexcept
{
    if (value)
    {
        result |= 1ull << position;
    }
    else
    {
        result &= ~(1ull << position);
    }
}

inline float flush_subnormals(float f) noexcept
{
    if (fabs(f) < 1.17549435082229e-38f)
    {
        // scaling by 0.0f preserves the sign bit
        return f * 0.0f;
    }
    return f;
}

inline float canonicalize_nan(float f) noexcept
{
    if (std::isnan(f))
    {
        uint32_t canonical_value = 0x7FC00000;
        std::memcpy(&f, &canonical_value, sizeof(float));
    }
    return f;
}

inline constexpr void set(int64_t& dst, int64_t src) noexcept
{
    dst = src;
}

template <typename TQ, typename TA>
inline std::enable_if_t<std::is_fundamental<TQ>::value && std::is_integral<TA>::value && std::is_signed<TA>::value> set(TQ& result,
                                                                                                                        TA ia) noexcept
{
    int64_t i64 = static_cast<int64_t>(ia);
    std::memcpy(&result, &i64, sizeof(result));
}

template <typename TQ, typename TA>
inline std::enable_if_t<std::is_fundamental<TQ>::value && std::is_integral<TA>::value && std::is_unsigned<TA>::value>
set(TQ& result, TA ia) noexcept
{
    uint64_t u64 = 0;
    std::memcpy(&u64, &ia, sizeof(ia));
    std::memcpy(&result, &u64, sizeof(result));
}

template <typename TQ, typename TA>
inline std::enable_if_t<std::is_fundamental<TQ>::value> set(TQ& result, double ia) noexcept
{
    uint64_t u64 = 0;
    std::memcpy(&u64, &ia, sizeof(ia));
    std::memcpy(&result, &u64, sizeof(result));
}

template <typename TQ>
inline std::enable_if_t<std::is_fundamental<TQ>::value> set(TQ& result, float ia) noexcept
{
    // Raw value is signed for internal continuity only
    int32_t i32 = 0;
    std::memcpy(&i32, &ia, sizeof(ia));
    int64_t i64 = i32;
    std::memcpy(&result, &i64, sizeof(result));
}

inline constexpr uint64_t to_u64(int64_t value) noexcept
{
    return static_cast<uint64_t>(value);
}

inline constexpr int64_t sign_extend(int64_t value, int bit_width) noexcept
{
    // bit_width 0 and 64 are degenerate no-ops; short-circuit both
    // before the body's signed left shift, which would otherwise hit
    // shift-count-equal-to-type-width UB at width 0 and (pre-C++20,
    // strictly enforced by GCC in constexpr context) signed-shift-
    // of-negative UB at width 64 (shift == 0, value < 0).
    if (bit_width == 0 || bit_width == 64)
    {
        return value;
    }
    int shift = (sizeof(int64_t) * 8) - bit_width;
    return (value << shift) >> shift;
}

inline constexpr void ld_exp(int64_t& result, int64_t value, int exp2) noexcept
{
    if (exp2 < 0)
    {
        exp2 = -exp2;
        if (exp2 <= 63)
        {
            result = value >> exp2;
        }
        else
        {
            fatal("Calling ld_exp with out of range negative exponent for int64");
        }
    }
    else
    {
        if (exp2 <= 63)
        {
            result = value << exp2;
        }
        else
        {
            fatal("Calling ld_exp with out of range positive exponent for int64");
        }
    }
}

inline constexpr bool dual_mem_is_valid_address(int size, int addr) noexcept
{
    return ((addr >= 0) && (addr < static_cast<int>(size)));
}

inline constexpr int64_t abs(int64_t value) noexcept
{
    int64_t shr = value >> 63;
    return (value ^ shr) - shr;
}

inline constexpr int64_t pow2(int64_t value) noexcept
{
    return (((int64_t)1) << value);
}

#ifdef CSL_USE_GMP

inline void fill_mpz_data(mp_int& dst, const uint64_t* words, uint16_t count, int8_t sign)
{
    mpz_import(dst.get(), count, -1, sizeof(uint64_t), 0, 0, words);
    if (sign < 0)
    {
        mpz_neg(dst.get(), dst.get());
    }
}

inline void fill_mpz_data(mp_int& dst, const uint64_t* words, const mp_int_info* infos, size_t index)
{
    mpz_import(dst.get(), infos[index].count, -1, sizeof(uint64_t), 0, 0, words + infos[index].offset);
    if (infos[index].sign < 0)
    {
        mpz_neg(dst.get(), dst.get());
    }
}

inline void set(mp_int& dst, const mp_int& src) noexcept
{
    dst = src;
}

template <typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
inline void set(T& result, const mp_int& ia) noexcept
{
    int64_t i64 = to_i64(ia);
    std::memcpy(&result, &i64, sizeof(result));
}

template <typename TA>
inline std::enable_if_t<std::is_integral<TA>::value && std::is_signed<TA>::value> set(mp_int& result, TA ia) noexcept
{
    int64_t i64 = static_cast<int64_t>(ia);
    result = i64;
}

template <typename TA>
inline std::enable_if_t<std::is_integral<TA>::value && std::is_unsigned<TA>::value> set(mp_int& result, TA ia) noexcept
{
    int64_t i64 = 0;
    std::memcpy(&i64, &ia, sizeof(ia));
    result = i64;
}

inline void set(mp_int& result, float ia) noexcept
{
    // Raw value is signed for internal continuity only
    int32_t i32 = 0;
    std::memcpy(&i32, &ia, sizeof(ia));
    int64_t i64 = i32;
    result = i64;
}

inline void set(mp_int& result, double ia) noexcept
{
    int64_t i64 = 0;
    std::memcpy(&i64, &ia, sizeof(ia));
    result = i64;
}

inline int64_t to_i64(const mp_int& value) noexcept
{
    // mpz_get_si/mpz_get_ui do not have the reinterpret_cast style
    // behaviour wanted here.
    // mpz_export does too much work and may require allocation.
    if (mpz_sgn(value.get()) == 0)
    {
        return 0;
    }
    mp_limb_t limb = mpz_getlimbn(value.get(), 0);
    static_assert(sizeof(mp_limb_t) == sizeof(uint64_t), "Expected mp_limb_t to be size of uint64_t");
    // Apply sign iff value fits in signed range
    if (mpz_sgn(value.get()) < 0 && mpz_sizeinbase(value.get(), 2) <= 63)
    {
        limb = static_cast<uint64_t>(-static_cast<int64_t>(limb));
    }
    return limb;
}

inline uint64_t to_u64(const mp_int& value) noexcept
{
    return static_cast<uint64_t>(to_i64(value));
}

inline int32_t to_i32(const mp_int& value) noexcept
{
    return static_cast<int32_t>(mpz_get_si(value.get()));
}

inline void safe_sub(mp_int& result, int64_t a, int64_t b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& bmp = alloc.alloc_int();
    mp_int& amp = alloc.alloc_int();
    bmp = b;
    amp = a;
    mpz_sub(result.get(), amp.get(), bmp.get());
    alloc.pop();
}

inline void safe_sub(mp_int& result, const mp_int& a, int64_t b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& bmp = alloc.alloc_int();
    bmp = b;
    mpz_sub(result.get(), a.get(), bmp.get());
    alloc.pop();
}

inline void safe_sub(mp_int& result, int64_t a, const mp_int& b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& amp = alloc.alloc_int();
    amp = a;
    mpz_sub(result.get(), amp.get(), b.get());
    alloc.pop();
}

inline void safe_sub(mp_int& result, const mp_int& a, const mp_int& b, mp_temp_allocator& alloc) noexcept
{
    (void)alloc;
    mpz_sub(result.get(), a.get(), b.get());
}

inline void safe_sub(int64_t& result, const mp_int& a, int64_t b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& bmp = alloc.alloc_int();
    bmp = b;
    mpz_sub(bmp.get(), a.get(), bmp.get());
    set(result, bmp);
    alloc.pop();
}

inline void safe_sub(int64_t& result, int64_t a, const mp_int& b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& amp = alloc.alloc_int();
    amp = a;
    mpz_sub(amp.get(), amp.get(), b.get());
    set(result, amp);
    alloc.pop();
}

inline void safe_sub(int64_t& result, const mp_int& a, const mp_int& b, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result_temp = alloc.alloc_int();
    mpz_sub(result_temp.get(), a.get(), b.get());
    set(result, result_temp);
    alloc.pop();
}

inline void mp_int::set_from_str(const char* str, int radix)
{
    if (mpz_set_str(m_value, str, radix) != 0)
    {
        error("Failed to set mp_int from string, defaulting to 0...");
        mpz_set_ui(m_value, 0);
    }
}

inline mp_int& mp_int::operator=(uint64_t i) noexcept
{
    mpz_set_ui(m_value, i);
    return *this;
}

inline mp_int& mp_int::operator=(int64_t i) noexcept
{
    mpz_set_si(m_value, i);
    return *this;
}

inline mp_int& mp_int::operator=(uint32_t i) noexcept
{
    mpz_set_ui(m_value, i);
    return *this;
}

inline mp_int& mp_int::operator=(int32_t i) noexcept
{
    mpz_set_si(m_value, i);
    return *this;
}

inline mp_int& mp_int::operator=(const mpz_t val) noexcept
{
    mpz_set(this->m_value, val);
    return *this;
}

inline mp_int& mp_int::operator=(const mpf_t val) noexcept
{
    mpz_set_f(this->m_value, val);
    return *this;
}

inline mp_int& mp_int::operator=(const mp_int& other) noexcept
{
    // Unconditional mpz_set: cheaper in the common case than guarding on
    // equality (mpz_cmp is already O(min(size_a, size_b)), and most hot-path
    // assignments in generated code are between unequal values), and avoids
    // a data-dependent branch in the middle of every step. Safe because:
    //   - mp_int default-construction always calls mpz_init (so m_value's
    //     _mp_d is never null on the receiver), and move-assignment is
    //     deleted so nothing can clear it;
    //   - mpz_set is documented to be safe for self-assignment.
    mpz_set(this->m_value, other.get());
    return *this;
}

inline mp_int::mp_int()
{
    mpz_init(this->m_value);
}

inline mp_int::~mp_int() noexcept
{
    if (this->m_value[0]._mp_d)
    {
        mpz_clear(this->m_value);
    }
}

inline constexpr mpz_t& mp_int::get() noexcept
{
    return m_value;
}

inline constexpr const mpz_t& mp_int::get() const noexcept
{
    return m_value;
}

CSL_NO_INLINE void mp_int::str(char* dst, size_t max_size) const noexcept
{
    // mpz_get_str assumes the storage location is large enough,
    // so only invoke it if it actually is.
    if (max_size >= (mpz_sizeinbase(m_value, 10) + 2))
    {
        mpz_get_str(dst, 10, m_value);
    }
    else
    {
        if (max_size > 0)
        {
            dst[0] = 0;
        }
        error("mp_int::str(): dst array was too small for output");
    }
}

CSL_NO_INLINE void mp_int::str_bin(char* dst, size_t max_size) const noexcept
{
    // mpz_get_str assumes the storage location is large enough,
    // so only invoke it if it actually is.
    if (max_size >= (mpz_sizeinbase(m_value, 2) + 2))
    {
        mpz_get_str(dst, 2, m_value);
    }
    else
    {
        if (max_size > 0)
        {
            dst[0] = 0;
        }
        error("mp_int::str_bin(): dst array was too small for output");
    }
}

// Two-step decode:
//   1. mpz_import reads 'array' as an unsigned little-endian magnitude in
//      uint32 chunks (array[0] is the LSB). This is the same primitive
//      already used by fill_mpz_data for the uint64 path, applied here at
//      uint32 granularity.
//   2. If the sign bit at position bit_width - 1 is set, reinterpret as
//      two's complement:
//          result = (raw & mask(bit_width - 1)) - 2^(bit_width - 1)
//
// Note: the naive simplification 'result = raw - 2^bit_width' is
// NOT equivalent when 'array' has bits set above position bit_width - 1
// (e.g. a narrow-width signal whose input uint32 array carries arbitrary
// upper bits in its topmost word). The function does not assume callers
// have pre-masked the input to exactly bit_width bits; the formulation
// below masks those upper bits off on the sign-flip branch, while the
// simplification would fold them into the magnitude and produce wrong
// results.
CSL_NO_INLINE void mp_int::set_from_uint_array(const uint32_t* array, size_t n, size_t bit_width, mp_temp_allocator& alloc) noexcept
{
    mpz_import(get(), n, -1, sizeof(uint32_t), 0, 0, array);

    if (bit_width > 1)
    {
        if (test_bit(bit_width - 1, *this))
        {
            alloc.push();
            mp_int& a2 = alloc.alloc_int();
            mp_int& t = alloc.alloc_int();
            mp_int& one = alloc.alloc_int();
            one = int64_t(1);
            mask_lower(a2, *this, bit_width - 1);
            ld_exp(t, one, static_cast<int32_t>(bit_width - 1));
            mpz_sub(get(), a2.get(), t.get());
            alloc.pop();
        }
    }
}

inline void mp_int::get_as_uint_array(uint32_t* arr, size_t n, mp_temp_allocator& alloc) const noexcept
{
    alloc.push();
    mp_int& curr = alloc.alloc_int();
    curr = *this;
    for (size_t i = 0; i < n; ++i)
    {
        uint64_t v = mpz_get_ui(curr.get());
        std::memcpy(&arr[i], &v, sizeof(uint32_t));
        curr >>= 32;
    }
    alloc.pop();
}

#ifdef CSL_MP_ALLOCATOR_OVERRIDES
namespace detail
{

inline void* mp_malloc(size_t size)
{
    return malloc(size);
}

inline void* mp_realloc(void* ptr, size_t old_size, size_t new_size)
{
    (void)old_size;
    return realloc(ptr, new_size);
}

inline void mp_free(void* ptr, size_t size)
{
    (void)size;
    free(ptr);
}

inline void* mp_no_malloc(size_t size)
{
    (void)size;
    fatal("malloc called after MP allocations were disabled");
}

inline void mp_no_free(void* ptr, size_t size)
{
    (void)ptr;
    (void)size;
    fatal("free called after MP allocations were disabled");
}

} // namespace detail

// Routes the GMP allocator through the standard library's malloc / realloc /
// free. CSL does not call this implicitly; tests that flipped to
// set_no_grow_mp_allocators below can call this to restore the default.
inline void set_default_mp_allocators() noexcept
{
    mp_set_memory_functions(&detail::mp_malloc, &detail::mp_realloc, &detail::mp_free);
}

// Verification fence used by CSL's internal tests, included for potentially interested
// users.
// After this call any *new*  mp_int / mp_float allocation (fresh malloc) or deallocation (free)
// triggers csl::fatal, while realloc still routes to libc realloc. The
// amortized realloc-grow of already-existing mpz_t / mpfr_t buffers is
// allowed because CSL's mp_int / mp_temp_allocator / delay_correction
// allocate their slots up front but cannot pre-size them - so first-touch
// of a wider-than-initial value reallocates exactly once per slot and then
// converges. Flipping this on after a warmup pass and then running the
// model is how the test suite verifies no allocation regressions slipped
// in.
inline void set_no_grow_mp_allocators() noexcept
{
    mp_set_memory_functions(&detail::mp_no_malloc, &detail::mp_realloc, &detail::mp_no_free);
}
#endif

inline bool is_zero(const mp_int& value) noexcept
{
    return mpz_cmp_si(value.get(), 0) == 0;
}

inline bool is_one(const mp_int& value) noexcept
{
    return mpz_cmp_si(value.get(), 1) == 0;
}

inline void negate(mp_int& result, const mp_int& v) noexcept
{
    result = v;
    mpz_neg(result.get(), result.get());
}

inline void complement(mp_int& result, const mp_int& v) noexcept
{
    result = v;
    mpz_com(result.get(), result.get());
}

inline bool operator==(const mp_int& a, const mp_int& b) noexcept
{
    return mpz_cmp(a.get(), b.get()) == 0;
}

inline bool operator==(const mp_int& a, int64_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) == 0;
}

inline bool operator==(const mp_int& a, uint64_t b) noexcept
{
    return mpz_cmp_ui(a.get(), b) == 0;
}

inline bool operator==(const mp_int& a, int32_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) == 0;
}

inline bool operator==(const mp_int& a, uint32_t b) noexcept
{
    return mpz_cmp_ui(a.get(), b) == 0;
}

inline bool operator==(int64_t a, const mp_int& b) noexcept
{
    return mpz_cmp_si(b.get(), a) == 0;
}

inline bool operator==(int32_t a, const mp_int& b) noexcept
{
    return mpz_cmp_si(b.get(), a) == 0;
}

inline bool operator==(uint64_t a, const mp_int& b) noexcept
{
    return mpz_cmp_ui(b.get(), a) == 0;
}

inline bool operator==(uint32_t a, const mp_int& b) noexcept
{
    return mpz_cmp_ui(b.get(), a) == 0;
}

inline mp_int& operator%=(mp_int& a, const mp_int& b) noexcept
{
    mpz_mod(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator+=(mp_int& a, const mp_int& b) noexcept
{
    mpz_add(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator-=(mp_int& a, const mp_int& b) noexcept
{
    mpz_sub(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator*=(mp_int& a, const mp_int& b) noexcept
{
    mpz_mul(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator|=(mp_int& a, const mp_int& b) noexcept
{
    mpz_ior(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator&=(mp_int& a, const mp_int& b) noexcept
{
    mpz_and(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator^=(mp_int& a, const mp_int& b) noexcept
{
    mpz_xor(a.get(), a.get(), b.get());
    return a;
}

inline mp_int& operator%=(mp_int& a, int64_t b) noexcept
{
    // Pass |b| to mpz_mod_ui (GMP-floor semantics, divisor sign
    // ignored). Magnitude computed via unsigned subtraction so
    // b == INT64_MIN does not invoke UB on `-b`.
    const uint64_t mag = (b >= 0) ? static_cast<uint64_t>(b) : static_cast<uint64_t>(0) - static_cast<uint64_t>(b);
    mpz_mod_ui(a.get(), a.get(), mag);
    return a;
}

inline mp_int& operator+=(mp_int& a, int64_t b) noexcept
{
    if (b >= 0)
    {
        mpz_add_ui(a.get(), a.get(), static_cast<uint64_t>(b));
    }
    else
    {
        // |b| via unsigned subtraction; `-b` would be UB at INT64_MIN.
        mpz_sub_ui(a.get(), a.get(), static_cast<uint64_t>(0) - static_cast<uint64_t>(b));
    }
    return a;
}

inline mp_int& operator-=(mp_int& a, int64_t b) noexcept
{
    if (b >= 0)
    {
        mpz_sub_ui(a.get(), a.get(), static_cast<uint64_t>(b));
    }
    else
    {
        // |b| via unsigned subtraction; `-b` would be UB at INT64_MIN.
        mpz_add_ui(a.get(), a.get(), static_cast<uint64_t>(0) - static_cast<uint64_t>(b));
    }
    return a;
}

inline mp_int& operator*=(mp_int& a, int64_t b) noexcept
{
    mpz_mul_si(a.get(), a.get(), b);
    return a;
}

inline mp_int& operator<<=(mp_int& num, mp_bitcnt_t amount) noexcept
{
    if (amount > 0)
    {
        mpz_mul_2exp(num.get(), num.get(), amount);
    }
    return num;
}

inline mp_int& operator>>=(mp_int& num, mp_bitcnt_t amount) noexcept
{
    if (amount > 0)
    {
        mpz_fdiv_q_2exp(num.get(), num.get(), amount);
    }
    return num;
}

inline bool operator!=(const mp_int& a, const mp_int& b) noexcept
{
    return mpz_cmp(a.get(), b.get()) != 0;
}

inline bool operator!=(const mp_int& a, int64_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) != 0;
}

inline bool operator!=(const mp_int& a, uint64_t b) noexcept
{
    return mpz_cmp_ui(a.get(), b) != 0;
}

inline bool operator!=(const mp_int& a, int32_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) != 0;
}

inline bool operator!=(const mp_int& a, uint32_t b) noexcept
{
    return mpz_cmp_ui(a.get(), b) != 0;
}

inline bool operator!=(int64_t a, const mp_int& b) noexcept
{
    return mpz_cmp_si(b.get(), a) != 0;
}

inline bool operator!=(uint64_t a, const mp_int& b) noexcept
{
    return mpz_cmp_ui(b.get(), a) != 0;
}

inline bool operator!=(int32_t a, const mp_int& b) noexcept
{
    return mpz_cmp_si(b.get(), a) != 0;
}

inline bool operator!=(uint32_t a, const mp_int& b) noexcept
{
    return mpz_cmp_ui(b.get(), a) != 0;
}

inline bool operator<(const mp_int& a, const mp_int& b) noexcept
{
    return mpz_cmp(a.get(), b.get()) < 0;
}

inline bool operator>(const mp_int& a, const mp_int& b) noexcept
{
    return mpz_cmp(a.get(), b.get()) > 0;
}

inline bool operator<(const mp_int& a, int64_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) < 0;
}

inline bool operator>(const mp_int& a, int64_t b) noexcept
{
    return mpz_cmp_si(a.get(), b) > 0;
}

inline bool operator<=(const mp_int& a, const mp_int& b) noexcept
{
    return !(mpz_cmp(a.get(), b.get()) > 0);
}

inline bool operator>=(const mp_int& a, const mp_int& b) noexcept
{
    return !(mpz_cmp(a.get(), b.get()) < 0);
}

inline bool operator<=(const mp_int& a, int64_t b) noexcept
{
    return !(mpz_cmp_si(a.get(), b) > 0);
}

inline bool operator>=(const mp_int& a, int64_t b) noexcept
{
    return !(mpz_cmp_si(a.get(), b) < 0);
}

inline void bit_mask_mp_int(mp_int& result, size_t amount) noexcept
{
    result = 1;
    result <<= amount;
    result -= 1;
}

inline void mask(mp_int& result, const mp_int& v, size_t bit_width) noexcept
{
    mpz_fdiv_r_2exp(result.get(), v.get(), bit_width);
}

inline void mask_lower(mp_int& result, const mp_int& value, size_t width) noexcept
{
    mpz_fdiv_r_2exp(result.get(), value.get(), width);
}

inline void mask_lower(mp_int& result, int64_t ia, size_t width) noexcept
{
    set(result, ia);
    mask_lower(result, result, width);
}

template <typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
inline void mask_lower(T& result, const mp_int& ia, size_t width) noexcept
{
    int64_t i64 = to_i64(ia);
    mask_lower(i64, i64, width);
    std::memcpy(&result, &i64, sizeof(result));
}

template <typename TA>
inline std::enable_if_t<std::is_integral<TA>::value && std::is_signed<TA>::value> mask_lower(mp_int& result, TA ia,
                                                                                             size_t width) noexcept
{
    int64_t i64 = static_cast<int64_t>(ia);
    set(result, i64);
    mask_lower(result, result, width);
}

template <typename TA>
inline std::enable_if_t<std::is_fundamental<TA>::value && (!std::is_integral<TA>::value || std::is_unsigned<TA>::value)>
mask_lower(mp_int& result, TA ia, size_t width) noexcept
{
    int64_t i64 = 0;
    std::memcpy(&i64, &ia, sizeof(ia));
    set(result, i64);
    mask_lower(result, result, width);
}

inline bool test_bit(size_t bit_position, const mp_int& value) noexcept
{
    return mpz_tstbit(value.get(), bit_position) != 0;
}

inline void ld_exp(mp_int& result, const mp_int& value, int exp2) noexcept
{
    if (exp2 < 0)
    {
        mpz_fdiv_q_2exp(result.get(), value.get(), static_cast<mp_bitcnt_t>(-exp2));
    }
    else
    {
        mpz_mul_2exp(result.get(), value.get(), static_cast<mp_bitcnt_t>(exp2));
    }
}

inline void set_upper(mp_int& value, size_t bit_width) noexcept
{
    mpz_com(value.get(), value.get());
    mask_lower(value, value, bit_width);
    mpz_com(value.get(), value.get());
}

inline void sign_or_zero_extend(mp_int& q, size_t bit_width, bool is_signed) noexcept
{
    if (is_signed && csl::test_bit(bit_width - 1, q))
    {
        csl::set_upper(q, bit_width);
    }
    else
    {
        csl::mask_lower(q, q, bit_width);
    }
}

inline void not_n(mp_int& result, const mp_int& value, int bit_width, mp_temp_allocator& alloc) noexcept
{
    // result = value XOR mask, where mask has the low bit_width bits set.
    // Three GMP ops to build the mask (set_ui / mul_2exp / sub_ui via
    // bit_mask_mp_int) plus one mpz_xor; constant in bit_width, where
    // the prior `mpz_combit` loop was linear.
    alloc.push();
    mp_int& mask = alloc.alloc_int();
    bit_mask_mp_int(mask, static_cast<size_t>(bit_width));
    mpz_xor(result.get(), value.get(), mask.get());
    alloc.pop();
}

inline void boolean_complement(mp_int& result, const mp_int& v) noexcept
{
    complement(result, v);
    // result &= 1
    mpz_set_ui(result.get(), static_cast<mpir_ui>(mpz_tstbit(result.get(), 0)));
}

inline void set_bit(mp_int& result, size_t position, bool value) noexcept
{
    if (value)
    {
        mpz_setbit(result.get(), position);
    }
    else
    {
        mpz_clrbit(result.get(), position);
    }
}

#endif

#ifdef CSL_USE_MPFR
inline void set(mp_float& dst, int64_t src) noexcept
{
    float tmp = sanitize_f32(src);
    mpfr_set_d(dst.get(), static_cast<double>(tmp), MPFR_RNDN);
}

inline void set(mp_float& dst, const mp_int& src) noexcept
{
    float tmp = sanitize_f32(src);
    mpfr_set_d(dst.get(), static_cast<double>(tmp), MPFR_RNDN);
}

inline mp_float& mp_float::operator=(const mp_float& x) noexcept
{
    mpfr_set(m_value, x.get(), GMP_RNDN);
    return *this;
}

inline mp_float::mp_float(mp_float_init_token)
{
    mpfr_init(m_value);
}

inline mp_float::mp_float(mp_prec_t precision)
{
    mpfr_init2(m_value, precision);
}

inline mp_float::~mp_float() noexcept
{
    mpfr_clear(m_value);
}

inline constexpr mpfr_t& mp_float::get() noexcept
{
    return m_value;
}
inline constexpr const mpfr_t& mp_float::get() const noexcept
{
    return m_value;
}

inline float sanitize_f32(float value) noexcept
{
    value = flush_subnormals(value);
    value = canonicalize_nan(value);
    return value;
}

inline float sanitize_f32(const mp_int& value) noexcept
{
    int32_t i32 = static_cast<int32_t>(mpz_get_si(value.get()));
    float f32;
    std::memcpy(&f32, &i32, sizeof(float));
    f32 = flush_subnormals(f32);
    f32 = canonicalize_nan(f32);
    return f32;
}

inline float sanitize_f32(int64_t value) noexcept
{
    int32_t i32 = static_cast<int32_t>(value);
    float f32;
    std::memcpy(&f32, &i32, sizeof(float));
    f32 = flush_subnormals(f32);
    f32 = canonicalize_nan(f32);
    return f32;
}

inline int64_t f32_to_i64(float value) noexcept
{
    int32_t v;
    std::memcpy(&v, &value, sizeof(int32_t));
    return v;
}

#endif

#ifdef CSL_USE_MPFR
#ifdef CSL_USE_GMP
CSL_NO_INLINE void float_pack_bits_default(mpfr_t& ref, int w_exp, int w_frac, mpz_t& z0, bool subnormals_to_zero) noexcept
{
    int bias = (1 << (w_exp - 1)) - 1;

    mpz_t z1;
    mpz_init(z1);

    bool nan = mpfr_nan_p(ref);
    bool inf = mpfr_inf_p(ref);
    int sgn = mpfr_sgn(ref);
    if (nan)
    {
        mpz_set_ui(z1, (1 << (w_exp + 1)) - 1);
        mpz_mul_2exp(z0, z1, w_frac);
        mpz_add_ui(z0, z0, 3);
    }
    else if (sgn == 0)
    {
        mpz_set_ui(z0, 0);
        if (mpfr_signbit(ref))
        {
            mpz_setbit(z0, w_exp + w_frac);
        }
    }
    else if (!inf)
    {
        mp_exp_t ex = mpfr_get_z_exp(z0, ref);
        ex = ex + bias + w_frac;
        if (ex <= 0)
        {
            if (subnormals_to_zero)
            {
                mpz_set_ui(z0, 0);
            }
            else
            {
                mpz_abs(z0, z0);

                mpfr_t y1;
                mpfr_init2(y1, 1 + w_frac);
                mpfr_set_z(y1, z0, GMP_RNDN);
                mpfr_div_2exp(y1, y1, 1 - ex, GMP_RNDN);
                mpfr_rint(y1, y1, GMP_RNDN);
                mpfr_get_z(z0, y1, GMP_RNDN);
                mpfr_clear(y1);
            }
            if (sgn < 0)
            {
                mpz_setbit(z0, w_exp + w_frac);
            }
        }
        else if (ex < ((1 << w_exp) - 1))
        {
            if (sgn < 0)
            {
                mpz_neg(z0, z0);
                mpz_setbit(z0, w_exp + w_frac);
            }
            mpz_clrbit(z0, w_frac);
            mpz_set_ui(z1, ex);
            mpz_mul_2exp(z1, z1, w_frac);
            mpz_ior(z0, z0, z1);
        }
        else
        {
            inf = true;
        }
    }

    if (inf)
    {
        mpz_set_ui(z1, (1 << w_exp) - 1);
        mpz_mul_2exp(z0, z1, w_frac);
        if (sgn < 0)
        {
            mpz_setbit(z0, w_exp + w_frac);
        }
    }

    mpz_clear(z1);
}
#endif

CSL_NO_INLINE void flush_bad_values(int exponent_width, mpfr_t& o) noexcept
{
    if (mpfr_regular_p(o))
    {
        const int64_t exponent_max = bit_mask_i64(exponent_width);
        const int64_t exponent_bias = bit_mask_i64(exponent_width - 1);
        const int64_t exponent_adjust = exponent_bias - 1;
        const int64_t adjusted_exponent = mpfr_get_exp(o) + exponent_adjust;

        if (exponent_max <= adjusted_exponent)
        {
            const int mpfr_sign_v = mpfr_sgn(o);
            mpfr_set_inf(o, mpfr_sign_v);
        }
        else if (adjusted_exponent <= 0)
        {
            const int mpfr_sign_v = mpfr_sgn(o);
            mpfr_set_zero(o, mpfr_sign_v);
        }
    }
}

CSL_NO_INLINE void mult_fp16_extend(mpfr_t& o, mpfr_t& a, mpfr_t& b) noexcept
{
    // 2^-14
    const double smallest_normal = 6.103515625e-5;
    const double in0 = mpfr_get_d(a, MPFR_RNDN);
    const double in1 = mpfr_get_d(b, MPFR_RNDN);
    const bool in0_denorm = (fabs(in0) < smallest_normal);
    const bool in1_denorm = (fabs(in1) < smallest_normal);
    const bool extra_test = (in0_denorm || in1_denorm) && !(mpfr_zero_p(a) || mpfr_zero_p(b));

    if (extra_test)
    {
        // 10 fraction bits + 1 implicit (hidden) bit
        const int out_prec = 11;

        mpfr_t in0_man, in1_man, man_prod, cst_rnd_n;
        mpfr_inits2(out_prec, in0_man, in1_man, cst_rnd_n, (mpfr_ptr)0);
        mpfr_init2(man_prod, 2 * out_prec);

        const int in0_exp = mpfr_get_exp(a);
        const int in1_exp = mpfr_get_exp(b);

        mpfr_set(in0_man, a, MPFR_RNDN);
        mpfr_set(in1_man, b, MPFR_RNDN);
        // For aligning denormalized operands. Smallest normal on half is 1.0 2^-14 but in MPFR this is 0.5 2^-13.
        mpfr_set_exp(in0_man, 1 + (in0_denorm ? (in0_exp + 13) : 0));
        mpfr_set_exp(in1_man, 1 + (in1_denorm ? (in1_exp + 13) : 0));

        mpfr_mul(man_prod, in0_man, in1_man, MPFR_RNDN);
        mpfr_abs(man_prod, man_prod, MPFR_RNDN);

        mpfr_set_si(cst_rnd_n, 1, MPFR_RNDN);
        // -11 is mantissa_width (10) + 1 bit
        mpfr_mul_2si(cst_rnd_n, cst_rnd_n, -11, MPFR_RNDN);
        mpfr_si_sub(cst_rnd_n, 1, cst_rnd_n, MPFR_RNDN);

        if (mpfr_cmp(man_prod, cst_rnd_n) < 0)
        {
            mpfr_mul(o, a, b, MPFR_RNDZ);
        }
        else
        {
            if (mpfr_cmp_si(man_prod, 1) >= 1)
            {
                mpfr_mul(o, a, b, MPFR_RNDN);
            }
            else
            {
                mpfr_mul(o, a, b, MPFR_RNDZ);
                if (mpfr_cmp_si(o, 0) > 0)
                {
                    mpfr_nextabove(o);
                }
                else
                {
                    mpfr_nextbelow(o);
                }
            }
        }
        mpfr_clears(in0_man, in1_man, cst_rnd_n, (mpfr_ptr)0);
    }
    else
    {
        mpfr_mul(o, a, b, MPFR_RNDN);
    }
}

inline int64_t extract_field(int64_t src, int offset, int width) noexcept
{
    return ((src >> offset) & bit_mask_i64(width));
}

CSL_NO_INLINE void transfer_fp(int exponent_width, int mantissa_width, mp_float& dst, int64_t src) noexcept
{
    const int64_t exponent_max = bit_mask_i64(exponent_width);
    const int64_t exponent_bias = bit_mask_i64(exponent_width - 1);

    const int64_t src_int = static_cast<int64_t>(src);
    const int64_t src_sign_field = extract_field(src_int, exponent_width + mantissa_width, 1);
    const int64_t src_exponent_field = extract_field(src_int, mantissa_width, exponent_width);
    const int64_t src_mantissa_field = extract_field(src_int, 0, mantissa_width);

    const int64_t mpfr_sign_v = (src_sign_field == 0) ? 1 : -1;

    if (src_exponent_field == exponent_max)
    {
        if (src_mantissa_field == 0)
        {
            mpfr_set_inf(dst.get(), static_cast<int>(mpfr_sign_v));
        }
        else
        {
            mpfr_set_nan(dst.get());
        }
    }
    else if (src_exponent_field == 0)
    {
        if (src_mantissa_field == 0)
        {
            mpfr_set_zero(dst.get(), static_cast<int>(mpfr_sign_v));
        }
        else
        {
            const int64_t src_signed_mantissa = mpfr_sign_v * src_mantissa_field;
            const int64_t exponent_adjust = (exponent_bias - 1) + mantissa_width;
            mpfr_set_si_2exp(dst.get(), static_cast<long>(src_signed_mantissa),
                             static_cast<mpfr_exp_t>(src_exponent_field - exponent_adjust), MPFR_RNDN);
        }
    }
    else
    {
        const int64_t src_full_mantissa = src_mantissa_field + pow2(mantissa_width);
        const int64_t src_signed_mantissa = mpfr_sign_v * src_full_mantissa;
        const int64_t exponent_adjust = exponent_bias + mantissa_width;
        mpfr_set_si_2exp(dst.get(), static_cast<long>(src_signed_mantissa),
                         static_cast<mpfr_exp_t>(src_exponent_field - exponent_adjust), MPFR_RNDN);
    }
}

inline void transfer_fp(int exponent_width, int mantissa_width, mp_float& dst, const mp_int& src) noexcept
{
    return transfer_fp(exponent_width, mantissa_width, dst, mpz_get_si(src.get()));
}
#endif

#if defined(CSL_USE_GMP) && defined(CSL_USE_MPFR)
CSL_NO_INLINE float fp_mul_impl(const float& x, const float& y, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_float& mp_x = alloc.alloc_float(24);
    mp_float& mp_y = alloc.alloc_float(24);

    // use MPFR for single precision multiply to handle subtlety when rounding close to a subnormal
    mpfr_set_d(mp_x.get(), static_cast<double>(sanitize_f32(x)), GMP_RNDN);
    mpfr_set_d(mp_y.get(), static_cast<double>(sanitize_f32(y)), GMP_RNDN);
    mpfr_mul(mp_x.get(), mp_x.get(), mp_y.get(), GMP_RNDN);

    // single precision exponent
    static constexpr int exp_width = 8;
    static constexpr int e_min_normal = 2 - (1 << (exp_width - 1)) + 1;
    static constexpr int e_max_normal = (1 << (exp_width - 1)) - 1 + 1;

    // Special values pass through unchanged
    if (!mpfr_nan_p(mp_x.get()) && !mpfr_inf_p(mp_x.get()))
    {
        // non-zero for negative
        int sign_x = mpfr_signbit(mp_x.get());
        int current_exp = mpfr_get_exp(mp_x.get());
        if (current_exp < e_min_normal)
        {
            // flush subnormals to zero
            mpfr_set_zero(mp_x.get(), (sign_x == 0) ? 1 : -1);
        }
        else if (current_exp > e_max_normal)
        {
            // overflow to infinity
            mpfr_set_inf(mp_x.get(), (sign_x == 0) ? 1 : -1);
        }
    }
    float q = static_cast<float>(mpfr_get_d(mp_x.get(), GMP_RNDN));
    alloc.pop();
    return sanitize_f32(q);
}
#endif

#ifdef CSL_USE_GMP
CSL_NO_INLINE void dual_mem_get_word(int index, int size, uint32_t byte_width, mp_int* store, mp_int& word, int64_t uaddr,
                                     int word_size, mp_temp_allocator& alloc) noexcept
{
    int addr = static_cast<int>(uaddr);
    const int mem_base = index * size;
    const int byte_addr = addr * word_size;

    if (!dual_mem_is_valid_address(size, byte_addr))
    {
        mpz_set_si(word.get(), 0xcdcdcdcd);
    }
    else if (word_size == 1)
    {
        word = store[mem_base + byte_addr];
    }
    else
    {
        // Little-endian: byte at offset 0 is the LSB and is processed
        // last so that nothing shifts it after it's been OR'd in.
        // Loop walks i = word_size-1 down to 0 inclusive.
        mpz_set_ui(word.get(), 0);
        alloc.push();
        mp_int& temp = alloc.alloc_int();
        for (int i = word_size - 1; i >= 0; --i)
        {
            const mp_int& byte = store[mem_base + byte_addr + i];
            mask_lower(temp, byte, byte_width);
            ld_exp(word, word, static_cast<int>(byte_width));
            mpz_ior(word.get(), word.get(), temp.get());
        }
        alloc.pop();
    }
}
#endif

CSL_NO_INLINE void dual_mem_get_word(int index, int size, uint32_t byte_width, int64_t* store, int64_t& word, int64_t uaddr,
                                     int word_size) noexcept
{
    int addr = static_cast<int>(uaddr);
    const int mem_base = index * size;
    const int byte_addr = addr * word_size;

    if (!dual_mem_is_valid_address(size, byte_addr))
    {
        word = 0xcdcdcdcd;
    }
    else if (word_size == 1)
    {
        word = store[mem_base + byte_addr];
    }
    else
    {
        // See the mp_int sibling above for the LE convention + loop-bound
        // rationale. Same shape mirrored on int64_t storage.
        word = 0;
        int64_t temp;
        for (int i = word_size - 1; i >= 0; --i)
        {
            const int64_t& byte = store[mem_base + byte_addr + i];
            mask_lower(temp, byte, byte_width);
            ld_exp(word, word, static_cast<int>(byte_width));
            word |= temp;
        }
    }
}

#ifdef CSL_USE_GMP

CSL_NO_INLINE bool dual_mem_put_word(int index, int size, uint32_t byte_width, mp_int* store, const mp_int& word, int64_t uaddr,
                                     int word_size, mp_temp_allocator& alloc) noexcept
{
    int addr = static_cast<int>(uaddr);
    const int mem_base = index * size;
    const int byte_addr = addr * word_size;

    if (!dual_mem_is_valid_address(size, byte_addr))
    {
        return false;
    }
    else if (word_size == 1)
    {
        store[mem_base + byte_addr] = word;
        return true;
    }
    else
    {
        // Little-endian: byte at offset 0 is the LSB and is processed
        // first. Each iteration masks out the low byte_width bits of
        // `tmp` into store[i] and then right-shifts `tmp` by byte_width
        // so the next iteration sees the next byte at the bottom.
        alloc.push();
        mp_int& tmp = alloc.alloc_int();
        tmp = word;
        for (int i = 0; i < word_size; ++i)
        {
            mp_int& byte = store[mem_base + byte_addr + i];
            mask_lower(byte, tmp, byte_width);
            ld_exp(tmp, tmp, -static_cast<int>(byte_width));
        }
        alloc.pop();
        return true;
    }
}

#endif

CSL_NO_INLINE bool dual_mem_put_word(int index, int size, uint32_t byte_width, int64_t* store, const int64_t& word, int64_t uaddr,
                                     int word_size) noexcept
{
    int addr = static_cast<int>(uaddr);
    const int mem_base = index * size;
    const int byte_addr = addr * word_size;

    if (!dual_mem_is_valid_address(size, byte_addr))
    {
        return false;
    }
    else if (word_size == 1)
    {
        store[mem_base + byte_addr] = word;
        return true;
    }
    else
    {
        // See the mp_int sibling above for the LE convention + shift-
        // direction rationale. Same shape mirrored on int64_t storage.
        int64_t tmp = word;
        for (int i = 0; i < word_size; ++i)
        {
            int64_t& byte = store[mem_base + byte_addr + i];
            mask_lower(byte, tmp, byte_width);
            ld_exp(tmp, tmp, -static_cast<int>(byte_width));
        }
        return true;
    }
}

template <typename T, size_t N>
inline typename delay_correction<T, N>::value_type delay_correction<T, N>::delay(int64_t value) noexcept
{
    m_curr = m_buffer[m_offset];
    set(m_buffer[m_offset], value);
    m_offset = (m_offset + 1) % N;
    return m_curr;
}

#ifdef CSL_USE_GMP

template <typename T, size_t N>
inline typename delay_correction<T, N>::value_type delay_correction<T, N>::delay(const mp_int& value) noexcept
{
    m_curr = m_buffer[m_offset];
    set(m_buffer[m_offset], value);
    m_offset = (m_offset + 1) % N;
    return m_curr;
}

#endif

/** Generated steps begin */
inline void step_logical_finalize(int64_t& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out) noexcept
{
    csl::sign_or_zero_extend(q, bit_width_in, has_signed_in);
    csl::sign_or_zero_extend(q, bit_width_out, has_signed_out);
}

// --------------------------------

inline void step_logical_finalize_inv(int64_t& q, int bit_width_in, int bit_width_out, bool has_signed_in,
                                      bool has_signed_out) noexcept
{
    csl::not_n(q, q, bit_width_in);
    csl::sign_or_zero_extend(q, bit_width_in, has_signed_in);
    csl::sign_or_zero_extend(q, bit_width_out, has_signed_out);
}

// --------------------------------

inline void step_add(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta += ib;
    set(iq, ta);
}

// --------------------------------

inline void step_mul(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta *= ib;
    set(iq, ta);
}

// --------------------------------

inline void step_sub(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta -= ib;
    set(iq, ta);
}

// --------------------------------

inline void step_addsub(int64_t ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

// --------------------------------

inline void step_subadd(int64_t ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

// --------------------------------

inline void step_and(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
}

// --------------------------------

inline void step_or(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
}

// --------------------------------

inline void step_xor(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
}

// --------------------------------

inline void step_reducing_or(int64_t& iq, int64_t ia) noexcept
{
    set(iq, (ia == 0) ? 0 : 1);
}

// --------------------------------

inline void step_reducing_nor(int64_t& iq, int64_t ia) noexcept
{
    step_reducing_or(iq, ia);
    boolean_complement(iq, iq);
}

// --------------------------------

inline void step_reducing_and(int64_t& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept
{
    (void)is_signed;
    uint64_t uia = static_cast<uint64_t>(ia);
    uint64_t mask = bit_mask_u64(bit_width);
    set(iq, (mask & uia) == mask);
}

// --------------------------------

inline void step_ld_exp(int64_t& iq, int64_t ia, int64_t ib, bool reverse) noexcept
{
    int exp = static_cast<int>(ib);
    int64_t tmp;
    ld_exp(tmp, ia, reverse ? -exp : exp);
    set(iq, tmp);
}

// --------------------------------

inline void step_equal(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

// --------------------------------

inline void step_nequal(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

// --------------------------------

inline void step_reducing_nand(int64_t& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept
{
    step_reducing_and(iq, ia, bit_width, is_signed);
    boolean_complement(iq, iq);
}

// --------------------------------

inline void step_reducing_xor(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    bool result = test_bit(0, ia);
    for (size_t i = 1; i < bit_width; ++i)
    {
        result = result ^ test_bit(i, ia);
    }
    set(iq, result ? 1 : 0);
}

// --------------------------------

inline void step_reducing_nxor(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    step_reducing_xor(iq, ia, bit_width);
    boolean_complement(iq, iq);
}

// --------------------------------

CSL_FORCE_INLINE void step_bit_extract(int64_t& iq, int64_t ia, size_t width, bool signed_extend, int bit_pos) noexcept
{
    int64_t result;
    ld_exp(result, ia, -bit_pos);
    if (signed_extend && test_bit(width - 1, result))
    {
        set_upper(result, width - 1);
    }
    else
    {
        mask_lower(result, result, width);
    }
    set(iq, result);
}

// --------------------------------

inline void step_biased_round(int64_t& iq, int64_t ia, int bit) noexcept
{
    static constexpr int64_t one{1};
    int64_t half;
    ld_exp(half, one, bit - 1);
    half += ia;
    ld_exp(half, half, -bit);
    set(iq, half);
}

// --------------------------------

CSL_NO_INLINE void step_unbiased_round(int64_t& iq, int64_t ia, int bit) noexcept
{
    int64_t half;
    int64_t frac_mask;
    static constexpr int64_t one{1};
    ld_exp(half, one, bit - 1);

    mask_lower(frac_mask, ia, static_cast<uint32_t>(bit));
    if (frac_mask == half)
    {
        // Past this point in the round-to-even branch the `half`
        // slot is free to repurpose. Alias it as the output
        // accumulator `q`. The else arm derives its own half via
        // step_biased_round, so the alias is local to this branch.
        int64_t& q = half;
        ld_exp(q, ia, -bit);
        if (test_bit(0, q))
        {
            q += 1;
        }
        set(iq, q);
    }
    else
    {
        step_biased_round(iq, ia, bit);
    }
}

// --------------------------------

inline void step_bit_reverse(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, 0);
    for (size_t i = 0; i < bit_width; ++i)
    {
        if (test_bit(i, ia))
        {
            set_bit(iq, bit_width - 1 - i, true);
        }
    }
}

// --------------------------------

inline void step_sign_bit(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == true) ? 1 : 0);
}

// --------------------------------

inline void step_nsign_bit(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == false) ? 1 : 0);
}

// --------------------------------

inline void step_shift_right(int64_t& iq, int64_t ia, size_t amount) noexcept
{
    int64_t ta;
    ta = ia;
    ta >>= amount;
    set(iq, ta);
}

// --------------------------------

inline void step_shift_left(int64_t& iq, int64_t ia, size_t amount) noexcept
{
    int64_t ta;
    ta = ia;
    ta <<= amount;
    set(iq, ta);
}

// --------------------------------

inline void step_test_bit(int64_t& iq, int64_t ia, size_t bit_position) noexcept
{
    set(iq, test_bit(bit_position, ia) ? 1 : 0);
}

// --------------------------------

inline void step_set_bit(int64_t& iq, int64_t ia, size_t bit_position) noexcept
{
    set_bit(iq, bit_position, ia != 0);
}

// --------------------------------

inline void step_not(int64_t& iq, int64_t ia, int bit_width) noexcept
{
    int64_t result;
    not_n(result, ia, bit_width);
    set(iq, result);
}

// --------------------------------

inline void step_not_signed(int64_t& iq, int64_t ia, int bit_width) noexcept
{
    int64_t result;
    not_n(result, ia, bit_width);
    set(iq, result);
    // Always signed (per the function name) - pass has_signed=true.
    csl::sign_or_zero_extend(iq, bit_width, true);
}

// --------------------------------

inline void step_sequencer(int64_t& state, int64_t& iq, int64_t ia, size_t offset, int64_t mod, int64_t cross) noexcept
{
    (void)offset;
    const bool enable = ia != 0;
    if (enable)
    {
        state += 1;
        state %= mod;
    }
    iq = (state >= cross) ? 1 : 0;
}

// --------------------------------

CSL_FORCE_INLINE void step_reduce(int64_t& iq, int64_t ia, size_t bit_width) noexcept
{
    // test sign bit
    int64_t a;
    mask_lower(a, ia, bit_width - 1);
    if (test_bit(bit_width - 1, ia) == 0)
    {
        set(iq, a);
    }
    else
    {
        static constexpr int64_t one{1};
        int64_t b;
        ld_exp(b, one, (int)(bit_width - 1));
        safe_sub(iq, a, b);
    }
}

// --------------------------------

inline void step_counter(int64_t& counter, int64_t& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

// --------------------------------

inline void step_bit_combine(int64_t& iq, int64_t ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos) noexcept
{
    if (index == 0)
    {
        int64_t ord;
        int64_t tb;
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        int64_t shifted_b;
        int64_t ibsz;
        ibsz = ib;
        int64_t result;
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
}

// --------------------------------

inline bool get_lookup_value(const int64_t* values, uint64_t n, uint64_t key, int64_t& out) noexcept
{
    if (key < n)
    {
        out = values[key];
        return true;
    }
    out = 0;
    return false;
}

// --------------------------------

CSL_NO_INLINE void step_lookup(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    get_lookup_value(values, n, ia, result);
    set(iq, result);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, int64_t& ivalid,
                                          int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    get_lookup_value(values, n, ia, result);
    set(iq, result);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, int64_t& ivalid,
                                               int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

// --------------------------------

inline void step_decode(int64_t& iq0, int64_t ia, int64_t ib, int32_t low, int32_t high, int32_t decode) noexcept
{
    int64_t tmp_a;
    tmp_a = ia;
    ld_exp(tmp_a, tmp_a, -low);
    mask_lower(tmp_a, tmp_a, static_cast<uint64_t>(static_cast<int64_t>(high) - low + 1));
    bool hit = (tmp_a == decode);
    if (hit)
    {
        set(iq0, ib);
    }
    else
    {
        set(iq0, int64_t(0));
    }
}

// --------------------------------

inline void step_decode(int64_t& iq0, int64_t& iq1, int64_t ia, int64_t ib, int32_t low, int32_t high, int32_t decode) noexcept
{
    int64_t tmp_a;
    tmp_a = ia;
    ld_exp(tmp_a, tmp_a, -low);
    mask_lower(tmp_a, tmp_a, static_cast<uint64_t>(static_cast<int64_t>(high) - low + 1));
    bool hit = (tmp_a == decode);
    if (hit)
    {
        set(iq0, ib);
        set(iq1, int64_t(1));
    }
    else
    {
        set(iq0, int64_t(0));
        set(iq1, int64_t(0));
    }
}

// --------------------------------

CSL_NO_INLINE void step_loadable_counter(int64_t& state_counter, int64_t& state_mod, int64_t& state_inc, int64_t& iq, int64_t ienable,
                                         int64_t iload, int64_t load_count, int64_t load_mod, int64_t load_inc) noexcept
{
    const bool enable = ienable != 0;
    const bool load = iload != 0;

    if (load)
    {
        state_counter = load_count;
        state_mod = load_mod;
        state_inc = load_inc;
        while (state_inc < 0)
        {
            state_inc += load_mod;
        }
    }
    else if (enable)
    {
        // Modulo zero is undefined - just like divide by zero. The hardware will count as
        // if there is no modulo however, and we will do the same. Currently we don't issue
        // a warning.
        state_counter += state_inc;
        if (state_mod != 0)
        {
            state_counter %= state_mod;
        }
    }
    set(iq, state_counter);
}

// --------------------------------

inline void step_enable_generator(const enable_gen_params& params, int64_t valid, int64_t enable_in, int64_t& enable_out,
                                  int64_t& count, int64_t& en_count, int64_t& zero_force_count, int64_t& enable,
                                  int64_t& enable_zero_forcing_sequencer) noexcept
{
    bool last_cycle = false;
    bool force_disable = false;

    // count enabled cycles so we know whether we're on the last enabled cycle
    if (enable != 0)
    {
        en_count++;
        if (en_count == params.compute_cycle_length)
        {
            en_count = 0;
            last_cycle = true;
        }
    }

    // the accumulator
    if (valid != 0)
    {
        count += params.valid_inc;
    }

    if (enable != 0)
    {
        count += params.ena_inc;
        if (last_cycle && (params.compute_cycle_length > 1))
        {
            count += params.last_enable_inc;
        }
    }

    if (params.use_sequencer_disable)
    {
        if (enable_zero_forcing_sequencer != 0)
        {
            ++zero_force_count;
            if (zero_force_count == params.num_forced_zeros)
            {
                enable_zero_forcing_sequencer = 0;
            }
        }

        if (last_cycle)
        {
            enable_zero_forcing_sequencer = 1;
            zero_force_count = 0;
        }

        force_disable = zero_force_count != 0;
    }
    else if (params.use_delay_disable)
    {
        force_disable = last_cycle;
    }

    // update the enable value
    enable = ((count < 0) && (!force_disable) && (enable_in != 0)) ? 1 : 0;

    // latency not modeled at this level, copy current value to output
    enable_out = enable;
}

// --------------------------------

CSL_NO_INLINE void step_cma_add(const int64_t* const prod_arr, int64_t* const sums_arr, const cma_add_params& params, int64_t sub_ctrl,
                                int64_t neg_ctrl, int64_t& region_sum) noexcept
{
    bool sub_ctrl_value = test_bit(0, sub_ctrl);
    bool neg_ctrl_value = test_bit(0, neg_ctrl);

    for (int k = 0, i = 0; i < params.systolic_region_count; ++i)
    {
        const int mults_in_region = csl::min(params.systolic_region_size, params.n_mults - k);
        region_sum = 0;

        if (sub_ctrl_value)
        {
            region_sum = prod_arr[params.pipeline_depth + 1];
            region_sum -= prod_arr[0];
            k += 2;
        }
        else
        {
            for (int j = 0; j < mults_in_region; ++j)
            {
                region_sum += prod_arr[k * (params.pipeline_depth + 1)];
                k++;
            }
        }

        const int i_offset = (i * params.systolic_region_latency);
        if ((i > 0) && (2 == params.systolic_region_latency))
        {
            sums_arr[i_offset - 1] = sums_arr[i_offset];
        }

        if ((i_offset + 1) == params.systolic_region_count)
        {
            sums_arr[i_offset] = region_sum;
        }
        else
        {
            if (neg_ctrl_value)
            {
                sums_arr[i_offset] = sums_arr[i_offset + 1];
                sums_arr[i_offset] -= region_sum;
            }
            else
            {
                sums_arr[i_offset] = sums_arr[i_offset + 1];
                sums_arr[i_offset] += region_sum;
            }
        }
    }
}

// --------------------------------

CSL_NO_INLINE void step_fifo(int64_t* store, const fifo_params& params, int64_t& data, int64_t write_en, int64_t read_en,
                             int64_t flush) noexcept
{
    const int base_index = params.base_index;
    const int read_ptr_index = base_index + 4 + params.depth;
    const int write_ptr_index = base_index + 5 + params.depth;
    const int user_sclr = params.user_sclr;

    int64_t read_ptr_64, write_ptr_64;
    set(read_ptr_64, store[read_ptr_index]);
    set(write_ptr_64, store[write_ptr_index]);
    int read_ptr = static_cast<int>(read_ptr_64);
    int write_ptr = static_cast<int>(write_ptr_64);

    const int twice_depth = 2 * params.depth;
    // (mod 2n) so that full and empty queue states can be disambiguated
    // in both of these cases
    //               mod(write_ptr - read_ptr,   m_depth) == 0
    // but if empty, mod(write_ptr - read_ptr, 2*m_depth) == 0
    // and if full,  mod(write_ptr - read_ptr, 2*m_depth) == m_depth

    int count = ((write_ptr - read_ptr) % twice_depth + twice_depth) % twice_depth;

    // update state independent of input signals
    int write_ptr_delayed;
    int count_delayed;
    bool clearing = user_sclr && flush != 0;

    // update state according to input operands
    if (clearing)
    {
        // Operation during SCLR

        // Flush input is high - clear FIFO state
        int frame_size = 7 + params.depth + params.write_latency; // room for FIFO + circular Buffer + state variables

        for (int i = 0; i < frame_size; ++i)
        {
            // delayed write pipeline -> set zero across the whole frame
            store[base_index + i] = 0;
        }

        // Flush the FIFO by resetting the address counters
        read_ptr = base_index; // Pointers to the start
        write_ptr = base_index;
        write_ptr_delayed = base_index;
        count_delayed = 0; // Counters to zero
        count = 0;

        store[read_ptr_index] = read_ptr; // Reset read pointer
        store[write_ptr_index] = write_ptr; // Reset write pointer
    }
    else
    {
        // Normal operation

        // update state independent of input signals (other than sclr)
        for (int i = params.write_latency; i > 0; --i)
        {
            // delayed write pipeline
            store[write_ptr_index + i] = store[write_ptr_index + i - 1];
        }

        if (write_en != 0)
        {
            if (count == params.depth)
            {
                // Warn on write when full
                info("Warning: write received by FIFO when FIFO is full - this may be intentional");
            }
            if (count < params.depth)
            {
                // enqueue (write enable is high) in circular buffer
                store[base_index + 4 + (write_ptr % params.depth)] = data;
                write_ptr = (write_ptr + 1) % twice_depth;
                ++count;
                store[write_ptr_index] = write_ptr;
            }
        }

        int64_t write_ptr_delayed_64;
        set(write_ptr_delayed_64, store[write_ptr_index + params.write_latency]);
        write_ptr_delayed = static_cast<int>(write_ptr_delayed_64);
        count_delayed = ((write_ptr_delayed - read_ptr) % twice_depth + twice_depth) % twice_depth;

        const int max_count_index = base_index + 6 + params.depth + params.write_latency;
        int64_t max_count;
        set(max_count, store[max_count_index]);
        if (count > max_count)
        {
            store[max_count_index] = count;
        }

        if (read_en != 0)
        {
            // dequeue (read enable is high) from circular buffer
            if (count_delayed > 0)
            {
                read_ptr = (read_ptr + 1) % twice_depth;
                --count_delayed;
                --count;
                store[read_ptr_index] = read_ptr;
            }
            else
            {
                // Warn on read when empty
                error("FIFO_READACK_VALID_LOW");
            }
        }
    }

    // output register update
    bool valid = count_delayed > 0;
    store[base_index + 0] = valid ? 1 : 0;
    store[base_index + 1] = (count >= params.fill_threshold) ? 1 : 0;
    store[base_index + 2] = (count >= params.full_threshold) ? 1 : 0;

    if (count_delayed > 0)
    {
        // update data output register
        store[base_index + 3] = store[base_index + 4 + (read_ptr % params.depth)];
    }
}

// --------------------------------

#ifdef CSL_USE_MPFR

inline void step_fp_add(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

// --------------------------------

inline void step_fp_sub(int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

// --------------------------------

#endif // CSL_USE_MPFR

#ifdef CSL_USE_GMP

inline void step_logical_finalize(mp_int& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out) noexcept
{
    csl::sign_or_zero_extend(q, bit_width_in, has_signed_in);
    csl::sign_or_zero_extend(q, bit_width_out, has_signed_out);
}

// --------------------------------

inline void step_logical_finalize_inv(mp_int& q, int bit_width_in, int bit_width_out, bool has_signed_in, bool has_signed_out,
                                      mp_temp_allocator& alloc) noexcept
{
    csl::not_n(q, q, bit_width_in, alloc);
    csl::sign_or_zero_extend(q, bit_width_in, has_signed_in);
    csl::sign_or_zero_extend(q, bit_width_out, has_signed_out);
}

// --------------------------------

inline void step_add(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_add(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_add(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_add(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta += ib;
    set(iq, ta);
}

inline void step_add(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_add(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_add(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta += ib;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_mul(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_mul(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_mul(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_mul(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta *= ib;
    set(iq, ta);
}

inline void step_mul(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_mul(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_mul(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta *= ib;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_sub(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_sub(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_sub(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_sub(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    ta = ia;
    ta -= ib;
    set(iq, ta);
}

inline void step_sub(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_sub(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

inline void step_sub(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta -= ib;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_addsub(int64_t ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(int64_t ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(int64_t ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(int64_t ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_addsub(int64_t ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(int64_t ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(int64_t ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_addsub(const mp_int& ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_addsub(const mp_int& ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_addsub(const mp_int& ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (!is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

// --------------------------------

inline void step_subadd(int64_t ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(int64_t ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(int64_t ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(int64_t ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_subadd(int64_t ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(int64_t ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(int64_t ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, int64_t& iq, int64_t ia, int64_t ib) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_subadd(const mp_int& ctrl, int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib);
    }
    else
    {
        step_sub(iq, ia, ib);
    }
}

inline void step_subadd(const mp_int& ctrl, mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

inline void step_subadd(const mp_int& ctrl, mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    if (is_zero(ctrl))
    {
        step_add(iq, ia, ib, alloc);
    }
    else
    {
        step_sub(iq, ia, ib, alloc);
    }
}

// --------------------------------

inline void step_and(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_and(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_and(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_and(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
}

inline void step_and(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_and(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_and(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta &= tb;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_or(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_or(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_or(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_or(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
}

inline void step_or(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_or(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_or(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta |= tb;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_xor(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_xor(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_xor(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_xor(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    int64_t ta;
    int64_t tb;
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
}

inline void step_xor(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_xor(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

inline void step_xor(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    mp_int& tb = alloc.alloc_int();
    ta = ia;
    tb = ib;
    ta ^= tb;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_reducing_or(int64_t& iq, const mp_int& ia) noexcept
{
    set(iq, (ia == 0) ? 0 : 1);
}

inline void step_reducing_or(mp_int& iq, int64_t ia) noexcept
{
    set(iq, (ia == 0) ? 0 : 1);
}

inline void step_reducing_or(mp_int& iq, const mp_int& ia) noexcept
{
    set(iq, (ia == 0) ? 0 : 1);
}

// --------------------------------

inline void step_reducing_nor(int64_t& iq, const mp_int& ia) noexcept
{
    step_reducing_or(iq, ia);
    boolean_complement(iq, iq);
}

inline void step_reducing_nor(mp_int& iq, int64_t ia) noexcept
{
    step_reducing_or(iq, ia);
    boolean_complement(iq, iq);
}

inline void step_reducing_nor(mp_int& iq, const mp_int& ia) noexcept
{
    step_reducing_or(iq, ia);
    boolean_complement(iq, iq);
}

// --------------------------------

inline void step_reducing_and(mp_int& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept
{
    (void)is_signed;
    uint64_t uia = static_cast<uint64_t>(ia);
    uint64_t mask = bit_mask_u64(bit_width);
    set(iq, (mask & uia) == mask);
}

// --------------------------------

CSL_NO_INLINE void step_reducing_and(int64_t& iq, const mp_int& ia, size_t bit_width, bool is_signed,
                                     mp_temp_allocator& alloc) noexcept
{
    bool result = false;
    if (is_signed)
    {
        result = (ia == -1);
    }
    else
    {
        // Mask `ia` to bit_width bits, then add 1. A carry out of bit
        // bit_width-1 (i.e. bit bit_width set in the post-increment
        // value) iff bits 0..bit_width-1 were all 1. The mask makes
        // the carry test robust to arbitrary high-bit content in
        // `ia` - callers don't have to pre-mask.
        alloc.push();
        mp_int& q = alloc.alloc_int();
        mask_lower(q, ia, bit_width);
        q += 1;
        result = test_bit(bit_width, q);
        alloc.pop();
    }
    set(iq, result ? 1 : 0);
}

CSL_NO_INLINE void step_reducing_and(mp_int& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept
{
    bool result = false;
    if (is_signed)
    {
        result = (ia == -1);
    }
    else
    {
        // Mask `ia` to bit_width bits, then add 1. A carry out of bit
        // bit_width-1 (i.e. bit bit_width set in the post-increment
        // value) iff bits 0..bit_width-1 were all 1. The mask makes
        // the carry test robust to arbitrary high-bit content in
        // `ia` - callers don't have to pre-mask.
        alloc.push();
        mp_int& q = alloc.alloc_int();
        mask_lower(q, ia, bit_width);
        q += 1;
        result = test_bit(bit_width, q);
        alloc.pop();
    }
    set(iq, result ? 1 : 0);
}

// --------------------------------

inline void step_ld_exp(int64_t& iq, const mp_int& ia, int64_t ib, bool reverse, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    int exp = static_cast<int>(ib);
    mp_int& tmp = alloc.alloc_int();
    ld_exp(tmp, ia, reverse ? -exp : exp);
    set(iq, tmp);
    alloc.pop();
}

inline void step_ld_exp(mp_int& iq, int64_t ia, int64_t ib, bool reverse) noexcept
{
    int exp = static_cast<int>(ib);
    int64_t tmp;
    ld_exp(tmp, ia, reverse ? -exp : exp);
    set(iq, tmp);
}

inline void step_ld_exp(mp_int& iq, const mp_int& ia, int64_t ib, bool reverse, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    int exp = static_cast<int>(ib);
    mp_int& tmp = alloc.alloc_int();
    ld_exp(tmp, ia, reverse ? -exp : exp);
    set(iq, tmp);
    alloc.pop();
}

// --------------------------------

inline void step_ld_exp(int64_t& iq, int64_t ia, const mp_int& ib, bool reverse) noexcept
{
    int ibi = to_i32(ib);
    int64_t tmp;
    ld_exp(tmp, ia, reverse ? (-ibi) : ibi);
    set(iq, tmp);
}

inline void step_ld_exp(int64_t& iq, const mp_int& ia, const mp_int& ib, bool reverse, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    int ibi = to_i32(ib);
    mp_int& tmp = alloc.alloc_int();
    ld_exp(tmp, ia, reverse ? (-ibi) : ibi);
    set(iq, tmp);
    alloc.pop();
}

inline void step_ld_exp(mp_int& iq, int64_t ia, const mp_int& ib, bool reverse) noexcept
{
    int ibi = to_i32(ib);
    int64_t tmp;
    ld_exp(tmp, ia, reverse ? (-ibi) : ibi);
    set(iq, tmp);
}

inline void step_ld_exp(mp_int& iq, const mp_int& ia, const mp_int& ib, bool reverse, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    int ibi = to_i32(ib);
    mp_int& tmp = alloc.alloc_int();
    ld_exp(tmp, ia, reverse ? (-ibi) : ibi);
    set(iq, tmp);
    alloc.pop();
}

// --------------------------------

inline void step_equal(int64_t& iq, int64_t ia, const mp_int& ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(int64_t& iq, const mp_int& ia, int64_t ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(mp_int& iq, int64_t ia, const mp_int& ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(mp_int& iq, const mp_int& ia, int64_t ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

inline void step_equal(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    set(iq, (ia == ib) ? 1 : 0);
}

// --------------------------------

inline void step_nequal(int64_t& iq, int64_t ia, const mp_int& ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(int64_t& iq, const mp_int& ia, int64_t ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(mp_int& iq, int64_t ia, const mp_int& ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(mp_int& iq, const mp_int& ia, int64_t ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

inline void step_nequal(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    set(iq, (ia != ib) ? 1 : 0);
}

// --------------------------------

inline void step_reducing_nand(int64_t& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept
{
    step_reducing_and(iq, ia, bit_width, is_signed, alloc);
    boolean_complement(iq, iq);
}

inline void step_reducing_nand(mp_int& iq, int64_t ia, size_t bit_width, bool is_signed) noexcept
{
    step_reducing_and(iq, ia, bit_width, is_signed);
    boolean_complement(iq, iq);
}

inline void step_reducing_nand(mp_int& iq, const mp_int& ia, size_t bit_width, bool is_signed, mp_temp_allocator& alloc) noexcept
{
    step_reducing_and(iq, ia, bit_width, is_signed, alloc);
    boolean_complement(iq, iq);
}

// --------------------------------

inline void step_reducing_xor(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept
{
    bool result = test_bit(0, ia);
    for (size_t i = 1; i < bit_width; ++i)
    {
        result = result ^ test_bit(i, ia);
    }
    set(iq, result ? 1 : 0);
}

inline void step_reducing_xor(mp_int& iq, int64_t ia, size_t bit_width) noexcept
{
    bool result = test_bit(0, ia);
    for (size_t i = 1; i < bit_width; ++i)
    {
        result = result ^ test_bit(i, ia);
    }
    set(iq, result ? 1 : 0);
}

inline void step_reducing_xor(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept
{
    bool result = test_bit(0, ia);
    for (size_t i = 1; i < bit_width; ++i)
    {
        result = result ^ test_bit(i, ia);
    }
    set(iq, result ? 1 : 0);
}

// --------------------------------

inline void step_reducing_nxor(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept
{
    step_reducing_xor(iq, ia, bit_width);
    boolean_complement(iq, iq);
}

inline void step_reducing_nxor(mp_int& iq, int64_t ia, size_t bit_width) noexcept
{
    step_reducing_xor(iq, ia, bit_width);
    boolean_complement(iq, iq);
}

inline void step_reducing_nxor(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept
{
    step_reducing_xor(iq, ia, bit_width);
    boolean_complement(iq, iq);
}

// --------------------------------

CSL_FORCE_INLINE void step_bit_extract(int64_t& iq, const mp_int& ia, size_t width, bool signed_extend, int bit_pos,
                                       mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    ld_exp(result, ia, -bit_pos);
    if (signed_extend && test_bit(width - 1, result))
    {
        set_upper(result, width - 1);
    }
    else
    {
        mask_lower(result, result, width);
    }
    set(iq, result);
    alloc.pop();
}

CSL_FORCE_INLINE void step_bit_extract(mp_int& iq, int64_t ia, size_t width, bool signed_extend, int bit_pos) noexcept
{
    int64_t result;
    ld_exp(result, ia, -bit_pos);
    if (signed_extend && test_bit(width - 1, result))
    {
        set_upper(result, width - 1);
    }
    else
    {
        mask_lower(result, result, width);
    }
    set(iq, result);
}

CSL_FORCE_INLINE void step_bit_extract(mp_int& iq, const mp_int& ia, size_t width, bool signed_extend, int bit_pos,
                                       mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    ld_exp(result, ia, -bit_pos);
    if (signed_extend && test_bit(width - 1, result))
    {
        set_upper(result, width - 1);
    }
    else
    {
        mask_lower(result, result, width);
    }
    set(iq, result);
    alloc.pop();
}

// --------------------------------

inline void step_biased_round(int64_t& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& one = alloc.alloc_int();
    one = int64_t(1);
    mp_int& half = alloc.alloc_int();
    ld_exp(half, one, bit - 1);
    half += ia;
    ld_exp(half, half, -bit);
    set(iq, half);
    alloc.pop();
}

inline void step_biased_round(mp_int& iq, int64_t ia, int bit) noexcept
{
    static constexpr int64_t one{1};
    int64_t half;
    ld_exp(half, one, bit - 1);
    half += ia;
    ld_exp(half, half, -bit);
    set(iq, half);
}

inline void step_biased_round(mp_int& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& one = alloc.alloc_int();
    one = int64_t(1);
    mp_int& half = alloc.alloc_int();
    ld_exp(half, one, bit - 1);
    half += ia;
    ld_exp(half, half, -bit);
    set(iq, half);
    alloc.pop();
}

// --------------------------------

CSL_NO_INLINE void step_unbiased_round(int64_t& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& half = alloc.alloc_int();
    mp_int& frac_mask = alloc.alloc_int();
    mp_int& one = alloc.alloc_int();
    one = int64_t(1);
    ld_exp(half, one, bit - 1);

    mask_lower(frac_mask, ia, static_cast<uint32_t>(bit));
    if (frac_mask == half)
    {
        // Past this point in the round-to-even branch the `half`
        // slot is free to repurpose. Alias it as the output
        // accumulator `q`. The else arm derives its own half via
        // step_biased_round, so the alias is local to this branch.
        mp_int& q = half;
        ld_exp(q, ia, -bit);
        if (test_bit(0, q))
        {
            q += 1;
        }
        set(iq, q);
    }
    else
    {
        step_biased_round(iq, ia, bit, alloc);
    }
    alloc.pop();
}

CSL_NO_INLINE void step_unbiased_round(mp_int& iq, int64_t ia, int bit) noexcept
{
    int64_t half;
    int64_t frac_mask;
    static constexpr int64_t one{1};
    ld_exp(half, one, bit - 1);

    mask_lower(frac_mask, ia, static_cast<uint32_t>(bit));
    if (frac_mask == half)
    {
        // Past this point in the round-to-even branch the `half`
        // slot is free to repurpose. Alias it as the output
        // accumulator `q`. The else arm derives its own half via
        // step_biased_round, so the alias is local to this branch.
        int64_t& q = half;
        ld_exp(q, ia, -bit);
        if (test_bit(0, q))
        {
            q += 1;
        }
        set(iq, q);
    }
    else
    {
        step_biased_round(iq, ia, bit);
    }
}

CSL_NO_INLINE void step_unbiased_round(mp_int& iq, const mp_int& ia, int bit, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& half = alloc.alloc_int();
    mp_int& frac_mask = alloc.alloc_int();
    mp_int& one = alloc.alloc_int();
    one = int64_t(1);
    ld_exp(half, one, bit - 1);

    mask_lower(frac_mask, ia, static_cast<uint32_t>(bit));
    if (frac_mask == half)
    {
        // Past this point in the round-to-even branch the `half`
        // slot is free to repurpose. Alias it as the output
        // accumulator `q`. The else arm derives its own half via
        // step_biased_round, so the alias is local to this branch.
        mp_int& q = half;
        ld_exp(q, ia, -bit);
        if (test_bit(0, q))
        {
            q += 1;
        }
        set(iq, q);
    }
    else
    {
        step_biased_round(iq, ia, bit, alloc);
    }
    alloc.pop();
}

// --------------------------------

inline void step_bit_reverse(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, 0);
    for (size_t i = 0; i < bit_width; ++i)
    {
        if (test_bit(i, ia))
        {
            set_bit(iq, bit_width - 1 - i, true);
        }
    }
}

inline void step_bit_reverse(mp_int& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, 0);
    for (size_t i = 0; i < bit_width; ++i)
    {
        if (test_bit(i, ia))
        {
            set_bit(iq, bit_width - 1 - i, true);
        }
    }
}

inline void step_bit_reverse(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, 0);
    for (size_t i = 0; i < bit_width; ++i)
    {
        if (test_bit(i, ia))
        {
            set_bit(iq, bit_width - 1 - i, true);
        }
    }
}

// --------------------------------

inline void step_sign_bit(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == true) ? 1 : 0);
}

inline void step_sign_bit(mp_int& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == true) ? 1 : 0);
}

inline void step_sign_bit(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == true) ? 1 : 0);
}

// --------------------------------

inline void step_nsign_bit(int64_t& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == false) ? 1 : 0);
}

inline void step_nsign_bit(mp_int& iq, int64_t ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == false) ? 1 : 0);
}

inline void step_nsign_bit(mp_int& iq, const mp_int& ia, size_t bit_width) noexcept
{
    set(iq, (test_bit(bit_width - 1, ia) == false) ? 1 : 0);
}

// --------------------------------

inline void step_shift_right(int64_t& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta >>= amount;
    set(iq, ta);
    alloc.pop();
}

inline void step_shift_right(mp_int& iq, int64_t ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta >>= amount;
    set(iq, ta);
    alloc.pop();
}

inline void step_shift_right(mp_int& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta >>= amount;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_shift_left(int64_t& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta <<= amount;
    set(iq, ta);
    alloc.pop();
}

inline void step_shift_left(mp_int& iq, int64_t ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta <<= amount;
    set(iq, ta);
    alloc.pop();
}

inline void step_shift_left(mp_int& iq, const mp_int& ia, size_t amount, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& ta = alloc.alloc_int();
    ta = ia;
    ta <<= amount;
    set(iq, ta);
    alloc.pop();
}

// --------------------------------

inline void step_test_bit(int64_t& iq, const mp_int& ia, size_t bit_position) noexcept
{
    set(iq, test_bit(bit_position, ia) ? 1 : 0);
}

inline void step_test_bit(mp_int& iq, int64_t ia, size_t bit_position) noexcept
{
    set(iq, test_bit(bit_position, ia) ? 1 : 0);
}

inline void step_test_bit(mp_int& iq, const mp_int& ia, size_t bit_position) noexcept
{
    set(iq, test_bit(bit_position, ia) ? 1 : 0);
}

// --------------------------------

inline void step_set_bit(int64_t& iq, const mp_int& ia, size_t bit_position) noexcept
{
    set_bit(iq, bit_position, ia != 0);
}

inline void step_set_bit(mp_int& iq, int64_t ia, size_t bit_position) noexcept
{
    set_bit(iq, bit_position, ia != 0);
}

inline void step_set_bit(mp_int& iq, const mp_int& ia, size_t bit_position) noexcept
{
    set_bit(iq, bit_position, ia != 0);
}

// --------------------------------

inline void step_not(int64_t& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    not_n(result, ia, bit_width, alloc);
    set(iq, result);
    alloc.pop();
}

inline void step_not(mp_int& iq, int64_t ia, int bit_width) noexcept
{
    int64_t result;
    not_n(result, ia, bit_width);
    set(iq, result);
}

inline void step_not(mp_int& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    not_n(result, ia, bit_width, alloc);
    set(iq, result);
    alloc.pop();
}

// --------------------------------

inline void step_not_signed(int64_t& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    not_n(result, ia, bit_width, alloc);
    set(iq, result);
    // Always signed (per the function name) - pass has_signed=true.
    csl::sign_or_zero_extend(iq, bit_width, true);
    alloc.pop();
}

inline void step_not_signed(mp_int& iq, int64_t ia, int bit_width) noexcept
{
    int64_t result;
    not_n(result, ia, bit_width);
    set(iq, result);
    // Always signed (per the function name) - pass has_signed=true.
    csl::sign_or_zero_extend(iq, bit_width, true);
}

inline void step_not_signed(mp_int& iq, const mp_int& ia, int bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& result = alloc.alloc_int();
    not_n(result, ia, bit_width, alloc);
    set(iq, result);
    // Always signed (per the function name) - pass has_signed=true.
    csl::sign_or_zero_extend(iq, bit_width, true);
    alloc.pop();
}

// --------------------------------

inline void step_sequencer(mp_int& state, mp_int& iq, const mp_int& ia, size_t offset, int64_t mod, int64_t cross) noexcept
{
    (void)offset;
    const bool enable = ia != 0;
    if (enable)
    {
        state += 1;
        state %= mod;
    }
    iq = (state >= cross) ? 1 : 0;
}

// --------------------------------

CSL_FORCE_INLINE void step_reduce(int64_t& iq, const mp_int& ia, size_t bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    // test sign bit
    mp_int& a = alloc.alloc_int();
    mask_lower(a, ia, bit_width - 1);
    if (test_bit(bit_width - 1, ia) == 0)
    {
        set(iq, a);
    }
    else
    {
        mp_int& one = alloc.alloc_int();
        one = int64_t(1);
        mp_int& b = alloc.alloc_int();
        ld_exp(b, one, (int)(bit_width - 1));
        safe_sub(iq, a, b, alloc);
    }
    alloc.pop();
}

CSL_FORCE_INLINE void step_reduce(mp_int& iq, int64_t ia, size_t bit_width, mp_temp_allocator& alloc) noexcept
{
    // test sign bit
    int64_t a;
    mask_lower(a, ia, bit_width - 1);
    if (test_bit(bit_width - 1, ia) == 0)
    {
        set(iq, a);
    }
    else
    {
        static constexpr int64_t one{1};
        int64_t b;
        ld_exp(b, one, (int)(bit_width - 1));
        safe_sub(iq, a, b, alloc);
    }
}

CSL_FORCE_INLINE void step_reduce(mp_int& iq, const mp_int& ia, size_t bit_width, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    // test sign bit
    mp_int& a = alloc.alloc_int();
    mask_lower(a, ia, bit_width - 1);
    if (test_bit(bit_width - 1, ia) == 0)
    {
        set(iq, a);
    }
    else
    {
        mp_int& one = alloc.alloc_int();
        one = int64_t(1);
        mp_int& b = alloc.alloc_int();
        ld_exp(b, one, (int)(bit_width - 1));
        safe_sub(iq, a, b, alloc);
    }
    alloc.pop();
}

// --------------------------------

inline void step_counter(int64_t& counter, int64_t& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(int64_t& counter, mp_int& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(int64_t& counter, mp_int& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(mp_int& counter, int64_t& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(mp_int& counter, int64_t& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(mp_int& counter, mp_int& iq, int64_t ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

inline void step_counter(mp_int& counter, mp_int& iq, const mp_int& ia, int32_t offset, int32_t inc, int32_t mod) noexcept
{
    const bool enable = (ia != 0);
    if (enable)
    {
        counter += inc;
        counter %= mod;
    }
    set(iq, counter);
    iq += offset;
}

// --------------------------------

inline void step_bit_combine(int64_t& iq, int64_t ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(int64_t& iq, const mp_int& ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(int64_t& iq, const mp_int& ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(mp_int& iq, int64_t ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos, size_t next_bit_pos,
                             mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        int64_t ord;
        int64_t tb;
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(mp_int& iq, int64_t ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(mp_int& iq, const mp_int& ia, int64_t ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

inline void step_bit_combine(mp_int& iq, const mp_int& ia, const mp_int& ib, size_t num_bits, size_t index, size_t bit_pos,
                             size_t next_bit_pos, mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    if (index == 0)
    {
        mp_int& ord = alloc.alloc_int();
        mp_int& tb = alloc.alloc_int();
        ord = ia;
        tb = ib;
        ord |= tb;
        set(iq, ord);
    }
    else
    {
        mp_int& shifted_b = alloc.alloc_int();
        mp_int& ibsz = alloc.alloc_int();
        ibsz = ib;
        mp_int& result = alloc.alloc_int();
        ld_exp(shifted_b, ibsz, static_cast<int>(bit_pos));
        if (index < num_bits - 1)
        {
            // avoid masking out sign of last element
            mask_lower(shifted_b, shifted_b, next_bit_pos);
        }
        if (index == 1)
        {
            // mask 1st element during this iteration, as index = 0 can sometimes be skipped
            set(result, ia);
            mask_lower(result, result, bit_pos);
        }
        else
        {
            result = ia;
        }
        result |= shifted_b;
        set(iq, result);
    }
    alloc.pop();
}

// --------------------------------

inline bool get_lookup_value(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t key, mp_int& out) noexcept
{
    if (key < n)
    {
        csl::fill_mpz_data(out, values, infos, key);
        return true;
    }
    out = 0;
    return false;
}

// --------------------------------

CSL_NO_INLINE void step_lookup(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    get_lookup_value(values, n, ia, result);
    set(iq, result);
}

// --------------------------------

CSL_NO_INLINE void step_lookup(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq,
                               int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq,
                               int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    alloc.pop();
}

// --------------------------------

CSL_NO_INLINE void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, int64_t& iq, mp_int& ivalid,
                                          int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

CSL_NO_INLINE void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, int64_t& ivalid,
                                          int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

CSL_NO_INLINE void step_lookup_with_valid(const int64_t* values, uint64_t n, uint64_t offset, mp_int& iq, mp_int& ivalid,
                                          int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq,
                                          int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, int64_t& iq,
                                          mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq,
                                          int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t offset, mp_int& iq,
                                          mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = ia_u64 - offset;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    get_lookup_value(values, n, ia, result);
    set(iq, result);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, int64_t& iq,
                                    int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_hash(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq,
                                    int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    alloc.pop();
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, int64_t& iq, mp_int& ivalid,
                                               int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

CSL_NO_INLINE void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, int64_t& ivalid,
                                               int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

CSL_NO_INLINE void step_lookup_hash_with_valid(const int64_t* values, uint64_t n, uint64_t mult, mp_int& iq, mp_int& ivalid,
                                               int64_t ia_in) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    int64_t result;
    bool valid = get_lookup_value(values, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
}

// --------------------------------

CSL_NO_INLINE void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult,
                                               int64_t& iq, int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult,
                                               int64_t& iq, mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq,
                                               int64_t& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

CSL_NO_INLINE void step_lookup_hash_with_valid(const uint64_t* values, const mp_int_info* infos, uint64_t n, uint64_t mult, mp_int& iq,
                                               mp_int& ivalid, int64_t ia_in, mp_temp_allocator& alloc) noexcept
{
    uint64_t ia_u64;
    memcpy(&ia_u64, &ia_in, sizeof(uint64_t));
    uint64_t ia = (ia_u64 * mult) % n;
    alloc.push();
    csl::mp_int& result = alloc.alloc_int();
    bool valid = get_lookup_value(values, infos, n, ia, result);
    set(iq, result);
    set(ivalid, valid ? 1 : 0);
    alloc.pop();
}

// --------------------------------

inline void step_decode(mp_int& iq0, const mp_int& ia, const mp_int& ib, int32_t low, int32_t high, int32_t decode,
                        mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& tmp_a = alloc.alloc_int();
    tmp_a = ia;
    ld_exp(tmp_a, tmp_a, -low);
    mask_lower(tmp_a, tmp_a, static_cast<uint64_t>(static_cast<int64_t>(high) - low + 1));
    bool hit = (tmp_a == decode);
    if (hit)
    {
        set(iq0, ib);
    }
    else
    {
        set(iq0, int64_t(0));
    }
    alloc.pop();
}

// --------------------------------

inline void step_decode(mp_int& iq0, mp_int& iq1, const mp_int& ia, const mp_int& ib, int32_t low, int32_t high, int32_t decode,
                        mp_temp_allocator& alloc) noexcept
{
    alloc.push();
    mp_int& tmp_a = alloc.alloc_int();
    tmp_a = ia;
    ld_exp(tmp_a, tmp_a, -low);
    mask_lower(tmp_a, tmp_a, static_cast<uint64_t>(static_cast<int64_t>(high) - low + 1));
    bool hit = (tmp_a == decode);
    if (hit)
    {
        set(iq0, ib);
        set(iq1, int64_t(1));
    }
    else
    {
        set(iq0, int64_t(0));
        set(iq1, int64_t(0));
    }
    alloc.pop();
}

// --------------------------------

CSL_NO_INLINE void step_loadable_counter(int64_t& state_counter, int64_t& state_mod, int64_t& state_inc, mp_int& iq, int64_t ienable,
                                         int64_t iload, int64_t load_count, int64_t load_mod, int64_t load_inc) noexcept
{
    const bool enable = ienable != 0;
    const bool load = iload != 0;

    if (load)
    {
        state_counter = load_count;
        state_mod = load_mod;
        state_inc = load_inc;
        while (state_inc < 0)
        {
            state_inc += load_mod;
        }
    }
    else if (enable)
    {
        // Modulo zero is undefined - just like divide by zero. The hardware will count as
        // if there is no modulo however, and we will do the same. Currently we don't issue
        // a warning.
        state_counter += state_inc;
        if (state_mod != 0)
        {
            state_counter %= state_mod;
        }
    }
    set(iq, state_counter);
}

CSL_NO_INLINE void step_loadable_counter(mp_int& state_counter, mp_int& state_mod, mp_int& state_inc, int64_t& iq,
                                         const mp_int& ienable, const mp_int& iload, const mp_int& load_count, const mp_int& load_mod,
                                         const mp_int& load_inc) noexcept
{
    const bool enable = ienable != 0;
    const bool load = iload != 0;

    if (load)
    {
        state_counter = load_count;
        state_mod = load_mod;
        state_inc = load_inc;
        while (state_inc < 0)
        {
            state_inc += load_mod;
        }
    }
    else if (enable)
    {
        // Modulo zero is undefined - just like divide by zero. The hardware will count as
        // if there is no modulo however, and we will do the same. Currently we don't issue
        // a warning.
        state_counter += state_inc;
        if (state_mod != 0)
        {
            state_counter %= state_mod;
        }
    }
    set(iq, state_counter);
}

CSL_NO_INLINE void step_loadable_counter(mp_int& state_counter, mp_int& state_mod, mp_int& state_inc, mp_int& iq,
                                         const mp_int& ienable, const mp_int& iload, const mp_int& load_count, const mp_int& load_mod,
                                         const mp_int& load_inc) noexcept
{
    const bool enable = ienable != 0;
    const bool load = iload != 0;

    if (load)
    {
        state_counter = load_count;
        state_mod = load_mod;
        state_inc = load_inc;
        while (state_inc < 0)
        {
            state_inc += load_mod;
        }
    }
    else if (enable)
    {
        // Modulo zero is undefined - just like divide by zero. The hardware will count as
        // if there is no modulo however, and we will do the same. Currently we don't issue
        // a warning.
        state_counter += state_inc;
        if (state_mod != 0)
        {
            state_counter %= state_mod;
        }
    }
    set(iq, state_counter);
}

// --------------------------------

CSL_NO_INLINE void step_cma_add(const mp_int* const prod_arr, mp_int* const sums_arr, const cma_add_params& params, int64_t sub_ctrl,
                                int64_t neg_ctrl, mp_int& region_sum) noexcept
{
    bool sub_ctrl_value = test_bit(0, sub_ctrl);
    bool neg_ctrl_value = test_bit(0, neg_ctrl);

    for (int k = 0, i = 0; i < params.systolic_region_count; ++i)
    {
        const int mults_in_region = csl::min(params.systolic_region_size, params.n_mults - k);
        region_sum = 0;

        if (sub_ctrl_value)
        {
            region_sum = prod_arr[params.pipeline_depth + 1];
            region_sum -= prod_arr[0];
            k += 2;
        }
        else
        {
            for (int j = 0; j < mults_in_region; ++j)
            {
                region_sum += prod_arr[k * (params.pipeline_depth + 1)];
                k++;
            }
        }

        const int i_offset = (i * params.systolic_region_latency);
        if ((i > 0) && (2 == params.systolic_region_latency))
        {
            sums_arr[i_offset - 1] = sums_arr[i_offset];
        }

        if ((i_offset + 1) == params.systolic_region_count)
        {
            sums_arr[i_offset] = region_sum;
        }
        else
        {
            if (neg_ctrl_value)
            {
                sums_arr[i_offset] = sums_arr[i_offset + 1];
                sums_arr[i_offset] -= region_sum;
            }
            else
            {
                sums_arr[i_offset] = sums_arr[i_offset + 1];
                sums_arr[i_offset] += region_sum;
            }
        }
    }
}

// --------------------------------

CSL_NO_INLINE void step_fifo(mp_int* store, const fifo_params& params, mp_int& data, int64_t write_en, int64_t read_en,
                             int64_t flush) noexcept
{
    const int base_index = params.base_index;
    const int read_ptr_index = base_index + 4 + params.depth;
    const int write_ptr_index = base_index + 5 + params.depth;
    const int user_sclr = params.user_sclr;

    int64_t read_ptr_64, write_ptr_64;
    set(read_ptr_64, store[read_ptr_index]);
    set(write_ptr_64, store[write_ptr_index]);
    int read_ptr = static_cast<int>(read_ptr_64);
    int write_ptr = static_cast<int>(write_ptr_64);

    const int twice_depth = 2 * params.depth;
    // (mod 2n) so that full and empty queue states can be disambiguated
    // in both of these cases
    //               mod(write_ptr - read_ptr,   m_depth) == 0
    // but if empty, mod(write_ptr - read_ptr, 2*m_depth) == 0
    // and if full,  mod(write_ptr - read_ptr, 2*m_depth) == m_depth

    int count = ((write_ptr - read_ptr) % twice_depth + twice_depth) % twice_depth;

    // update state independent of input signals
    int write_ptr_delayed;
    int count_delayed;
    bool clearing = user_sclr && flush != 0;

    // update state according to input operands
    if (clearing)
    {
        // Operation during SCLR

        // Flush input is high - clear FIFO state
        int frame_size = 7 + params.depth + params.write_latency; // room for FIFO + circular Buffer + state variables

        for (int i = 0; i < frame_size; ++i)
        {
            // delayed write pipeline -> set zero across the whole frame
            store[base_index + i] = 0;
        }

        // Flush the FIFO by resetting the address counters
        read_ptr = base_index; // Pointers to the start
        write_ptr = base_index;
        write_ptr_delayed = base_index;
        count_delayed = 0; // Counters to zero
        count = 0;

        store[read_ptr_index] = read_ptr; // Reset read pointer
        store[write_ptr_index] = write_ptr; // Reset write pointer
    }
    else
    {
        // Normal operation

        // update state independent of input signals (other than sclr)
        for (int i = params.write_latency; i > 0; --i)
        {
            // delayed write pipeline
            store[write_ptr_index + i] = store[write_ptr_index + i - 1];
        }

        if (write_en != 0)
        {
            if (count == params.depth)
            {
                // Warn on write when full
                info("Warning: write received by FIFO when FIFO is full - this may be intentional");
            }
            if (count < params.depth)
            {
                // enqueue (write enable is high) in circular buffer
                store[base_index + 4 + (write_ptr % params.depth)] = data;
                write_ptr = (write_ptr + 1) % twice_depth;
                ++count;
                store[write_ptr_index] = write_ptr;
            }
        }

        int64_t write_ptr_delayed_64;
        set(write_ptr_delayed_64, store[write_ptr_index + params.write_latency]);
        write_ptr_delayed = static_cast<int>(write_ptr_delayed_64);
        count_delayed = ((write_ptr_delayed - read_ptr) % twice_depth + twice_depth) % twice_depth;

        const int max_count_index = base_index + 6 + params.depth + params.write_latency;
        int64_t max_count;
        set(max_count, store[max_count_index]);
        if (count > max_count)
        {
            store[max_count_index] = count;
        }

        if (read_en != 0)
        {
            // dequeue (read enable is high) from circular buffer
            if (count_delayed > 0)
            {
                read_ptr = (read_ptr + 1) % twice_depth;
                --count_delayed;
                --count;
                store[read_ptr_index] = read_ptr;
            }
            else
            {
                // Warn on read when empty
                error("FIFO_READACK_VALID_LOW");
            }
        }
    }

    // output register update
    bool valid = count_delayed > 0;
    store[base_index + 0] = valid ? 1 : 0;
    store[base_index + 1] = (count >= params.fill_threshold) ? 1 : 0;
    store[base_index + 2] = (count >= params.full_threshold) ? 1 : 0;

    if (count_delayed > 0)
    {
        // update data output register
        store[base_index + 3] = store[base_index + 4 + (read_ptr % params.depth)];
    }
}

// --------------------------------

#ifdef CSL_USE_MPFR

inline void step_fp_add(int64_t& iq, int64_t ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(int64_t& iq, const mp_int& ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(mp_int& iq, int64_t ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(mp_int& iq, const mp_int& ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

inline void step_fp_add(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a + b)));
}

// --------------------------------

inline void step_fp_sub(int64_t& iq, int64_t ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(int64_t& iq, const mp_int& ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(int64_t& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(mp_int& iq, int64_t ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(mp_int& iq, int64_t ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(mp_int& iq, const mp_int& ia, int64_t ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

inline void step_fp_sub(mp_int& iq, const mp_int& ia, const mp_int& ib) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(a - b)));
}

// --------------------------------

inline void step_fp_mul(int64_t& iq, int64_t ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(int64_t& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(int64_t& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(int64_t& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(mp_int& iq, int64_t ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(mp_int& iq, int64_t ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(mp_int& iq, const mp_int& ia, int64_t ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

inline void step_fp_mul(mp_int& iq, const mp_int& ia, const mp_int& ib, mp_temp_allocator& alloc) noexcept
{
    float a = sanitize_f32(ia);
    float b = sanitize_f32(ib);
    set(iq, f32_to_i64(sanitize_f32(fp_mul_impl(a, b, alloc))));
}

// --------------------------------

CSL_NO_INLINE void step_fp_mult_acc(int64_t& iacc, int64_t control, int64_t& iq, int64_t ix, int64_t iy,
                                    mp_temp_allocator& alloc) noexcept
{
    step_fp_mul(iq, ix, iy, alloc);
    if (control == 0)
    {
        // acc = (x*y)
        set(iacc, iq);
    }
    else
    {
        step_fp_add(iacc, iacc, iq);
    }
    set(iq, iacc);
}

CSL_NO_INLINE void step_fp_mult_acc(mp_int& iacc, int64_t control, int64_t& iq, int64_t ix, int64_t iy,
                                    mp_temp_allocator& alloc) noexcept
{
    step_fp_mul(iq, ix, iy, alloc);
    if (control == 0)
    {
        // acc = (x*y)
        set(iacc, iq);
    }
    else
    {
        step_fp_add(iacc, iacc, iq);
    }
    set(iq, iacc);
}

// --------------------------------

#endif // CSL_USE_MPFR

#endif // CSL_USE_GMP
/** Generated steps end */

} // namespace csl
