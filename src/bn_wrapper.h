// include/bn_wrapper.h
#pragma once
#include <openssl/types.h>

class BN_ptr {
public:
    BN_ptr();
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

private:
    BIGNUM* bn;
    static void check_error(int result);
};
