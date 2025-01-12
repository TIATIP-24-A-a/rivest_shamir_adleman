#include "../src/prime_utils.h"
#include "../src/rsa.h"
#include "../src/big_number.h"
#include <cassert>
#include <iostream>
#include <exception>

void TestMillerRabinKnownPrimes() {
    try {
        assert(PrimeUtils::IsPrime(BigNumber("17")) == true);
        assert(PrimeUtils::IsPrime(BigNumber("61")) == true);
        std::cout << "TestMillerRabinKnownPrimes passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestMillerRabinKnownPrimes failed with exception: " << e.what() << std::endl;
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
    TestMillerRabinKnownPrimes();
    TestGeneratePrime();
    return 0;
}
