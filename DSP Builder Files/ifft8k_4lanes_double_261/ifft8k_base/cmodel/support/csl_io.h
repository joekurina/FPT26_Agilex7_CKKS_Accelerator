/** 
 * csl_io.h declares/defines the functions/types used by
 * the DSPBA software model ATB implementation.
 *
 * CSL is an abbreviation of 'C++ software model Support Library'
 *
 * The ATBs use standard library IO functionality and 
 * so require additional headers versus those included in
 * csl.h which aims to be minimal.
 *
 * CSL is header-only for maximum compatibility with user build 
 * systems and to enable inlining of performance-critical paths.
 */
#pragma once

#ifndef CSL_CSL_IO_H
#define CSL_CSL_IO_H

#include "csl.h"
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdarg>

/**
 * To achieve gigabyte/sec+ throughput when reading stimulus files,
 * the stimulus reader implementations use SIMD instructions that require
 * the target machine supports SSE2.
 * Defining [[CSL_NO_SSE2]] will fall back to a non-vectorized implementation.
 */
#ifndef CSL_NO_SSE2
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <emmintrin.h>
#endif
#endif

namespace csl
{

/**
 * Compares two .stm files, returning true if they match. Usage:
 *
 *   - compare_stm_files("result.stm", "reference.stm");
 *
 * The comparison requires that:
 *   - The files contain the same number of lines
 *   - For each line, there are the same number of columns each with the same value
 *
 * Differing line endings, whitespace etc are allowed.
 */
bool compare_stm_files(const char* result_file_name, const char* reference_file_name);

/**
 * Writes stimulus files in DSPBA .stm format.
 *
 * Usage:
 *   - output_stimulus_file file("out_file.stm");
 *   - file.write_stm_data(value, width);
 *   - file.close();
 *
 * The primary use of this class is to output
 * stm files in the software model ATB for comparison
 * against the Simulink result.
 */
class output_stimulus_file
{
public:
    output_stimulus_file();
    output_stimulus_file(const char* filename);
    /** Copying/moving disabled as usage patterns should not require either */
    output_stimulus_file(const output_stimulus_file&) = delete;
    output_stimulus_file(output_stimulus_file&&) = delete;
    output_stimulus_file& operator=(const output_stimulus_file&) = delete;
    output_stimulus_file& operator=(output_stimulus_file&&) = delete;
    ~output_stimulus_file();

    void open(const char* filename);
    void close();

    /** Writes out the value to the file */
    void write_stm_data(int64_t v, int64_t width);
    void write_stm_data(int32_t v, int64_t width);
    void write_stm_data(int16_t v, int64_t width);
    void write_stm_data(int8_t v, int64_t width);
    void write_stm_data(double v);
    void write_stm_data(float v);

#ifdef CSL_USE_GMP
    /** Writes out the value to the file */
    void write_stm_data(const mp_int& v, int64_t width);
#endif

    /** Proceed to the next line/row of output values */
    void next_line();
    /** Get the total number of lines/rows written */
    size_t get_line_count() const;

private:
    void write_stm_data_impl(int64_t v, int64_t width);

private:
#ifdef CSL_USE_GMP
    mp_int m_mask;
    mp_temp_allocator m_temp_alloc;
#endif
    size_t m_line_count = 0;
    std::ofstream m_file;
};

namespace detail
{

/** Buffer for reading stimulus file lines */
struct stimulus_line_buffer
{
    size_t pos;
    size_t size;
    static constexpr size_t BUFFER_SIZE = 1024;
    char data[BUFFER_SIZE];
};

/**
 * Stores the data for a stimulus file line and the offsets
 * of the number values in that line
 */
struct stimulus_line_data
{
    size_t numbers_str_length;
    uint32_t curr_index;
    std::vector<char> numbers_str;
    std::vector<size_t> col_offsets;
};

} // namespace detail

enum class stimulus_format
{
    SIGNED,
    BINARY,
    UNKNOWN
};

/**
 * Reads stimulus files in DSPBA .stm format.
 *
 * Usage:
 *   stimulus_file file("input.stm", stimulus_format::SIGNED);
 *   file.next_line();
 *   int32_t value_out;
 *   file.get(value_out, 1);
 *   ...
 *
 * Files are buffered and read in chunks, then processed line-by-line.
 * Note: not thread-safe - use separate instances per thread.
 */
class stimulus_file
{
private:
    /**
     * Gets the next 32-bit integer.
     * @returns True if a value was successfully read
     */
    bool get_u32(uint32_t& value);
    void discover_format();

public:
    stimulus_file();
    /** The same as calling the default constructor followed by open() */
    stimulus_file(const char* file_name, stimulus_format format);
    /** Copying/moving disabled as usage patterns should not require either */
    stimulus_file(const stimulus_file&) = delete;
    stimulus_file(stimulus_file&&) = delete;
    stimulus_file& operator=(const stimulus_file&) = delete;
    stimulus_file& operator=(stimulus_file&&) = delete;
    ~stimulus_file();

    /** Attempts to close the open file */
    void close();

    /**
     * Opens a new file
     * @param file_name Path of the stimulus file to be opened
     * @returns True if the file was opened successfully
     */
    bool open(const char* file_name, stimulus_format format);

    /** Returns true if a file is currently open */
    bool is_open() const;

    /** Returns true if the current row of the stimulus file has been read in full */
    bool is_line_fully_read() const;

    /**
     * Progresses to the next line, warning if the previous has not been read. Must be called first after open().
     * @returns True if a new line was successfully read
     */
    bool next_line();

    /**
     * Skips the next n lines. Must be called first after open().
     * @returns True if all lines were successfully read and skipped
     */
    bool skip_lines(size_t n);

    /**
     * Skips the next line, warning if the previous has not been read. Must be called first after open().
     * @returns True if a new line was successfully read and skipped
     */
    bool skip_line();

    /**
     * Skips a number of entries
     * @param count the number of entries to skip, count is an integer because
     * it is possible to skip backwards and reread a value, although there is no anticipated
     * need to do this.
     */
    void skip(int count);

    /**
     * Gets the next bit_width integer.
     * @returns True if a value was successfully read
     */
    bool get(int64_t& value, size_t bit_width);
    bool get(int32_t& value, size_t bit_width);
    bool get(int16_t& value, size_t bit_width);
    bool get(int8_t& value, size_t bit_width);

    /**
     * Gets the next double-precision value (reading 64 bits).
     * @returns True if a value was successfully read
     */
    bool get(double& value);

    /**
     * Gets the next single-precision value (reading 32 bits).
     * @returns True if a value was successfully read
     */
    bool get(float& value);

#ifdef CSL_USE_GMP
    /**
     * Gets the next arbitrary precision unsigned integer
     * @returns True if a value was successfully read
     * @param var The mpz_t to store the result in
     * @param bit_width the number of bits to read for the variable
     */
    bool get(mp_int& var, size_t bit_width);
    bool get(uint32_t* values, size_t bit_width, size_t capacity);
#endif

    stimulus_format get_stm_format() const
    {
        return m_stm_format;
    }

private:
#ifdef CSL_USE_GMP
    mp_temp_allocator m_temp_alloc;
    std::vector<uint32_t> m_wide_value_buffer;
#endif

    std::ifstream m_stm_file;

    detail::stimulus_line_buffer m_buffer{};
    detail::stimulus_line_data m_line{};

    stimulus_format m_stm_format;
};

/** Implementation begins */
namespace detail
{

static constexpr size_t MAX_LOG_MESSAGE_LENGTH = 1024;

/** Call csl::error with a formatted message */
inline void error_fmt(const char* msg, ...)
{
    char buffer[MAX_LOG_MESSAGE_LENGTH];
    va_list args;
    va_start(args, msg);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, msg, args);
    va_end(args);
    error(buffer);
}

/** Call csl::info with a formatted message */
inline void info_fmt(const char* msg, ...)
{
    char buffer[MAX_LOG_MESSAGE_LENGTH];
    va_list args;
    va_start(args, msg);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, msg, args);
    va_end(args);
    info(buffer);
}

static constexpr int64_t pow2mask[65] = {(((int64_t)1) << 0) - 1,
                                         (((int64_t)1) << 1) - 1,
                                         (((int64_t)1) << 2) - 1,
                                         (((int64_t)1) << 3) - 1,
                                         (((int64_t)1) << 4) - 1,
                                         (((int64_t)1) << 5) - 1,
                                         (((int64_t)1) << 6) - 1,
                                         (((int64_t)1) << 7) - 1,
                                         (((int64_t)1) << 8) - 1,
                                         (((int64_t)1) << 9) - 1,
                                         (((int64_t)1) << 10) - 1,
                                         (((int64_t)1) << 11) - 1,
                                         (((int64_t)1) << 12) - 1,
                                         (((int64_t)1) << 13) - 1,
                                         (((int64_t)1) << 14) - 1,
                                         (((int64_t)1) << 15) - 1,
                                         (((int64_t)1) << 16) - 1,
                                         (((int64_t)1) << 17) - 1,
                                         (((int64_t)1) << 18) - 1,
                                         (((int64_t)1) << 19) - 1,
                                         (((int64_t)1) << 20) - 1,
                                         (((int64_t)1) << 21) - 1,
                                         (((int64_t)1) << 22) - 1,
                                         (((int64_t)1) << 23) - 1,
                                         (((int64_t)1) << 24) - 1,
                                         (((int64_t)1) << 25) - 1,
                                         (((int64_t)1) << 26) - 1,
                                         (((int64_t)1) << 27) - 1,
                                         (((int64_t)1) << 28) - 1,
                                         (((int64_t)1) << 29) - 1,
                                         (((int64_t)1) << 30) - 1,
                                         (((int64_t)1) << 31) - 1,
                                         (((int64_t)1) << 32) - 1,
                                         (((int64_t)1) << 33) - 1,
                                         (((int64_t)1) << 34) - 1,
                                         (((int64_t)1) << 35) - 1,
                                         (((int64_t)1) << 36) - 1,
                                         (((int64_t)1) << 37) - 1,
                                         (((int64_t)1) << 38) - 1,
                                         (((int64_t)1) << 39) - 1,
                                         (((int64_t)1) << 40) - 1,
                                         (((int64_t)1) << 41) - 1,
                                         (((int64_t)1) << 42) - 1,
                                         (((int64_t)1) << 43) - 1,
                                         (((int64_t)1) << 44) - 1,
                                         (((int64_t)1) << 45) - 1,
                                         (((int64_t)1) << 46) - 1,
                                         (((int64_t)1) << 47) - 1,
                                         (((int64_t)1) << 48) - 1,
                                         (((int64_t)1) << 49) - 1,
                                         (((int64_t)1) << 50) - 1,
                                         (((int64_t)1) << 51) - 1,
                                         (((int64_t)1) << 52) - 1,
                                         (((int64_t)1) << 53) - 1,
                                         (((int64_t)1) << 54) - 1,
                                         (((int64_t)1) << 55) - 1,
                                         (((int64_t)1) << 56) - 1,
                                         (((int64_t)1) << 57) - 1,
                                         (((int64_t)1) << 58) - 1,
                                         (((int64_t)1) << 59) - 1,
                                         (((int64_t)1) << 60) - 1,
                                         (((int64_t)1) << 61) - 1,
                                         (((int64_t)1) << 62) - 1,
                                         (int64_t)0x7FFFFFFFFFFFFFFFLL,
                                         ~0};

/**
 * Returns in 'output' the binary representation of 'v' as a string,
 * up to the 'width' number of bits.
 * e.g: toBinary(..., 2, 3) returns "10", toBinary(..., 2, 2) returns "10", toBinary(..., 2, 1) returns "0"
 * 'output_size' - the size of the output buffer - must be at least 1 larger than 'width'
 */
CSL_NO_INLINE void to_binary(char* output, size_t output_size, uint64_t v, unsigned width)
{
    if (output_size < (width + 1))
    {
        error("Output buffer for 'to_binary' was too small, skipping...");
        if (output_size > 0)
        {
            output[0] = '\0';
        }
        return;
    }
    uint64_t pow2 = ((uint64_t)1) << (width - 1);
    for (unsigned i = 0; i < width; i++)
    {
        if (i > 0)
        {
            pow2 = pow2 >> 1;
        }
        if (v >= pow2)
        {
            output[i] = '1';
            v -= pow2;
        }
        else
        {
            output[i] = '0';
        }
    }
    output[width] = '\0';
}

/** Copy dst to src, transforming non-number characters to 0 */
CSL_NO_INLINE void copy_and_transform_line(const char* src, char* dst, size_t n)
{
#ifdef CSL_NO_SSE2
    size_t i = 0;
    for (; i < n; ++i)
    {
        char c = src[i];
        if (((c >= '0') && (c <= '9')) || (c == '.') || (c == '-') || (c == '+'))
        {
            dst[i] = c;
        }
        else
        {
            dst[i] = '\0';
        }
    }
#else
    size_t i = 0;
    for (; i + 16 <= n; i += 16)
    {
        __m128i chunk = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src + i));
        __m128i mask_nums =
            _mm_and_si128(_mm_cmpgt_epi8(chunk, _mm_set1_epi8('0' - 1)), _mm_cmplt_epi8(chunk, _mm_set1_epi8('9' + 1)));
        __m128i mask_dot = _mm_cmpeq_epi8(chunk, _mm_set1_epi8('.'));
        __m128i mask_minus = _mm_cmpeq_epi8(chunk, _mm_set1_epi8('-'));
        __m128i mask_plus = _mm_cmpeq_epi8(chunk, _mm_set1_epi8('+'));
        __m128i mask_any = _mm_or_si128(mask_nums, mask_dot);
        mask_any = _mm_or_si128(mask_any, mask_minus);
        mask_any = _mm_or_si128(mask_any, mask_plus);
        __m128i result = _mm_and_si128(mask_any, chunk);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(dst + i), result);
    }
    for (; i < n; ++i)
    {
        char c = src[i];

        if (((c >= '0') && (c <= '9')) || (c == '.') || (c == '-') || (c == '+'))
        {
            dst[i] = c;
        }
        else
        {
            dst[i] = '\0';
        }
    }
#endif
}

/**
 * Return true and set newline_pos to the first new line offset in the buffer if
 * a new line character is found, else return false
 */
CSL_NO_INLINE bool find_newline(const char* buffer, size_t start, size_t end, size_t& newline_pos)
{
#ifdef CSL_NO_SSE2
    size_t i = start;
    for (; i < end; ++i)
    {
        if (buffer[i] == '\n')
        {
            newline_pos = i;
            return true;
        }
    }
    return false;
#else
    const __m128i newline = _mm_set1_epi8('\n');
    size_t i = start;
    for (; i + 16 <= end; i += 16)
    {
        __m128i chunk = _mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer + i));
        __m128i cmp = _mm_cmpeq_epi8(chunk, newline);
        int mask = _mm_movemask_epi8(cmp);
        if (mask != 0)
        {
#ifdef _MSC_VER
            unsigned int offset = _tzcnt_u32(static_cast<unsigned int>(mask));
#else
            unsigned int offset = static_cast<unsigned int>(__builtin_ctz(mask));
#endif
            newline_pos = i + offset;
            return true;
        }
    }
    for (; i < end; ++i)
    {
        if (buffer[i] == '\n')
        {
            newline_pos = i;
            return true;
        }
    }
    return false;
#endif
}

/** Finds and stores number start offsets */
CSL_NO_INLINE void parse_line(stimulus_line_data& line)
{
    const char* data = line.numbers_str.data();
    line.col_offsets.clear();
    if (line.numbers_str_length > 0)
    {
        if (data[0] != 0)
        {
            line.col_offsets.push_back(0);
        }
    }
#ifdef CSL_NO_SSE2
    for (size_t i = 1; i < line.numbers_str_length; ++i)
    {
        bool is_valid = line.numbers_str[i] != 0;
        bool prev_is_valid = line.numbers_str[i - 1] != 0;
        if (is_valid && !prev_is_valid)
        {
            line.col_offsets.push_back(i);
        }
    }
#else
    size_t i = 1;
    for (; i + 16 <= line.numbers_str_length; i += 16)
    {
        __m128i curr = _mm_loadu_si128(reinterpret_cast<const __m128i*>(data + i));
        __m128i prevs = _mm_loadu_si128(reinterpret_cast<const __m128i*>(data + i - 1));
        __m128i curr_nonzero = _mm_cmpgt_epi8(curr, _mm_setzero_si128());
        __m128i prev_zero = _mm_cmpeq_epi8(prevs, _mm_setzero_si128());
        __m128i starts_mask = _mm_and_si128(curr_nonzero, prev_zero);
        int mask = _mm_movemask_epi8(starts_mask);
        while (mask)
        {
#ifdef _MSC_VER
            unsigned int bit = _tzcnt_u32(static_cast<unsigned int>(mask));
#else
            unsigned int bit = static_cast<unsigned int>(__builtin_ctz(mask));
#endif
            line.col_offsets.push_back(i + bit);
            mask &= mask - 1;
        }
    }
    for (; i < line.numbers_str_length; ++i)
    {
        if (data[i] != 0 && data[i - 1] == 0)
        {
            line.col_offsets.push_back(i);
        }
    }
#endif
}

CSL_NO_INLINE bool read_line(std::ifstream& stm_file, stimulus_line_data& line, stimulus_line_buffer& buffer)
{
    line.numbers_str_length = 0;
    for (;;)
    {
        if ((line.numbers_str_length + buffer.size) > line.numbers_str.size())
        {
            line.numbers_str.resize((line.numbers_str_length + buffer.size) + 1);
        }
        size_t new_line_pos = 0;
        if (find_newline(buffer.data, buffer.pos, buffer.size, new_line_pos))
        {
            size_t count = new_line_pos - buffer.pos;
            char* num_data = line.numbers_str.data();
            copy_and_transform_line(buffer.data + buffer.pos, num_data + line.numbers_str_length, count);
            line.numbers_str_length += count;
            line.numbers_str[line.numbers_str_length] = '\0';
            buffer.pos = new_line_pos + 1;
            return true;
        }
        size_t remaining = buffer.size - buffer.pos;
        char* num_data = line.numbers_str.data();
        copy_and_transform_line(buffer.data + buffer.pos, num_data + line.numbers_str_length, remaining);
        line.numbers_str_length += remaining;
        if (!stm_file.is_open() || stm_file.eof())
        {
            return false;
        }
        stm_file.read(buffer.data, stimulus_line_buffer::BUFFER_SIZE);
        buffer.size = static_cast<size_t>(stm_file.gcount());
        buffer.pos = 0;
    }
}

} // namespace detail

CSL_NO_INLINE bool compare_stm_files(const char* result_file_name, const char* reference_file_name)
{
    std::ifstream result_file(result_file_name);
    std::ifstream ref_file(reference_file_name);

    detail::stimulus_line_buffer ref_buffer{}, result_buffer{};
    detail::stimulus_line_data ref_line{}, result_line{};
    size_t ref_lines = 0;
    while (detail::read_line(ref_file, ref_line, ref_buffer))
    {
        ++ref_lines;
    }
    size_t result_lines = 0;
    while (detail::read_line(result_file, result_line, result_buffer))
    {
        ++result_lines;
    }
    if (result_lines != ref_lines)
    {
        detail::info_fmt("Line count mismatch between reference file '%s' (%d lines) and result file '%s' (%d lines)",
                         reference_file_name, ref_lines, result_file_name, result_lines);
        return false;
    }
    if (result_lines == 0)
    {
        detail::info_fmt("Both reference and result files were empty. This is treated as a comparison failure as a vacuously true "
                         "comparison is almost never intended.",
                         ref_lines, result_lines);
        return false;
    }
    result_file.clear();
    result_file.seekg(0);
    ref_file.clear();
    ref_file.seekg(0);

    size_t line = 0;
    while (detail::read_line(ref_file, ref_line, ref_buffer))
    {
        if (!detail::read_line(result_file, result_line, result_buffer))
        {
            error("Unexpected error reading result line for reference line. This should never happen as "
                  "line counts were previously "
                  "verified to match.");
            return false;
        }
        detail::parse_line(ref_line);
        detail::parse_line(result_line);
        if (ref_line.col_offsets.size() != result_line.col_offsets.size())
        {
            detail::info_fmt(
                "Stimulus column count mismatch between reference file '%s' (%d columns) and result file '%s' (%d columns)",
                reference_file_name, ref_line.col_offsets.size(), result_file_name, result_line.col_offsets.size());
            return false;
        }
        for (size_t i = 0; i < ref_line.col_offsets.size(); ++i)
        {
            const char* ref_str = ref_line.numbers_str.data() + ref_line.col_offsets[i];
            const char* result_str = result_line.numbers_str.data() + result_line.col_offsets[i];
            if (strcmp(ref_str, result_str) != 0)
            {
                detail::info_fmt("Mismatch on result line %d column %d. Expected <%s> but got <%s>.", line, i, ref_str, result_str);
                return false;
            }
        }
        ++line;
    }
    return true;
}

inline bool stimulus_file::get_u32(uint32_t& value)
{
    if (m_line.curr_index < m_line.col_offsets.size())
    {
        char* last;
        const char* src = m_line.numbers_str.data() + m_line.col_offsets[m_line.curr_index++];
        int32_t int_value = strtol(src, &last, 10);
        std::memcpy(&value, &int_value, sizeof(value));
        return true;
    }
    return false;
}

CSL_NO_INLINE void stimulus_file::discover_format()
{
    if (!is_open() || (m_stm_format != stimulus_format::UNKNOWN))
    {
        return;
    }

    // If the format is unknown, attempt to infer it from the values in the file
    m_stm_file.clear();
    m_stm_file.seekg(0, std::ios::beg);

    while (next_line())
    {
        for (size_t i = 0; i < m_line.col_offsets.size(); ++i)
        {
            const char* str = m_line.numbers_str.data() + m_line.col_offsets[i];
            size_t len = strlen(str);

            // numbers are only padded with 0s in the binary format
            if ((len > 1) && (str[0] == '0'))
            {
                m_stm_format = stimulus_format::BINARY;
                m_stm_file.clear();
                m_stm_file.seekg(0, std::ios::beg);
                return;
            }
            // any number >1 or negative means the format must be signed
            if (strcspn(str, "-23456789") < len)
            {
                m_stm_format = stimulus_format::SIGNED;
                m_stm_file.clear();
                m_stm_file.seekg(0, std::ios::beg);
                return;
            }
        }
    }
}

inline stimulus_file::stimulus_file(const char* fileName, stimulus_format format)
    : m_line()
    , m_stm_format(format)
{
    open(fileName, format);
}

inline stimulus_file::stimulus_file()
    : m_line()
    , m_stm_format(stimulus_format::UNKNOWN)
{
    m_line.curr_index = 0;
}

inline stimulus_file::~stimulus_file()
{
    close();
}

inline void stimulus_file::close()
{
    if (is_open())
    {
        m_stm_file.close();
    }
}

CSL_NO_INLINE bool stimulus_file::open(const char* file_name, stimulus_format format)
{
    if (is_open())
    {
        close();
    }

    m_stm_format = format;
    m_stm_file.open(file_name, std::ios::in | std::ios::binary);
    bool open = is_open();
    if (!open)
    {
        detail::error_fmt("Could not open stimulus file (%s).\n", file_name);
    }
    else
    {
        discover_format();
    }
    return open;
}

inline bool stimulus_file::is_open() const
{
    return m_stm_file.is_open();
}

inline bool stimulus_file::is_line_fully_read() const
{
    return m_line.curr_index == m_line.col_offsets.size();
}

CSL_NO_INLINE bool stimulus_file::next_line()
{
    if (!is_line_fully_read())
    {
        error("Previous line was not fully read");
    }
    m_line.curr_index = 0;
    if (detail::read_line(m_stm_file, m_line, m_buffer))
    {
        detail::parse_line(m_line);
        return true;
    }
    return false;
}

CSL_NO_INLINE bool stimulus_file::skip_lines(size_t n)
{
    bool success = true;
    for (size_t i = 0; i < n; ++i)
    {
        success &= skip_line();
    }
    return success;
}

CSL_NO_INLINE bool stimulus_file::skip_line()
{
    if (!is_line_fully_read())
    {
        error("Previous line was not fully read");
    }
    // Read a line, but do not parse it
    m_line.curr_index = 0;
    m_line.col_offsets.clear();
    return detail::read_line(m_stm_file, m_line, m_buffer);
}

inline void stimulus_file::skip(int count)
{
    m_line.curr_index += count;
}

#ifdef CSL_USE_GMP
CSL_NO_INLINE bool stimulus_file::get(uint32_t* values, size_t bit_width, size_t capacity)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        values[i] = 0;
    }
    if (bit_width <= 0)
    {
        return false;
    }

    if (m_stm_format == stimulus_format::SIGNED)
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            if (!get_u32(values[i]))
            {
                return false;
            }
        }
    }
    else
    {
        error("Non-signed stimulus files currently unsupported for wrapper ATBs");
        return false;
    }
    return true;
}

CSL_NO_INLINE bool stimulus_file::get(mp_int& var, size_t bit_width)
{
    if (bit_width <= 0)
    {
        var = 0;
        return false;
    }

    var = 0;
    if (m_stm_format == stimulus_format::SIGNED)
    {
        // as per get_int_arb, but no processing on the ints required
        size_t num_ints = static_cast<size_t>(static_cast<int32_t>(((bit_width - 1) / 32) + 1));
        m_wide_value_buffer.resize(num_ints);
        for (size_t i = 0; i < num_ints; ++i)
        {
            if (!get_u32(m_wide_value_buffer[i]))
            {
                var = 0;
                return false;
            }
        }
        var.set_from_uint_array(m_wide_value_buffer.data(), m_wide_value_buffer.size(), bit_width, m_temp_alloc);
        return true;
    }
    else if (m_stm_format == stimulus_format::BINARY)
    {
        if (m_line.curr_index < m_line.col_offsets.size())
        {
            var.set_from_str(m_line.numbers_str.data() + m_line.col_offsets[m_line.curr_index++], 2);
            return true;
        }
    }

    return false;
}
#endif

CSL_NO_INLINE bool stimulus_file::get(int64_t& value, size_t bit_width)
{
    if (bit_width <= 0)
    {
        value = 0ull;
        return false;
    }

    uint64_t result = 0;
    if (m_line.curr_index < m_line.col_offsets.size())
    {
        if (m_stm_format == stimulus_format::SIGNED)
        {
            uint32_t result_u32 = 0;
            get_u32(result_u32);
            result = result_u32;

            size_t count = 1 + ((bit_width - 1) / 32);
            if (count > 1)
            {
                if (m_line.curr_index >= m_line.col_offsets.size())
                {
                    return false;
                }
                uint32_t v = 0;
                get_u32(v);
                result |= static_cast<uint64_t>(v) << 32;
            }

            std::memcpy(&value, &result, sizeof(value));
            return true;
        }
        else if (m_stm_format == stimulus_format::BINARY)
        {
            if (m_line.curr_index < m_line.col_offsets.size())
            {
                char* last;
                const char* src = m_line.numbers_str.data() + m_line.col_offsets[m_line.curr_index++];
                int64_t int_value = strtoll(src, &last, 2);
                std::memcpy(&value, &int_value, sizeof(value));
                return true;
            }
        }
    }
    value = 0ull;
    return false;
}

inline bool stimulus_file::get(int32_t& value, size_t bit_width)
{
    int64_t int_value = 0;
    bool result = get(int_value, bit_width);
    std::memcpy(&value, &int_value, sizeof(int32_t));
    return result;
}

inline bool stimulus_file::get(int16_t& value, size_t bit_width)
{
    int64_t int_value = 0;
    bool result = get(int_value, bit_width);
    std::memcpy(&value, &int_value, sizeof(int16_t));
    return result;
}

inline bool stimulus_file::get(int8_t& value, size_t bit_width)
{
    int64_t int_value = 0;
    bool result = get(int_value, bit_width);
    std::memcpy(&value, &int_value, sizeof(int8_t));
    return result;
}

inline bool stimulus_file::get(double& value)
{
    int64_t int_value = 0;
    bool result = get(int_value, 64);
    std::memcpy(&value, &int_value, sizeof(double));
    return result;
}

inline bool stimulus_file::get(float& value)
{
    int64_t int_value = 0;
    bool result = get(int_value, 32);
    std::memcpy(&value, &int_value, sizeof(float));
    return result;
}

inline output_stimulus_file::output_stimulus_file()
{
#ifdef CSL_USE_GMP
    set(m_mask, 0xFFFFFFFFll);
#endif
}

inline output_stimulus_file::output_stimulus_file(const char* filename)
{
#ifdef CSL_USE_GMP
    set(m_mask, 0xFFFFFFFFll);
#endif
    open(filename);
}

inline output_stimulus_file::~output_stimulus_file()
{
    close();
}

inline void output_stimulus_file::open(const char* filename)
{
    close();
    m_file.open(filename);
    if (!m_file.is_open())
    {
        detail::error_fmt("Could not open file: %s", filename);
    }
}

inline void output_stimulus_file::close()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

CSL_NO_INLINE void output_stimulus_file::write_stm_data_impl(int64_t v, int64_t width)
{
    if (!m_file.is_open())
    {
        error("Attempting to write stimulus but no file was opened.");
        return;
    }

#if defined(CSL_BINARY_STM_OUT)
    v &= bit_mask_i64(width);
    char binary_str[128];
    detail::to_binary(binary_str, sizeof(binary_str), v, static_cast<uint32_t>(width));
    int64_t value_str_len = static_cast<int64_t>(strlen(binary_str));
    for (int64_t i = 0; i < (width - value_str_len); ++i)
    {
        m_file << "0";
    }
    m_file << binary_str << " ";
#elif defined(CSL_UNSPLIT_STM_OUT)
    x &= bit_mask_i64(width);
    m_file << x << " ";
#else
    char buffer[32];
    for (int bit = 0; bit < width; bit += 32)
    {
        if (bit + 32 > width)
        {
            v &= detail::pow2mask[width - bit];
        }
        int r = std::snprintf(buffer, 32, "%d ", static_cast<int>(v & 0xffffffff));
        m_file.write(buffer, r);
        v >>= 32;
    }
#endif
}

inline void output_stimulus_file::write_stm_data(int64_t v, int64_t width)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(int64_t));
    write_stm_data_impl(x, width);
}

inline void output_stimulus_file::write_stm_data(int32_t v, int64_t width)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(int32_t));
    write_stm_data_impl(x, width);
}

inline void output_stimulus_file::write_stm_data(int16_t v, int64_t width)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(int16_t));
    write_stm_data_impl(x, width);
}

inline void output_stimulus_file::write_stm_data(int8_t v, int64_t width)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(int8_t));
    write_stm_data_impl(x, width);
}

inline void output_stimulus_file::write_stm_data(double v)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(double));
    write_stm_data_impl(x, 64);
}

inline void output_stimulus_file::write_stm_data(float v)
{
    int64_t x = 0;
    std::memcpy(&x, &v, sizeof(float));
    write_stm_data_impl(x, 32);
}

#ifdef CSL_USE_GMP
CSL_NO_INLINE void output_stimulus_file::write_stm_data(const mp_int& v, int64_t width)
{
    if (!m_file.is_open())
    {
        detail::error_fmt("Attempting to write stimulus but no file was opened.");
        return;
    }

    m_temp_alloc.push();
    mp_int& masked_val = m_temp_alloc.alloc_int();
    mp_int& curr = m_temp_alloc.alloc_int();
    curr = v;

#if defined(CSL_BINARY_STM_OUT)
    (void)width;
    static constexpr size_t MAX_BINARY_VALUE_LENGTH = 2048;
    char value[MAX_BINARY_VALUE_LENGTH];
    curr.str_bin(value, MAX_BINARY_VALUE_LENGTH);
    int64_t value_str_len = static_cast<int64_t>(strlen(value));
    for (int64_t i = 0; i < (width - value_str_len); ++i)
    {
        m_file << "0";
    }
    m_file << value << " ";
#elif defined(CSL_UNSPLIT_STM_OUT)
    (void)width;
    static constexpr size_t MAX_UNSPLIT_VALUE_LENGTH = 2048;
    char value[MAX_UNSPLIT_VALUE_LENGTH];
    curr.str(value, MAX_UNSPLIT_VALUE_LENGTH);
    m_file << value << " ";
#else
    char buffer[32];
    for (int bit = 0; bit < width; bit += 32)
    {
        mpz_and(masked_val.get(), curr.get(), m_mask.get());
        int int_value = (int)static_cast<unsigned int>(mpz_get_ui(masked_val.get()));
        if (width - bit <= 32)
        {
            int_value &= detail::pow2mask[width - bit];
        }
        int r = std::snprintf(buffer, 32, "%d ", int_value);
        m_file.write(buffer, r);
        mpz_fdiv_q_2exp(curr.get(), curr.get(), 32);
    }
#endif

    m_temp_alloc.pop();
}

#endif

inline void output_stimulus_file::next_line()
{
    if (m_file.is_open())
    {
        m_file << "\n";
        ++m_line_count;
    }
    else
    {
        detail::error_fmt("Attempting to write stimulus but no file was opened.");
    }
}

inline size_t output_stimulus_file::get_line_count() const
{
    return m_line_count;
}

} // namespace csl

#endif // CSL_CSL_IO_H