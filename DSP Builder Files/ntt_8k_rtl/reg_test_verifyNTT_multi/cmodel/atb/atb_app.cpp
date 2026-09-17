/**
 * High Level Design Compiler for Altera(R) FPGAs Version 2026.3 (Release Build #847757300c)
 * Software model created on 2026-08-26 10:03:58
 * Generation mode: Bit Accurate
 */
#undef WRITE_STM_FILES
#define WRITE_STM_FILES
#include "reg_test_verifyNTT_multi_DUT_atb.h"
#include <iostream>

static bool s_has_error = false;

namespace csl
{
[[noreturn]] void fatal(const char* msg) { std::cout << "Fatal error: " << msg << "\n"; exit(1); }
void error(const char* msg)   { s_has_error = true; std::cout << "Error: " << msg << "\n"; }
void info(const char* msg)    { std::cout << "Info: " << msg << "\n"; }
}

/**
 * Top-level test harness
 * 
 * Runs the automated test bench(es) and reports results.
 * 
 * Usage:
 *   ./atb_app                    - Run device-level ATB
 *   ./atb_app runIndividualAtbs  - Run individual subsystem ATBs (if any exist)
 * 
 * Exit codes:
 *   0 - All tests passed
 *   1 - Error occurred during execution
 *   2 - Test comparison failed
 */
int main(int argc, char** argv)
{
    bool success = true;
    const bool run_individual_atbs = (argc > 1) ? (strcmp("runIndividualAtbs", argv[1]) == 0) : false;
    if (!run_individual_atbs)
    {
        reg_test_verifyNTT_multi_DUTATB device_atb;
        success = device_atb.run();
        success = success && device_atb.compare();
    }

    if (run_individual_atbs)
    {
    }

    if (!s_has_error && success)
    {
        if (run_individual_atbs)
        {
            csl::info("[reg_test_verifyNTT_multi_DUT] Success! All individual software model ATB results matched the Simulink simulation results.");
        }
        else
        {
            csl::info("[reg_test_verifyNTT_multi_DUT] Success! Device-level software model ATB results matched the Simulink simulation results.");
        }
    }
    else if (s_has_error)
    {
        csl::error("[reg_test_verifyNTT_multi_DUT] An error occurred before the software model ATB could complete.");
    }
    else
    {
        if (run_individual_atbs)
        {
            csl::error("[reg_test_verifyNTT_multi_DUT] Failed! At least one individual ATB result did not match the Simulink simulation results.");
        }
        else
        {
            csl::error("[reg_test_verifyNTT_multi_DUT] Failed! Device-level software model ATB results did not match the Simulink simulation results.");
        }
        csl::info("NOTE: Mismatches may be expected if the software model simulation mode does not match the DSPBA mode.");
    }

    return success ? 0 : (s_has_error ? 1 : 2);
}
