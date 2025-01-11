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

/* Tests encryption and decryption using RSA keys. */
void TestEncryptDecrypt() {
    try {
        RSA::KeyPair key_pair = RSA::GenerateKeyPair(50, 100);
        int message = 42; /* Message to encrypt and decrypt. */

        int encrypted = RSA::Encrypt(message, key_pair.public_key);
        int decrypted = RSA::Decrypt(encrypted, key_pair.private_key);

        assert(decrypted == message); /* The decrypted message should match the original. */
        std::cout << "TestEncryptDecrypt passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestEncryptDecrypt failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestEncryptDecrypt failed with an unknown exception!" << std::endl;
    }
}

/* Tests the StringToInt function for correct conversion of a string to an integer. */
void TestStringToInt() {
    try {
        std::string message = "fortnite"; /* Input string message. */
        std::string result = RSA::StringToInt(message);

        /* Expected result: f=102, o=111, r=114, t=116, n=110, i=105, t=116, e=101 */
        std::string expected = "102111114116110105116101"; /* ASCII concatenation as string. */

        assert(result == expected); /* The result should match the expected value. */
        std::cout << "TestStringToInt passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestStringToInt failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestStringToInt failed with an unknown exception!" << std::endl;
    }
}

/* Tests the IntToString function for correct conversion of a concatenated ASCII string to the original message. */
void TestIntToString() {
    try {
        /* Input integer string: ASCII values concatenated. */
        std::string input = "102111114116110105116101"; // Represents "fortnite"

        /* Call the function to convert back to a string message. */
        std::string result = RSA::IntToString(input);

        /* Expected result: Original message. */
        std::string expected = "fortnite";

        /* Verify the result matches the expected value. */
        assert(result == expected);
        std::cout << "TestIntToString passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestIntToString failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestIntToString failed with an unknown exception!" << std::endl;
    }
}

/* Tests the BigNumber constructor for very large numbers. */
void TestBigNumberConstructor() {
    try {
        std::string large_number = "1234567890123456789012345678901234567890";
        BigNumber num(large_number);
        assert(num.ToString() == large_number);
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

        assert(num.ToString() == expected);
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

        assert(num.ToString() == expected);
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
        std::cout << "  Num1: " << num1.ToString() << std::endl;
        std::cout << "  Num2: " << num2.ToString() << std::endl;
        std::cout << "  Result: " << result.ToString() << std::endl;
        std::cout << "  Expected: " << expected << std::endl;

        assert(result.ToString() == expected);  /* Verify the result matches the expected value. */
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
        std::cout << "  Num1: " << num1.ToString() << std::endl;
        std::cout << "  Num2: " << num2.ToString() << std::endl;
        std::cout << "  Result: " << result.ToString() << std::endl;
        std::cout << "  Expected: " << expected << std::endl;

        assert(result.ToString() == expected);  // Verify the result matches the expected value.
        std::cout << "TestBigNumberSubtract passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberSubtract failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberSubtract failed with an unknown exception!" << std::endl;
    }
}

int main() {
    TestIsPrime();
    TestGeneratePrime();
    TestGenerateKeyPair();
    TestEncryptDecrypt();
    TestStringToInt();
    TestIntToString();
    TestBigNumberConstructor();
    TestBigNumberAppendDigit();
    TestBigNumberMultiplyBy10();
    TestBigNumberAdd();
    return 0;
}
