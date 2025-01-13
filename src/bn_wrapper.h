// include/bn_wrapper.h
#pragma once
#include <openssl/bn.h>
#include <stdexcept>

class BN_ptr {
public:
    BN_ptr() : bn(BN_new()) {
        if (!bn) throw std::runtime_error("BN_new failed");
    }

    ~BN_ptr() {
        if (bn) BN_free(bn);
    }

    BIGNUM* get() { return bn; }
    const BIGNUM* get() const { return bn; }

private:
    BIGNUM* bn;
};