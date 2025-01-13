#include "../src/bn_wrapper.h"
#include <iostream>
#include <cassert>

void TestBNPtrBasicCreation() {
    try {
        BN_ptr num;
        assert(num.get() != nullptr);
        std::cout << "TestBNPtrBasicCreation passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrBasicCreation failed with exception: " << e.what() << std::endl;
    }
}
void TestBNPtrValue() {
    try {
        BN_ptr num;
        BN_set_word(num.get(), 123);
        assert(BN_get_word(num.get()) == 123);
        std::cout << "TestBNPtrValue passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrValue failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMove() {
    try {
        BN_ptr num1;
        BN_set_word(num1.get(), 123);
        BN_ptr num2 = std::move(num1);
        assert(num1.get() == nullptr);  // Should be null after move
        assert(BN_get_word(num2.get()) == 123);  // Should have the value
        std::cout << "TestBNPtrMove passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMove failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrComparison() {
    try {
        BN_ptr num1, num2;
        BN_set_word(num1.get(), 123);
        BN_set_word(num2.get(), 123);
        assert(BN_cmp(num1.get(), num2.get()) == 0);  // Should be equal

        BN_set_word(num2.get(), 124);
        assert(BN_cmp(num1.get(), num2.get()) < 0);  // num1 should be less
        std::cout << "TestBNPtrComparison passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrComparison failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrErrorHandling() {
    try {
        BN_ptr num;
        bool caught_error = false;

        try {
            num.set_word(1);    // Nonzero
            num.set_negative(1);
            num.get_word();     // Should throw now
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
        BN_ptr num;
        assert(num.generate_random(256));  // Generate 256-bit random number

        // Generate in range
        BN_ptr min, max;
        min.set_word(1000);
        max.set_word(2000);
        BN_ptr random = BN_ptr::generate_in_range(min.get(), max.get());
        assert(BN_cmp(random.get(), min.get()) >= 0);
        assert(BN_cmp(random.get(), max.get()) <= 0);

        std::cout << "TestBNPtrRandom passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrRandom failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrPrimality() {
    try {
        BN_ptr num;
        num.set_word(17);  // Known prime
        assert(num.is_prime());

        num.set_word(24);  // Known composite
        assert(!num.is_prime());

        std::cout << "TestBNPtrPrimality passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrPrimality failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrAddition() {
    try {
        BN_ptr a, b;
        a.set_word(50);
        b.set_word(30);
        BN_ptr result = a.add(b.get());
        assert(result.get_word() == 80);
        std::cout << "TestBNPtrAddition passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrAddition failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrSubtraction() {
    try {
        BN_ptr a, b;
        a.set_word(50);
        b.set_word(30);
        BN_ptr result = a.sub(b.get());
        assert(result.get_word() == 20);
        std::cout << "TestBNPtrSubtraction passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrSubtraction failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMultiplication() {
    try {
        BN_ptr a, b;
        a.set_word(50);
        b.set_word(30);
        BN_ptr result = a.mul(b.get());
        assert(result.get_word() == 1500);
        std::cout << "TestBNPtrMultiplication passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMultiplication failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrDivision() {
    try {
        BN_ptr a, b;
        a.set_word(100);
        b.set_word(5);
        BN_ptr result = a.div(b.get());
        assert(result.get_word() == 20);
        std::cout << "TestBNPtrDivision passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrDivision failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrModExp() {
    try {
        BN_ptr base, exponent, modulus;
        base.set_word(4);
        exponent.set_word(13);
        modulus.set_word(497);
        // 4^13 mod 497 = 445
        BN_ptr result = base.mod_exp(exponent.get(), modulus.get());
        assert(result.get_word() == 445);
        std::cout << "TestBNPtrModExp passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrModExp failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrMod() {
    try {
        BN_ptr num, mod;
        num.set_word(100);
        mod.set_word(30);
        BN_ptr result = num.mod(mod.get());
        assert(result.get_word() == 10);  // 100 mod 30 = 10
        std::cout << "TestBNPtrMod passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrMod failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrGetSetBit() {
    try {
        BN_ptr num;
        num.set_word(8);  // 1000 in binary
        assert(num.get_bit(3) == 1);  // Fourth bit should be set
        assert(num.get_bit(2) == 0);  // Third bit should not be set
        assert(num.get_bit(1) == 0);  // Second bit should not be set
        assert(num.get_bit(0) == 0);  // First bit should not be set
        std::cout << "TestBNPtrGetSetBit passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrGetSetBit failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForEight() {
    try {
        BN_ptr num;
        num.set_word(8);    // 1000 in binary
        assert(num.num_bits() == 4);
        std::cout << "TestBNPtrNumBitsForEight passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForEight failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForFifteen() {
    try {
        BN_ptr num;
        num.set_word(15);   // 1111 in binary
        assert(num.num_bits() == 4);
        std::cout << "TestBNPtrNumBitsForFifteen passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForFifteen failed with exception: " << e.what() << std::endl;
    }
}

void TestBNPtrNumBitsForSixteen() {
    try {
        BN_ptr num;
        num.set_word(16);   // 10000 in binary
        assert(num.num_bits() == 5);
        std::cout << "TestBNPtrNumBitsForSixteen passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBNPtrNumBitsForSixteen failed with exception: " << e.what() << std::endl;
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
    return 0;
}