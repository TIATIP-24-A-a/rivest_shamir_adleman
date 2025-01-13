#pragma once
#include <big_number.h>
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:
    /* Generates a random integer within a specified range.
     *
     * Produces a random unsigned 64-bit integer that lies within the inclusive range [min, max].
     *
     * Args:
     *   min: The minimum value of the range (inclusive).
     *   max: The maximum value of the range (inclusive).
     * Returns:
     *   A random unsigned 64-bit integer in the range [min, max].
     */
    uint64_t GetRange(uint64_t min, uint64_t max);

    // Get random Big Number in range
    BigNumber GetBigNumberRange(const BigNumber& min, const BigNumber& max);

    // Get random bytes into the provided buffer
    void GetBytes(uint8_t* buffer, size_t size);
};