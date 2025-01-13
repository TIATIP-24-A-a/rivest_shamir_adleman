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
    void set_negative(int sign);

    bool generate_random(int bits);
    static BN_ptr generate_in_range(const BIGNUM* min, const BIGNUM* max);

    bool is_prime(int checks = BN_prime_checks) const;

    BN_ptr add(const BIGNUM* rhs) const;
    BN_ptr sub(const BIGNUM* rhs) const;
    BN_ptr mul(const BIGNUM* rhs) const;
    BN_ptr div(const BIGNUM* rhs) const;

    BN_ptr mod_exp(const BIGNUM* exp, const BIGNUM* m) const;
    BN_ptr mod(const BIGNUM* m) const;

    int get_bit(int n) const;
    int num_bits() const;

    bool generate_prime(int bits);
    BN_ptr gcd(const BIGNUM* rhs) const;
    BN_ptr mod_inverse(const BIGNUM* m) const;

    bool generate_safe_prime(int bits);
    static const BIGNUM* value_one() { return BN_value_one(); }

    BN_ptr copy() const;

    std::string to_string() const;

private:
    BIGNUM* bn;
    static void check_error(int result);
    static BN_CTX* get_ctx();
};
