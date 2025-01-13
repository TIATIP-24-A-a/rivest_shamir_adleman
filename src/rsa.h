#ifndef RSA_H_
#define RSA_H_
#include <string>
#include "bn_wrapper.h"

namespace RSA_APP {

    struct PublicKey {
        BN_ptr n;  // Modulus
        BN_ptr e;  // Public exponent
    };

    struct PrivateKey {
        BN_ptr n;  // Modulus
        BN_ptr d;  // Private exponent
    };

    struct KeyPair {
        PublicKey public_key;
        PrivateKey private_key;
    };

    KeyPair generate_key_pair(int bits);

    /* Encrypts a message using the RSA public key.
     *
     * Args:
     *   message: The BigNumber message to encrypt.
     *   public_key: The RSA public key.
     * Returns:
     *   The encrypted message as a BigNumber.
     */
    BN_ptr encrypt(const BN_ptr& message, const PublicKey& public_key);

    /* Decrypts a ciphertext using the RSA private key.
     *
     * Args:
     *   ciphertext: The encrypted BigNumber message to decrypt.
     *   private_key: The RSA private key.
     * Returns:
     *   The decrypted message as a BigNumber.
     */
    BN_ptr decrypt(const BN_ptr& ciphertext, const PrivateKey& private_key);

    /* Converts a string to a BigNumber representation.
     *
     * Each character of the string is converted to its ASCII value and concatenated.
     *
     * Args:
     *   message: The string message to convert.
     * Returns:
     *   A BigNumber representing the ASCII values of the string.
     */
    BN_ptr string_to_number(const std::string& message);

    /* Converts a BigNumber back to the original string representation.
     *
     * The BigNumber is interpreted as concatenated ASCII values, which are converted back to characters.
     *
     * Args:
     *   big_number: The BigNumber representing the ASCII values of the string.
     * Returns:
     *   The original string message.
     */
    std::string number_to_string(const BN_ptr& number);

    std::string base64_encode(const std::string& input);
    std::string format_big_number(const BN_ptr& number);
    void print_rsa_keys(const KeyPair& key_pair);

}  // namespace RSA_APP

#endif  // RSA_H_
