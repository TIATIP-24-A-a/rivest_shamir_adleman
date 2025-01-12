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

void TestMillerRabinKnownComposites() {
    try {
        assert(PrimeUtils::IsPrime(BigNumber("24")) == false);
        assert(PrimeUtils::IsPrime(BigNumber("100")) == false);
        std::cout << "TestMillerRabinKnownComposites passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestMillerRabinKnownComposites failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestMillerRabinKnownPrimes();
    return 0;
}
