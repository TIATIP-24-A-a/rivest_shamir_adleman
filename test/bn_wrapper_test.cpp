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

int main() {
    TestBNPtrBasicCreation();
    return 0;
}