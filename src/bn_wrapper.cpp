// src/bn_wrapper.cpp
#include "bn_wrapper.h"
#include <stdexcept>
#include <openssl/bn.h>

BN_ptr::BN_ptr() : bn(BN_new()) {
    if (!bn) throw std::runtime_error("BN_new failed");
}

BN_ptr::~BN_ptr() {
    if (bn) BN_free(bn);
}

BIGNUM* BN_ptr::get() {
    return bn;
}

const BIGNUM* BN_ptr::get() const {
    return bn;
}