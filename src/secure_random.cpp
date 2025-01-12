// src/secure_random.cpp
#include "secure_random.h"
#include <limits>

#if defined(_WIN32)
    #include <windows.h>
    extern "C" BOOLEAN NTAPI SystemFunction036(PVOID RandomBuffer, ULONG RandomBufferLength);
#define RtlGenRandom SystemFunction036
#else
#include <sys/random.h>
#endif


uint64_t SecureRandom::GetRange(uint64_t min, uint64_t max) {
    if (min > max) {
        throw std::invalid_argument("min must be <= max");
    }

    uint64_t range = max - min + 1;
    uint64_t result;

    GetBytes(reinterpret_cast<uint8_t*>(&result), sizeof(result));
    return min + (result % range);
}