#ifndef PRIME_UTILS_H_
#define PRIME_UTILS_H_

#include <random>

namespace PrimeUtils {

    /* Checks whether a given number is prime.
     * Args:
     *   number: The number to check.
     * Returns:
     *   True if the number is prime, otherwise false.
     */
    bool IsPrime(int number);

    /* Generates a random prime number within the specified range.
     * Args:
     *   min: The minimum value of the range (inclusive).
     *   max: The maximum value of the range (inclusive).
     * Returns:
     *   A random prime number within the range [min, max].
     * Throws:
     *   std::invalid_argument if the range is invalid.
     */
    int GeneratePrime(int min, int max);

}

#endif  // PRIME_UTILS_H_
