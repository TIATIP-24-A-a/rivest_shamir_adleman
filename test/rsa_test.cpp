#include "../src/prime_utils.h"
#include <cassert>
#include <iostream>

/* Tests whether the IsPrime function correctly identifies prime numbers.
 * Ensures the function returns true for primes and false for non-primes.
 */
void TestIsPrime() {
    assert(PrimeUtils::IsPrime(17) == true);  /* 17 is a prime number. */
    assert(PrimeUtils::IsPrime(18) == false); /* 18 is not a prime number. */
    std::cout << "TestIsPrime passed!" << std::endl;
}

/* Tests whether the GeneratePrime function generates valid prime numbers
 * within a specified range. Ensures the generated number is prime and
 * within the range.
 */
void TestGeneratePrime() {
    try {
        int prime = PrimeUtils::GeneratePrime(10, 50);
        assert(prime >= 10 && prime <= 50);          /* Prime should be within range. */
        assert(PrimeUtils::IsPrime(prime) == true); /* Prime should be valid. */
        std::cout << "TestGeneratePrime passed!" << std::endl;
    } catch (...) {
        std::cerr << "TestGeneratePrime failed!" << std::endl;
        assert(false);
    }
}

/* Tests whether the RSA key pair is generated correctly.
 * Ensures that the keys satisfy the RSA requirements.
 */
void TestGenerateKeyPair() {
    RSA::KeyPair key_pair = RSA::GenerateKeyPair(50, 100); /* Small range for testing. */
    assert(key_pair.public_key.n > 0);                     /* n must be positive. */
    assert(key_pair.private_key.d > 0);                   /* d must be positive. */
    assert(key_pair.public_key.e > 0);                    /* e must be positive. */
    assert(key_pair.public_key.e < key_pair.public_key.n); /* e must be less than n. */

    std::cout << "TestGenerateKeyPair passed!" << std::endl;
}

int main() {
    TestIsPrime();
    TestGeneratePrime();
    TestGenerateKeyPair();
    return 0;
}
