/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#pragma once

#ifndef SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_MULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLO0000OF0CDJ6OF0CD16OL0QCZ_H_
#define SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_MULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLO0000OF0CDJ6OF0CD16OL0QCZ_H_

#include "support/csl.h"
#ifdef WRITE_STM_FILES
#include "support/csl_io.h"
#endif

class flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz
{
public:
    /** Input struct for "in_0" */
    struct io_struct_in_0
    {
        double port_in_0;
    };

    /** Input struct for "in_1" */
    struct io_struct_in_1
    {
        double port_in_1;
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
    flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz() {};
    flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz(const flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz&) = delete;
    flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz(flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz&&) = delete;
    flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz& operator=(const flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz&) = delete;
    flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz& operator=(flt_ifft8k_base_DUT_multBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFlo0000of0cdj6of0cd16ol0qcz&&) = delete;

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
        bool needs_to_execute = (m_io_cycle[2] == m_update_cycle);
        if (needs_to_execute)
        {
            m_io_cycle[2]++;
            execute();
        }

        csl::mask_lower(output.port_out_primwireout, m_w[PORT_OUT_PRIMWIREOUT2], 64);
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

    void write(const io_struct_in_1& input)
    {
        bool needs_to_execute = (m_io_cycle[1] == m_update_cycle);
        if (needs_to_execute)
        {
            csl::set(m_w[PORT_IN_11], input.port_in_1);
            m_io_cycle[1]++;
            execute();
        }
    }

    /** Resets internal simulation state to default values and opens stimulus files. */
    void reset()
    {
        static constexpr int64_t native_reset_range_values[] = { 0ll };
        static constexpr uint32_t native_reset_range_value_indices[] = { 0ull };
        static constexpr size_t native_reset_range_indices[] = { 0ull };
        static constexpr size_t native_reset_range_sizes[] = { 127ull };
        for (size_t i = 0; i < 1; ++i)
        {
            csl::fill_n(&m_n[native_reset_range_indices[i]], native_reset_range_sizes[i], native_reset_range_values[native_reset_range_value_indices[i]]);
        }
        static constexpr uint64_t wide_reset_range_values[] = { 0ull };
        static constexpr csl::mp_int_info wide_reset_range_infos[] = { { 0, 1, 0 } };
        static constexpr uint32_t wide_reset_range_value_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_sizes[] = { 15ull };
        for (size_t i = 0; i < 1; ++i)
        {
            for (size_t j = 0; j < wide_reset_range_sizes[i]; ++j)
            {
                csl::fill_mpz_data(m_w[wide_reset_range_indices[i] + j],
                    wide_reset_range_values, wide_reset_range_infos, wide_reset_range_value_indices[i]);
            }
        }
        csl::fill_n(m_io_cycle, 3, -1);
        csl::fill_n(m_segment_cycle, 4, -1);
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
            m_io_cycle[2] = m_update_cycle + 1;
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
        csl::set(m_n[7], 0ll); // step_const
        csl::set(m_n[1], 1ll); // step_const
        csl::set(m_n[6], 2047ll); // step_const
        csl::set(m_n[22], 0ll); // step_const
        csl::set(m_n[21], 0ll); // step_const
        csl::set(m_n[20], 2047ll); // step_const
        csl::set(m_n[8], 0ll); // step_const
        csl::set(m_n[91], 2047ll); // step_const
        csl::set(m_n[92], 2047ll); // step_const
        csl::set(m_n[0], 0ll); // step_const
        csl::set(m_n[38], 1ll); // step_const
        csl::set(m_n[35], 1ll); // step_const
        csl::set(m_n[117], 0ll); // step_const
        csl::set(m_n[113], 0ll); // step_const
        csl::set(m_n[106], 0ll); // step_const
        csl::set(m_n[102], 0ll); // step_const
        csl::set(m_n[61], 0ll); // step_const
        csl::set(m_n[58], 2ll); // step_const
        csl::set(m_n[53], 0ll); // step_const
        csl::set(m_n[41], 1023ll); // step_const
        csl::set(m_n[94], 0ll); // step_const
        csl::set(m_n[68], 2047ll); // step_const
        csl::set(m_n[87], 1ll); // step_const
        csl::set(m_n[88], 0ll); // step_const
        csl::set(m_n[89], 0ll); // step_const
    }

    void execute_segment_0()
    {
        execute_segment_0_fragment_0();
    }

    void execute_segment_1_fragment_0()
    {
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[10], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[7], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[10], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[13], m_n[TMP_N_3], 52, false);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[9], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[6], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[12], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[13], 1);
        csl::step_and(m_n[15], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[15], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[8], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[11], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[13], 1);
        csl::step_not_signed(m_n[14], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[14], 1);
        csl::step_and(m_n[16], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[16], 1, 1, false, true);
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[4], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[34], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[34], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[35], 1);
        csl::step_bit_combine(m_n[36], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 53);
        csl::step_bit_extract(m_n[98], m_n[TMP_N_0], 27, true, 26);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 26);
        csl::step_bit_extract(m_n[114], m_n[TMP_N_0], 26, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[113], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[114], 26);
        csl::step_bit_combine(m_n[115], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[115], 27);
        csl::step_bit_extract(m_n[116], m_n[TMP_N_0], 27, false, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 26);
        csl::step_bit_extract(m_n[107], m_n[TMP_N_0], 26, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[106], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[107], 26);
        csl::step_bit_combine(m_n[108], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[108], 27);
        csl::step_bit_extract(m_n[109], m_n[TMP_N_0], 27, false, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 53);
        csl::step_bit_extract(m_n[101], m_n[TMP_N_0], 27, true, 26);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[2], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::step_not_signed(m_n[17], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::step_not_signed(m_n[18], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[18], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[17], 1);
        csl::step_and(m_n[19], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[19], 1, 1, false, true);
    }

    void execute_segment_1()
    {
        execute_segment_1_fragment_0();
    }

    void execute_segment_2_fragment_0()
    {
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[23], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[23], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[22], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[25], m_n[TMP_N_3], 11, false);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[24], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[21], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[24], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[27], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[23], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[20], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[26], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[26], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[27], 1);
        csl::step_and(m_n[29], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[29], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::step_not_signed(m_n[28], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[26], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[28], 1);
        csl::step_and(m_n[30], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[30], 1, 1, false, true);
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_11], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[5], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[37], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[37], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[38], 1);
        csl::step_bit_combine(m_n[39], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[39], 53);
        csl::step_bit_extract(m_n[99], m_n[TMP_N_0], 27, true, 26);
        csl::mask_lower(m_n[TMP_N_0], m_n[39], 26);
        csl::step_bit_extract(m_n[118], m_n[TMP_N_0], 26, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[117], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[118], 26);
        csl::step_bit_combine(m_n[119], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[119], 27);
        csl::step_bit_extract(m_n[120], m_n[TMP_N_0], 27, false, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[39], 53);
        csl::step_bit_extract(m_n[110], m_n[TMP_N_0], 27, true, 26);
        csl::mask_lower(m_n[TMP_N_0], m_n[39], 26);
        csl::step_bit_extract(m_n[103], m_n[TMP_N_0], 26, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[102], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[103], 26);
        csl::step_bit_combine(m_n[104], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[104], 27);
        csl::step_bit_extract(m_n[105], m_n[TMP_N_0], 27, false, 0);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[3], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[26], 1);
        csl::step_not_signed(m_n[31], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 1);
        csl::step_not_signed(m_n[32], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[32], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[31], 1);
        csl::step_and(m_n[33], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[33], 1, 1, false, true);
    }

    void execute_segment_2()
    {
        execute_segment_2_fragment_0();
    }

    void execute_segment_3_fragment_0()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[15], 1);
        csl::step_and(m_n[81], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[81], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::step_and(m_n[82], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[82], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[82], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[81], 1);
        csl::step_or(m_n[83], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[83], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[16], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[30], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[83], 1);
        csl::step_or(m_n[84], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_or(m_n[84], m_n[84], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[84], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[84], 1);
        csl::step_not_signed(m_n[96], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[5], 1);
        csl::step_xor(m_n[43], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[43], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[43], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[96], 1);
        csl::step_and(m_n[97], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[97], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_n[98], 27);
        csl::mask_lower(m_n[TMP_N_1], m_n[99], 27);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_mul(m_n[100], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[116], 27);
        csl::mask_lower(m_n[TMP_N_1], m_n[120], 27);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_mul(m_n[121], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::step_reduce(m_n[TMP_N_0], m_n[121], 54);
        csl::step_reduce(m_n[TMP_N_1], m_n[100], 54);
        csl::step_bit_combine(m_w[7], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 54, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[7], 108);
        csl::step_bit_extract(m_w[8], m_w[TMP_W_0], 81, true, 27, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[101], 27);
        csl::mask_lower(m_n[TMP_N_3], m_n[105], 27);
        csl::mask_lower(m_n[TMP_N_4], m_n[109], 27);
        csl::mask_lower(m_n[TMP_N_5], m_n[110], 27);
        csl::step_mul(m_n[TMP_N_6], m_n[TMP_N_2], m_n[TMP_N_3]);
        csl::step_mul(m_n[TMP_N_7], m_n[TMP_N_4], m_n[TMP_N_5]);
        csl::step_addsub(m_n[TMP_N_1], m_n[111], m_n[TMP_N_6], m_n[TMP_N_7]);
        csl::mask_lower(m_n[TMP_N_0], m_n[111], 55);
        csl::step_bit_extract(m_n[112], m_n[TMP_N_0], 55, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[112], 55);
        csl::mask_lower(m_w[TMP_W_0], m_w[8], 81);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[9], m_n[TMP_N_0], m_w[TMP_W_0], m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_w[7], 27);
        csl::step_bit_extract(m_n[122], m_n[TMP_N_0], 27, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[122], 27);
        csl::step_reduce(m_w[TMP_W_0], m_w[9], 82, m_temp_alloc);
        csl::step_bit_combine(m_w[10], m_n[TMP_N_0], m_w[TMP_W_0], 2, 1, 27, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[10], 108);
        csl::step_bit_extract(m_w[11], m_w[TMP_W_0], 106, true, 2, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[11], 106, m_temp_alloc);
        csl::step_bit_extract(m_w[3], m_w[TMP_W_0], 106, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[3], 106, m_temp_alloc);
        csl::step_bit_extract(m_n[44], m_w[TMP_W_0], 1, true, 105, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[3], 105);
        csl::step_bit_extract(m_n[46], m_w[TMP_W_0], 53, true, 52, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[3], 104);
        csl::step_bit_extract(m_n[47], m_w[TMP_W_0], 53, true, 51, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[3], 106, m_temp_alloc);
        csl::step_bit_extract(m_n[45], m_w[TMP_W_0], 1, true, 105, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[45], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[47], 53);
        csl::mask_lower(m_n[TMP_N_3], m_n[46], 53);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_206[2] = { 129, 130 };
        csl::set(m_n[48], m_n[csl::checked_array_value(mux_lookup_206, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[48], 2);
        csl::step_bit_extract(m_n[56], m_n[TMP_N_0], 2, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_w[3], 52, m_temp_alloc);
    }

    void execute_segment_3_fragment_1()
    {
        csl::step_bit_extract(m_n[50], m_n[TMP_N_0], 1, true, 51);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[44], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[0], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[50], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_217[2] = { 129, 130 };
        csl::set(m_n[51], m_n[csl::checked_array_value(mux_lookup_217, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[3], 51);
        csl::step_bit_extract(m_n[49], m_n[TMP_N_0], 51, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[49], 51);
        csl::step_reduce(m_n[TMP_N_1], m_n[51], 1);
        csl::step_bit_combine(m_n[52], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 51, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[52], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[53], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[54], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[54], 1);
        csl::step_not_signed(m_n[55], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[55], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[56], 2);
        csl::step_bit_combine(m_n[57], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[57], 3);
        csl::mask_lower(m_n[TMP_N_2], m_n[58], 3);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 3, 3, false, false);
        csl::step_reducing_and(m_n[59], m_n[TMP_N_3], 3, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[59], 1);
        csl::step_not_signed(m_n[60], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[60], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[61], 52);
        csl::step_reduce(m_n[TMP_N_2], m_n[44], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[0], 1);
        csl::step_bit_combine(m_n[62], m_n[TMP_N_0], m_n[TMP_N_1], 4, 1, 1, 53);
        csl::step_bit_combine(m_n[62], m_n[62], m_n[TMP_N_2], 4, 2, 53, 54);
        csl::step_bit_combine(m_n[62], m_n[62], m_n[TMP_N_3], 4, 3, 54, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[2], 11);
        csl::mask_lower(m_n[TMP_N_1], m_n[3], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_add(m_n[40], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[40], 12);
        csl::step_reduce(m_n[TMP_N_1], m_n[41], 13);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[42], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::step_reduce(m_n[TMP_N_0], m_n[48], 53);
        csl::step_reduce(m_n[TMP_N_1], m_n[42], 14);
        csl::step_bit_combine(m_w[4], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 53, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[4], 67, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_n[62], 55);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[5], m_w[TMP_W_0], m_n[TMP_N_0], m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[5], 68, m_temp_alloc);
        csl::step_bit_extract(m_n[64], m_w[TMP_W_0], 15, true, 53, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_n[64], 11);
        csl::step_bit_extract(m_n[65], m_n[TMP_N_0], 11, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[65], 11);
        csl::step_bit_extract(m_n[93], m_n[TMP_N_0], 11, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[64], 15);
        csl::mask_lower(m_n[TMP_N_1], m_n[68], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[70], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_nsign_bit(m_n[69], m_n[70], 17);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[19], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[69], 1);
        csl::step_and(m_n[79], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[79], m_n[79], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[79], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[33], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[15], 1);
        csl::step_and(m_n[78], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[78], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[19], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::step_and(m_n[77], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[77], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[15], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::step_and(m_n[76], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[76], 1, 1, false, true);
    }

    void execute_segment_3_fragment_2()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[76], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[77], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[78], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[79], 1);
        csl::step_or(m_n[80], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_or(m_n[80], m_n[80], m_n[TMP_N_3]);
        csl::step_or(m_n[80], m_n[80], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[80], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_n[0], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[64], 15);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[67], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_nsign_bit(m_n[66], m_n[67], 17);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[19], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[66], 1);
        csl::step_and(m_n[74], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[74], m_n[74], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[74], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[19], 1);
        csl::step_and(m_n[73], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[73], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 1);
        csl::step_and(m_n[72], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[72], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[25], 1);
        csl::step_and(m_n[71], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[71], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[71], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[72], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[73], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[74], 1);
        csl::step_or(m_n[75], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_or(m_n[75], m_n[75], m_n[TMP_N_3]);
        csl::step_or(m_n[75], m_n[75], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[75], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[75], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[80], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[84], 1);
        csl::step_bit_combine(m_n[85], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 1, 2);
        csl::step_bit_combine(m_n[85], m_n[85], m_n[TMP_N_2], 3, 2, 2, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[85], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_361[] = {
            1ll, 0ll, 2ll, 0ll, 3ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_361, 8, 0, m_n[86], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[86], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[94], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[93], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[92], 11);
        csl::mask_lower(m_n[TMP_N_5], m_n[91], 11);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_369[4] = { 129, 130, 131, 132 };
        csl::set(m_n[95], m_n[csl::checked_array_value(mux_lookup_369, m_n[TMP_N_6])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[5], 53);
        csl::step_bit_extract(m_n[63], m_n[TMP_N_0], 52, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[86], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[89], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[63], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[88], 52);
        csl::mask_lower(m_n[TMP_N_5], m_n[87], 52);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_382[4] = { 129, 130, 131, 132 };
        csl::set(m_n[90], m_n[csl::checked_array_value(mux_lookup_382, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[90], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[95], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[97], 1);
        csl::step_bit_combine(m_w[6], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[6], m_w[6], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[6], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[0], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[0], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREOUT2] = m_w[TMP_W_0];
    }

    void execute_segment_3()
    {
        execute_segment_3_fragment_0();
        execute_segment_3_fragment_1();
        execute_segment_3_fragment_2();
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
        if ((m_segment_cycle[2] == m_update_cycle) && (m_io_cycle[1] > m_update_cycle))
        {
            execute_segment_2();
            ++m_segment_cycle[2];
        }
        if ((m_segment_cycle[3] == m_update_cycle) && (m_io_cycle[1] > m_update_cycle) && (m_io_cycle[0] > m_update_cycle))
        {
            execute_segment_3();
            ++m_segment_cycle[3];
        }
        const bool all_io_ready = (m_io_cycle[0] > m_update_cycle) && (m_io_cycle[1] > m_update_cycle) && (m_io_cycle[2] > m_update_cycle);
        if (all_io_ready && (m_segment_cycle[0] > m_update_cycle) && (m_segment_cycle[1] > m_update_cycle) && (m_segment_cycle[2] > m_update_cycle) && (m_segment_cycle[3] > m_update_cycle))
        {
            execute_segment_update();
            ++m_update_cycle;
        }
    }

    static constexpr size_t PORT_IN_00 = 1;
    static constexpr size_t PORT_IN_11 = 2;
    static constexpr size_t PORT_OUT_PRIMWIREOUT2 = 14;
    static constexpr size_t TMP_N_0 = 127;
    static constexpr size_t TMP_N_1 = 128;
    static constexpr size_t TMP_N_2 = 129;
    static constexpr size_t TMP_N_3 = 130;
    static constexpr size_t TMP_N_4 = 131;
    static constexpr size_t TMP_N_5 = 132;
    static constexpr size_t TMP_N_6 = 133;
    static constexpr size_t TMP_N_7 = 134;
    static constexpr size_t TMP_W_0 = 15;

    int64_t m_io_cycle[3];
    int64_t m_segment_cycle[4];
    int64_t m_update_cycle;

    csl::mp_temp_allocator m_temp_alloc;
    int64_t m_n[135];
    csl::mp_int m_w[16];
};

#endif // SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_MULTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLO0000OF0CDJ6OF0CD16OL0QCZ_H_