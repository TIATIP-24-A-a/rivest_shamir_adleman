#pragma once

#include <string>
#include <openssl/bn.h>

/* A wrapper class for managing OpenSSL BIGNUM resources.
 *
 * The BN_ptr class simplifies the management of BIGNUM pointers,
 * providing automatic memory management and utility functions
 * for common big-number operations.
 */
class BN_ptr {
public:
    /* Default constructor.
     *
     * Initializes a new BIGNUM instance.
     */
    BN_ptr();

    /* Constructor with explicit BIGNUM initialization.
     *
     * Takes ownership of the provided BIGNUM pointer.
     *
     * Args:
     *   bn_value: A pointer to an existing BIGNUM.
     */
    explicit BN_ptr(BIGNUM* bn_value);

    /* Destructor.
     *
     * Frees the associated BIGNUM resource.
     */
    ~BN_ptr();

    /* Accessor for the underlying BIGNUM pointer.
     *
     * Returns:
     *   A mutable pointer to the underlying BIGNUM.
     */
    BIGNUM* get();

    /* Const accessor for the underlying BIGNUM pointer.
     *
     * Returns:
     *   A constant pointer to the underlying BIGNUM.
     */
    const BIGNUM* get() const;

    /* Move constructor.
     *
     * Transfers ownership of the BIGNUM from another BN_ptr.
     *
     * Args:
     *   other: The BN_ptr to move from.
     */
    BN_ptr(BN_ptr&& other) noexcept;

    /* Move assignment operator.
     *
     * Transfers ownership of the BIGNUM from another BN_ptr.
     *
     * Args:
     *   other: The BN_ptr to move from.
     * Returns:
     *   A reference to the updated BN_ptr.
     */
    BN_ptr& operator=(BN_ptr&& other) noexcept;

    // Delete copy operations
    BN_ptr(const BN_ptr&) = delete;
    BN_ptr& operator=(const BN_ptr&) = delete;

    /* Sets the value of the BIGNUM.
     *
     * Args:
     *   value: The unsigned long value to set.
     */
    void set_word(unsigned long value);

    /* Retrieves the value of the BIGNUM.
     *
     * Returns:
     *   The unsigned long value of the BIGNUM.
     */
    unsigned long get_word() const;

    /* Sets the sign of the BIGNUM.
     *
     * Args:
     *   sign: The sign to set (1 for negative, 0 for positive).
     */
    void set_negative(int sign);

    /* Generates a random BIGNUM with the specified number of bits.
     *
     * Args:
     *   bits: The number of bits for the random BIGNUM.
     * Returns:
     *   True if the random number was generated successfully, false otherwise.
     */
    bool generate_random(int bits);

    /* Generates a random BIGNUM within a specified range.
     *
     * Args:
     *   min: The minimum value (inclusive).
     *   max: The maximum value (inclusive).
     * Returns:
     *   A BN_ptr containing the generated random BIGNUM.
     */
    static BN_ptr generate_in_range(const BIGNUM* min, const BIGNUM* max);

    /* Checks whether the BIGNUM is a prime number.
     *
     * Args:
     *   checks: The number of primality tests to perform (default: BN_prime_checks).
     * Returns:
     *   True if the BIGNUM is prime, false otherwise.
     */
    bool is_prime(int checks = BN_prime_checks) const;

    /* Adds another BIGNUM to this BIGNUM.
     *
     * Args:
     *   rhs: The BIGNUM to add.
     * Returns:
     *   A BN_ptr containing the result of the addition.
     */
    BN_ptr add(const BIGNUM* rhs) const;

    /* Subtracts another BIGNUM from this BIGNUM.
     *
     * Args:
     *   rhs: The BIGNUM to subtract.
     * Returns:
     *   A BN_ptr containing the result of the subtraction.
     */
    BN_ptr sub(const BIGNUM* rhs) const;

    /* Multiplies this BIGNUM with another BIGNUM.
     *
     * Args:
     *   rhs: The BIGNUM to multiply with.
     * Returns:
     *   A BN_ptr containing the result of the multiplication.
     */
    BN_ptr mul(const BIGNUM* rhs) const;

    /* Divides this BIGNUM by another BIGNUM.
     *
     * Args:
     *   rhs: The divisor BIGNUM.
     * Returns:
     *   A BN_ptr containing the quotient.
     */
    BN_ptr div(const BIGNUM* rhs) const;

    /* Performs modular exponentiation.
     *
     * Computes (this^exp) % m.
     *
     * Args:
     *   exp: The exponent BIGNUM.
     *   m: The modulus BIGNUM.
     * Returns:
     *   A BN_ptr containing the result.
     */
    BN_ptr mod_exp(const BIGNUM* exp, const BIGNUM* m) const;

    /* Computes the modulus of this BIGNUM with another.
     *
     * Args:
     *   m: The modulus BIGNUM.
     * Returns:
     *   A BN_ptr containing the result of the modulus operation.
     */
    BN_ptr mod(const BIGNUM* m) const;

    /* Retrieves the value of a specific bit.
     *
     * Args:
     *   n: The bit index (0-based).
     * Returns:
     *   The value of the bit (0 or 1).
     */
    int get_bit(int n) const;

    /* Computes the number of bits in the BIGNUM.
     *
     * Returns:
     *   The number of significant bits in the BIGNUM.
     */
    int num_bits() const;

    /* Generates a random prime BIGNUM with a specified number of bits.
     *
     * Args:
     *   bits: The bit length of the prime.
     * Returns:
     *   True if the prime was generated successfully, false otherwise.
     */
    bool generate_prime(int bits);

    /* Computes the greatest common divisor (GCD) of this BIGNUM and another.
     *
     * Args:
     *   rhs: The other BIGNUM.
     * Returns:
     *   A BN_ptr containing the GCD.
     */
    BN_ptr gcd(const BIGNUM* rhs) const;

    /* Computes the modular inverse of this BIGNUM modulo another.
     *
     * Args:
     *   m: The modulus BIGNUM.
     * Returns:
     *   A BN_ptr containing the modular inverse.
     * Throws:
     *   std::runtime_error if no modular inverse exists.
     */
    BN_ptr mod_inverse(const BIGNUM* m) const;

    /* Generates a random safe prime with a specified number of bits.
     *
     * Args:
     *   bits: The bit length of the safe prime.
     * Returns:
     *   True if the safe prime was generated successfully, false otherwise.
     */
    bool generate_safe_prime(int bits);

    /* Retrieves the OpenSSL constant value one.
     *
     * Returns:
     *   A pointer to the BIGNUM constant value one.
     */
    static const BIGNUM* value_one() { return BN_value_one(); }

    /* Creates a copy of the BIGNUM.
     *
     * Returns:
     *   A BN_ptr containing a copy of the current BIGNUM.
     */
    BN_ptr copy() const;

    /* Converts the BIGNUM to its string representation.
     *
     * Returns:
     *   A string representing the value of the BIGNUM.
     */
    std::string to_string() const;

private:
    BIGNUM* bn;

    /* Checks for errors in OpenSSL operations.
     *
     * Args:
     *   result: The result code of an OpenSSL operation.
     * Throws:
     *   std::runtime_error if the result indicates an error.
     */
    static void check_error(int result);

    /* Provides a thread-safe OpenSSL context.
     *
     * Returns:
     *   A pointer to a BN_CTX object.
     */
    static BN_CTX* get_ctx();
};
