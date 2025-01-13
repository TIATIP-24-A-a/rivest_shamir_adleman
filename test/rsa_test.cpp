#include "../src/prime_utils.h"
#include "../src/rsa.h"
#include "../src/big_number.h"
#include <cassert>
#include <iostream>
#include <exception>

void TestRSAKeyGeneration() {
    try {
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(2048);

        // Verify key sizes
        assert(key_pair.public_key.n.num_bits() == 2048);

        // Verify e is typically 65537
        assert(key_pair.public_key.e.get_word() == 65537);

        // Verify n is the same in both keys
        assert(BN_cmp(key_pair.public_key.n.get(), key_pair.private_key.n.get()) == 0);

        std::cout << "TestRSAKeyGeneration passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAKeyGeneration failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAEncryptDecrypt() {
    try {
        // Generate a key pair
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(2048);

        // Create test message
        BN_ptr message;
        message.set_word(42);

        // Encrypt
        BN_ptr ciphertext = RSA_APP::encrypt(message, key_pair.public_key);

        // Decrypt
        BN_ptr decrypted = RSA_APP::decrypt(ciphertext, key_pair.private_key);

        // Verify
        assert(BN_cmp(message.get(), decrypted.get()) == 0);

        std::cout << "TestRSAEncryptDecrypt passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAEncryptDecrypt failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAStringConversion() {
    try {
        std::string original = "Hello, RSA!";

        // Convert string to number
        BN_ptr number = RSA_APP::string_to_number(original);

        // Convert back to string
        std::string result = RSA_APP::number_to_string(number);

        assert(original == result);

        std::cout << "TestRSAStringConversion passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAStringConversion failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAFullProcess() {
    try {
        // Generate keys
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(2048);

        // Original message
        std::string original = "Secret message";

        // Convert to number
        BN_ptr message = RSA_APP::string_to_number(original);

        // Encrypt
        BN_ptr ciphertext = RSA_APP::encrypt(message, key_pair.public_key);

        // Decrypt
        BN_ptr decrypted = RSA_APP::decrypt(ciphertext, key_pair.private_key);

        // Convert back to string
        std::string result = RSA_APP::number_to_string(decrypted);

        assert(original == result);

        std::cout << "TestRSAFullProcess passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAFullProcess failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestRSAEncryptDecrypt();
    TestRSAFullProcess();
    TestRSAKeyGeneration();
    TestRSAStringConversion();
    return 0;
}
