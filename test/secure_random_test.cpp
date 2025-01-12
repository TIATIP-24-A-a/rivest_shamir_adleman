#include "../src/secure_random.h"
#include <iostream>
#include <vector>
#include <cassert>

void TestSecureRandomGetRange() {
    try {
        SecureRandom random;
        uint64_t min = 1000;
        uint64_t max = 2000;

        uint64_t value = random.GetRange(min, max);
        assert(value >= min && value <= max && "Generated number should be within range");

        std::cout << "TestSecureRandomGetRange passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestSecureRandomGetRange failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestSecureRandomGetRange();
    return 0;
}