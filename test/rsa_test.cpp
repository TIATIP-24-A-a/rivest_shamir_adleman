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

/* Tests whether the RSA key pair is generated correctly. */
void TestGenerateKeyPair() {
    try {
        RSA::KeyPair key_pair = RSA::GenerateKeyPair(50, 100); /* Small range for testing. */
        assert(key_pair.public_key.n > 0);                    /* n must be positive. */
        std::cout << "TestGenerateKeyPair passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestGenerateKeyPair failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestGenerateKeyPair failed with an unknown exception!" << std::endl;
    }
}

/* Tests encryption and decryption using RSA keys.
 *
 * Ensures that a message encrypted using the public key can be
 * successfully decrypted back to the original message using the private key.
 */
void TestEncryptDecrypt() {
    try {
        // Generate RSA key pair
        RSA::KeyPair key_pair = RSA::GenerateKeyPair(50, 100);

        // Define the message as a BigNumber
        BigNumber message("42");  // Message to encrypt and decrypt

        // Encrypt the message using the public key
        BigNumber encrypted = RSA::Encrypt(message, key_pair.public_key);

        // Decrypt the encrypted message using the private key
        BigNumber decrypted = RSA::Decrypt(encrypted, key_pair.private_key);

        // Verify that the decrypted message matches the original message
        assert(decrypted.ToString() == message.ToString());

        std::cout << "TestEncryptDecrypt passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestEncryptDecrypt failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestEncryptDecrypt failed with an unknown exception!" << std::endl;
    }
}

/* Tests the StringToBigNumber function. */
void TestStringToBigNumber() {
    try {
        std::string message = "fortnite";
        BigNumber result = RSA::StringToBigNumber(message);
        std::string expected = "102111114116110105116101";
        assert(result.ToString() == expected);
        std::cout << "TestStringToBigNumber passed!" << std::endl;
    } catch (...) {
        std::cerr << "TestStringToBigNumber failed!" << std::endl;
    }
}

/* Tests the BigNumberToString function. */
void TestBigNumberToString() {
    try {
        BigNumber input("102111114116110105116101");
        std::string result = RSA::BigNumberToString(input);
        std::string expected = "fortnite";
        assert(result == expected);
        std::cout << "TestBigNumberToString passed!" << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberToString failed!" << std::endl;
    }
}

int main() {
    TestIsPrime();
    TestGeneratePrime();
    TestGenerateKeyPair();
    TestEncryptDecrypt();
    TestStringToBigNumber();
    TestBigNumberToString();
    return 0;
}
