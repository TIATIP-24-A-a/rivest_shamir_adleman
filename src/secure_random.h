// secure_random.h
#pragma once
#include <big_number.h>
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:
    uint64_t GetRange(uint64_t min, uint64_t max);

    // Get random bytes into the provided buffer
    void GetBytes(uint8_t* buffer, size_t size);

    // Get random integer in range [min, max]
    BigNumber GetBigNumberRange(const BigNumber& min, const BigNumber& max);
private:

};