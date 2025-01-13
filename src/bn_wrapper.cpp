// src/bn_wrapper.cpp
#include "bn_wrapper.h"
#include <stdexcept>

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

BN_ptr::BN_ptr(BN_ptr&& other) noexcept : bn(other.bn) {
    other.bn = nullptr;
}

BN_ptr& BN_ptr::operator=(BN_ptr&& other) noexcept {
    if (this != &other) {
        if (bn) BN_free(bn);
        bn = other.bn;
        other.bn = nullptr;
    }
    return *this;
}

void BN_ptr::set_word(unsigned long value) {
    check_error(BN_set_word(bn, value));
}

unsigned long BN_ptr::get_word() const {
    if (BN_is_negative(bn)) {
        throw std::runtime_error("Cannot convert negative number to word");
    }
    unsigned long result = BN_get_word(bn);
    if (result == 0xffffffffL && !BN_is_zero(bn)) {  // OpenSSL's error indicator
        throw std::runtime_error("Number too large for word");
    }
    return result;
}

void BN_ptr::set_negative(int sign) {
    BN_set_negative(bn, sign);
}

void BN_ptr::check_error(int result) {
    if (result == 0) {
        throw std::runtime_error("OpenSSL BIGNUM operation failed");
    }
}