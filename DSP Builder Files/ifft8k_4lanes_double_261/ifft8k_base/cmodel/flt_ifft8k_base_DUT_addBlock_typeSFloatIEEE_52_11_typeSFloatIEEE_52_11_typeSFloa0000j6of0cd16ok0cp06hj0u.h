/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#pragma once

#ifndef SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLOA0000J6OF0CD16OK0CP06HJ0U_H_
#define SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLOA0000J6OF0CD16OK0CP06HJ0U_H_

#include "support/csl.h"
#ifdef WRITE_STM_FILES
#include "support/csl_io.h"
#endif

class flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u
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
    flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u() {};
    flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u(const flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u&) = delete;
    flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u(flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u&&) = delete;
    flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u& operator=(const flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u&) = delete;
    flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u& operator=(flt_ifft8k_base_DUT_addBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_typeSFloa0000j6of0cd16ok0cp06hj0u&&) = delete;

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
        static constexpr size_t native_reset_range_sizes[] = { 172ull };
        for (size_t i = 0; i < 1; ++i)
        {
            csl::fill_n(&m_n[native_reset_range_indices[i]], native_reset_range_sizes[i], native_reset_range_values[native_reset_range_value_indices[i]]);
        }
        static constexpr uint64_t wide_reset_range_values[] = { 0ull };
        static constexpr csl::mp_int_info wide_reset_range_infos[] = { { 0, 1, 0 } };
        static constexpr uint32_t wide_reset_range_value_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_sizes[] = { 19ull };
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
        csl::set(m_n[71], 57ll); // step_const
        csl::set(m_n[131], 0ll); // step_const
        csl::set(m_n[1], 1ll); // step_const
        csl::set(m_n[0], 0ll); // step_const
        csl::set(m_n[64], 0ll); // step_const
        csl::set(m_n[48], 54ll); // step_const
        csl::set(m_n[24], 0ll); // step_const
        csl::set(m_n[43], 0ll); // step_const
        csl::set(m_n[52], 0ll); // step_const
        csl::set(m_n[61], 1ll); // step_const
        csl::set(m_n[60], 0ll); // step_const
        csl::set(m_n[55], 0ll); // step_const
        csl::set(m_n[139], 0ll); // step_const
        csl::set(m_n[134], -1ll); // step_const
        csl::set(m_n[145], 0ll); // step_const
        csl::set(m_n[151], 0ll); // step_const
        csl::set(m_n[157], 0ll); // step_const
        csl::set(m_n[163], 0ll); // step_const
        csl::set(m_n[22], 2047ll); // step_const
        csl::set(m_n[8], 2047ll); // step_const
        csl::set(m_n[10], 0ll); // step_const
        csl::set(m_n[23], 0ll); // step_const
        csl::set(m_n[9], 0ll); // step_const
        csl::set(m_n[127], 2047ll); // step_const
        csl::set(m_n[128], 2047ll); // step_const
        csl::set(m_n[84], 8ll); // step_const
        csl::set(m_n[75], 1ll); // step_const
        csl::set(m_n[129], 0ll); // step_const
        csl::set(m_n[91], 1ll); // step_const
        csl::set(m_n[88], 2047ll); // step_const
        csl::set(m_n[95], 0ll); // step_const
        csl::set(m_n[123], 1ll); // step_const
        csl::set(m_n[124], 0ll); // step_const
        csl::set(m_n[125], 0ll); // step_const
    }

    void execute_segment_0()
    {
        execute_segment_0_fragment_0();
    }

    void execute_segment_1_fragment_0()
    {
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_11], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[7], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[6], m_w[TMP_W_0], 11, true, 52, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[5], m_w[TMP_W_0], 52, true, 0, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[5], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[6], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[7], 1);
        csl::step_bit_combine(m_w[4], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[4], m_w[4], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[3], m_w[TMP_W_0], 63, true, 0, m_temp_alloc);
    }

    void execute_segment_1()
    {
        execute_segment_1_fragment_0();
    }

    void execute_segment_2_fragment_0()
    {
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[5], m_w[TMP_W_0], 64, false, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[5], 64);
        csl::step_bit_extract(m_w[6], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[6], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[7], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_00], 64);
        csl::step_bit_extract(m_n[2], m_w[TMP_W_0], 63, true, 0, m_temp_alloc);
    }

    void execute_segment_2()
    {
        execute_segment_2_fragment_0();
    }

    void execute_segment_3_fragment_0()
    {
        csl::mask_lower(m_n[TMP_N_0], m_n[2], 63);
        csl::mask_lower(m_n[TMP_N_1], m_n[3], 63);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_w[TMP_W_0], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_w[3], m_n[TMP_N_0], m_w[TMP_W_0], m_temp_alloc);
        csl::step_nsign_bit(m_n[4], m_w[3], 65);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[7], 64, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_1], m_w[4], 64, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_2], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_36[2] = { 19, 20 };
        csl::set(m_w[9], m_w[csl::checked_array_value(mux_lookup_36, m_n[TMP_N_2])]);
        csl::step_reduce(m_w[TMP_W_0], m_w[9], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[41], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[4], 64, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_1], m_w[7], 64, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_2], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_44[2] = { 19, 20 };
        csl::set(m_w[8], m_w[csl::checked_array_value(mux_lookup_44, m_n[TMP_N_2])]);
        csl::step_reduce(m_w[TMP_W_0], m_w[8], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[40], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[41], 1);
        csl::step_xor(m_n[42], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[42], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[9], 63);
        csl::step_bit_extract(m_n[37], m_n[TMP_N_0], 11, true, 52);
        csl::mask_lower(m_n[TMP_N_0], m_w[8], 63);
        csl::step_bit_extract(m_n[36], m_n[TMP_N_0], 11, true, 52);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 11);
        csl::mask_lower(m_n[TMP_N_1], m_n[37], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[47], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::step_reduce(m_n[TMP_N_0], m_n[47], 12);
        csl::step_bit_extract(m_n[49], m_n[TMP_N_0], 12, false, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[48], 6);
        csl::mask_lower(m_n[TMP_N_1], m_n[49], 12);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[51], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_sign_bit(m_n[50], m_n[51], 14);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[50], 1);
        csl::step_not_signed(m_n[53], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_w[9], 63);
        csl::step_bit_extract(m_n[25], m_n[TMP_N_0], 11, true, 52);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[24], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[27], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::step_not_signed(m_n[45], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_w[9], 52);
        csl::step_bit_extract(m_n[39], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[39], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[43], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_92[2] = { 174, 175 };
        csl::set(m_n[44], m_n[csl::checked_array_value(mux_lookup_92, m_n[TMP_N_4])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[44], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[45], 1);
        csl::step_bit_combine(m_n[46], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[52], 54);
        csl::step_reduce(m_n[TMP_N_1], m_n[46], 53);
        csl::step_bit_combine(m_w[10], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 54, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[10], 107);
        csl::mask_lower(m_n[TMP_N_0], m_n[47], 12);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_ld_exp(m_w[11], m_w[TMP_W_0], m_n[TMP_N_0], true, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_w[TMP_W_0], m_w[11], 107);
        csl::step_reduce(m_n[TMP_N_1], m_n[53], 1);
        csl::step_and(m_w[12], m_w[TMP_W_0], m_n[TMP_N_1], m_temp_alloc);
        csl::step_logical_finalize(m_w[12], 107, 107, true, true);
        csl::mask_lower(m_w[TMP_W_0], m_w[12], 107);
        csl::step_bit_extract(m_n[63], m_w[TMP_W_0], 55, true, 52, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[63], 55);
    }

    void execute_segment_3_fragment_1()
    {
        csl::step_reduce(m_n[TMP_N_1], m_n[64], 1);
        csl::step_bit_combine(m_n[65], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 55, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[65], 56);
        csl::step_reduce(m_n[TMP_N_2], m_n[42], 1);
        csl::step_xor(m_n[66], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[66], 56, 56, true, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[8], 52);
        csl::step_bit_extract(m_n[38], m_n[TMP_N_0], 52, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_w[12], 52);
        csl::step_bit_extract(m_n[54], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[54], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[55], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[56], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[56], 1);
        csl::step_not_signed(m_n[57], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[57], 1);
        csl::step_not_signed(m_n[58], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[42], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[58], 1);
        csl::step_and(m_n[59], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[59], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[59], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[60], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[38], 52);
        csl::step_reduce(m_n[TMP_N_3], m_n[61], 2);
        csl::step_bit_combine(m_n[62], m_n[TMP_N_0], m_n[TMP_N_1], 4, 1, 1, 2);
        csl::step_bit_combine(m_n[62], m_n[62], m_n[TMP_N_2], 4, 2, 2, 54);
        csl::step_bit_combine(m_n[62], m_n[62], m_n[TMP_N_3], 4, 3, 54, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[62], 56);
        csl::mask_lower(m_n[TMP_N_1], m_n[66], 56);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_add(m_n[67], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[67], 56);
        csl::step_bit_extract(m_n[68], m_n[TMP_N_0], 56, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[57], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[68], 56);
        csl::step_bit_combine(m_n[69], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::step_bit_extract(m_n[132], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[132], 32);
        csl::mask_lower(m_n[TMP_N_2], m_n[131], 32);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 32, 32, false, false);
        csl::step_reducing_and(m_n[133], m_n[TMP_N_3], 32, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 25);
        csl::step_bit_extract(m_n[135], m_n[TMP_N_0], 25, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[134], 7);
        csl::step_reduce(m_n[TMP_N_1], m_n[135], 25);
        csl::step_bit_combine(m_n[136], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 7, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::step_bit_extract(m_n[137], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[133], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[137], 32);
        csl::mask_lower(m_n[TMP_N_3], m_n[136], 32);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_174[2] = { 174, 175 };
        csl::set(m_n[138], m_n[csl::checked_array_value(mux_lookup_174, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[138], 32);
        csl::step_bit_extract(m_n[140], m_n[TMP_N_0], 16, true, 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[140], 16);
        csl::mask_lower(m_n[TMP_N_2], m_n[139], 16);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 16, 16, false, false);
        csl::step_reducing_and(m_n[141], m_n[TMP_N_3], 16, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[138], 16);
        csl::step_bit_extract(m_n[142], m_n[TMP_N_0], 16, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[138], 32);
        csl::step_bit_extract(m_n[143], m_n[TMP_N_0], 16, true, 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[141], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[143], 16);
        csl::mask_lower(m_n[TMP_N_3], m_n[142], 16);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_192[2] = { 174, 175 };
        csl::set(m_n[144], m_n[csl::checked_array_value(mux_lookup_192, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[144], 16);
        csl::step_bit_extract(m_n[146], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[146], 8);
        csl::mask_lower(m_n[TMP_N_2], m_n[145], 8);
    }

    void execute_segment_3_fragment_2()
    {
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 8, 8, false, false);
        csl::step_reducing_and(m_n[147], m_n[TMP_N_3], 8, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[144], 8);
        csl::step_bit_extract(m_n[148], m_n[TMP_N_0], 8, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[144], 16);
        csl::step_bit_extract(m_n[149], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[147], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[149], 8);
        csl::mask_lower(m_n[TMP_N_3], m_n[148], 8);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_210[2] = { 174, 175 };
        csl::set(m_n[150], m_n[csl::checked_array_value(mux_lookup_210, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[150], 8);
        csl::step_bit_extract(m_n[152], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[152], 4);
        csl::mask_lower(m_n[TMP_N_2], m_n[151], 4);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 4, 4, false, false);
        csl::step_reducing_and(m_n[153], m_n[TMP_N_3], 4, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[150], 4);
        csl::step_bit_extract(m_n[154], m_n[TMP_N_0], 4, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[150], 8);
        csl::step_bit_extract(m_n[155], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[153], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[155], 4);
        csl::mask_lower(m_n[TMP_N_3], m_n[154], 4);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_228[2] = { 174, 175 };
        csl::set(m_n[156], m_n[csl::checked_array_value(mux_lookup_228, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[156], 4);
        csl::step_bit_extract(m_n[158], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[158], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[157], 2);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 2, 2, false, false);
        csl::step_reducing_and(m_n[159], m_n[TMP_N_3], 2, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[156], 2);
        csl::step_bit_extract(m_n[160], m_n[TMP_N_0], 2, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[156], 4);
        csl::step_bit_extract(m_n[161], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[159], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[161], 2);
        csl::mask_lower(m_n[TMP_N_3], m_n[160], 2);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_246[2] = { 174, 175 };
        csl::set(m_n[162], m_n[csl::checked_array_value(mux_lookup_246, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[162], 2);
        csl::step_bit_extract(m_n[164], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[164], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[163], 1);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 1, 1, false, false);
        csl::step_reducing_and(m_n[165], m_n[TMP_N_3], 1, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[165], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[159], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[153], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[147], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[141], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[133], 1);
        csl::step_bit_combine(m_n[166], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[166], m_n[166], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[166], m_n[166], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[166], m_n[166], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[166], m_n[166], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[166], 6);
        csl::step_bit_extract(m_n[70], m_n[TMP_N_0], 6, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[70], 6);
        csl::mask_lower(m_n[TMP_N_2], m_n[71], 6);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 6, 6, false, false);
        csl::step_reducing_and(m_n[72], m_n[TMP_N_3], 6, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[72], 1);
        csl::step_not_signed(m_n[112], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[22], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[28], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[28], 1);
        csl::step_not_signed(m_n[33], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::step_not_signed(m_n[34], m_n[TMP_N_1], 1);
    }

    void execute_segment_3_fragment_3()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[34], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 1);
        csl::step_and(m_n[35], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[35], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[8], 63);
        csl::step_bit_extract(m_n[11], m_n[TMP_N_0], 11, true, 52);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[8], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[14], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[14], 1);
        csl::step_not_signed(m_n[19], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[10], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[13], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[13], 1);
        csl::step_not_signed(m_n[20], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[20], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[19], 1);
        csl::step_and(m_n[21], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[21], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[21], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[35], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[112], 1);
        csl::step_and(m_n[113], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[113], m_n[113], m_n[TMP_N_3]);
        csl::step_and(m_n[113], m_n[113], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[113], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[13], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[27], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[41], 1);
        csl::step_and(m_n[117], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[117], m_n[117], m_n[TMP_N_3]);
        csl::step_and(m_n[117], m_n[117], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[117], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[21], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::step_and(m_n[118], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[118], m_n[118], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[118], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[118], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[117], 1);
        csl::step_or(m_n[119], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[119], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[9], 52);
        csl::step_bit_extract(m_n[26], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[23], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[26], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[29], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[28], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::step_and(m_n[31], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[31], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[41], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[31], 1);
        csl::step_and(m_n[114], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[114], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[8], 52);
        csl::step_bit_extract(m_n[12], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[12], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[15], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[14], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[15], 1);
        csl::step_and(m_n[17], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[17], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[17], 1);
        csl::step_and(m_n[115], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[115], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[115], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[114], 1);
        csl::step_or(m_n[116], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[116], 1, 1, false, true);
    }

    void execute_segment_3_fragment_4()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[116], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[119], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[113], 1);
        csl::step_or(m_n[120], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_or(m_n[120], m_n[120], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[120], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[29], 1);
        csl::step_not_signed(m_n[30], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[28], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[30], 1);
        csl::step_and(m_n[32], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[32], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[15], 1);
        csl::step_not_signed(m_n[16], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[14], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[16], 1);
        csl::step_and(m_n[18], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[18], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[18], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[32], 1);
        csl::step_or(m_n[107], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[107], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[17], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[31], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[42], 1);
        csl::step_and(m_n[108], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[108], m_n[108], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[108], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[108], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[107], 1);
        csl::step_or(m_n[109], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[109], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[109], 1);
        csl::step_not_signed(m_n[121], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[121], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[120], 1);
        csl::step_and(m_n[122], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[122], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::mask_lower(m_n[TMP_N_1], m_n[70], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_ld_exp(m_n[73], m_n[TMP_N_0], m_n[TMP_N_1], false);
        csl::step_reduce(m_n[TMP_N_0], m_n[73], 5);
        csl::step_bit_extract(m_n[82], m_n[TMP_N_0], 1, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[73], 4);
        csl::step_bit_extract(m_n[81], m_n[TMP_N_0], 1, true, 3);
        csl::step_reduce(m_n[TMP_N_0], m_n[73], 3);
        csl::step_bit_extract(m_n[80], m_n[TMP_N_0], 1, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[73], 2);
        csl::step_bit_extract(m_n[79], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[73], 1);
        csl::step_bit_extract(m_n[78], m_n[TMP_N_0], 1, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[78], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[79], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[80], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[81], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[82], 1);
        csl::step_bit_combine(m_n[83], m_n[TMP_N_0], m_n[TMP_N_1], 5, 1, 1, 2);
        csl::step_bit_combine(m_n[83], m_n[83], m_n[TMP_N_2], 5, 2, 2, 3);
        csl::step_bit_combine(m_n[83], m_n[83], m_n[TMP_N_3], 5, 3, 3, 4);
        csl::step_bit_combine(m_n[83], m_n[83], m_n[TMP_N_4], 5, 4, 4, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[83], 5);
        csl::mask_lower(m_n[TMP_N_2], m_n[84], 5);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 5, 5, false, false);
        csl::step_reducing_and(m_n[85], m_n[TMP_N_3], 5, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[85], 1);
        csl::step_not_signed(m_n[86], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_n[36], 11);
        csl::mask_lower(m_n[TMP_N_1], m_n[75], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_add(m_n[76], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[76], 12);
        csl::mask_lower(m_n[TMP_N_1], m_n[70], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[77], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[73], 57);
        csl::step_bit_extract(m_n[74], m_n[TMP_N_0], 56, true, 1);
        csl::mask_lower(m_n[TMP_N_0], m_n[74], 55);
        csl::step_bit_extract(m_n[87], m_n[TMP_N_0], 53, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[87], 53);
        csl::step_reduce(m_n[TMP_N_1], m_n[77], 13);
    }

    void execute_segment_3_fragment_5()
    {
        csl::step_bit_combine(m_w[13], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 53, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[13], 66);
        csl::mask_lower(m_n[TMP_N_0], m_n[86], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[14], m_w[TMP_W_0], m_n[TMP_N_0], m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[14], 64);
        csl::step_bit_extract(m_n[100], m_w[TMP_W_0], 11, true, 53, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[14], 66);
        csl::step_bit_extract(m_n[92], m_w[TMP_W_0], 2, true, 64, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[92], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[91], 2);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 2, 2, false, false);
        csl::step_reducing_and(m_n[93], m_n[TMP_N_3], 2, false);
        csl::mask_lower(m_w[TMP_W_0], m_w[14], 66);
        csl::step_bit_extract(m_n[89], m_w[TMP_W_0], 13, true, 53, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[89], 13);
        csl::mask_lower(m_n[TMP_N_2], m_n[88], 13);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 13, 13, false, false);
        csl::step_reducing_and(m_n[90], m_n[TMP_N_3], 13, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[90], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[93], 1);
        csl::step_or(m_n[94], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[94], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[21], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[35], 1);
        csl::step_and(m_n[101], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[101], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[101], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[94], 1);
        csl::step_and(m_n[104], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[104], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[42], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[17], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[31], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[18], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[32], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[104], 1);
        csl::step_bit_combine(m_n[105], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[105], m_n[105], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[105], m_n[105], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[105], m_n[105], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[105], m_n[105], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[105], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_498[] = {
            0ll, 0ll, 1ll, 1ll, 1ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_498, 64, 0, m_n[106], m_n[TMP_N_0]);
        csl::step_reduce(m_w[TMP_W_0], m_w[14], 66, m_temp_alloc);
        csl::step_bit_extract(m_n[97], m_w[TMP_W_0], 1, true, 65, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[89], 13);
        csl::mask_lower(m_n[TMP_N_2], m_n[95], 13);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 13, 13, false, false);
        csl::step_reducing_and(m_n[96], m_n[TMP_N_3], 13, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[96], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[97], 1);
        csl::step_or(m_n[98], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[98], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[13], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[27], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[101], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[98], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[72], 1);
        csl::step_bit_combine(m_n[102], m_n[TMP_N_0], m_n[TMP_N_1], 5, 1, 1, 2);
        csl::step_bit_combine(m_n[102], m_n[102], m_n[TMP_N_2], 5, 2, 2, 3);
        csl::step_bit_combine(m_n[102], m_n[102], m_n[TMP_N_3], 5, 3, 3, 4);
        csl::step_bit_combine(m_n[102], m_n[102], m_n[TMP_N_4], 5, 4, 4, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[102], 5);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_519[] = {
            0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_519, 32, 0, m_n[103], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[103], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[106], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[109], 1);
        csl::step_bit_combine(m_n[110], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 1, 2);
        csl::step_bit_combine(m_n[110], m_n[110], m_n[TMP_N_2], 3, 2, 2, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[110], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_526[] = {
            1ll, 0ll, 2ll, 2ll, 3ll, 3ll, 3ll, 3ll
        };
        csl::step_lookup(lut_init_data_526, 8, 0, m_n[111], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[111], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[129], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[100], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[128], 11);
        csl::mask_lower(m_n[TMP_N_5], m_n[127], 11);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_534[4] = { 174, 175, 176, 177 };
        csl::set(m_n[130], m_n[csl::checked_array_value(mux_lookup_534, m_n[TMP_N_6])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[14], 53);
        csl::step_bit_extract(m_n[99], m_n[TMP_N_0], 52, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
    }

    void execute_segment_3_fragment_6()
    {
        csl::mask_lower(m_n[TMP_N_1], m_n[111], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[125], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[99], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[124], 52);
        csl::mask_lower(m_n[TMP_N_5], m_n[123], 52);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_547[4] = { 174, 175, 176, 177 };
        csl::set(m_n[126], m_n[csl::checked_array_value(mux_lookup_547, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[126], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[130], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[122], 1);
        csl::step_bit_combine(m_w[15], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[15], m_w[15], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[15], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[0], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[0], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREOUT2] = m_w[TMP_W_0];
    }

    void execute_segment_3()
    {
        execute_segment_3_fragment_0();
        execute_segment_3_fragment_1();
        execute_segment_3_fragment_2();
        execute_segment_3_fragment_3();
        execute_segment_3_fragment_4();
        execute_segment_3_fragment_5();
        execute_segment_3_fragment_6();
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
        if ((m_segment_cycle[1] == m_update_cycle) && (m_io_cycle[1] > m_update_cycle))
        {
            execute_segment_1();
            ++m_segment_cycle[1];
        }
        if ((m_segment_cycle[2] == m_update_cycle) && (m_io_cycle[0] > m_update_cycle))
        {
            execute_segment_2();
            ++m_segment_cycle[2];
        }
        if ((m_segment_cycle[3] == m_update_cycle) && (m_io_cycle[0] > m_update_cycle) && (m_io_cycle[1] > m_update_cycle))
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
    static constexpr size_t PORT_OUT_PRIMWIREOUT2 = 18;
    static constexpr size_t TMP_N_0 = 172;
    static constexpr size_t TMP_N_1 = 173;
    static constexpr size_t TMP_N_2 = 174;
    static constexpr size_t TMP_N_3 = 175;
    static constexpr size_t TMP_N_4 = 176;
    static constexpr size_t TMP_N_5 = 177;
    static constexpr size_t TMP_N_6 = 178;
    static constexpr size_t TMP_W_0 = 19;
    static constexpr size_t TMP_W_1 = 20;

    int64_t m_io_cycle[3];
    int64_t m_segment_cycle[4];
    int64_t m_update_cycle;

    csl::mp_temp_allocator m_temp_alloc;
    int64_t m_n[179];
    csl::mp_int m_w[21];
};

#endif // SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_TYPESFLOA0000J6OF0CD16OK0CP06HJ0U_H_