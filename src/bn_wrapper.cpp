// src/bn_wrapper.cpp
#include "bn_wrapper.h"
#include <stdexcept>

BN_ptr::BN_ptr() : bn(BN_new()) {
    if (!bn) throw std::runtime_error("BN_new failed");
}

BN_ptr::BN_ptr(BIGNUM* bn_value) : bn(bn_value) {
    if (!bn) throw std::runtime_error("Null BIGNUM provided");
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

bool BN_ptr::generate_random(int bits) {
    check_error(BN_rand(bn, bits, 0, 0));
    return true;
}

BN_ptr BN_ptr::generate_in_range(const BIGNUM* min, const BIGNUM* max) {
    BN_CTX* ctx = get_ctx();
    BIGNUM* range_bn = BN_new();
    if (!range_bn) throw std::runtime_error("BN_new failed");
    BN_ptr range(range_bn);  // Now this will work

    // Calculate range = max - min + 1
    check_error(BN_sub(range.get(), max, min));
    check_error(BN_add_word(range.get(), 1));

    BN_ptr result;
    do {
        check_error(BN_rand_range(result.get(), range.get()));
        check_error(BN_add(result.get(), result.get(), min));
    } while (BN_cmp(result.get(), max) > 0);

    BN_CTX_free(ctx);
    return result;
}

BN_CTX* BN_ptr::get_ctx() {
    BN_CTX* ctx = BN_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create BN_CTX");
    return ctx;
}

bool BN_ptr::is_prime(int checks) const {
    int is_prime = BN_is_prime_ex(bn, checks, get_ctx(), nullptr);
    check_error(is_prime >= 0);
    return is_prime == 1;
}

BN_ptr BN_ptr::add(const BIGNUM* rhs) const {
    BN_ptr result;
    check_error(BN_add(result.get(), bn, rhs));
    return result;
}

BN_ptr BN_ptr::sub(const BIGNUM* rhs) const {
    BN_ptr result;
    check_error(BN_sub(result.get(), bn, rhs));
    return result;
}
