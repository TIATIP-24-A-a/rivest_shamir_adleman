#include "../src/bn_wrapper.h"
#include <iostream>
#include <cassert>

void TestBNPtrBasicCreation() {
    try {
        BigNumber num;
        assert(num.Get() != nullptr);
        std::cout << "TestBNPtrBasicCreation passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrBasicCreation failed with exception: " << e.what() << std::endl;
    }
}
void TestBNPtrValue() {
    try {
        BigNumber num;
        BN_set_word(num.Get(), 123);
        assert(BN_get_word(num.Get()) == 123);
        std::cout << "TestBNPtrValue passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrValue failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMove() {
    try {
        BigNumber num1;
        BN_set_word(num1.Get(), 123);
        BigNumber num2 = std::move(num1);
        assert(num1.Get() == nullptr);  // Should be null after move
        assert(BN_get_word(num2.Get()) == 123);  // Should have the value
        std::cout << "TestBNPtrMove passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMove failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrComparison() {
    try {
        BigNumber num1, num2;
        BN_set_word(num1.Get(), 123);
        BN_set_word(num2.Get(), 123);
        assert(BN_cmp(num1.Get(), num2.Get()) == 0);  // Should be equal

        BN_set_word(num2.Get(), 124);
        assert(BN_cmp(num1.Get(), num2.Get()) < 0);  // num1 should be less
        std::cout << "TestBNPtrComparison passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrComparison failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrErrorHandling() {
    try {
        BigNumber num;
        bool caught_error = false;

        try {
            num.SetWord(1);    // Nonzero
            num.SetNegative(1);
            num.GetWord();     // Should throw now
        } catch (const std::runtime_error&) {
            caught_error = true;
        }

        assert(caught_error && "Should have caught error");
        std::cout << "TestBNPtrErrorHandling passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrErrorHandling failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrRandom() {
    try {
        BigNumber num;
        assert(num.GenerateRandom(256));  // Generate 256-bit random number

        // Generate in range
        BigNumber min, max;
        min.SetWord(1000);
        max.SetWord(2000);
        BigNumber random = BigNumber::GenerateInRange(min.Get(), max.Get());
        assert(BN_cmp(random.Get(), min.Get()) >= 0);
        assert(BN_cmp(random.Get(), max.Get()) <= 0);

        std::cout << "TestBNPtrRandom passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrRandom failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrPrimality() {
    try {
        BigNumber num;
        num.SetWord(17);  // Known prime
        assert(num.IsPrime());

        num.SetWord(24);  // Known composite
        assert(!num.IsPrime());

        std::cout << "TestBNPtrPrimality passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrPrimality failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrAddition() {
    try {
        BigNumber a, b;
        a.SetWord(50);
        b.SetWord(30);
        BigNumber result = a.Add(b.Get());
        assert(result.GetWord() == 80);
        std::cout << "TestBNPtrAddition passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrAddition failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrSubtraction() {
    try {
        BigNumber a, b;
        a.SetWord(50);
        b.SetWord(30);
        BigNumber result = a.Sub(b.Get());
        assert(result.GetWord() == 20);
        std::cout << "TestBNPtrSubtraction passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrSubtraction failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMultiplication() {
    try {
        BigNumber a, b;
        a.SetWord(50);
        b.SetWord(30);
        BigNumber result = a.Mul(b.Get());
        assert(result.GetWord() == 1500);
        std::cout << "TestBNPtrMultiplication passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMultiplication failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrDivision() {
    try {
        BigNumber a, b;
        a.SetWord(100);
        b.SetWord(5);
        BigNumber result = a.Div(b.Get());
        assert(result.GetWord() == 20);
        std::cout << "TestBNPtrDivision passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrDivision failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrModExp() {
    try {
        BigNumber base, exponent, modulus;
        base.SetWord(4);
        exponent.SetWord(13);
        modulus.SetWord(497);
        // 4^13 mod 497 = 445
        BigNumber result = base.ModExp(exponent.Get(), modulus.Get());
        assert(result.GetWord() == 445);
        std::cout << "TestBNPtrModExp passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrModExp failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMod() {
    try {
        BigNumber num, mod;
        num.SetWord(100);
        mod.SetWord(30);
        BigNumber result = num.Mod(mod.Get());
        assert(result.GetWord() == 10);  // 100 mod 30 = 10
        std::cout << "TestBNPtrMod passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMod failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrGetSetBit() {
    try {
        BigNumber num;
        num.SetWord(8);  // 1000 in binary
        assert(num.GetBit(3) == 1);  // Fourth bit should be set
        assert(num.GetBit(2) == 0);  // Third bit should not be set
        assert(num.GetBit(1) == 0);  // Second bit should not be set
        assert(num.GetBit(0) == 0);  // First bit should not be set
        std::cout << "TestBNPtrGetSetBit passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrGetSetBit failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForEight() {
    try {
        BigNumber num;
        num.SetWord(8);    // 1000 in binary
        assert(num.NumBits() == 4);
        std::cout << "TestBNPtrNumBitsForEight passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForEight failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForFifteen() {
    try {
        BigNumber num;
        num.SetWord(15);   // 1111 in binary
        assert(num.NumBits() == 4);
        std::cout << "TestBNPtrNumBitsForFifteen passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForFifteen failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForSixteen() {
    try {
        BigNumber num;
        num.SetWord(16);   // 10000 in binary
        assert(num.NumBits() == 5);
        std::cout << "TestBNPtrNumBitsForSixteen passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForSixteen failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrGenerateRandomPrime512() {
    try {
        BigNumber prime;
        // We'll add a new method generate_prime
        prime.GeneratePrime(512);

        // Should be exactly 512 bits
        assert(prime.NumBits() == 512);
        // Should be prime
        assert(prime.IsPrime());

        std::cout << "TestBNPtrGenerateRandomPrime512 passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrGenerateRandomPrime512 failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrGCD() {
    try {
        BigNumber a, b;
        a.SetWord(48);
        b.SetWord(18);
        BigNumber result = a.Gcd(b.Get());
        assert(result.GetWord() == 6);  // GCD(48,18) = 6

        std::cout << "TestBNPtrGCD passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrGCD failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrModInverse() {
    try {
        BigNumber a, m;
        a.SetWord(5);
        m.SetWord(11);
        BigNumber result = a.ModInverse(m.Get());
        // 5 * 9 ≡ 1 (mod 11)
        assert(result.GetWord() == 9);

        std::cout << "TestBNPtrModInverse passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrModInverse failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrGenerateSafePrime() {
    try {
        BigNumber prime;
        prime.GenerateSafePrime(512);  // Smaller size for test

        // Should be prime
        assert(prime.IsPrime());

        // (p-1)/2 should also be prime
        BigNumber p_minus_1 = prime.Sub(BN_value_one());
        BigNumber two;
        two.SetWord(2);
        BigNumber q = p_minus_1.Div(two.Get());
        assert(q.IsPrime());

        std::cout << "TestBNPtrGenerateSafePrime passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrGenerateSafePrime failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrIsRelativelyPrime() {
    try {
        BigNumber a, b;
        a.SetWord(9);
        b.SetWord(14);
        // 9 and 14 are relatively prime
        assert(a.Gcd(b.Get()).GetWord() == 1);

        std::cout << "TestBNPtrIsRelativelyPrime passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrIsRelativelyPrime failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrLargePrimeLength() {
    try {
        BigNumber prime;
        int bits = 2048;  // Test with 2048 bits
        prime.GeneratePrime(bits);

        // Should be exactly the requested bit length
        assert(prime.NumBits() == bits);

        std::cout << "TestBNPtrLargePrimeLength passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrLargePrimeLength failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrRSAExponent() {
    try {
        BigNumber p, q, e;
        p.GeneratePrime(512);  // Small primes for test
        q.GeneratePrime(512);

        // Calculate (p-1)(q-1)
        BigNumber p_minus_1 = p.Sub(BN_value_one());
        BigNumber q_minus_1 = q.Sub(BN_value_one());
        BigNumber totient = p_minus_1.Mul(q_minus_1.Get());

        // Common RSA public exponent
        e.SetWord(65537);

        // Should be coprime
        assert(e.Gcd(totient.Get()).GetWord() == 1);

        std::cout << "TestBNPtrRSAExponent passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrRSAExponent failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrRSAModularArithmetic() {
    try {
        // Small numbers for test verification
        BigNumber message, e, d, n;
        message.SetWord(42);  // Message
        e.SetWord(17);       // Public exponent
        n.SetWord(3233);     // Modulus (61 * 53)
        d.SetWord(413);      // Private exponent

        // Encrypt: c = m^e mod n
        BigNumber cipher = message.ModExp(e.Get(), n.Get());
        // Decrypt: m = c^d mod n
        BigNumber decrypted = cipher.ModExp(d.Get(), n.Get());

        assert(decrypted.GetWord() == 42);

        std::cout << "TestBNPtrRSAModularArithmetic passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrRSAModularArithmetic failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrRSAKeySize() {
    try {
        BigNumber p, q;
        p.GeneratePrime(2048);
        q.GeneratePrime(2048);
        BigNumber n = p.Mul(q.Get());

        // RSA-4096 modulus should be 4096 bits
        assert(n.NumBits() >= 4095 && n.NumBits() <= 4096);

        std::cout << "TestBNPtrRSAKeySize passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrRSAKeySize failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrCopy() {
    try {
        BigNumber original;
        original.SetWord(12345);

        BigNumber copied = original.Copy();
        assert(BN_cmp(original.Get(), copied.Get()) == 0);

        // Modify original, copy shouldn't change
        original.SetWord(54321);
        assert(BN_get_word(copied.Get()) == 12345);

        std::cout << "TestBNPtrCopy passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrCopy failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrToString() {
    try {
        BigNumber num;
        num.SetWord(0x123ABC);  // Set a test value
        std::string result = num.ToString();  // Call the to_string method
        assert(result == "123ABC");  // Hexadecimal representation of 0x123ABC
        std::cout << "TestBNPtrToString passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrToString failed with exception: " << e.what() << std::endl;
    }
}

int main() {
    TestBNPtrBasicCreation();
    TestBNPtrValue();
    TestBNPtrMove();
    TestBNPtrComparison();
    TestBNPtrErrorHandling();
    TestBNPtrRandom();
    TestBNPtrPrimality();
    TestBNPtrAddition();
    TestBNPtrSubtraction();
    TestBNPtrMultiplication();
    TestBNPtrDivision();
    TestBNPtrModExp();
    TestBNPtrMod();
    TestBNPtrGetSetBit();
    TestBNPtrNumBitsForEight();
    TestBNPtrNumBitsForFifteen();
    TestBNPtrNumBitsForSixteen();
    TestBNPtrGenerateRandomPrime512();
    TestBNPtrGCD();
    TestBNPtrModInverse();
    TestBNPtrGenerateSafePrime();
    TestBNPtrIsRelativelyPrime();
    TestBNPtrLargePrimeLength();
    TestBNPtrRSAExponent();
    TestBNPtrRSAModularArithmetic();
    TestBNPtrRSAKeySize();
    TestBNPtrCopy();
    TestBNPtrToString();
    return 0;
}