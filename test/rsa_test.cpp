#include "../src/rsa.h"
#include <cassert>
#include <iostream>
#include <exception>
#include <sstream>

void TestRSAKeyGeneration() {
    try {
        rsa_app::KeyPair key_pair = rsa_app::GenerateKeyPair(2048);

        // Verify key sizes
        assert(key_pair.public_key.n.NumBits() == 2048);

        // Verify e is typically 65537
        assert(key_pair.public_key.e.GetWord() == 65537);

        // Verify n is the same in both keys
        assert(BN_cmp(key_pair.public_key.n.Get(), key_pair.private_key.n.Get()) == 0);

        std::cout << "TestRSAKeyGeneration passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAKeyGeneration failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAEncryptDecrypt() {
    try {
        // Generate a key pair
        rsa_app::KeyPair key_pair = rsa_app::GenerateKeyPair(2048);

        // Create test message
        BigNumber message;
        message.SetWord(42);

        // Encrypt
        BigNumber ciphertext = rsa_app::Encrypt(message, key_pair.public_key);

        // Decrypt
        BigNumber decrypted = rsa_app::Decrypt(ciphertext, key_pair.private_key);

        // Verify
        assert(BN_cmp(message.Get(), decrypted.Get()) == 0);

        std::cout << "TestRSAEncryptDecrypt passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAEncryptDecrypt failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAStringConversion() {
    try {
        std::string original = "Hello, RSA!";

        // Convert string to number
        BigNumber number = rsa_app::StringToNumber(original);

        // Convert back to string
        std::string result = rsa_app::NumberToString(number);

        assert(original == result);

        std::cout << "TestRSAStringConversion passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAStringConversion failed with exception: " << e.what() << std::endl;
    }
}

void TestRSAFullProcess() {
    try {
        // Generate keys
        rsa_app::KeyPair key_pair = rsa_app::GenerateKeyPair(2048);

        // Original message
        std::string original = "Secret message";

        // Convert to number
        BigNumber message = rsa_app::StringToNumber(original);

        // Encrypt
        BigNumber ciphertext = rsa_app::Encrypt(message, key_pair.public_key);

        // Decrypt
        BigNumber decrypted = rsa_app::Decrypt(ciphertext, key_pair.private_key);

        // Convert back to string
        std::string result = rsa_app::NumberToString(decrypted);

        assert(original == result);

        std::cout << "TestRSAFullProcess passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestRSAFullProcess failed with exception: " << e.what() << std::endl;
    }
}

void TestFormatBigNumber() {
    try {
        BigNumber num;
        num.SetWord(12345);  // Example number
        std::string formatted = rsa_app::FormatBigNumber(num);

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
        std::string encoded = rsa_app::Base64Encode(input);
        assert(encoded == "SGVsbG8sIFJTQSE=");  // Expected Base64 encoding
        std::cout << "TestBase64Encode passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBase64Encode failed with exception: " << e.what() << std::endl;
    }
}

void TestPrintRSAKeys() {
    try {
        // Generate a key pair
        rsa_app::KeyPair key_pair = rsa_app::GenerateKeyPair(512);  // Use smaller size for testing

        // Redirect output to a string
        std::ostringstream output;
        std::streambuf* old_cout_buf = std::cout.rdbuf(output.rdbuf());
        PrintRsaKeys(key_pair);
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
