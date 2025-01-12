#include "../src/big_number.h"
#include <cassert>
#include <iostream>
#include <exception>

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

void TestBigNumberLessThanDifferentSigns() {
    try {
        assert(BigNumber("-1") < BigNumber("1"));
        assert(!(BigNumber("1") < BigNumber("-1")));
        std::cout << "TestBigNumberLessThanDifferentSigns passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanDifferentSigns failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanDifferentSigns failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberLessThanDifferentLengths() {
    try {
        assert(BigNumber("1") < BigNumber("10"));
        assert(!(BigNumber("10") < BigNumber("1")));
        std::cout << "TestBigNumberLessThanDifferentLengths passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanDifferentLengths failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanDifferentLengths failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberLessThanSameLength() {
    try {
        assert(BigNumber("123") < BigNumber("124"));
        assert(!(BigNumber("124") < BigNumber("123")));
        std::cout << "TestBigNumberLessThanSameLength passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanSameLength failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanSameLength failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberLessThanNegativeNumbers() {
    try {
        assert(BigNumber("-124") < BigNumber("-123"));
        assert(!(BigNumber("-123") < BigNumber("-124")));
        std::cout << "TestBigNumberLessThanNegativeNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanNegativeNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanNegativeNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberEqualsSameNumbers() {
    try {
        assert(BigNumber("123") == BigNumber("123"));
        assert(BigNumber("-123") == BigNumber("-123"));
        std::cout << "TestBigNumberEqualsSameNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberEqualsSameNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberEqualsSameNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberEqualsDifferentSigns() {
    try {
        assert(!(BigNumber("123") == BigNumber("-123")));
        std::cout << "TestBigNumberEqualsDifferentSigns passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberEqualsDifferentSigns failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberEqualsDifferentSigns failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberEqualsLeadingZeros() {
    try {
        assert(BigNumber("00123") == BigNumber("123"));
        std::cout << "TestBigNumberEqualsLeadingZeros passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberEqualsLeadingZeros failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberEqualsLeadingZeros failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberNotEqualsDifferentNumbers() {
    try {
        assert(BigNumber("123") != BigNumber("124"));
        std::cout << "TestBigNumberNotEqualsDifferentNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberNotEqualsDifferentNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberNotEqualsDifferentNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberNotEqualsDifferentSigns() {
    try {
        assert(BigNumber("123") != BigNumber("-123"));
        std::cout << "TestBigNumberNotEqualsDifferentSigns passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberNotEqualsDifferentSigns failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberNotEqualsDifferentSigns failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberLessThanEqualSameNumbers() {
    try {
        assert(BigNumber("123") <= BigNumber("123"));
        std::cout << "TestBigNumberLessThanEqualSameNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanEqualSameNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanEqualSameNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberLessThanEqualDifferentNumbers() {
    try {
        assert(BigNumber("123") <= BigNumber("124"));
        assert(!(BigNumber("124") <= BigNumber("123")));
        std::cout << "TestBigNumberLessThanEqualDifferentNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberLessThanEqualDifferentNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberLessThanEqualDifferentNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberGreaterThanDifferentNumbers() {
    try {
        assert(BigNumber("124") > BigNumber("123"));
        assert(!(BigNumber("123") > BigNumber("124")));
        std::cout << "TestBigNumberGreaterThanDifferentNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberGreaterThanDifferentNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberGreaterThanDifferentNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberGreaterThanEqualSameNumbers() {
    try {
        assert(BigNumber("123") >= BigNumber("123"));
        std::cout << "TestBigNumberGreaterThanEqualSameNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberGreaterThanEqualSameNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberGreaterThanEqualSameNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberGreaterThanEqualDifferentNumbers() {
    try {
        assert(BigNumber("124") >= BigNumber("123"));
        assert(!(BigNumber("123") >= BigNumber("124")));
        std::cout << "TestBigNumberGreaterThanEqualDifferentNumbers passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberGreaterThanEqualDifferentNumbers failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberGreaterThanEqualDifferentNumbers failed with an unknown exception!" << std::endl;
    }
}

void TestBigNumberEdgeCaseZeros() {
    try {
        assert(BigNumber("0") == BigNumber("-0"));
        assert(BigNumber("0") <= BigNumber("1"));
        assert(BigNumber("0") >= BigNumber("-1"));
        std::cout << "TestBigNumberEdgeCaseZeros passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "TestBigNumberEdgeCaseZeros failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "TestBigNumberEdgeCaseZeros failed with an unknown exception!" << std::endl;
    }
}

int main() {
    TestBigNumberLessThanDifferentSigns();
    TestBigNumberLessThanDifferentLengths();
    TestBigNumberLessThanSameLength();
    TestBigNumberLessThanNegativeNumbers();
    TestBigNumberEqualsSameNumbers();
    TestBigNumberEqualsDifferentSigns();
    TestBigNumberEqualsLeadingZeros();
    TestBigNumberNotEqualsDifferentNumbers();
    TestBigNumberNotEqualsDifferentSigns();
    TestBigNumberLessThanEqualSameNumbers();
    TestBigNumberLessThanEqualDifferentNumbers();
    TestBigNumberGreaterThanDifferentNumbers();
    TestBigNumberGreaterThanEqualSameNumbers();
    TestBigNumberGreaterThanEqualDifferentNumbers();
    TestBigNumberEdgeCaseZeros();
    TestBigNumberConstructor();
    TestBigNumberAppendDigit();
    TestBigNumberMultiplyBy10();
    TestBigNumberAdd();
    TestBigNumberSubtract();
    TestBigNumberMultiply();
    return 0;
}
