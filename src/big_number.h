#ifndef BIG_NUMBER_H_
#define BIG_NUMBER_H_

#include <string>
#include <vector>

class BigNumber {
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

    /* Copy constructor. */
    BigNumber(const BigNumber& other);

    /* Converts BigNumber to its string representation.
     *
     * Returns:
     *   A string representing the number (e.g., "123456789").
     */
    std::string ToString() const;

    /* Appends a single digit to the BigNumber.
     *
     * Args:
     *   digit: A single integer digit (0-9) to append.
     * Throws:
     *   std::invalid_argument if the digit is out of range.
     */
    void AppendDigit(int digit);

private:
    std::vector<int> digits_;  // Digits stored in reverse order for easier arithmetic.
    bool is_negative_;         // Sign of the number (true if negative).

    /* Removes leading zeros and normalizes the number.
     * Ensures that zero is always represented as a single digit.
     */
    void Normalize();
};

#endif  // BIG_NUMBER_H_
