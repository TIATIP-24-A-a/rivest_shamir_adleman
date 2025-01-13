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

int main() {
    TestBNPtrBasicCreation();
    TestBNPtrValue();
    TestBNPtrMove();
    TestBNPtrComparison();
    TestBNPtrErrorHandling();
    TestBNPtrRandom();
    return 0;
}