#pragma once
#include <string>
#include <openssl/bn.h>  // Changed from types.h

class BN_ptr {
public:
    BN_ptr();
    explicit BN_ptr(BIGNUM* bn_value);
    ~BN_ptr();

    BIGNUM* get();
    const BIGNUM* get() const;

    // Move operations
    BN_ptr(BN_ptr&& other) noexcept;
    BN_ptr& operator=(BN_ptr&& other) noexcept;

    // Delete copy operations
    BN_ptr(const BN_ptr&) = delete;
    BN_ptr& operator=(const BN_ptr&) = delete;

    void set_word(unsigned long value);
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
