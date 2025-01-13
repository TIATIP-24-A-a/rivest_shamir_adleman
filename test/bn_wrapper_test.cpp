#include "../src/bn_wrapper.h"
#include <iostream>
#include <cassert>
#include <openssl/bn.h>

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

int main() {
    TestBNPtrBasicCreation();
    TestBNPtrValue();
    TestBNPtrMove();
    TestBNPtrComparison();
    return 0;
}