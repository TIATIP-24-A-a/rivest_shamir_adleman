#include "big_number.h"
#include <algorithm>  // For std::reverse
#include <stdexcept>  // For std::invalid_argument

/* Default constructor. Initializes the number to zero. */
BigNumber::BigNumber() : is_negative_(false) {
    digits_.push_back(0);  // Initialize to zero.
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
