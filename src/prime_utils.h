#ifndef PRIME_UTILS_H_
#define PRIME_UTILS_H_

#include <big_number.h>
#include <openssl/bn.h>

namespace PrimeUtils {
    bool IsPrime(const BigNumber& number);
    BigNumber GeneratePrime(const BigNumber& min, const BigNumber& max);
    BigNumber GeneratePrimeWithBitLength(int bitLength);
    BigNumber GenerateRSASafePrime(int bitLength);
    bool IsRSASafe(const BigNumber& prime);
    bool IsPrimeOpenSSL(const BIGNUM* n);
}

#endif  // PRIME_UTILS_H_
