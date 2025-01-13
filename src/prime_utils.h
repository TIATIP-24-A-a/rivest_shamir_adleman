#ifndef PRIME_UTILS_H_
#define PRIME_UTILS_H_

#include <big_number.h>
#include <openssl/bn.h>

namespace PrimeUtils {
    /* Checks whether a BigNumber is a prime number.
     *
     * Determines if the given BigNumber is a prime using trial division up to the square root of the number.
     *
     * Args:
     *   number: The BigNumber to check for primality.
     * Returns:
     *   True if the BigNumber is a prime number, false otherwise.
     */
    bool IsPrime(const BigNumber& number);    BigNumber GeneratePrime(const BigNumber& min, const BigNumber& max);
    BigNumber GeneratePrimeWithBitLength(int bitLength);
    BigNumber GenerateRSASafePrime(int bitLength);
    bool IsRSASafe(const BigNumber& prime);
    bool IsPrimeOpenSSL(const BIGNUM* n);
}

#endif  // PRIME_UTILS_H_
