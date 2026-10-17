#pragma once

#include <array>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "fpt2026_benchmark/benchmark_config.hpp"

namespace seal {
class Ciphertext;
class CKKSEncoder;
class Decryptor;
class EncryptionParameters;
class SEALContext;
class SecretKey;
} // namespace seal

namespace fpt2026 {

std::filesystem::path require_key_file(
    const std::filesystem::path& path);

seal::EncryptionParameters make_ckks_parameters();

class SealOracle {
public:
    explicit SealOracle(const std::filesystem::path& serialized_secret_key_path);
    ~SealOracle();

    SealOracle(const SealOracle&) = delete;
    SealOracle& operator=(const SealOracle&) = delete;

    std::vector<std::complex<double>> decrypt_decode(
        const seal::Ciphertext& ciphertext) const;

    // Compares the adapter's packed 2-bit coefficient-domain key against the
    // serialized SEAL key after an independent inverse NTT.
    bool verify_compact_secret_key(
        const std::filesystem::path& compact_secret_key_path) const;

    const seal::SEALContext& context() const noexcept;

private:
    std::unique_ptr<seal::EncryptionParameters> parameters_;
    std::unique_ptr<seal::SEALContext> context_;
    std::unique_ptr<seal::SecretKey> secret_key_;
    std::unique_ptr<seal::CKKSEncoder> encoder_;
    std::unique_ptr<seal::Decryptor> decryptor_;
};

} // namespace fpt2026
