#include "../src/prime_utils.h"
#include "../src/rsa.h"
#include "../src/big_number.h"
#include <cassert>
#include <iostream>
#include <exception>

/* Tests whether the IsPrime function correctly identifies a prime number. */
void TestIsPrime() {
    try {
        assert(PrimeUtils::IsPrime(17) == true); /* 17 is a prime number. */
        std::cout << "TestIsPrime passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestIsPrime failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestIsPrime failed with an unknown exception!" << std::endl;
    }
}

/* Tests whether the GeneratePrime function generates a valid prime number
 * within a specified range.
 */
void TestGeneratePrime() {
    try {
        int prime = PrimeUtils::GeneratePrime(10, 50);
        assert(prime >= 10 && prime <= 50); /* Prime should be within range. */
        std::cout << "TestGeneratePrime passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestGeneratePrime failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestGeneratePrime failed with an unknown exception!" << std::endl;
    }
}

int main() {
    TestIsPrime();
    TestGeneratePrime();
    return 0;
}
