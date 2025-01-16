#include "rsa.h"

#include <stdexcept>
#include <numeric>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>

namespace rsa_app {

KeyPair GenerateKeyPair(int bits) {
  BigNumber e;
  e.SetWord(65537);

  BigNumber p, q;
  p.GeneratePrime(bits / 2);
  do {
    q.GeneratePrime(bits / 2);
  } while (BN_cmp(p.Get(), q.Get()) == 0);

  if (!p.GetBit(bits / 2 - 1) || !q.GetBit(bits / 2 - 1)) {
    throw std::runtime_error("Generated primes do not have the required bit length");
  }

  BigNumber n = p.Mul(q.Get());
  BigNumber p_minus_1 = p.Sub(BN_value_one());
  BigNumber q_minus_1 = q.Sub(BN_value_one());
  BigNumber totient = p_minus_1.Mul(q_minus_1.Get());

  if (e.Gcd(totient.Get()).GetWord() != 1) {
    throw std::runtime_error("Public exponent not coprime with totient");
  }

  BigNumber d = e.ModInverse(totient.Get());

  return KeyPair{
      PublicKey{n.Copy(), std::move(e)},
      PrivateKey{std::move(n), std::move(d)}};
}

BigNumber Encrypt(const BigNumber& message, const PublicKey& public_key) {
  if (BN_cmp(message.Get(), public_key.n.Get()) >= 0) {
    throw std::invalid_argument("Message too large for key size");
  }

  return message.ModExp(public_key.e.Get(), public_key.n.Get());
}

BigNumber Decrypt(const BigNumber& ciphertext, const PrivateKey& private_key) {
  if (BN_cmp(ciphertext.Get(), private_key.n.Get()) >= 0) {
    throw std::invalid_argument("Ciphertext too large for key size");
  }

  return ciphertext.ModExp(private_key.d.Get(), private_key.n.Get());
}

BigNumber StringToNumber(const std::string& message) {
  BigNumber result;
  BigNumber base;
  base.SetWord(256);

  result.SetWord(0);
  for (unsigned char c : message) {
    result = result.Mul(base.Get());
    BigNumber char_value;
    char_value.SetWord(c);
    result = result.Add(char_value.Get());
  }

  return result;
}

std::string NumberToString(const BigNumber& number) {
  std::string result;
  BigNumber remaining = number.Copy();
  BigNumber base;
  base.SetWord(256);
  BigNumber zero;
  zero.SetWord(0);

  while (BN_cmp(remaining.Get(), zero.Get()) > 0) {
    BigNumber quotient, remainder;
    remainder = remaining.Mod(base.Get());
    remaining = remaining.Div(base.Get());

    unsigned long char_value = remainder.GetWord();
    result.insert(result.begin(), static_cast<char>(char_value));
  }

  return result;
}

std::string FormatBigNumber(const BigNumber& number) {
  unsigned char* bin_data = nullptr;
  int bin_length = BN_num_bytes(number.Get());
  bin_data = new unsigned char[bin_length];
  BN_bn2bin(number.Get(), bin_data);

  std::string binary_string(reinterpret_cast<char*>(bin_data), bin_length);
  delete[] bin_data;

  return Base64Encode(binary_string);
}

std::string Base64Encode(const std::string& input) {
  BIO* bio = BIO_new(BIO_s_mem());
  BIO* b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(bio, input.data(), input.size());
  BIO_flush(bio);

  char* encoded_data;
  long len = BIO_get_mem_data(bio, &encoded_data);

  std::string result(encoded_data, len);
  BIO_free_all(bio);
  return result;
}

void PrintRsaKeys(const KeyPair& key_pair) {
  std::cout << "-----BEGIN PUBLIC KEY-----\n";
  std::string public_key =
      FormatBigNumber(key_pair.public_key.n) +
      FormatBigNumber(key_pair.public_key.e);
  std::cout << public_key << "\n-----END PUBLIC KEY-----\n";

  std::cout << "-----BEGIN PRIVATE KEY-----\n";
  std::string private_key =
      FormatBigNumber(key_pair.private_key.n) +
      FormatBigNumber(key_pair.private_key.d);
  std::cout << private_key << "\n-----END PRIVATE KEY-----\n";
}

}  // namespace rsa_app