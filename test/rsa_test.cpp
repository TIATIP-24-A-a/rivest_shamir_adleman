#include "../src/prime_utils.h"
#include <cassert>
#include <iostream>

// Tests the IsPrime function in PrimeUtils.
void TestIsPrime() {
    // Test a known prime number.
    assert(PrimeUtils::IsPrime(17) == true);

    // Test a known non-prime number.
    assert(PrimeUtils::IsPrime(18) == false);

    std::cout << "TestIsPrime passed!" << std::endl;
}

int main() {
    TestIsPrime();  // Run the IsPrime test.
    return 0;
}
