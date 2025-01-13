#include "../src/prime_utils.h"
#include "../src/rsa.h"
#include "../src/big_number.h"
#include <cassert>
#include <iostream>
#include <exception>
#include <openssl/bn.h>

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

void TestMillerRabinCarmichaelNumber() {
    try {
        assert(PrimeUtils::IsPrime(BigNumber("561")) == false);  // Carmichael number
        std::cout << "TestMillerRabinCarmichaelNumber passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestMillerRabinCarmichaelNumber failed with exception: " << e.what() << std::endl;
    }
}

void TestGeneratePrimeInRange() {
    try {
        BigNumber min("1000");
        BigNumber max("2000");
        BigNumber prime = PrimeUtils::GeneratePrime(min, max);
        assert(prime >= min && prime <= max);
        assert(PrimeUtils::IsPrime(prime) == true);
        std::cout << "TestGeneratePrimeInRange passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestGeneratePrimeInRange failed with exception: " << e.what() << std::endl;
    }
}

void TestGeneratePrimeWithBitLength() {
    try {
        int bitLength = 512;
        BigNumber min = BigNumber("2").ModularExponentiation(BigNumber(std::to_string(bitLength - 1)), BigNumber("1"));
        BigNumber max = BigNumber("2").ModularExponentiation(BigNumber(std::to_string(bitLength)), BigNumber("1")) - BigNumber("1");

        BigNumber prime = PrimeUtils::GeneratePrimeWithBitLength(bitLength);
        assert(prime >= min);
        assert(prime <= max);
        assert(PrimeUtils::IsPrime(prime) == true);
        std::cout << "TestGeneratePrimeWithBitLength passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestGeneratePrimeWithBitLength failed with exception: " << e.what() << std::endl;
    }
}

void TestGenerateRSASafePrime() {
    try {
        BigNumber prime = PrimeUtils::GenerateRSASafePrime(512);  // Small bit length for testing
        assert(PrimeUtils::IsPrime(prime) == true);
        // Test p-1 has large prime factor
        assert(PrimeUtils::IsPrime((prime - BigNumber("1")) / BigNumber("2")) == true);
        std::cout << "TestGenerateRSASafePrime passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestGenerateRSASafePrime failed with exception: " << e.what() << std::endl;
    }
}

// In the same test file
void TestOpenSSLPrimeBasic() {
    try {
        BIGNUM* num = BN_new();
        BN_set_word(num, 17);  // Test with same number as TestMillerRabinKnownPrimes
        bool is_prime = PrimeUtils::IsPrimeOpenSSL(num);
        assert(is_prime == true);
        BN_free(num);

        // Test a known composite
        num = BN_new();
        BN_set_word(num, 24);  // Test with same number as TestMillerRabinKnownComposites
        is_prime = PrimeUtils::IsPrimeOpenSSL(num);
        assert(is_prime == false);
        BN_free(num);

        std::cout << "TestOpenSSLPrimeBasic passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestOpenSSLPrimeBasic failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestMillerRabinKnownPrimes();
    TestMillerRabinKnownComposites();
    TestMillerRabinCarmichaelNumber();
    TestGeneratePrimeInRange();
    TestGenerateRSASafePrime();
    TestOpenSSLPrimeBasic();
    return 0;
}
