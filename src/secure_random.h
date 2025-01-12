// secure_random.h
#pragma once
#include <big_number.h>
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:
    // Get random bytes into the provided buffer
    void GetBytes(uint8_t* buffer, size_t size);

    // Get random integer in range [min, max]
    BigNumber GetBigNumberRange(const BigNumber& min, const BigNumber& max);
};