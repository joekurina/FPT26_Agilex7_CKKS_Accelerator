#include "fpt2026_benchmark/seal_oracle.hpp"
#include "seal/seal.h"
#include "seal/util/iterator.h"
#include "seal/util/ntt.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "Usage: ckks_generate_keys NEW_DIRECTORY\n"
                  << "Create a matching SEAL and compact benchmark secret key.\n";
        return 0;
    }
    if (argc != 2) {
        std::cerr << "Usage: ckks_generate_keys NEW_DIRECTORY\n";
        return 2;
    }
    try {
        // Keep newly generated key material private and refuse to overwrite keys.
        umask(0077);
        const auto directory = std::filesystem::absolute(argv[1]);
        if (!std::filesystem::create_directory(directory)) {
            throw std::runtime_error("Key directory already exists");
        }
        const auto seal_path = directory / "secret-key.seal";
        const auto compact_path = directory / "secret-key.compact";
        const seal::SEALContext context(fpt2026::make_ckks_parameters());
        if (!context.parameters_set()) {
            throw std::runtime_error("Invalid benchmark encryption parameters");
        }
        const seal::KeyGenerator generator(context);
        const seal::SecretKey key = generator.secret_key();

        std::ofstream seal_stream(seal_path, std::ios::binary);
        if (!seal_stream) throw std::runtime_error("Cannot create key");
        key.save(seal_stream, seal::compr_mode_type::none);
        seal_stream.close();
        if (!seal_stream) throw std::runtime_error("Cannot save key");

        // Convert all key-context limbs back to the same ternary coefficient key.
        seal::Plaintext coefficients = key.data();
        const auto key_context = context.key_context_data();
        const auto& moduli = key_context->parms().coeff_modulus();
        seal::util::RNSIter limbs(coefficients.data(), fpt2026::kPolyModulusDegree);
        seal::util::inverse_ntt_negacyclic_harvey(
            limbs, moduli.size(), key_context->small_ntt_tables());
        std::array<std::uint8_t, fpt2026::kPolyModulusDegree / 4> packed{};
        for (std::size_t i = 0; i < fpt2026::kPolyModulusDegree; ++i) {
            const auto value = coefficients[i];
            unsigned symbol;
            if (value == moduli[0].value() - 1) symbol = 0;
            else if (value == 0) symbol = 1;
            else if (value == 1) symbol = 2;
            else throw std::runtime_error("Secret-key coefficient is not ternary");
            for (std::size_t p = 0; p < moduli.size(); ++p) {
                const auto expected = symbol == 0 ? moduli[p].value() - 1 : symbol - 1;
                if (coefficients[p * fpt2026::kPolyModulusDegree + i] != expected) {
                    throw std::runtime_error("Secret-key limbs disagree");
                }
            }
            packed[i / 4] |= static_cast<std::uint8_t>(symbol << (6 - 2 * (i % 4)));
        }
        std::ofstream compact(compact_path, std::ios::binary);
        if (!compact) throw std::runtime_error("Cannot create compact key");
        compact.write(reinterpret_cast<const char*>(packed.data()), packed.size());
        compact.close();
        if (!compact) throw std::runtime_error("Cannot save compact key");

        const fpt2026::SealOracle oracle(seal_path);
        if (!oracle.verify_compact_secret_key(compact_path)) {
            throw std::runtime_error("Generated key-pair verification failed");
        }
        std::cout << "KEY_PAIR_VERIFIED\nseal_key=" << seal_path.string()
                  << "\ncompact_key=" << compact_path.string() << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Key generation failed: " << error.what() << '\n';
        return 1;
    }
}
