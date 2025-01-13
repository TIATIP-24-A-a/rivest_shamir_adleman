/*
 *
 *
 * FOR EDUCATIONAL PURPOSES ONLY
 *
 *
 */
#include "secure_random.h"
#include <limits>

#if defined(_WIN32)
    #include <windows.h>
    extern "C" BOOLEAN NTAPI SystemFunction036(PVOID RandomBuffer, ULONG RandomBufferLength);
#define RtlGenRandom SystemFunction036
#else
#include <sys/random.h>
#endif

// Add this definition - it was missing
void SecureRandom::GetBytes(uint8_t* buffer, size_t size) {
#if defined(_WIN32)
    if (!RtlGenRandom(buffer, (ULONG)size)) {
        throw std::runtime_error("Failed to generate random bytes");
    }
#else
    size_t pos = 0;
    while (pos < size) {
        ssize_t result = getrandom(buffer + pos, size - pos, 0);
        if (result < 0) {
            throw std::runtime_error("Failed to generate random bytes");
        }
        pos += result;
    }
#endif
}

uint64_t SecureRandom::GetRange(uint64_t min, uint64_t max) {
    if (min > max) {
        throw std::invalid_argument("min must be <= max");
    }

    uint64_t range = max - min + 1;
    uint64_t result;

    GetBytes(reinterpret_cast<uint8_t*>(&result), sizeof(result));
    return min + (result % range);
}

BigNumber SecureRandom::GetBigNumberRange(const BigNumber& min, const BigNumber& max) {
    if (min > max) {
        throw std::invalid_argument("min must be <= max");
    }

    // Calculate number of bytes needed
    BigNumber range = max - min + BigNumber("1");
    size_t bytes_needed = (range.ToString().length() + 2) / 3 + 1;

    std::vector<uint8_t> buffer(bytes_needed);
    BigNumber result;

    do {
        GetBytes(buffer.data(), bytes_needed);

        // Convert bytes to BigNumber
        result = BigNumber("0");
        for (size_t i = 0; i < bytes_needed; i++) {
            result.MultiplyBy10();
            result.MultiplyBy10();
            result.MultiplyBy10();
            result = result + BigNumber(std::to_string(buffer[i]));
        }

        result = result % range;  // Map to our range
        result = result + min;

    } while (result > max);  // Ensure we're within bounds

    return result;
}