#ifndef PRIME_UTILS_H_
#define PRIME_UTILS_H_

#include <big_number.h>
#include <random>

namespace PrimeUtils {
    bool IsPrime(const BigNumber& number);
    BigNumber GeneratePrime(const BigNumber& min, const BigNumber& max);
    BigNumber GeneratePrimeWithBitLength(int bitLength);
    BigNumber GenerateRSASafePrime(int bitLength);
    bool IsRSASafe(const BigNumber& prime);
}

#endif  // PRIME_UTILS_H_
