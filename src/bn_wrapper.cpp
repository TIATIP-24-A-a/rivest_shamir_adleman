#include "bn_wrapper.h"

#include <stdexcept>
#include <string>

BigNumber::BigNumber() : bn_(BN_new()) {
  if (!bn_) throw std::runtime_error("BN_new failed");
}

BigNumber::BigNumber(BIGNUM* bn_value) : bn_(bn_value) {
  if (!bn_) throw std::runtime_error("Null BIGNUM provided");
}

BigNumber::~BigNumber() {
  if (bn_) BN_free(bn_);
}

BIGNUM* BigNumber::Get() {
  return bn_;
}

const BIGNUM* BigNumber::Get() const {
  return bn_;
}

BigNumber::BigNumber(BigNumber&& other) noexcept : bn_(other.bn_) {
  other.bn_ = nullptr;
}

BigNumber& BigNumber::operator=(BigNumber&& other) noexcept {
  if (this != &other) {
    if (bn_) BN_free(bn_);
    bn_ = other.bn_;
    other.bn_ = nullptr;
  }
  return *this;
}

void BigNumber::SetWord(unsigned long value) {
  CheckError(BN_set_word(bn_, value));
}

unsigned long BigNumber::GetWord() const {
  if (BN_is_negative(bn_)) {
    throw std::runtime_error("Cannot convert negative number to word");
  }
  unsigned long result = BN_get_word(bn_);
  if (result == 0xffffffffL && !BN_is_zero(bn_)) {
    throw std::runtime_error("Number too large for word");
  }
  return result;
}

void BigNumber::SetNegative(int sign) {
  BN_set_negative(bn_, sign);
}

void BigNumber::CheckError(int result) {
  if (result == 0) {
    throw std::runtime_error("OpenSSL BIGNUM operation failed");
  }
}

bool BigNumber::GenerateRandom(int bits) {
  CheckError(BN_rand(bn_, bits, 0, 0));
  return true;
}

BigNumber BigNumber::GenerateInRange(const BIGNUM* min, const BIGNUM* max) {
  BN_CTX* ctx = GetCtx();
  BIGNUM* range_bn = BN_new();
  if (!range_bn) throw std::runtime_error("BN_new failed");
  BigNumber range(range_bn);

  CheckError(BN_sub(range.Get(), max, min));
  CheckError(BN_add_word(range.Get(), 1));

  BigNumber result;
  do {
    CheckError(BN_rand_range(result.Get(), range.Get()));
    CheckError(BN_add(result.Get(), result.Get(), min));
  } while (BN_cmp(result.Get(), max) > 0);

  BN_CTX_free(ctx);
  return result;
}

BN_CTX* BigNumber::GetCtx() {
  BN_CTX* ctx = BN_CTX_new();
  if (!ctx) throw std::runtime_error("Failed to create BN_CTX");
  return ctx;
}

bool BigNumber::IsPrime(int checks) const {
  int is_prime = BN_is_prime_ex(bn_, checks, GetCtx(), nullptr);
  CheckError(is_prime >= 0);
  return is_prime == 1;
}

BigNumber BigNumber::Add(const BIGNUM* rhs) const {
  BigNumber result;
  CheckError(BN_add(result.Get(), bn_, rhs));
  return result;
}

BigNumber BigNumber::Sub(const BIGNUM* rhs) const {
  BigNumber result;
  CheckError(BN_sub(result.Get(), bn_, rhs));
  return result;
}

BigNumber BigNumber::Mul(const BIGNUM* rhs) const {
  BigNumber result;
  CheckError(BN_mul(result.Get(), bn_, rhs, GetCtx()));
  return result;
}

BigNumber BigNumber::Div(const BIGNUM* rhs) const {
  BigNumber result;
  CheckError(BN_div(result.Get(), nullptr, bn_, rhs, GetCtx()));
  return result;
}

BigNumber BigNumber::ModExp(const BIGNUM* exp, const BIGNUM* m) const {
  BigNumber result;
  BN_CTX* ctx = GetCtx();
  CheckError(BN_mod_exp(result.Get(), bn_, exp, m, ctx));
  BN_CTX_free(ctx);
  return result;
}

BigNumber BigNumber::Mod(const BIGNUM* m) const {
  BigNumber result;
  BN_CTX* ctx = GetCtx();
  CheckError(BN_mod(result.Get(), bn_, m, ctx));
  BN_CTX_free(ctx);
  return result;
}

int BigNumber::GetBit(int n) const {
  return BN_is_bit_set(bn_, n);
}

int BigNumber::NumBits() const {
  return BN_num_bits(bn_);
}

bool BigNumber::GeneratePrime(int bits) {
  CheckError(BN_generate_prime_ex(bn_, bits, 0, nullptr, nullptr, nullptr));
  return true;
}

BigNumber BigNumber::Gcd(const BIGNUM* rhs) const {
  BigNumber result;
  BN_CTX* ctx = GetCtx();
  CheckError(BN_gcd(result.Get(), bn_, rhs, ctx));
  BN_CTX_free(ctx);
  return result;
}

BigNumber BigNumber::ModInverse(const BIGNUM* m) const {
  BigNumber result;
  BN_CTX* ctx = GetCtx();
  CheckError(BN_mod_inverse(result.Get(), bn_, m, ctx) != nullptr);
  BN_CTX_free(ctx);
  return result;
}

bool BigNumber::GenerateSafePrime(int bits) {
  CheckError(BN_generate_prime_ex(bn_, bits, 1, nullptr, nullptr, nullptr));
  return true;
}

BigNumber BigNumber::Copy() const {
  if (!bn_) {
    throw std::runtime_error("Source BigNumber is uninitialized (bn_ is null)");
  }
  BigNumber result;
  if (BN_copy(result.Get(), bn_) == nullptr) {
    throw std::runtime_error("BN_copy failed");
  }
  return result;
}

std::string BigNumber::ToString() const {
  if (!bn_) {
    throw std::runtime_error("BIGNUM is uninitialized");
  }
  char* hex_str = BN_bn2hex(bn_);
  if (!hex_str) {
    throw std::runtime_error("Failed to convert BIGNUM to string");
  }
  std::string result(hex_str);
  OPENSSL_free(hex_str);
  return result;
}