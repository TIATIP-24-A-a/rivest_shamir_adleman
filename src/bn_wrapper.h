// include/bn_wrapper.h
#pragma once
#include <openssl/bn.h>

class BN_ptr {
public:
    BN_ptr();
    ~BN_ptr();

    BIGNUM* get();
    const BIGNUM* get() const;

private:
    BIGNUM* bn;
};