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
    
    BN_ptr(BN_ptr&& other) noexcept : bn(other.bn) {
        other.bn = nullptr;
    }
    
    BN_ptr& operator=(BN_ptr&& other) noexcept {
        if (this != &other) {
            if (bn) BN_free(bn);
            bn = other.bn;
            other.bn = nullptr;
        }
        return *this;
    }
    
    BN_ptr(const BN_ptr&) = delete;
    BN_ptr& operator=(const BN_ptr&) = delete;

private:
    BIGNUM* bn;
};