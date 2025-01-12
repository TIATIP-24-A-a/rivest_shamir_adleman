// secure_random.h
#pragma once
#include <cstdint>
#include <stdexcept>

class SecureRandom {
public:

    // Get random integer in range [min, max]
    uint64_t GetRange(uint64_t min, uint64_t max);
};