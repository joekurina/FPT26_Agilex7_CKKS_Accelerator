#include "fpt2026_benchmark/seal_oracle.hpp"

#include <array>
#include <fstream>
#include <stdexcept>

#include "seal/seal.h"
#include "seal/util/iterator.h"
#include "seal/util/ntt.h"

namespace fpt2026 {

std::filesystem::path require_key_file(
    const std::filesystem::path& path)
{
    if (!path.is_absolute()) {
        throw std::invalid_argument("path must be absolute: " + path.string());
    }
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("path does not exist: " + path.string());
    }
    if (!std::filesystem::is_regular_file(path)) {
        throw std::invalid_argument("path is not a regular file: " + path.string());
    }
    return std::filesystem::canonical(path);
}

seal::EncryptionParameters make_ckks_parameters()
{
    seal::EncryptionParameters parameters(seal::scheme_type::ckks);
    parameters.set_poly_modulus_degree(kPolyModulusDegree);

    std::vector<seal::Modulus> moduli;
    moduli.reserve(kDataModulusCount + 1);
    for (const std::uint32_t modulus : kDataModuli) {
        moduli.emplace_back(static_cast<std::uint64_t>(modulus));
    }
    const auto special = seal::CoeffModulus::Create(kPolyModulusDegree, {38});
    moduli.push_back(special.front());
    parameters.set_coeff_modulus(moduli);

    return parameters;
}

SealOracle::SealOracle(
    const std::filesystem::path& serialized_secret_key_path)
{
    const auto key_path = require_key_file(serialized_secret_key_path);
    parameters_ = std::make_unique<seal::EncryptionParameters>(make_ckks_parameters());

    context_ = std::make_unique<seal::SEALContext>(*parameters_);
    if (!context_->parameters_set()) {
        throw std::runtime_error("Microsoft SEAL rejected the FPT 2026 parameter context");
    }

    secret_key_ = std::make_unique<seal::SecretKey>();
    std::ifstream key_stream(key_path, std::ios::binary);
    if (!key_stream) {
        throw std::runtime_error("cannot open serialized benchmark secret key: " + key_path.string());
    }
    secret_key_->load(*context_, key_stream);

    encoder_ = std::make_unique<seal::CKKSEncoder>(*context_);
    decryptor_ = std::make_unique<seal::Decryptor>(*context_, *secret_key_);
}

SealOracle::~SealOracle() = default;

std::vector<std::complex<double>> SealOracle::decrypt_decode(
    const seal::Ciphertext& ciphertext) const
{
    seal::Plaintext plaintext;
    decryptor_->decrypt(ciphertext, plaintext);
    std::vector<std::complex<double>> decoded;
    encoder_->decode(plaintext, decoded);
    return decoded;
}

bool SealOracle::verify_compact_secret_key(
    const std::filesystem::path& compact_secret_key_path) const
{
    const auto path = require_key_file(compact_secret_key_path);
    constexpr std::size_t packed_size = kPolyModulusDegree / 4;
    std::array<std::uint8_t, packed_size> packed{};
    std::ifstream input(path, std::ios::binary);
    input.read(reinterpret_cast<char*>(packed.data()),
               static_cast<std::streamsize>(packed.size()));
    if (input.gcount() != static_cast<std::streamsize>(packed.size()) ||
        input.peek() != std::char_traits<char>::eof()) {
        return false;
    }

    seal::Plaintext coefficients = secret_key_->data();
    const auto key_data = context_->key_context_data();
    if (!key_data || !coefficients.is_ntt_form()) {
        return false;
    }
    const auto& moduli = key_data->parms().coeff_modulus();
    seal::util::RNSIter coefficients_iter(coefficients.data(), kPolyModulusDegree);
    seal::util::inverse_ntt_negacyclic_harvey(
        coefficients_iter, moduli.size(), key_data->small_ntt_tables());

    for (std::size_t i = 0; i < kPolyModulusDegree; ++i) {
        const std::uint8_t symbol = static_cast<std::uint8_t>(
            (packed[i / 4] >> (6u - 2u * static_cast<unsigned>(i % 4))) & 0x3u);
        if (symbol == 3u) {
            return false;
        }
        for (std::size_t p = 0; p < moduli.size(); ++p) {
            const std::uint64_t expected = symbol == 0u
                ? moduli[p].value() - 1u
                : static_cast<std::uint64_t>(symbol - 1u);
            if (coefficients[p * kPolyModulusDegree + i] != expected) {
                return false;
            }
        }
    }
    return true;
}

const seal::SEALContext& SealOracle::context() const noexcept
{
    return *context_;
}

} // namespace fpt2026
