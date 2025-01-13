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
    bool IsPrime(const BigNumber& number);

    /* Generates a random prime BigNumber within a specified range.
     *
     * Produces a random prime BigNumber that lies within the inclusive range [min, max].
     *
     * Args:
     *   min: The minimum BigNumber value of the range (inclusive).
     *   max: The maximum BigNumber value of the range (inclusive).
     * Returns:
     *   A random prime BigNumber in the range [min, max].
     * Throws:
     *   std::runtime_error if no prime can be found within the range.
     */
    BigNumber GeneratePrime(const BigNumber& min, const BigNumber& max);

    /* Generates a random prime BigNumber with a specified bit length.
     *
     * Produces a random prime BigNumber with a length equal to the specified number of bits.
     *
     * Args:
     *   bitLength: The desired bit length of the generated prime.
     * Returns:
     *   A random prime BigNumber with the specified bit length.
     * Throws:
     *   std::runtime_error if a suitable prime cannot be generated.
     */
    BigNumber GeneratePrimeWithBitLength(int bitLength);

    /* Generates a random RSA-safe prime with a specified bit length.
     *
     * Produces a random prime number suitable for RSA encryption, ensuring the generated number meets
     * the criteria for an RSA-safe prime (p is prime, and (p - 1) / 2 is also prime).
     *
     * Args:
     *   bitLength: The desired bit length of the generated RSA-safe prime.
     * Returns:
     *   A random RSA-safe prime BigNumber with the specified bit length.
     * Throws:
     *   std::runtime_error if a suitable RSA-safe prime cannot be generated.
     */
    BigNumber GenerateRSASafePrime(int bitLength);

    /* Checks whether a BigNumber is an RSA-safe prime.
     *
     * Verifies that the given BigNumber meets the criteria for an RSA-safe prime.
     * An RSA-safe prime p satisfies:
     *   - p is prime
     *   - (p - 1) / 2 is also prime
     *
     * Args:
     *   prime: The BigNumber to check for RSA-safety.
     * Returns:
     *   True if the BigNumber is RSA-safe, false otherwise.
     */
    bool IsRSASafe(const BigNumber& prime);

    /* Checks whether a BIGNUM is prime using OpenSSL.
     *
     * Uses OpenSSL's cryptographic library to determine if the given BIGNUM is a prime number.
     *
     * Args:
     *   n: A pointer to the BIGNUM to check for primality.
     * Returns:
     *   True if the BIGNUM is prime, false otherwise.
     */
    bool IsPrimeOpenSSL(const BIGNUM* n);
}

#endif  // PRIME_UTILS_H_
