// bn_wrapper.h
#pragma once

#include <string>
#include <openssl/bn.h>

/**
 * A wrapper class for managing OpenSSL BIGNUM resources.
 *
 * This class simplifies the management of BIGNUM pointers provided
 * by OpenSSL, ensuring proper memory management and utility functions
 * for common BigNumber operations.
 */
class BN_ptr {
 public:
  /**
   * Default constructor.
   *
   * Initializes a new BIGNUM instance.
   * @throws std::runtime_error If the BIGNUM allocation fails.
   */
  BN_ptr();

  /**
   * Constructor with explicit BIGNUM initialization.
   *
   * Takes ownership of the provided BIGNUM pointer.
   *
   * @param bn_value A pointer to an existing BIGNUM.
   * @throws std::runtime_error If a null BIGNUM is provided.
   */
  explicit BN_ptr(BIGNUM* bn_value);

  /**
   * Destructor.
   *
   * Frees the associated BIGNUM resource.
   */
  ~BN_ptr();

  /**
   * Accessor for the underlying BIGNUM pointer.
   *
   * @return A mutable pointer to the underlying BIGNUM.
   */
  BIGNUM* get();

  /**
   * Const accessor for the underlying BIGNUM pointer.
   *
   * @return A constant pointer to the underlying BIGNUM.
   */
  const BIGNUM* get() const;

  /**
   * Move constructor.
   *
   * Transfers ownership of the BIGNUM from another BN_ptr.
   *
   * @param other The BN_ptr to move from.
   */
  BN_ptr(BN_ptr&& other) noexcept;

  /**
   * Move assignment operator.
   *
   * Transfers ownership of the BIGNUM from another BN_ptr.
   *
   * @param other The BN_ptr to move from.
   * @return A reference to the updated BN_ptr.
   */
  BN_ptr& operator=(BN_ptr&& other) noexcept;

  /**
   * Deleted copy constructor.
   *
   * Copying is not allowed to ensure unique ownership of the BIGNUM.
   */
  BN_ptr(const BN_ptr&) = delete;

  /**
   * Deleted copy assignment operator.
   *
   * Copying is not allowed to ensure unique ownership of the BIGNUM.
   */
  BN_ptr& operator=(const BN_ptr&) = delete;

  /**
   * Sets the value of the BIGNUM.
   *
   * @param value The unsigned long value to set.
   * @throws std::runtime_error If the operation fails.
   */
  void set_word(unsigned long value);

  /**
   * Retrieves the value of the BIGNUM as an unsigned long.
   *
   * @return The value of the BIGNUM.
   * @throws std::runtime_error If the value cannot fit in an unsigned long or the BIGNUM is negative.
   */
  unsigned long get_word() const;

  /**
   * Sets the sign of the BIGNUM.
   *
   * @param sign The sign to set (1 for negative, 0 for positive).
   */
  void set_negative(int sign);

  /**
   * Generates a random BIGNUM with the specified number of bits.
   *
   * @param bits The number of bits for the random BIGNUM.
   * @return True if the random number was generated successfully.
   * @throws std::runtime_error If the operation fails.
   */
  bool generate_random(int bits);

  /**
   * Generates a random BIGNUM within a specified range.
   *
   * @param min The minimum value (inclusive).
   * @param max The maximum value (inclusive).
   * @return A `BN_ptr` containing the generated random BIGNUM.
   * @throws std::runtime_error If the operation fails.
   */
  static BN_ptr generate_in_range(const BIGNUM* min, const BIGNUM* max);

  /**
   * Checks whether the BIGNUM is prime using multiple primality tests.
   *
   * @param checks The number of primality tests to perform (default: `BN_prime_checks`).
   * @return True if the BIGNUM is prime, false otherwise.
   */
  bool is_prime(int checks = BN_prime_checks) const;

  /**
   * Adds another BIGNUM to this BIGNUM.
   *
   * @param rhs The BIGNUM to add.
   * @return A `BN_ptr` containing the result of the addition.
   * @throws std::runtime_error If the addition operation fails.
   */
  BN_ptr add(const BIGNUM* rhs) const;

  /**
   * Subtracts another BIGNUM from this BIGNUM.
   *
   * @param rhs The BIGNUM to subtract.
   * @return A `BN_ptr` containing the result of the subtraction.
   * @throws std::runtime_error If the subtraction operation fails.
   */
  BN_ptr sub(const BIGNUM* rhs) const;

  /**
   * Multiplies this BIGNUM by another BIGNUM.
   *
   * @param rhs The BIGNUM to multiply with.
   * @return A `BN_ptr` containing the result of the multiplication.
   * @throws std::runtime_error If the multiplication operation fails.
   */
  BN_ptr mul(const BIGNUM* rhs) const;

  /**
   * Divides this BIGNUM by another BIGNUM.
   *
   * @param rhs The divisor BIGNUM.
   * @return A `BN_ptr` containing the quotient.
   * @throws std::runtime_error If the division operation fails.
   */
  BN_ptr div(const BIGNUM* rhs) const;

  /**
   * Performs modular exponentiation.
   *
   * Computes `(this^exp) % m`.
   *
   * @param exp The exponent BIGNUM.
   * @param m The modulus BIGNUM.
   * @return A `BN_ptr` containing the result of the modular exponentiation.
   * @throws std::runtime_error If the operation fails.
   */
  BN_ptr mod_exp(const BIGNUM* exp, const BIGNUM* m) const;

  /**
   * Computes the modulus of this BIGNUM with another.
   *
   * @param m The modulus BIGNUM.
   * @return A `BN_ptr` containing the modulus result.
   * @throws std::runtime_error If the operation fails.
   */
  BN_ptr mod(const BIGNUM* m) const;

  /**
   * Retrieves the value of a specific bit in the BIGNUM.
   *
   * @param n The bit index (0-based).
   * @return The value of the bit (0 or 1).
   */
  int get_bit(int n) const;

  /**
   * Computes the number of significant bits in the BIGNUM.
   *
   * @return The number of bits in the BIGNUM.
   */
  int num_bits() const;

  /**
   * Generates a random prime BIGNUM with the specified number of bits.
   *
   * @param bits The bit length of the prime.
   * @return True if the prime was generated successfully.
   * @throws std::runtime_error If the operation fails.
   */
  bool generate_prime(int bits);

  /**
   * Computes the greatest common divisor (GCD) of this BIGNUM and another.
   *
   * @param rhs The other BIGNUM.
   * @return A `BN_ptr` containing the GCD.
   * @throws std::runtime_error If the operation fails.
   */
  BN_ptr gcd(const BIGNUM* rhs) const;

  /**
   * Computes the modular inverse of this BIGNUM modulo another.
   *
   * @param m The modulus BIGNUM.
   * @return A `BN_ptr` containing the modular inverse.
   * @throws std::runtime_error If no modular inverse exists.
   */
  BN_ptr mod_inverse(const BIGNUM* m) const;

  /**
   * Generates a random safe prime with a specified number of bits.
   *
   * A safe prime is a prime number p such that `(p-1)/2` is also prime.
   *
   * @param bits The bit length of the safe prime.
   * @return True if the safe prime was generated successfully.
   */
  bool generate_safe_prime(int bits);

  /**
   * Retrieves the OpenSSL constant value one.
   *
   * @return A pointer to the BIGNUM constant value one.
   */
  static const BIGNUM* value_one() { return BN_value_one(); }

  /**
   * Creates a copy of the BIGNUM.
   *
   * @return A `BN_ptr` containing a copy of the current BIGNUM.
   * @throws std::runtime_error If the operation fails or the BIGNUM is uninitialized.
   */
  BN_ptr copy() const;

  /**
   * Converts the BIGNUM to its string representation.
   *
   * @return A string representing the value of the BIGNUM in hexadecimal format.
   */
  std::string to_string() const;

 private:
  BIGNUM* bn;  ///< The underlying BIGNUM pointer.

  /**
   * Checks for errors in OpenSSL operations.
   *
   * @param result The result code of an OpenSSL operation.
   * @throws std::runtime_error If the result indicates an error.
   */
  static void check_error(int result);

  /**
   * Provides a thread-safe OpenSSL context.
   *
   * @return A pointer to a BN_CTX object used for BIGNUM operations.
   * @throws std::runtime_error If the context cannot be created.
   */
  static BN_CTX* get_ctx();
};