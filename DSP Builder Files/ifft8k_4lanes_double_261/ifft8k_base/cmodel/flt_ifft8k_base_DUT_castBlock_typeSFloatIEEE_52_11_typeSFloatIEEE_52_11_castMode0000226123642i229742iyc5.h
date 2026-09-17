/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#pragma once

#ifndef SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CASTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_CASTMODE0000226123642I229742IYC5_H_
#define SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CASTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_CASTMODE0000226123642I229742IYC5_H_

#include "support/csl.h"
#ifdef WRITE_STM_FILES
#include "support/csl_io.h"
#endif

class flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5
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
    flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5() {};
    flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5(const flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5&) = delete;
    flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5(flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5&&) = delete;
    flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5& operator=(const flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5&) = delete;
    flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5& operator=(flt_ifft8k_base_DUT_castBlock_typeSFloatIEEE_52_11_typeSFloatIEEE_52_11_castMode0000226123642i229742iyc5&&) = delete;

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
        static constexpr int64_t native_type_reset_values[] = { 0ull, 0ull };
        std::memcpy(m_n, native_type_reset_values, 2 * sizeof(int64_t));
        static constexpr uint64_t wide_type_reset_values[] = { 0ull, 0ull, 0ull };
        static constexpr csl::mp_int_info wide_type_reset_infos[] = { { 0, 1, 0 }, { 1, 1, 0 }, { 2, 1, 0 } };
        for (size_t i = 0; i < 3; ++i)
        {
            csl::fill_mpz_data(m_w[i], wide_type_reset_values, wide_type_reset_infos, i);
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
    void execute_segment_0()
    {
    }

    void execute_segment_1_fragment_0()
    {
        csl::step_reduce(m_w[TMP_W_0], m_w[PORT_IN_00], 64, m_temp_alloc);
        csl::step_bit_extract(m_w[0], m_w[TMP_W_0], 64, true, 0, m_temp_alloc);
        csl::step_reduce(m_w[TMP_W_0], m_w[0], 64, m_temp_alloc);
        m_w[PORT_OUT_PRIMWIREOUT1] = m_w[TMP_W_0];
    }

    void execute_segment_1()
    {
        execute_segment_1_fragment_0();
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
    static constexpr size_t PORT_OUT_PRIMWIREOUT1 = 2;
    static constexpr size_t TMP_W_0 = 3;

    int64_t m_io_cycle[2];
    int64_t m_segment_cycle[2];
    int64_t m_update_cycle;

    csl::mp_temp_allocator m_temp_alloc;
    int64_t m_n[2];
    csl::mp_int m_w[4];
};

#endif // SOFTWARE_MODEL_FLT_IFFT8K_BASE_DUT_CASTBLOCK_TYPESFLOATIEEE_52_11_TYPESFLOATIEEE_52_11_CASTMODE0000226123642I229742IYC5_H_