/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#pragma once

#ifndef SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDSUBFUSEDBLOCK_TYPESFLOATIEEE_52_11_4_CORRECTROUNDING_38560000X0AO30CD06CJ6OK0DPZC_H_
#define SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDSUBFUSEDBLOCK_TYPESFLOATIEEE_52_11_4_CORRECTROUNDING_38560000X0AO30CD06CJ6OK0DPZC_H_

#include "support/csl.h"
#ifdef WRITE_STM_FILES
#include "support/csl_io.h"
#endif

class flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc
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

    /** Output struct for "out_primWireAux" */
    struct io_struct_out_primWireAux
    {
        double port_out_primwireaux;
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
    flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc() {};
    flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc(const flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc&) = delete;
    flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc(flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc&&) = delete;
    flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc& operator=(const flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc&) = delete;
    flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc& operator=(flt_ifft8k_base_DUT_addSubFusedBlock_typeSFloatIEEE_52_11_4_correctRounding_38560000x0ao30cd06cj6ok0dpzc&&) = delete;

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
    void read(io_struct_out_primWireAux& output)
    {
        bool needs_to_execute = (m_io_cycle[2] == m_update_cycle);
        if (needs_to_execute)
        {
            m_io_cycle[2]++;
            execute();
        }

        csl::mask_lower(output.port_out_primwireaux, m_w[PORT_OUT_PRIMWIREAUX2], 64);
    }

    void read(io_struct_out_primWireOut& output)
    {
        bool needs_to_execute = (m_io_cycle[3] == m_update_cycle);
        if (needs_to_execute)
        {
            m_io_cycle[3]++;
            execute();
        }

        csl::mask_lower(output.port_out_primwireout, m_w[PORT_OUT_PRIMWIREOUT3], 64);
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
        static constexpr size_t native_reset_range_sizes[] = { 241ull };
        for (size_t i = 0; i < 1; ++i)
        {
            csl::fill_n(&m_n[native_reset_range_indices[i]], native_reset_range_sizes[i], native_reset_range_values[native_reset_range_value_indices[i]]);
        }
        static constexpr uint64_t wide_reset_range_values[] = { 0ull };
        static constexpr csl::mp_int_info wide_reset_range_infos[] = { { 0, 1, 0 } };
        static constexpr uint32_t wide_reset_range_value_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_indices[] = { 0ull };
        static constexpr size_t wide_reset_range_sizes[] = { 20ull };
        for (size_t i = 0; i < 1; ++i)
        {
            for (size_t j = 0; j < wide_reset_range_sizes[i]; ++j)
            {
                csl::fill_mpz_data(m_w[wide_reset_range_indices[i] + j],
                    wide_reset_range_values, wide_reset_range_infos, wide_reset_range_value_indices[i]);
            }
        }
        csl::fill_n(m_io_cycle, 4, -1);
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
            m_io_cycle[3] = m_update_cycle + 1;
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
        csl::set(m_n[0], 0ll); // step_const
        csl::set(m_n[1], 1ll); // step_const
        csl::set(m_n[22], 0ll); // step_const
        csl::set(m_n[8], 0ll); // step_const
        csl::set(m_n[75], 57ll); // step_const
        csl::set(m_n[197], 0ll); // step_const
        csl::set(m_n[41], 0ll); // step_const
        csl::set(m_n[44], 55ll); // step_const
        csl::set(m_n[45], 54ll); // step_const
        csl::set(m_n[57], 0ll); // step_const
        csl::set(m_n[59], 0ll); // step_const
        csl::set(m_n[42], 1ll); // step_const
        csl::set(m_n[64], 0ll); // step_const
        csl::set(m_n[205], 0ll); // step_const
        csl::set(m_n[200], -1ll); // step_const
        csl::set(m_n[211], 0ll); // step_const
        csl::set(m_n[217], 0ll); // step_const
        csl::set(m_n[223], 0ll); // step_const
        csl::set(m_n[229], 0ll); // step_const
        csl::set(m_n[20], 2047ll); // step_const
        csl::set(m_n[6], 2047ll); // step_const
        csl::set(m_n[21], 0ll); // step_const
        csl::set(m_n[7], 0ll); // step_const
        csl::set(m_n[135], 2047ll); // step_const
        csl::set(m_n[136], 2047ll); // step_const
        csl::set(m_n[88], 8ll); // step_const
        csl::set(m_n[161], 0ll); // step_const
        csl::set(m_n[169], 0ll); // step_const
        csl::set(m_n[164], -1ll); // step_const
        csl::set(m_n[175], 0ll); // step_const
        csl::set(m_n[181], 0ll); // step_const
        csl::set(m_n[187], 0ll); // step_const
        csl::set(m_n[193], 0ll); // step_const
        csl::set(m_n[137], 0ll); // step_const
        csl::set(m_n[99], 2047ll); // step_const
        csl::set(m_n[131], 1ll); // step_const
        csl::set(m_n[132], 0ll); // step_const
        csl::set(m_n[133], 0ll); // step_const
        csl::set(m_n[149], 2047ll); // step_const
        csl::set(m_n[150], 2047ll); // step_const
        csl::set(m_n[151], 0ll); // step_const
        csl::set(m_n[145], 1ll); // step_const
        csl::set(m_n[146], 0ll); // step_const
        csl::set(m_n[147], 0ll); // step_const
    }

    void execute_segment_0()
    {
        execute_segment_0_fragment_0();
    }

    void execute_segment_1_fragment_0()
    {
        csl::mask_lower(m_w[TMP_W_0], m_w[PORT_IN_11], 64);
        csl::step_bit_extract(m_n[3], m_w[TMP_W_0], 63, true, 0, m_temp_alloc);
    }

    void execute_segment_1()
    {
        execute_segment_1_fragment_0();
    }

    void execute_segment_2_fragment_0()
    {
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
        csl::step_sub(m_w[4], m_n[TMP_N_0], m_w[TMP_W_0], m_temp_alloc);
        csl::step_nsign_bit(m_n[4], m_w[4], 65);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_1], m_w[PORT_IN_11], 64, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_2], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_18[2] = { 20, 21 };
        csl::set(m_w[6], m_w[csl::checked_array_value(mux_lookup_18, m_n[TMP_N_2])]);
        csl::step_reduce(m_w[TMP_W_0], m_w[6], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[39], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_11], 64, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_1], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_2], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_26[2] = { 20, 21 };
        csl::set(m_w[5], m_w[csl::checked_array_value(mux_lookup_26, m_n[TMP_N_2])]);
        csl::step_reduce(m_w[TMP_W_0], m_w[5], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[38], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[38], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[39], 1);
        csl::step_xor(m_n[40], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[40], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[6], 63);
        csl::step_bit_extract(m_n[23], m_n[TMP_N_0], 11, true, 52);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[23], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[22], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[25], m_n[TMP_N_3], 11, false);
        csl::mask_lower(m_n[TMP_N_0], m_w[5], 63);
        csl::step_bit_extract(m_n[9], m_n[TMP_N_0], 11, true, 52);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[8], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[11], m_n[TMP_N_3], 11, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[25], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::step_and(m_n[139], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[139], m_n[139], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[139], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[139], 1);
        csl::step_not_signed(m_n[140], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_w[6], 63);
        csl::step_bit_extract(m_n[35], m_n[TMP_N_0], 11, true, 52);
        csl::mask_lower(m_n[TMP_N_0], m_w[5], 63);
        csl::step_bit_extract(m_n[34], m_n[TMP_N_0], 11, true, 52);
        csl::mask_lower(m_n[TMP_N_0], m_n[34], 11);
        csl::mask_lower(m_n[TMP_N_1], m_n[35], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[43], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[43], 6);
        csl::step_bit_extract(m_n[52], m_n[TMP_N_0], 6, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[35], 11);
        csl::step_reducing_or(m_n[47], m_n[TMP_N_1]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[47], 1);
        csl::step_not_signed(m_n[48], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[43], 12);
        csl::step_bit_extract(m_n[46], m_n[TMP_N_0], 12, false, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[45], 6);
        csl::mask_lower(m_n[TMP_N_1], m_n[46], 12);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[50], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_sign_bit(m_n[49], m_n[50], 14);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[49], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[48], 1);
        csl::step_or(m_n[51], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[51], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[51], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[52], 6);
        csl::mask_lower(m_n[TMP_N_3], m_n[44], 6);
    }

    void execute_segment_3_fragment_1()
    {
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_96[2] = { 243, 244 };
        csl::set(m_n[53], m_n[csl::checked_array_value(mux_lookup_96, m_n[TMP_N_4])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[25], 1);
        csl::step_not_signed(m_n[54], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_w[6], 52);
        csl::step_bit_extract(m_n[37], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[37], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[54], 1);
        csl::step_bit_combine(m_n[55], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[57], 55);
        csl::step_reduce(m_n[TMP_N_1], m_n[55], 53);
        csl::step_bit_combine(m_w[7], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 55, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[7], 108);
        csl::mask_lower(m_n[TMP_N_0], m_n[53], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_ld_exp(m_w[8], m_w[TMP_W_0], m_n[TMP_N_0], true, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[8], 108);
        csl::step_bit_extract(m_n[62], m_w[TMP_W_0], 55, true, 53, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_w[8], 53);
        csl::step_bit_extract(m_n[58], m_n[TMP_N_0], 53, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[58], 53);
        csl::mask_lower(m_n[TMP_N_2], m_n[59], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 53, 53, false, false);
        csl::step_reducing_and(m_n[60], m_n[TMP_N_3], 53, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[60], 1);
        csl::step_not_signed(m_n[61], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[61], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[62], 55);
        csl::step_bit_combine(m_n[63], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 1, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[63], 56);
        csl::step_reduce(m_n[TMP_N_1], m_n[41], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[41], 1);
        csl::step_bit_combine(m_n[66], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 56, 57);
        csl::step_bit_combine(m_n[66], m_n[66], m_n[TMP_N_2], 3, 2, 57, 0);
        csl::mask_lower(m_n[TMP_N_0], m_w[5], 52);
        csl::step_bit_extract(m_n[36], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[36], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[42], 1);
        csl::step_bit_combine(m_n[56], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 52, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[64], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[56], 53);
        csl::step_bit_combine(m_n[65], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 3, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[65], 56);
        csl::mask_lower(m_n[TMP_N_1], m_n[66], 58);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[68], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[68], 57);
        csl::step_bit_extract(m_n[70], m_n[TMP_N_0], 57, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[70], 57);
        csl::step_bit_extract(m_n[198], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[198], 32);
        csl::mask_lower(m_n[TMP_N_2], m_n[197], 32);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 32, 32, false, false);
        csl::step_reducing_and(m_n[199], m_n[TMP_N_3], 32, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[70], 25);
        csl::step_bit_extract(m_n[201], m_n[TMP_N_0], 25, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[200], 7);
        csl::step_reduce(m_n[TMP_N_1], m_n[201], 25);
        csl::step_bit_combine(m_n[202], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 7, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[70], 57);
        csl::step_bit_extract(m_n[203], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[199], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[203], 32);
        csl::mask_lower(m_n[TMP_N_3], m_n[202], 32);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_170[2] = { 243, 244 };
        csl::set(m_n[204], m_n[csl::checked_array_value(mux_lookup_170, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[204], 32);
        csl::step_bit_extract(m_n[206], m_n[TMP_N_0], 16, true, 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[206], 16);
        csl::mask_lower(m_n[TMP_N_2], m_n[205], 16);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 16, 16, false, false);
        csl::step_reducing_and(m_n[207], m_n[TMP_N_3], 16, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[204], 16);
        csl::step_bit_extract(m_n[208], m_n[TMP_N_0], 16, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[204], 32);
        csl::step_bit_extract(m_n[209], m_n[TMP_N_0], 16, true, 16);
    }

    void execute_segment_3_fragment_2()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[207], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[209], 16);
        csl::mask_lower(m_n[TMP_N_3], m_n[208], 16);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_188[2] = { 243, 244 };
        csl::set(m_n[210], m_n[csl::checked_array_value(mux_lookup_188, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[210], 16);
        csl::step_bit_extract(m_n[212], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[212], 8);
        csl::mask_lower(m_n[TMP_N_2], m_n[211], 8);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 8, 8, false, false);
        csl::step_reducing_and(m_n[213], m_n[TMP_N_3], 8, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[210], 8);
        csl::step_bit_extract(m_n[214], m_n[TMP_N_0], 8, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[210], 16);
        csl::step_bit_extract(m_n[215], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[213], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[215], 8);
        csl::mask_lower(m_n[TMP_N_3], m_n[214], 8);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_206[2] = { 243, 244 };
        csl::set(m_n[216], m_n[csl::checked_array_value(mux_lookup_206, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[216], 8);
        csl::step_bit_extract(m_n[218], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[218], 4);
        csl::mask_lower(m_n[TMP_N_2], m_n[217], 4);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 4, 4, false, false);
        csl::step_reducing_and(m_n[219], m_n[TMP_N_3], 4, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[216], 4);
        csl::step_bit_extract(m_n[220], m_n[TMP_N_0], 4, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[216], 8);
        csl::step_bit_extract(m_n[221], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[219], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[221], 4);
        csl::mask_lower(m_n[TMP_N_3], m_n[220], 4);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_224[2] = { 243, 244 };
        csl::set(m_n[222], m_n[csl::checked_array_value(mux_lookup_224, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[222], 4);
        csl::step_bit_extract(m_n[224], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[224], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[223], 2);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 2, 2, false, false);
        csl::step_reducing_and(m_n[225], m_n[TMP_N_3], 2, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[222], 2);
        csl::step_bit_extract(m_n[226], m_n[TMP_N_0], 2, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[222], 4);
        csl::step_bit_extract(m_n[227], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[225], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[227], 2);
        csl::mask_lower(m_n[TMP_N_3], m_n[226], 2);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_242[2] = { 243, 244 };
        csl::set(m_n[228], m_n[csl::checked_array_value(mux_lookup_242, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[228], 2);
        csl::step_bit_extract(m_n[230], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[230], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[229], 1);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 1, 1, false, false);
        csl::step_reducing_and(m_n[231], m_n[TMP_N_3], 1, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[231], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[225], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[219], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[213], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[207], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[199], 1);
        csl::step_bit_combine(m_n[232], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[232], m_n[232], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[232], m_n[232], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[232], m_n[232], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[232], m_n[232], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[232], 6);
        csl::step_bit_extract(m_n[73], m_n[TMP_N_0], 6, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[73], 6);
        csl::mask_lower(m_n[TMP_N_2], m_n[75], 6);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 6, 6, false, false);
        csl::step_reducing_and(m_n[76], m_n[TMP_N_3], 6, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[23], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[20], 11);
    }

    void execute_segment_3_fragment_3()
    {
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[26], m_n[TMP_N_3], 11, false);
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
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[9], 11);
        csl::mask_lower(m_n[TMP_N_2], m_n[6], 11);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 11, 11, false, false);
        csl::step_reducing_and(m_n[12], m_n[TMP_N_3], 11, false);
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
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[19], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[33], 1);
        csl::step_and(m_n[110], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[110], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[110], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[76], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::step_and(m_n[141], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[141], m_n[141], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[141], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[141], 1);
        csl::step_not_signed(m_n[142], m_n[TMP_N_1], 1);
        csl::step_reduce(m_w[TMP_W_0], m_w[5], 64, m_temp_alloc);
        csl::step_bit_extract(m_n[107], m_w[TMP_W_0], 1, true, 63, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_w[6], 52);
        csl::step_bit_extract(m_n[24], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[21], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[24], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[27], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[27], 1);
        csl::step_not_signed(m_n[28], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[26], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[28], 1);
        csl::step_and(m_n[30], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[30], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_w[5], 52);
        csl::step_bit_extract(m_n[10], m_n[TMP_N_0], 52, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[7], 52);
        csl::mask_lower(m_n[TMP_N_2], m_n[10], 52);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 52, 52, false, false);
        csl::step_reducing_and(m_n[13], m_n[TMP_N_3], 52, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[13], 1);
        csl::step_not_signed(m_n[14], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[14], 1);
        csl::step_and(m_n[16], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[16], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[16], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[30], 1);
        csl::step_or(m_n[114], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[114], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[26], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[27], 1);
        csl::step_and(m_n[29], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[29], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[12], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[13], 1);
        csl::step_and(m_n[15], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[15], 1, 1, false, true);
    }

    void execute_segment_3_fragment_4()
    {
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[15], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[40], 1);
        csl::step_and(m_n[118], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[118], m_n[118], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[118], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[118], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[114], 1);
        csl::step_or(m_n[119], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[119], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[119], 1);
        csl::step_not_signed(m_n[143], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[143], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[107], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[142], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[140], 1);
        csl::step_and(m_n[144], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[144], m_n[144], m_n[TMP_N_3]);
        csl::step_and(m_n[144], m_n[144], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[144], 1, 1, false, true);
        csl::mask_lower(m_n[TMP_N_0], m_n[70], 57);
        csl::mask_lower(m_n[TMP_N_1], m_n[73], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_ld_exp(m_n[74], m_n[TMP_N_0], m_n[TMP_N_1], false);
        csl::step_reduce(m_n[TMP_N_0], m_n[74], 5);
        csl::step_bit_extract(m_n[95], m_n[TMP_N_0], 1, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[74], 4);
        csl::step_bit_extract(m_n[94], m_n[TMP_N_0], 1, true, 3);
        csl::step_reduce(m_n[TMP_N_0], m_n[74], 3);
        csl::step_bit_extract(m_n[93], m_n[TMP_N_0], 1, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[74], 2);
        csl::step_bit_extract(m_n[92], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[74], 1);
        csl::step_bit_extract(m_n[91], m_n[TMP_N_0], 1, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[91], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[92], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[93], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[94], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[95], 1);
        csl::step_bit_combine(m_n[96], m_n[TMP_N_0], m_n[TMP_N_1], 5, 1, 1, 2);
        csl::step_bit_combine(m_n[96], m_n[96], m_n[TMP_N_2], 5, 2, 2, 3);
        csl::step_bit_combine(m_n[96], m_n[96], m_n[TMP_N_3], 5, 3, 3, 4);
        csl::step_bit_combine(m_n[96], m_n[96], m_n[TMP_N_4], 5, 4, 4, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[96], 5);
        csl::mask_lower(m_n[TMP_N_2], m_n[88], 5);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 5, 5, false, false);
        csl::step_reducing_and(m_n[97], m_n[TMP_N_3], 5, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[97], 1);
        csl::step_not_signed(m_n[98], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_n[34], 11);
        csl::mask_lower(m_n[TMP_N_1], m_n[42], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_add(m_n[77], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[77], 12);
        csl::mask_lower(m_n[TMP_N_1], m_n[73], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[78], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[74], 56);
        csl::step_bit_extract(m_n[80], m_n[TMP_N_0], 53, true, 3);
        csl::step_reduce(m_n[TMP_N_0], m_n[80], 53);
        csl::step_reduce(m_n[TMP_N_1], m_n[78], 13);
        csl::step_bit_combine(m_w[9], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 53, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[9], 66);
        csl::mask_lower(m_n[TMP_N_0], m_n[98], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[12], m_w[TMP_W_0], m_n[TMP_N_0], m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[12], 64);
        csl::step_bit_extract(m_n[109], m_w[TMP_W_0], 11, true, 53, m_temp_alloc);
        csl::mask_lower(m_n[TMP_N_0], m_n[65], 56);
        csl::mask_lower(m_n[TMP_N_1], m_n[66], 58);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_add(m_n[67], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[67], 57);
        csl::step_bit_extract(m_n[69], m_n[TMP_N_0], 57, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::step_bit_extract(m_n[162], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[162], 32);
        csl::mask_lower(m_n[TMP_N_2], m_n[161], 32);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 32, 32, false, false);
        csl::step_reducing_and(m_n[163], m_n[TMP_N_3], 32, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 25);
        csl::step_bit_extract(m_n[165], m_n[TMP_N_0], 25, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[164], 7);
    }

    void execute_segment_3_fragment_5()
    {
        csl::step_reduce(m_n[TMP_N_1], m_n[165], 25);
        csl::step_bit_combine(m_n[166], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 7, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::step_bit_extract(m_n[167], m_n[TMP_N_0], 32, true, 25);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[163], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[167], 32);
        csl::mask_lower(m_n[TMP_N_3], m_n[166], 32);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_448[2] = { 243, 244 };
        csl::set(m_n[168], m_n[csl::checked_array_value(mux_lookup_448, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[168], 32);
        csl::step_bit_extract(m_n[170], m_n[TMP_N_0], 16, true, 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[170], 16);
        csl::mask_lower(m_n[TMP_N_2], m_n[169], 16);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 16, 16, false, false);
        csl::step_reducing_and(m_n[171], m_n[TMP_N_3], 16, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[168], 16);
        csl::step_bit_extract(m_n[172], m_n[TMP_N_0], 16, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[168], 32);
        csl::step_bit_extract(m_n[173], m_n[TMP_N_0], 16, true, 16);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[171], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[173], 16);
        csl::mask_lower(m_n[TMP_N_3], m_n[172], 16);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_466[2] = { 243, 244 };
        csl::set(m_n[174], m_n[csl::checked_array_value(mux_lookup_466, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[174], 16);
        csl::step_bit_extract(m_n[176], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[176], 8);
        csl::mask_lower(m_n[TMP_N_2], m_n[175], 8);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 8, 8, false, false);
        csl::step_reducing_and(m_n[177], m_n[TMP_N_3], 8, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[174], 8);
        csl::step_bit_extract(m_n[178], m_n[TMP_N_0], 8, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[174], 16);
        csl::step_bit_extract(m_n[179], m_n[TMP_N_0], 8, true, 8);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[177], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[179], 8);
        csl::mask_lower(m_n[TMP_N_3], m_n[178], 8);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_484[2] = { 243, 244 };
        csl::set(m_n[180], m_n[csl::checked_array_value(mux_lookup_484, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[180], 8);
        csl::step_bit_extract(m_n[182], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[182], 4);
        csl::mask_lower(m_n[TMP_N_2], m_n[181], 4);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 4, 4, false, false);
        csl::step_reducing_and(m_n[183], m_n[TMP_N_3], 4, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[180], 4);
        csl::step_bit_extract(m_n[184], m_n[TMP_N_0], 4, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[180], 8);
        csl::step_bit_extract(m_n[185], m_n[TMP_N_0], 4, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[183], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[185], 4);
        csl::mask_lower(m_n[TMP_N_3], m_n[184], 4);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_502[2] = { 243, 244 };
        csl::set(m_n[186], m_n[csl::checked_array_value(mux_lookup_502, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[186], 4);
        csl::step_bit_extract(m_n[188], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[188], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[187], 2);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 2, 2, false, false);
        csl::step_reducing_and(m_n[189], m_n[TMP_N_3], 2, false);
        csl::mask_lower(m_n[TMP_N_0], m_n[186], 2);
        csl::step_bit_extract(m_n[190], m_n[TMP_N_0], 2, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[186], 4);
        csl::step_bit_extract(m_n[191], m_n[TMP_N_0], 2, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[189], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[191], 2);
        csl::mask_lower(m_n[TMP_N_3], m_n[190], 2);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_520[2] = { 243, 244 };
        csl::set(m_n[192], m_n[csl::checked_array_value(mux_lookup_520, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[192], 2);
        csl::step_bit_extract(m_n[194], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
    }

    void execute_segment_3_fragment_6()
    {
        csl::mask_lower(m_n[TMP_N_1], m_n[194], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[193], 1);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 1, 1, false, false);
        csl::step_reducing_and(m_n[195], m_n[TMP_N_3], 1, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[195], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[189], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[183], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[177], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[171], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[163], 1);
        csl::step_bit_combine(m_n[196], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[196], m_n[196], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[196], m_n[196], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[196], m_n[196], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[196], m_n[196], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[196], 6);
        csl::step_bit_extract(m_n[71], m_n[TMP_N_0], 6, true, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[69], 57);
        csl::mask_lower(m_n[TMP_N_1], m_n[71], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_ld_exp(m_n[72], m_n[TMP_N_0], m_n[TMP_N_1], false);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 5);
        csl::step_bit_extract(m_n[86], m_n[TMP_N_0], 1, true, 4);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 4);
        csl::step_bit_extract(m_n[85], m_n[TMP_N_0], 1, true, 3);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 3);
        csl::step_bit_extract(m_n[84], m_n[TMP_N_0], 1, true, 2);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 2);
        csl::step_bit_extract(m_n[83], m_n[TMP_N_0], 1, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[72], 1);
        csl::step_bit_extract(m_n[82], m_n[TMP_N_0], 1, true, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[82], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[83], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[84], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[85], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[86], 1);
        csl::step_bit_combine(m_n[87], m_n[TMP_N_0], m_n[TMP_N_1], 5, 1, 1, 2);
        csl::step_bit_combine(m_n[87], m_n[87], m_n[TMP_N_2], 5, 2, 2, 3);
        csl::step_bit_combine(m_n[87], m_n[87], m_n[TMP_N_3], 5, 3, 3, 4);
        csl::step_bit_combine(m_n[87], m_n[87], m_n[TMP_N_4], 5, 4, 4, 0);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[87], 5);
        csl::mask_lower(m_n[TMP_N_2], m_n[88], 5);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 5, 5, false, false);
        csl::step_reducing_and(m_n[89], m_n[TMP_N_3], 5, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[89], 1);
        csl::step_not_signed(m_n[90], m_n[TMP_N_1], 1);
        csl::mask_lower(m_n[TMP_N_0], m_n[77], 12);
        csl::mask_lower(m_n[TMP_N_1], m_n[71], 6);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::step_sub(m_n[79], m_n[TMP_N_0], m_n[TMP_N_1]);
        csl::mask_lower(m_n[TMP_N_0], m_n[72], 56);
        csl::step_bit_extract(m_n[81], m_n[TMP_N_0], 53, true, 3);
        csl::step_reduce(m_n[TMP_N_0], m_n[81], 53);
        csl::step_reduce(m_n[TMP_N_1], m_n[79], 13);
        csl::step_bit_combine(m_w[10], m_n[TMP_N_0], m_n[TMP_N_1], 2, 1, 53, 0, m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[10], 66);
        csl::mask_lower(m_n[TMP_N_0], m_n[90], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        csl::step_add(m_w[11], m_w[TMP_W_0], m_n[TMP_N_0], m_temp_alloc);
        csl::mask_lower(m_w[TMP_W_0], m_w[11], 64);
        csl::step_bit_extract(m_n[106], m_w[TMP_W_0], 11, true, 53, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[106], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[109], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_585[2] = { 243, 244 };
        csl::set(m_n[124], m_n[csl::checked_array_value(mux_lookup_585, m_n[TMP_N_4])]);
        csl::mask_lower(m_w[TMP_W_0], m_w[11], 66);
        csl::step_bit_extract(m_n[100], m_w[TMP_W_0], 13, true, 53, m_temp_alloc);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[100], 13);
        csl::mask_lower(m_n[TMP_N_2], m_n[99], 13);
        csl::step_xor(m_n[TMP_N_3], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize_inv(m_n[TMP_N_3], 13, 13, false, false);
        csl::step_reducing_and(m_n[101], m_n[TMP_N_3], 13, false);
        csl::step_reduce(m_n[TMP_N_0], m_n[15], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[29], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[110], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[101], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[114], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[40], 1);
        csl::step_bit_combine(m_n[115], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[115], m_n[115], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[115], m_n[115], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[115], m_n[115], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[115], m_n[115], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[115], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_604[] = {
            0ll, 1ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 1ll, 1ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_604, 64, 0, m_n[116], m_n[TMP_N_0]);
        csl::step_reduce(m_w[TMP_W_0], m_w[12], 66, m_temp_alloc);
        csl::step_bit_extract(m_n[102], m_w[TMP_W_0], 13, true, 53, m_temp_alloc);
    }

    void execute_segment_3_fragment_7()
    {
        csl::mask_lower(m_n[TMP_N_0], m_n[0], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[102], 13);
        csl::step_reduce(m_n[TMP_N_2], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[0], 1);
        csl::step_add(m_n[TMP_N_4], m_n[TMP_N_1], m_n[TMP_N_3]);
        csl::step_sub(m_n[104], m_n[TMP_N_0], m_n[TMP_N_4]);
        csl::step_nsign_bit(m_n[103], m_n[104], 15);
        csl::step_reduce(m_n[TMP_N_0], m_n[11], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[25], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[110], 1);
        csl::step_reduce(m_n[TMP_N_3], m_n[103], 1);
        csl::step_reduce(m_n[TMP_N_4], m_n[76], 1);
        csl::step_reduce(m_n[TMP_N_5], m_n[40], 1);
        csl::step_bit_combine(m_n[111], m_n[TMP_N_0], m_n[TMP_N_1], 6, 1, 1, 2);
        csl::step_bit_combine(m_n[111], m_n[111], m_n[TMP_N_2], 6, 2, 2, 3);
        csl::step_bit_combine(m_n[111], m_n[111], m_n[TMP_N_3], 6, 3, 3, 4);
        csl::step_bit_combine(m_n[111], m_n[111], m_n[TMP_N_4], 6, 4, 4, 5);
        csl::step_bit_combine(m_n[111], m_n[111], m_n[TMP_N_5], 6, 5, 5, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[111], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_623[] = {
            0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 
            0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_623, 64, 0, m_n[112], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[112], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[116], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[119], 1);
        csl::step_bit_combine(m_n[128], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 1, 2);
        csl::step_bit_combine(m_n[128], m_n[128], m_n[TMP_N_2], 3, 2, 2, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[128], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_630[] = {
            1ll, 0ll, 2ll, 0ll, 3ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_630, 8, 0, m_n[130], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[130], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[137], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[124], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[136], 11);
        csl::mask_lower(m_n[TMP_N_5], m_n[135], 11);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_638[4] = { 243, 244, 245, 246 };
        csl::set(m_n[138], m_n[csl::checked_array_value(mux_lookup_638, m_n[TMP_N_6])]);
        csl::mask_lower(m_n[TMP_N_0], m_w[12], 53);
        csl::step_bit_extract(m_n[108], m_n[TMP_N_0], 52, true, 1);
        csl::mask_lower(m_n[TMP_N_0], m_w[11], 53);
        csl::step_bit_extract(m_n[105], m_n[TMP_N_0], 52, true, 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[105], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[108], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_650[2] = { 243, 244 };
        csl::set(m_n[123], m_n[csl::checked_array_value(mux_lookup_650, m_n[TMP_N_4])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[130], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[133], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[123], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[132], 52);
        csl::mask_lower(m_n[TMP_N_5], m_n[131], 52);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_659[4] = { 243, 244, 245, 246 };
        csl::set(m_n[134], m_n[csl::checked_array_value(mux_lookup_659, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[134], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[138], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[144], 1);
        csl::step_bit_combine(m_w[13], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[13], m_w[13], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[13], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[0], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[0], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREOUT3] = m_w[TMP_W_0];
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::step_not_signed(m_n[153], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[11], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[25], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[153], 1);
        csl::step_and(m_n[154], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[154], m_n[154], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[154], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[154], 1);
        csl::step_not_signed(m_n[155], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[110], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[76], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[153], 1);
        csl::step_and(m_n[156], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[156], m_n[156], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[156], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[156], 1);
        csl::step_not_signed(m_n[157], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[4], 1);
        csl::step_not_signed(m_n[5], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
    }

    void execute_segment_3_fragment_8()
    {
        csl::mask_lower(m_n[TMP_N_1], m_n[107], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[5], 1);
        csl::step_xor(m_n[158], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[158], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::step_not_signed(m_n[120], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[15], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[29], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[120], 1);
        csl::step_and(m_n[121], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[121], m_n[121], m_n[TMP_N_3]);
        csl::step_logical_finalize(m_n[121], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[121], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[114], 1);
        csl::step_or(m_n[122], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_logical_finalize(m_n[122], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[122], 1);
        csl::step_not_signed(m_n[159], m_n[TMP_N_1], 1);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[159], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[158], 1);
        csl::mask_lower(m_n[TMP_N_3], m_n[157], 1);
        csl::mask_lower(m_n[TMP_N_4], m_n[155], 1);
        csl::step_and(m_n[160], m_n[TMP_N_1], m_n[TMP_N_2]);
        csl::step_and(m_n[160], m_n[160], m_n[TMP_N_3]);
        csl::step_and(m_n[160], m_n[160], m_n[TMP_N_4]);
        csl::step_logical_finalize(m_n[160], 1, 1, false, true);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[109], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[106], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_722[2] = { 243, 244 };
        csl::set(m_n[126], m_n[csl::checked_array_value(mux_lookup_722, m_n[TMP_N_4])]);
        csl::mask_lower(m_n[TMP_N_0], m_n[115], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_726[] = {
            0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 1ll, 1ll, 1ll, 0ll, 0ll, 0ll, 0ll, 0ll, 1ll, 1ll, 1ll, 1ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_726, 64, 0, m_n[117], m_n[TMP_N_0]);
        csl::mask_lower(m_n[TMP_N_0], m_n[111], 6);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_729[] = {
            0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 1ll, 
            0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 1ll, 0ll, 0ll, 0ll, 1ll, 1ll, 0ll, 0ll, 1ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 
            0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_729, 64, 0, m_n[113], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[113], 1);
        csl::step_reduce(m_n[TMP_N_1], m_n[117], 1);
        csl::step_reduce(m_n[TMP_N_2], m_n[122], 1);
        csl::step_bit_combine(m_n[127], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 1, 2);
        csl::step_bit_combine(m_n[127], m_n[127], m_n[TMP_N_2], 3, 2, 2, 0);
        csl::mask_lower(m_n[TMP_N_0], m_n[127], 3);
        csl::step_reduce(m_n[TMP_N_1], m_n[1], 1);
        static constexpr int64_t lut_init_data_736[] = {
            1ll, 0ll, 2ll, 0ll, 3ll, 0ll, 0ll, 0ll
        };
        csl::step_lookup(lut_init_data_736, 8, 0, m_n[129], m_n[TMP_N_0]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[129], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[151], 11);
        csl::mask_lower(m_n[TMP_N_3], m_n[126], 11);
        csl::mask_lower(m_n[TMP_N_4], m_n[150], 11);
        csl::mask_lower(m_n[TMP_N_5], m_n[149], 11);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_744[4] = { 243, 244, 245, 246 };
        csl::set(m_n[152], m_n[csl::checked_array_value(mux_lookup_744, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[40], 1);
        csl::mask_lower(m_n[TMP_N_2], m_n[108], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[105], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[TMP_N_1], 1);
        static constexpr size_t mux_lookup_752[2] = { 243, 244 };
        csl::set(m_n[125], m_n[csl::checked_array_value(mux_lookup_752, m_n[TMP_N_4])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[1], 1);
        csl::mask_lower(m_n[TMP_N_1], m_n[129], 2);
        csl::mask_lower(m_n[TMP_N_2], m_n[147], 52);
        csl::mask_lower(m_n[TMP_N_3], m_n[125], 52);
        csl::mask_lower(m_n[TMP_N_4], m_n[146], 52);
        csl::mask_lower(m_n[TMP_N_5], m_n[145], 52);
        csl::mask_lower(m_n[TMP_N_6], m_n[TMP_N_1], 2);
        static constexpr size_t mux_lookup_761[4] = { 243, 244, 245, 246 };
        csl::set(m_n[148], m_n[csl::checked_array_value(mux_lookup_761, m_n[TMP_N_6])]);
        csl::step_reduce(m_n[TMP_N_0], m_n[148], 52);
        csl::step_reduce(m_n[TMP_N_1], m_n[152], 11);
        csl::step_reduce(m_n[TMP_N_2], m_n[160], 1);
        csl::step_bit_combine(m_w[14], m_n[TMP_N_0], m_n[TMP_N_1], 3, 1, 52, 63, m_temp_alloc);
        csl::step_bit_combine(m_w[14], m_w[14], m_n[TMP_N_2], 3, 2, 63, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[14], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[1], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[1], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREAUX2] = m_w[TMP_W_0];
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
        execute_segment_3_fragment_7();
        execute_segment_3_fragment_8();
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
        const bool all_io_ready = (m_io_cycle[0] > m_update_cycle) && (m_io_cycle[1] > m_update_cycle) && (m_io_cycle[2] > m_update_cycle) && (m_io_cycle[3] > m_update_cycle);
        if (all_io_ready && (m_segment_cycle[0] > m_update_cycle) && (m_segment_cycle[1] > m_update_cycle) && (m_segment_cycle[2] > m_update_cycle) && (m_segment_cycle[3] > m_update_cycle))
        {
            execute_segment_update();
            ++m_update_cycle;
        }
    }

    static constexpr size_t PORT_IN_00 = 2;
    static constexpr size_t PORT_IN_11 = 3;
    static constexpr size_t PORT_OUT_PRIMWIREOUT3 = 18;
    static constexpr size_t PORT_OUT_PRIMWIREAUX2 = 19;
    static constexpr size_t TMP_N_0 = 241;
    static constexpr size_t TMP_N_1 = 242;
    static constexpr size_t TMP_N_2 = 243;
    static constexpr size_t TMP_N_3 = 244;
    static constexpr size_t TMP_N_4 = 245;
    static constexpr size_t TMP_N_5 = 246;
    static constexpr size_t TMP_N_6 = 247;
    static constexpr size_t TMP_W_0 = 20;
    static constexpr size_t TMP_W_1 = 21;

    int64_t m_io_cycle[4];
    int64_t m_segment_cycle[4];
    int64_t m_update_cycle;

    csl::mp_temp_allocator m_temp_alloc;
    int64_t m_n[248];
    csl::mp_int m_w[22];
};

#endif // SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_ADDSUBFUSEDBLOCK_TYPESFLOATIEEE_52_11_4_CORRECTROUNDING_38560000X0AO30CD06CJ6OK0DPZC_H_