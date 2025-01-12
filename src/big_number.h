#ifndef BIG_NUMBER_H_
#define BIG_NUMBER_H_

#include <string>
#include <vector>

class BigNumber
{
public:
    /* Default constructor. Initializes to zero. */
    BigNumber();

    /* Constructs BigNumber from a string representation of a number.
     *
     * Args:
     *   value: String representing the number (e.g., "123456789").
     * Throws:
     *   std::invalid_argument if the input string is invalid.
     */
    explicit BigNumber(const std::string& value);

    /* Constructs BigNumber from an integer value.
 *
 * Args:
 *   value: Integer value to initialize the BigNumber.
 */
    explicit BigNumber(int value);

    /* Copy constructor. */
    BigNumber(const BigNumber& other);

    /* Converts BigNumber to its string representation.
     *
     * Returns:
     *   A string representing the number (e.g., "123456789").
     */
    std::string to_string() const;

    /* Appends a single digit to the BigNumber.
     *
     * Args:
     *   digit: A single integer digit (0-9) to append.
     * Throws:
     *   std::invalid_argument if the digit is out of range.
     */
    void AppendDigit(int digit);

    /* Multiplies the BigNumber by 10.
     *
     * This effectively shifts the digits left by one place.
     */
    void MultiplyBy10();

    /* Adds two BigNumbers.
     *
     * Args:
     *   other: Another BigNumber to add.
     * Returns:
     *   A new BigNumber representing the sum of the two numbers.
     */
    BigNumber Add(const BigNumber& other) const;

    /* Subtracts another BigNumber from this one.
     *
     * Args:
     *   other: Another BigNumber to subtract.
     * Returns:
     *   A new BigNumber representing the difference.
     */
    BigNumber Subtract(const BigNumber& other) const;

    /* Multiplies this BigNumber by another BigNumber.
     *
     * Args:
     *   other: The BigNumber to multiply with.
     * Returns:
     *   A new BigNumber representing the product.
     */
    BigNumber Multiply(const BigNumber& other) const;

    /* Computes the modulo (remainder) of this BigNumber divided by another.
     *
     * Args:
     *   other: The divisor BigNumber.
     * Returns:
     *   A new BigNumber representing the remainder.
     */
    BigNumber Modulo(const BigNumber& other) const;

    /* Converts this BigNumber to an int (only if the value is small enough).
     *
     * Returns:
     *   The integer representation of the BigNumber.
     * Throws:
     *   std::overflow_error if the BigNumber is too large to fit in an int.
     */
    int to_int() const;

    /* Divides this BigNumber by another and returns the quotient.
     *
     * Args:
     *   other: The divisor BigNumber.
     * Returns:
     *   A new BigNumber representing the quotient.
     * Throws:
     *   std::invalid_argument if the divisor is zero.
     */
    BigNumber Divide(const BigNumber& other) const;

    /* Performs modular exponentiation: (base^exponent) % modulus.
     *
     * Args:
     *   exponent: The BigNumber exponent.
     *   modulus: The BigNumber modulus.
     * Returns:
     *   The result of (this^exponent) % modulus as a BigNumber.
     */
    BigNumber ModularExponentiation(const BigNumber& exponent, const BigNumber& modulus) const;

    /* Multiplies the BigNumber by 10^power.
     *
     * This effectively shifts the digits to the left by the specified power.
     *
     * Args:
     *   power: The number of decimal places to shift.
     */
    void MultiplyByPowerOf10(int power);

    /* Returns the absolute value of this BigNumber.
     *
     * Removes the sign of the number (if negative) and returns a new BigNumber.
     *
     * Returns:
     *   A BigNumber representing the absolute value of this number.
     */
    BigNumber Abs() const;

    /* Compares if two BigNumbers are equal.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if both BigNumbers have the same value and sign; false otherwise.
     */
    bool operator==(const BigNumber& other) const;

    /* Compares if two BigNumbers are not equal.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if both BigNumbers have the same value and sign; false otherwise.
     */
    bool operator!=(const BigNumber& other) const;

    /* Compares if this BigNumber is greater than another.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if this BigNumber is greater than the other; false otherwise.
     */
    bool operator>(const BigNumber& other) const;

    /* Checks if this BigNumber is less than another.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if this number is less than the other, false otherwise.
     */
    bool operator<(const BigNumber& other) const;

    /* Checks if this BigNumber is less than or equal as another.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if this number is less than the other, false otherwise.
     */
    bool operator<=(const BigNumber& other) const;

    /* Checks if this BigNumber is greater than or equal to another.
     *
     * Args:
     *   other: The BigNumber to compare with.
     * Returns:
     *   True if this BigNumber is greater than or equal to the other; false otherwise.
     */
    bool operator>=(const BigNumber& other) const;

    /* Overloads the multiplication operator for BigNumber.
     *
     * Multiplies two BigNumbers and returns the result.
     *
     * Args:
     *   other: The BigNumber to multiply with.
     * Returns:
     *   The product of the two BigNumbers.
     */

    BigNumber operator*(const BigNumber& other) const { return Multiply(other); }

    /* Overloads the division operator for BigNumber.
     *
     * Divides the current BigNumber by another BigNumber and returns the result.
     *
     * Args:
     *   other: The BigNumber divisor.
     * Returns:
     *   The quotient as a BigNumber.
     * Throws:
     *   std::invalid_argument if the divisor is zero.
     */
    BigNumber operator/(const BigNumber& other) const { return Divide(other); }

    /* Overloads the modulo operator for BigNumber.
     *
     * Computes the remainder when the current BigNumber is divided by another BigNumber.
     *
     * Args:
     *   other: The BigNumber divisor.
     * Returns:
     *   The remainder as a BigNumber.
     * Throws:
     *   std::invalid_argument if the divisor is zero.
     */
    BigNumber operator%(const BigNumber& other) const { return Modulo(other); }

private:
    std::vector<int> digits_; // Digits stored in reverse order for easier arithmetic.
    bool is_negative_; // Sign of the number (true if negative).

    /**
    * Performs raw addition of two BigNumbers without sign handling.
    * Assumes both numbers are positive and handles only the digit addition.
    *
    * @param other The BigNumber to add to this one
    * @return A new BigNumber containing the sum of digits
    */
    BigNumber AddRaw(const BigNumber& other) const;

    /**
    * Performs raw subtraction of two BigNumbers without sign handling.
    * Assumes this number is greater than or equal to other and both are positive.
    *
    * @param other The BigNumber to subtract from this one
    * @return A new BigNumber containing the difference of digits
    */
    BigNumber SubtractRaw(const BigNumber& other) const;

    /* Removes leading zeros and normalizes the number.
     * Ensures that zero is always represented as a single digit.
     */
    void Normalize();
};

#endif  // BIG_NUMBER_H_
