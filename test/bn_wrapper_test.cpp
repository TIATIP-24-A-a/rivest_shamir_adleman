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

// Update main():
int main() {
    TestBNPtrBasicCreation();
    TestBNPtrValue();
    return 0;
}