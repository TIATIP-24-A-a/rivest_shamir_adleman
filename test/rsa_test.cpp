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
        assert(decrypted.to_string() == message.to_string());

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
        assert(result.to_string() == expected);
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

/* Tests the BigNumber constructor for very large numbers. */
void TestBigNumberConstructor() {
    try {
        std::string large_number = "1234567890123456789012345678901234567890";
        BigNumber num(large_number);
        assert(num.to_string() == large_number);
        std::cout << "TestBigNumberConstructor passed for large number!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberConstructor failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberConstructor failed with an unknown exception!" << std::endl;
    }
}

/* Tests the AppendDigit function for appending single digits to BigNumber. */
void TestBigNumberAppendDigit() {
    try {
        BigNumber num("123");  /* Start with the number 123. */
        num.AppendDigit(4);    /* Append the digit 4. */
        std::string expected = "1234";  /* The result should be 1234. */

        assert(num.to_string() == expected);
        std::cout << "TestBigNumberAppendDigit passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberAppendDigit failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberAppendDigit failed with an unknown exception!" << std::endl;
    }
}

/* Tests the MultiplyBy10 function for shifting digits left by one place. */
void TestBigNumberMultiplyBy10() {
    try {
        BigNumber num("123");  /* Start with the number 123. */
        num.MultiplyBy10();    /* Multiply by 10 (shift digits left). */
        std::string expected = "1230";  /* The result should be 1230. */

        assert(num.to_string() == expected);
        std::cout << "TestBigNumberMultiplyBy10 passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberMultiplyBy10 failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberMultiplyBy10 failed with an unknown exception!" << std::endl;
    }
}

/* Tests the Add function for correctly adding two BigNumbers. */
void TestBigNumberAdd() {
    try {
        BigNumber num1("123");  /* First number. */
        BigNumber num2("456");  /* Second number. */
        BigNumber result = num1.Add(num2);  /* Perform addition. */

        std::string expected = "579";  /* Expected result: 123 + 456 = 579. */

        std::cout << "BigNumber Add Debugging:" << std::endl;
        std::cout << "  Num1: " << num1.to_string() << std::endl;
        std::cout << "  Num2: " << num2.to_string() << std::endl;
        std::cout << "  Result: " << result.to_string() << std::endl;
        std::cout << "  Expected: " << expected << std::endl;

        assert(result.to_string() == expected);  /* Verify the result matches the expected value. */
        std::cout << "TestBigNumberAdd passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberAdd failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberAdd failed with an unknown exception!" << std::endl;
    }
}

/* Tests the Subtract function for correctly subtracting two BigNumbers. */
void TestBigNumberSubtract() {
    try {
        BigNumber num1("579");  /* First number. */
        BigNumber num2("456");  /* Second number. */
        BigNumber result = num1.Subtract(num2);  /* Perform subtraction. */

        std::string expected = "123";  /* Expected result: 579 - 456 = 123. */

        std::cout << "BigNumber Subtract Debugging:" << std::endl;
        std::cout << "  Num1: " << num1.to_string() << std::endl;
        std::cout << "  Num2: " << num2.to_string() << std::endl;
        std::cout << "  Result: " << result.to_string() << std::endl;
        std::cout << "  Expected: " << expected << std::endl;

        assert(result.to_string() == expected);  // Verify the result matches the expected value.
        std::cout << "TestBigNumberSubtract passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberSubtract failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberSubtract failed with an unknown exception!" << std::endl;
    }
}

/* Tests the Multiply method of BigNumber for correct multiplication. */
void TestBigNumberMultiply() {
    try {
        BigNumber num1("123");
        BigNumber num2("456");

        BigNumber result = num1.Multiply(num2);

        std::string expected = "56088";  // 123 * 456 = 56088.

        std::cout << "BigNumber Multiply Debugging:" << std::endl;
        std::cout << "  Num1: " << num1.to_string() << std::endl;
        std::cout << "  Num2: " << num2.to_string() << std::endl;
        std::cout << "  Result: " << result.to_string() << std::endl;
        std::cout << "  Expected: " << expected << std::endl;

        assert(result.to_string() == expected);
        std::cout << "TestBigNumberMultiply passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberMultiply failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberMultiply failed with an unknown exception!" << std::endl;
    }
}

int main() {
    TestIsPrime();
    TestGeneratePrime();
    TestGenerateKeyPair();
    TestEncryptDecrypt();
    TestStringToBigNumber();
    TestBigNumberToString();
    TestBigNumberConstructor();
    TestBigNumberAppendDigit();
    TestBigNumberMultiplyBy10();
    TestBigNumberAdd();
    TestBigNumberSubtract();
    TestBigNumberMultiply();
    return 0;
}
