/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#pragma once

#ifndef SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CONSTMULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_1_30000CD06CJ0OF0CDJ6OR33Z0_H_
#define SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CONSTMULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_1_30000CD06CJ0OF0CDJ6OR33Z0_H_

#include "support/csl.h"
#ifdef WRITE_STM_FILES
#include "support/csl_io.h"
#endif

class flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0
{
public:
    /** Input struct for "in_0" */
    struct io_struct_in_0
    {
        double port_in_0;
    };

    /** Output struct for "out_primWireOut" */
    struct io_struct_out_primWireOut
    {
        double port_out_primwireout;
    };

public:
    /**
     * Model classes may not be copied, moved or assigned.
     * Constructing a model does not fully initialize it.
     * Call reset() to initialize the model after constructing.
     */ 
    flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0() {};
    flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0(const flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0&) = delete;
    flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0(flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0&&) = delete;
    flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0& operator=(const flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0&) = delete;
    flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0& operator=(flt_ifft8k_base_DUT_constMultBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_1_30000cd06cj0of0cdj6or33z0&&) = delete;

    /**
     * Reads output values from the model.
     * 
     * Applies delay correction for bit-accurate non-cycle-accurate models
     * to simulate latency from delay balancing (matches DSP Builder's Simulink behavior).
     * 
     * Appends output to stimulus files when WRITE_STM_FILES is defined.
     * 
     * Should be called once per cycle. Subsequent calls in the same cycle
     * will copy output values but will not write stimulus or update state.
     */
    void read(io_struct_out_primWireOut& output)
    {
        bool needs_to_execute = (m_io_cycle[1] == m_update_cycle);
        if (needs_to_execute)
        {
            m_io_cycle[1]++;
            execute();
        }

        csl::mask_lower(output.port_out_primwireout, m_w[PORT_OUT_PRIMWIREOUT1], 64);
    }

    /**
     * Writes input values to the model and initiates internal simulation.
     * 
     * When all input nodes have been written for the current cycle,
     * the model automatically advances to the next cycle.
     * 
     * Appends input to stimulus files when WRITE_STM_FILES is defined.
     * 
     * Should be called once per cycle. Subsequent calls in the same cycle
     * will be ignored.
     */
    void write(const io_struct_in_0& input)
    {
        bool needs_to_execute = (m_io_cycle[0] == m_update_cycle);
        if (needs_to_execute)
        {
            csl::set(m_w[PORT_IN_00], input.port_in_0);
            m_io_cycle[0]++;
            execute();
        }
    }

    /** Resets internal simulation state to default values and opens stimulus files. */
    void reset()
    {
        static constexpr int64_t native_reset_range_values[] = { 0ll };
        static constexpr uint32_t native_reset_range_value_indices[] = { 0ull };
        static constexpr size_t native_reset_range_indices[] = { 0ull };
        static constexpr size_t native_reset_range_sizes[] = { 76ull };
        for (size_t i = 0; i < 1; ++i)
        {
            csl::fill_n(&m_n[native_reset_range_indices[i]], native_reset_range_sizes[i], native_reset_range_values[native_reset_range_value_indices[i]]);
        }
        static constexpr uint64_t wide_reset_range_values[] = { 0ull };
        static constexpr csl::mp_int_info wide_reset_range_infos[] = { { 0, 1, 0 } };
        static constexpr uint32_t wide_reset_range_value_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_sizes[] = { 10ull };
        for (size_t i = 0; i < 1; ++i)
        {
            for (size_t j = 0; j < wide_reset_range_sizes[i]; ++j)
            {
                csl::fill_mpz_data(m_w[wide_reset_range_indices[i] + j],
                    wide_reset_range_values, wide_reset_range_infos, wide_reset_range_value_indices[i]);
            }
        }
        csl::fill_n(m_io_cycle, 2, -1);
        csl::fill_n(m_segment_cycle, 2, -1);
        m_update_cycle = -1;
    }

    /**
     * Opens all stimulus files associated with this class and its children.
     * Files will be flushed and closed on destruction or by calling close_stimulus_files().
     */
    void open_stimulus_files()
    {
#ifdef WRITE_STM_FILES
#endif
    }

    /**
     * Closes and flushes all stimulus files associated with this class and its children.
     * Must call open_stimulus_files() before writing more stimulus data to re-open the files.
     */
    void close_stimulus_files()
    {
#ifdef WRITE_STM_FILES
#endif
    }

    /**
     * If the current cycle of this system is equal to the
     * input cycle, sets the state of all output IO structs to read,
     * allowing the simulation state to advance to the next cycle.
     * 
     * This allows skipping the reading of unused output structs without
     * blocking the simulation.
     * 
     * This function is primarily intended for internal usage within
     * model hierarchies.
     */
    void flush_outputs(int64_t cycle)
    {
        if (m_update_cycle == cycle)
        {
            m_io_cycle[1] = m_update_cycle + 1;
            execute();
        }
    }

    /**
     * Returns the temporary allocator instance for this model
     */
    csl::mp_temp_allocator& get_temp_allocator()
    {
        return m_temp_alloc;
    }

private:
    /**
     * Execution is divided into segments based on input dependencies.
     * These functions are invoked automatically as inputs are provided.
     */
    void execute_segment_0_fragment_0()
    {
        csl::set(m_n[4], 0ll); // step_const
        csl::set(m_n[1], 1ll); // step_const
        csl::set(m_n[3], 2047ll); // step_const
        csl::set(m_n[63], 2047ll); // step_const
        csl::set(m_n[64], 2047ll); // step_const
        csl::set(m_n[0], 0ll); // step_const
        csl::set(m_n[73], 0ll); // step_const
        csl::set(m_n[18], 1ll); // step_const
        csl::set(m_n[72], 0ll); // step_const
        csl::set(m_n[41], 0ll); // step_const
        csl::set(m_n[38], 2ll); // step_const
        csl::set(m_n[33], 0ll); // step_const
        csl::set(m_n[25], 0ll); // step_const
        csl::set(m_n[65], 0ll); // step_const
        csl::set(m_n[47], 2047ll); // step_const
        csl::set(m_n[5], 0ll); // step_const
        csl::set(m_n[59], 1ll); // step_const
        csl::set(m_n[60], 0ll); // step_const
        csl::set(m_n[61], 0ll); // step_const
    }

    void execute_segment_0()
    {
        execute_segment_0_fragment_0();
    }

    void execute_segment_1_fragment_0()
    {
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[7], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[7], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[10], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[10], 1);
        csl::step_not_signed(m_n[11], m_n[TMP_N_1], 1);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[6], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[6], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[3], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[9], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[11], 1);
        csl::step_and(m_n[13], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[13], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[13], 1);
        csl::step_not_signed(m_n[67], m_n[TMP_N_1], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[50], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[50], 1);
        csl::step_not_signed(m_n[51], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[51], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[67], 1);
        csl::step_and(m_n[68], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[68], 1, 1, false, true);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[17], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[17], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[18], 1);
        csl::step_bit_combine(m_n[19], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[19], 53);
        csl::step_bit_extract(m_n[20], m_n[TMP_N_0], 53, false, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[20], 53);
        csl::step_bit_extract(m_n[69], m_n[TMP_N_0], 53, false, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[69], 53);
        csl::step_bit_extract(m_n[70], m_n[TMP_N_0], 53, false, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[70], 53);
        csl::step_bit_extract(m_n[71], m_n[TMP_N_0], 53, false, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 63);
        csl::step_reduce(m_n[TMP_N_1], m_n[71], 53);
        csl::step_reduce(m_n[TMP_N_2], m_n[73], 1);
        csl::step_bit_combine(m_w[6], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 63, 116, m_temp_alloc);
        csl::step_bit_combine(m_w[6], m_w[6], m_n[TMP_N_2], 3, 2, 116, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[6], 117, m_temp_alloc);
        csl::step_bit_extract(m_w[7], m_w[TMP_W_0], 117, false, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[7], 117, m_temp_alloc);
        csl::step_bit_extract(m_w[2], m_w[TMP_W_0], 117, false, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[2], 117, m_temp_alloc);
        csl::step_bit_extract(m_n[28], m_w[TMP_W_0], 1, true, 116, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[2], 116);
        csl::step_bit_extract(m_n[22], m_w[TMP_W_0], 53, true, 63, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[2], 115);
        csl::step_bit_extract(m_n[23], m_w[TMP_W_0], 53, true, 62, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[2], 117, m_temp_alloc);
        csl::step_bit_extract(m_n[21], m_w[TMP_W_0], 1, true, 116, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[21], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[23], 53);
        csl::mask_lower(m_n[TMP_N_3], m_n[22], 53);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_78[2] = { 78, 79 };
        csl::set(m_n[24], m_n[csl::checked_array_value(mux_lookup_78, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[24], 2);
        csl::step_bit_extract(m_n[36], m_n[TMP_N_0], 2, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_w[2], 63, m_temp_alloc);
        csl::step_bit_extract(m_n[30], m_n[TMP_N_0], 1, true, 62);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[28], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[0], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[30], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_89[2] = { 78, 79 };
        csl::set(m_n[31], m_n[csl::checked_array_value(mux_lookup_89, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[2], 62);
        csl::step_bit_extract(m_n[29], m_n[TMP_N_0], 62, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[29], 62);
        csl::step_reduce(m_n[TMP_N_1], m_n[31], 1);
    }

    void execute_segment_1_fragment_1()
    {
        csl::step_bit_combine(m_n[32], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 62, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[32], 63);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 63);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 63, 63, false, false);
        csl::step_reducing_and(m_n[34], m_n[TMP_N_3], 63, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[34], 1);
        csl::step_not_signed(m_n[35], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[35], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[36], 2);
        csl::step_bit_combine(m_n[37], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[37], 3);
        csl::mask_lower(m_n[TMP_N_2], m_n[38], 3);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 3, 3, false, false);
        csl::step_reducing_and(m_n[39], m_n[TMP_N_3], 3, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[39], 1);
        csl::step_not_signed(m_n[40], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[40], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[41], 52);
        csl::step_reduce(m_n[TMP_N_2], m_n[28], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[0], 1);
        csl::step_bit_combine(m_n[42], m_n[TMP_N_0], m_n[TMP_N_1], 4, 1, 1, 53);
        csl::step_bit_combine(m_n[42], m_n[42], m_n[TMP_N_2], 4, 2, 53, 54);
        csl::step_bit_combine(m_n[42], m_n[42], m_n[TMP_N_3], 4, 3, 54, 0);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[2], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[2], 11);
        csl::step_reduce(m_n[TMP_N_1], m_n[25], 2);
        csl::step_bit_combine(m_n[26], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 11, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[26], 13);
        csl::step_bit_extract(m_n[27], m_n[TMP_N_0], 13, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[24], 53);
        csl::step_reduce(m_n[TMP_N_1], m_n[27], 13);
        csl::step_bit_combine(m_w[3], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 53, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[3], 66, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_n[42], 55);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[4], m_w[TMP_W_0], m_n[TMP_N_0], m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[4], 67, m_temp_alloc);
        csl::step_bit_extract(m_n[43], m_w[TMP_W_0], 14, true, 53, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_n[43], 11);
        csl::step_bit_extract(m_n[52], m_n[TMP_N_0], 11, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[43], 14);
        csl::mask_lower(m_n[TMP_N_1], m_n[47], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[49], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_nsign_bit(m_n[48], m_n[49], 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 1);
        csl::step_not_signed(m_n[14], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[6], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[5], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[8], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[8], 1);
        csl::step_not_signed(m_n[15], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[15], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[14], 1);
        csl::step_and(m_n[16], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[16], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[16], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[48], 1);
        csl::step_and(m_n[53], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[53], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[10], 1);
        csl::step_and(m_n[12], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[12], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[53], 1);
        csl::step_or(m_n[54], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[54], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_n[0], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[43], 14);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
    }

    void execute_segment_1_fragment_2()
    {
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[46], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_nsign_bit(m_n[45], m_n[46], 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[16], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[45], 1);
        csl::step_and(m_n[55], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[55], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[8], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[55], 1);
        csl::step_or(m_n[56], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[56], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[56], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[54], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[13], 1);
        csl::step_bit_combine(m_n[57], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 1, 2);
        csl::step_bit_combine(m_n[57], m_n[57], m_n[TMP_N_2], 3, 2, 2, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[57], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_196[] = {
            1ll, 0ll, 2ll, 0ll, 3ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_196, 8, 0, m_n[58], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[58], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[65], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[52], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[64], 11);
        csl::mask_lower(m_n[TMP_N_5], m_n[63], 11);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_204[4] = { 78, 79, 80, 81 };
        csl::set(m_n[66], m_n[csl::checked_array_value(mux_lookup_204, m_n[TMP_N_6])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[4], 53);
        csl::step_bit_extract(m_n[44], m_n[TMP_N_0], 52, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[58], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[61], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[44], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[60], 52);
        csl::mask_lower(m_n[TMP_N_5], m_n[59], 52);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_217[4] = { 78, 79, 80, 81 };
        csl::set(m_n[62], m_n[csl::checked_array_value(mux_lookup_217, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[62], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[66], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[68], 1);
        csl::step_bit_combine(m_w[5], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[5], m_w[5], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[5], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[0], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[0], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREOUT1] = m_w[TMP_W_0];
    }

    void execute_segment_1()
    {
        execute_segment_1_fragment_0();
        execute_segment_1_fragment_1();
        execute_segment_1_fragment_2();
    }

    void execute_segment_update()
    {
    }

    /**
     * Progresses the internal simulation state based on the currently
     * available input values
     */
    void execute()
    {
        if (m_segment_cycle[0] == m_update_cycle)
        {
            execute_segment_0();
            ++m_segment_cycle[0];
        }
        if ((m_segment_cycle[1] == m_update_cycle) && (m_io_cycle[0] > m_update_cycle))
        {
            execute_segment_1();
            ++m_segment_cycle[1];
        }
        const bool all_io_ready = (m_io_cycle[0] > m_update_cycle) && (m_io_cycle[1] > m_update_cycle);
        if (all_io_ready && (m_segment_cycle[0] > m_update_cycle) && (m_segment_cycle[1] > m_update_cycle))
        {
            execute_segment_update();
            ++m_update_cycle;
        }
    }

    static constexpr size_t PORT_IN_00 = 1;
    static constexpr size_t PORT_OUT_PRIMWIREOUT1 = 9;
    static constexpr size_t TMP_N_0 = 76;
    static constexpr size_t TMP_N_1 = 77;
    static constexpr size_t TMP_N_2 = 78;
    static constexpr size_t TMP_N_3 = 79;
    static constexpr size_t TMP_N_4 = 80;
    static constexpr size_t TMP_N_5 = 81;
    static constexpr size_t TMP_N_6 = 82;
    static constexpr size_t TMP_W_0 = 10;

    int64_t m_io_cycle[2];
    int64_t m_segment_cycle[2];
    int64_t m_update_cycle;

    csl::mp_temp_allocator m_temp_alloc;
    int64_t m_n[83];
    csl::mp_int m_w[11];
};

#endif // SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CONSTMULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_1_30000CD06CJ0OF0CDJ6OR33Z0_H_