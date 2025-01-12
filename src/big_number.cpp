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

/* Catch-all method that checks what operation to actually perform when adding two BigNumbers. */
BigNumber BigNumber::Add(const BigNumber& other) const {
    if (is_negative_ == other.is_negative_) {
        BigNumber result = AddRaw(other);
        result.is_negative_ = is_negative_;
        result.Normalize();
        return result;
    }

    // Compare absolute values to determine which to subtract from which
    if (this->Abs() >= other.Abs()) {
        // |this| >= |other|: subtract other from this, keep this sign
        BigNumber result = SubtractRaw(other);
        result.is_negative_ = is_negative_;
        result.Normalize();
        return result;
    } else {
        // |this| < |other|: subtract this from other, take other's sign
        BigNumber result = other.SubtractRaw(*this);
        result.is_negative_ = other.is_negative_;
        result.Normalize();
        return result;
    }
}

/* Adds two BigNumbers with no checks. */
BigNumber BigNumber::AddRaw(const BigNumber& other) const {
    std::vector<int> result;
    int carry = 0;
    size_t max_size = std::max(digits_.size(), other.digits_.size());

    // Add digits one by one, handling carry
    for (size_t i = 0; i < max_size || carry; ++i) {
        int sum = carry;
        if (i < digits_.size()) {
            sum += digits_[i];
        }
        if (i < other.digits_.size()) {
            sum += other.digits_[i];
        }
        result.push_back(sum % 10);  // Store current digit
        carry = sum / 10;            // Calculate carry for next iteration
    }

    BigNumber temp;
    temp.digits_ = result;
    return temp;
}

/* Catch-all method that checks what operation to actually perform when subtracting from another BigNumber. */
BigNumber BigNumber::Subtract(const BigNumber& other) const {
    if (is_negative_ != other.is_negative_) {
        BigNumber result = AddRaw(other);
        result.is_negative_ = is_negative_;
        result.Normalize();
        return result;
    }

    // Compare absolute values to determine which to subtract from which
    if (this->Abs() >= other.Abs()) {
        // |this| >= |other|: subtract other from this, keep this sign
        BigNumber result = SubtractRaw(other);
        result.is_negative_ = is_negative_;
        result.Normalize();
        return result;
    } else {
        // |this| < |other|: subtract this from other, flip sign
        BigNumber result = other.SubtractRaw(*this);
        result.is_negative_ = !other.is_negative_;
        result.Normalize();
        return result;
    }
}

/* Subtracts another BigNumber without performing additional checks. */
BigNumber BigNumber::SubtractRaw(const BigNumber& other) const {
    std::vector<int> result;
    int borrow = 0;

    // Subtract digits one by one, handling borrow
    for (size_t i = 0; i < digits_.size(); ++i) {
        int diff = digits_[i] - borrow;
        if (i < other.digits_.size()) {
            diff -= other.digits_[i];
        }

        if (diff < 0) {
            diff += 10;    // Borrow from next digit
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }

    BigNumber temp;
    temp.digits_ = result;
    return temp;
}

/* Multiplies this BigNumber by another BigNumber. */
BigNumber BigNumber::Multiply(const BigNumber& other) const {
    BigNumber result;
    result.digits_.resize(digits_.size() + other.digits_.size(), 0);  // Pre-allocate space

    // Multiply each digit
    for (size_t i = 0; i < other.digits_.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < digits_.size(); j++) {
            int product = result.digits_[i + j] + digits_[j] * other.digits_[i] + carry;
            result.digits_[i + j] = product % 10;
            carry = product / 10;
        }
        if (carry) result.digits_[i + digits_.size()] = carry;
    }

    result.is_negative_ = is_negative_ != other.is_negative_;
    result.Normalize();
    return result;
}

/* Divides this BigNumber by another BigNumber. */
BigNumber BigNumber::Divide(const BigNumber& other) const {
    if (other == BigNumber("0")) {
        throw std::invalid_argument("Division by zero");
    }

    BigNumber quotient;
    BigNumber remainder;

    for (int i = digits_.size() - 1; i >= 0; i--) {
        remainder.MultiplyBy10();
        remainder.digits_[0] = digits_[i];  // Add new digit directly

        int q = 0;
        while (remainder.Abs() >= other.Abs()) {
            remainder = remainder.Subtract(other);
            q++;
        }
        quotient.digits_.insert(quotient.digits_.begin(), q);
    }

    quotient.is_negative_ = is_negative_ != other.is_negative_;
    quotient.Normalize();
    return quotient;
}

BigNumber BigNumber::Modulo(const BigNumber& other) const {
    if (other == BigNumber("0")) {
        throw std::invalid_argument("Modulo by zero is not allowed.");
    }

    BigNumber quotient = Divide(other);  // Integer division
    BigNumber product = quotient.Multiply(other);  // Multiply back
    return Subtract(product);  // Remainder = this - (quotient * other)
}

BigNumber BigNumber::ModularExponentiation(const BigNumber& exponent, const BigNumber& modulus) const {
    if (modulus == BigNumber("0")) {
        throw std::invalid_argument("Modulus cannot be zero");
    }
    static const BigNumber ZERO(0);
    static const BigNumber ONE(1);
    static const BigNumber TWO(2);

    BigNumber base = *this % modulus;  // Initial base modulo
    BigNumber result = ONE;           // Start with 1
    BigNumber exp = exponent;         // Copy for manipulation

    while (exp > ZERO) {
        if (exp % TWO == ONE) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp = exp / TWO;
    }

    return result;
}

/* Multiplies the BigNumber by 10^power. */
void BigNumber::MultiplyByPowerOf10(int power) {
    if (power < 0) {
        throw std::invalid_argument("BigNumber::MultiplyByPowerOf10: Power must be non-negative.");
    }

    // Append `power` number of zeros to the digit vector.
    digits_.insert(digits_.begin(), power, 0);
}

/* Returns the absolute value of this BigNumber. */
BigNumber BigNumber::Abs() const {
    BigNumber result = *this;       // Create a copy of the current number.
    result.is_negative_ = false;   // Set the sign to positive.
    return result;                 // Return the absolute value.
}

int BigNumber::to_int() const {
    static const BigNumber MAX_INT(INT_MAX);

    if (digits_.size() > 10 || *this > MAX_INT) {
        throw std::overflow_error("BigNumber too large for int");
    }

    int result = 0;
    int multiplier = 1;

    for (int digit : digits_) {
        result += digit * multiplier;
        multiplier *= 10;
    }

    return is_negative_ ? -result : result;
}

/* Converts BigNumber to its string representation. */
std::string BigNumber::to_string() const {
    std::string result;
    result.reserve(digits_.size() + (is_negative_ ? 1 : 0));

    if (is_negative_) {
        result += '-';
    }

    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it) {
        result += '0' + *it;
    }

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

bool BigNumber::operator==(const BigNumber& other) const {
    // Check if the signs are different.
    if (is_negative_ != other.is_negative_) {
        return false;
    }

    // Check if the digit sizes are different.
    if (digits_.size() != other.digits_.size()) {
        return false;
    }

    // Compare each digit.
    for (size_t i = 0; i < digits_.size(); ++i) {
        if (digits_[i] != other.digits_[i]) {
            return false;
        }
    }

    // If all checks passed, the numbers are equal.
    return true;
}

bool BigNumber::operator>(const BigNumber& other) const {
    // Compare signs
    if (is_negative_ != other.is_negative_) {
        return other.is_negative_;  // Positive is always greater than negative.
    }

    // Compare absolute magnitudes
    bool abs_greater = false;
    if (digits_.size() != other.digits_.size()) {
        abs_greater = digits_.size() > other.digits_.size();
    } else {
        for (size_t i = digits_.size(); i-- > 0;) {  // Compare digits from most significant
            if (digits_[i] != other.digits_[i]) {
                abs_greater = digits_[i] > other.digits_[i];
                break;
            }
        }
    }

    // If both numbers have the same sign:
    // - For positive numbers, return `abs_greater`.
    // - For negative numbers, flip the result (`greater magnitude means smaller value`).
    return is_negative_ ? !abs_greater : abs_greater;
}

bool BigNumber::operator>=(const BigNumber& other) const {
    // A number is greater than or equal if it is either greater than or equal to the other number.
    return (*this > other) || (*this == other);
}

/* Overloads the multiplication operator for BigNumber. */
BigNumber BigNumber::operator*(const BigNumber& other) const {
    BigNumber result;
    result.is_negative_ = (is_negative_ != other.is_negative_);  // Determine the sign.

    for (size_t i = 0; i < other.digits_.size(); ++i) {
        BigNumber temp(*this);                  // Copy the current number.
        temp.MultiplyByPowerOf10(static_cast<int>(i));                 // Shift left by i places.
        for (int j = 0; j < other.digits_[i]; ++j) {
            result = result.Add(temp);         // Add the temp value.
        }
    }

    result.Normalize();                        // Remove leading zeros.
    return result;
}

/* Overloads the division operator for BigNumber. */
BigNumber BigNumber::operator/(const BigNumber& other) const {
    if (other == BigNumber("0")) {
        throw std::invalid_argument("BigNumber: Division by zero.");
    }

    BigNumber dividend = *this;
    BigNumber divisor = other.Abs();
    BigNumber result;
    result.is_negative_ = (is_negative_ != other.is_negative_);

    while (dividend >= divisor) {
        dividend = dividend.Subtract(divisor);
        result = result.Add(BigNumber("1"));
    }

    return result;
}

/* Overloads the modulo operator for BigNumber. */
BigNumber BigNumber::operator%(const BigNumber& other) const {
    if (other == BigNumber("0")) {
        throw std::invalid_argument("BigNumber: Modulo by zero.");
    }

    BigNumber dividend = *this;
    BigNumber divisor = other.Abs();

    while (dividend >= divisor) {
        dividend = dividend.Subtract(divisor);
    }

    return dividend;
}