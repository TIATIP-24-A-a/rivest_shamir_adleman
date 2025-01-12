// secure_random.h
#pragma once
#include <big_number.h>
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:
    // Get random integer in range [min, max]
    uint64_t GetRange(uint64_t min, uint64_t max);

    // Get random Big Number in range
    BigNumber GetBigNumberRange(const BigNumber& min, const BigNumber& max);
private:
    // Get random bytes into the provided buffer
    void GetBytes(uint8_t* buffer, size_t size);
};