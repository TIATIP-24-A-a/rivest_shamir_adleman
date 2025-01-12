// secure_random.h
#pragma once
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:
    // Get random bytes into the provided buffer
    void GetBytes(uint8_t* buffer, size_t size);

    // Get random integer in range [min, max]
    uint64_t GetRange(uint64_t min, uint64_t max);
};