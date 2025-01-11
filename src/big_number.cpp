#include "big_number.h"
#include <algorithm>  // For std::reverse
#include <stdexcept>  // For std::invalid_argument

/* Default constructor. Initializes the number to zero. */
BigNumber::BigNumber() : is_negative_(false) {
    digits_.push_back(0);  // Initialize to zero.
}

/* Constructs BigNumber from an integer value. */
BigNumber::BigNumber(int value) : is_negative_(false) {
    if (value == 0) {
        digits_.push_back(0);
        return;
    }

    if (value < 0) {
        is_negative_ = true;
        value = -value;  // Make the value positive for digit extraction.
    }

    while (value > 0) {
        digits_.push_back(value % 10);  // Extract least significant digit.
        value /= 10;                   // Remove the least significant digit.
    }
}

/* Constructs BigNumber from a string representation of a number. */
BigNumber::BigNumber(const std::string& value) : is_negative_(false) {
    if (value.empty()) {
        throw std::invalid_argument("BigNumber: Input string is empty.");
    }

    size_t start = 0;
    if (value[0] == '-') {
        is_negative_ = true;
        start = 1;  // Skip the negative sign.
    }

    for (size_t i = start; i < value.size(); ++i) {
        if (!std::isdigit(value[i])) {
            throw std::invalid_argument("BigNumber: Input string contains non-numeric characters.");
        }
        digits_.push_back(value[i] - '0');  // Store each digit as an integer.
    }

    std::reverse(digits_.begin(), digits_.end());  // Reverse for easier arithmetic.
    Normalize();
}

/* Copy constructor. */
BigNumber::BigNumber(const BigNumber& other)
        : digits_(other.digits_), is_negative_(other.is_negative_) {}

/* Removes leading zeros and normalizes the number. */
void BigNumber::Normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }

    // If the number is zero, ensure it's not negative.
    if (digits_.size() == 1 && digits_[0] == 0) {
        is_negative_ = false;
    }
}

/* Converts BigNumber to its string representation. */
std::string BigNumber::ToString() const {
    if (digits_.empty()) {
        return "0";
    }

    std::string result = is_negative_ ? "-" : "";
    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it) {
        result += std::to_string(*it);
    }

    return result;
}

/* Appends a single digit to the BigNumber. */
void BigNumber::AppendDigit(int digit) {
    if (digit < 0 || digit > 9) {
        throw std::invalid_argument("BigNumber: Digit must be in range 0-9.");
    }

    if (digits_.size() == 1 && digits_[0] == 0) {
        // Replace leading zero with the digit.
        digits_[0] = digit;
    } else {
        // Append the digit to the end.
        digits_.insert(digits_.begin(), digit);
    }
}

/* Multiplies the BigNumber by 10 (shifts digits left). */
void BigNumber::MultiplyBy10() {
    if (digits_.size() == 1 && digits_[0] == 0) {
        return;  // Multiplying zero by 10 is still zero.
    }

    digits_.insert(digits_.begin(), 0);  // Shift all digits left by inserting 0 at the beginning.
}

/* Adds two BigNumbers. */
BigNumber BigNumber::Add(const BigNumber& other) const {
    // Handle signs
    if (is_negative_ && !other.is_negative_) {
        return other.Subtract(*this);  /* -A + B = B - A. */
    } else if (!is_negative_ && other.is_negative_) {
        return Subtract(other);  /* A + (-B) = A - B. */
    }

    // Determine the sign of the result.
    bool result_negative = is_negative_ && other.is_negative_;

    std::vector<int> result_digits;
    int carry = 0;

    size_t max_size = std::max(digits_.size(), other.digits_.size());
    for (size_t i = 0; i < max_size || carry; ++i) {
        int digit1 = (i < digits_.size()) ? digits_[i] : 0;
        int digit2 = (i < other.digits_.size()) ? other.digits_[i] : 0;

        int sum = digit1 + digit2 + carry;
        result_digits.push_back(sum % 10);  /* Take the remainder (ones place). */
        carry = sum / 10;  /* Carry over the tens place. */
    }

    BigNumber result;
    result.digits_ = result_digits;
    result.is_negative_ = result_negative;
    result.Normalize();  /* Remove leading zeros if any. */

    return result;
}

/* Subtracts another BigNumber. */
BigNumber BigNumber::Subtract(const BigNumber& other) const {
    // Handle signs
    if (is_negative_ && !other.is_negative_) {
        BigNumber result = Add(other);  // -A - B = -(A + B)
        result.is_negative_ = true;
        return result;
    } else if (!is_negative_ && other.is_negative_) {
        return Add(other);  // A - (-B) = A + B
    } else if (is_negative_ && other.is_negative_) {
        return other.Negate().Subtract(this->Negate());  // -A - (-B) = B - A
    }

    // Handle same-sign subtraction
    bool result_negative = false;
    const BigNumber* larger = this;
    const BigNumber* smaller = &other;

    // Determine which number is larger in absolute value
    if (*this < other) {
        result_negative = true;  // Result will be negative
        larger = &other;
        smaller = this;
    }

    std::vector<int> result_digits;
    int borrow = 0;

    for (size_t i = 0; i < larger->digits_.size(); ++i) {
        int digit1 = larger->digits_[i];
        int digit2 = (i < smaller->digits_.size()) ? smaller->digits_[i] : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;  // Borrow from the next digit
            borrow = 1;
        } else {
            borrow = 0;
        }

        result_digits.push_back(diff);
    }

    BigNumber result;
    result.digits_ = result_digits;
    result.is_negative_ = result_negative;
    result.Normalize();  // Remove leading zeros if any

    return result;
}

/* Returns the negation of this BigNumber. */
BigNumber BigNumber::Negate() const {
    BigNumber result = *this;
    result.is_negative_ = !is_negative_;  // Flip the sign.
    return result;
}

/* Checks if this BigNumber is less than another. */
bool BigNumber::operator<(const BigNumber& other) const {
    // Compare signs first
    if (is_negative_ != other.is_negative_) {
        return is_negative_;  // Negative numbers are always less than positive ones
    }

    // Compare absolute magnitudes
    if (digits_.size() != other.digits_.size()) {
        // For positive numbers: fewer digits means smaller
        // For negative numbers: fewer digits means larger
        return is_negative_ ?
               (digits_.size() > other.digits_.size()) :
               (digits_.size() < other.digits_.size());
    }

    // Same number of digits, compare from most significant digit
    for (int i = digits_.size() - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i]) {
            // For positive numbers: smaller digit means smaller number
            // For negative numbers: smaller digit means larger number
            return is_negative_ ?
                   (digits_[i] > other.digits_[i]) :
                   (digits_[i] < other.digits_[i]);
        }
    }

    return false;  // Numbers are equal
}

/* Multiplies this BigNumber by another BigNumber. */
BigNumber BigNumber::Multiply(const BigNumber& other) const {
    BigNumber result("0");  // Initialize result to zero.

    // Perform multiplication using the standard algorithm.
    for (size_t i = 0; i < other.digits_.size(); ++i) {
        BigNumber temp_result;
        temp_result.digits_.resize(i, 0);  // Shift left by `i` positions.

        int carry = 0;
        for (size_t j = 0; j < digits_.size() || carry; ++j) {
            int digit1 = (j < digits_.size()) ? digits_[j] : 0;
            int product = digit1 * other.digits_[i] + carry;
            temp_result.digits_.push_back(product % 10);  // Store remainder.
            carry = product / 10;  // Calculate carry.
        }

        result = result.Add(temp_result);  // Accumulate the partial result.
    }

    // Adjust the sign of the result.
    result.is_negative_ = is_negative_ != other.is_negative_;
    result.Normalize();  // Remove leading zeros.
    return result;
}
