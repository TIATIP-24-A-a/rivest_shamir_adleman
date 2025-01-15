#include "../src/rsa.h"
#include <cassert>
#include <iostream>
#include <exception>
#include <sstream>

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

void TestFormatBigNumber() {
    try {
        BN_ptr num;
        num.set_word(12345);  // Example number
        std::string formatted = RSA_APP::format_big_number(num);

        // Convert 12345 to Base64 (binary: "0x3039" → Base64: "MDM5")
        assert(formatted == "MDk=");
        std::cout << "TestFormatBigNumber passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestFormatBigNumber failed with exception: " << e.what() << std::endl;
    }
}

void TestBase64Encode() {
    try {
        std::string input = "Hello, RSA!";
        std::string encoded = RSA_APP::base64_encode(input);
        assert(encoded == "SGVsbG8sIFJTQSE=");  // Expected Base64 encoding
        std::cout << "TestBase64Encode passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBase64Encode failed with exception: " << e.what() << std::endl;
    }
}

void TestPrintRSAKeys() {
    try {
        // Generate a key pair
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(512);  // Use smaller size for testing

        // Redirect output to a string
        std::ostringstream output;
        std::streambuf* old_cout_buf = std::cout.rdbuf(output.rdbuf());
        print_rsa_keys(key_pair);
        std::cout.rdbuf(old_cout_buf);  // Restore standard output

        std::string result = output.str();

        // Check the output format
        assert(result.find("-----BEGIN PUBLIC KEY-----") != std::string::npos);
        assert(result.find("-----END PUBLIC KEY-----") != std::string::npos);
        assert(result.find("-----BEGIN PRIVATE KEY-----") != std::string::npos);
        assert(result.find("-----END PRIVATE KEY-----") != std::string::npos);

        std::cout << "TestPrintRSAKeys passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestPrintRSAKeys failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestRSAKeyGeneration();
    TestRSAEncryptDecrypt();
    TestRSAStringConversion();
    TestRSAFullProcess();
    TestBase64Encode();
    TestFormatBigNumber();
    TestPrintRSAKeys();
    return 0;
}
