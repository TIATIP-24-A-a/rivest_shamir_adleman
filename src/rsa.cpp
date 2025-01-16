#include "rsa.h"
#include <stdexcept>
#include <numeric>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>

namespace RSA_APP {

    KeyPair generate_key_pair(int bits) {
        BN_ptr e;
        e.set_word(65537);

        BN_ptr p, q;
        p.generate_prime(bits / 2);
        do {
            q.generate_prime(bits / 2);
        } while (BN_cmp(p.get(), q.get()) == 0);

        if (!p.get_bit(bits / 2 - 1) || !q.get_bit(bits / 2 - 1)) {
            throw std::runtime_error("Generated primes do not have the required bit length");
        }

        BN_ptr n = p.mul(q.get());
        BN_ptr p_minus_1 = p.sub(BN_value_one());
        BN_ptr q_minus_1 = q.sub(BN_value_one());
        BN_ptr totient = p_minus_1.mul(q_minus_1.get());

        if (e.gcd(totient.get()).get_word() != 1) {
            throw std::runtime_error("Public exponent not coprime with totient");
        }

        BN_ptr d = e.mod_inverse(totient.get());

        return KeyPair{
            PublicKey{n.copy(), std::move(e)},
            PrivateKey{std::move(n), std::move(d)}
        };
    }

    BN_ptr encrypt(const BN_ptr& message, const PublicKey& public_key) {
        if (BN_cmp(message.get(), public_key.n.get()) >= 0) {
            throw std::invalid_argument("Message too large for key size");
        }

        return message.mod_exp(public_key.e.get(), public_key.n.get());
    }

    BN_ptr decrypt(const BN_ptr& ciphertext, const PrivateKey& private_key) {
        if (BN_cmp(ciphertext.get(), private_key.n.get()) >= 0) {
            throw std::invalid_argument("Ciphertext too large for key size");
        }

        return ciphertext.mod_exp(private_key.d.get(), private_key.n.get());
    }

    BN_ptr string_to_number(const std::string& message) {
        BN_ptr result;
        BN_ptr base;
        base.set_word(256);

        result.set_word(0);
        for (unsigned char c : message) {
            result = result.mul(base.get());
            BN_ptr char_value;
            char_value.set_word(c);
            result = result.add(char_value.get());
        }

        return result;
    }

    std::string number_to_string(const BN_ptr& number) {
        std::string result;
        BN_ptr remaining = number.copy();
        BN_ptr base;
        base.set_word(256);
        BN_ptr zero;
        zero.set_word(0);

        while (BN_cmp(remaining.get(), zero.get()) > 0) {
            BN_ptr quotient, remainder;
            remainder = remaining.mod(base.get());
            remaining = remaining.div(base.get());

            unsigned long char_value = remainder.get_word();
            result.insert(result.begin(), static_cast<char>(char_value));
        }

        return result;
    }

    std::string format_big_number(const BN_ptr& number) {
        unsigned char* bin_data = nullptr;
        int bin_length = BN_num_bytes(number.get());
        bin_data = new unsigned char[bin_length];
        BN_bn2bin(number.get(), bin_data);

        std::string binary_string(reinterpret_cast<char*>(bin_data), bin_length);
        delete[] bin_data;

        return base64_encode(binary_string);
    }

    std::string base64_encode(const std::string& input) {
        BIO* bio = BIO_new(BIO_s_mem());
        BIO* b64 = BIO_new(BIO_f_base64());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
        BIO_write(bio, input.data(), input.size());
        BIO_flush(bio);

        char* encoded_data;
        long len = BIO_get_mem_data(bio, &encoded_data);

        std::string result(encoded_data, len);
        BIO_free_all(bio);
        return result;
    }

    void print_rsa_keys(const RSA_APP::KeyPair& key_pair) {
        std::cout << "-----BEGIN PUBLIC KEY-----\n";
        std::string public_key = format_big_number(key_pair.public_key.n) + format_big_number(key_pair.public_key.e);
        std::cout << public_key << "\n-----END PUBLIC KEY-----\n";

        std::cout << "-----BEGIN PRIVATE KEY-----\n";
        std::string private_key = format_big_number(key_pair.private_key.n) + format_big_number(key_pair.private_key.d);
        std::cout << private_key << "\n-----END PRIVATE KEY-----\n";
    }

}  // namespace RSA_APP