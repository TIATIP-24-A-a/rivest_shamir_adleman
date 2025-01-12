#ifndef RSA_H_
#define RSA_H_
#include <string>
#include "big_number.h"

namespace RSA {

    struct PublicKey {
        int n;  // Modulus
        int e;  // Public exponent
    };

    struct PrivateKey {
        int n;  // Modulus
        int d;  // Private exponent
    };

    struct KeyPair {
        PublicKey public_key;
        PrivateKey private_key;
    };

    KeyPair GenerateKeyPair(int min, int max);

    /* Encrypts a message using the RSA public key.
     *
     * Args:
     *   message: The BigNumber message to encrypt.
     *   public_key: The RSA public key.
     * Returns:
     *   The encrypted message as a BigNumber.
     */
    BigNumber Encrypt(const BigNumber& message, const PublicKey& public_key);

    /* Decrypts a ciphertext using the RSA private key.
     *
     * Args:
     *   ciphertext: The encrypted BigNumber message to decrypt.
     *   private_key: The RSA private key.
     * Returns:
     *   The decrypted message as a BigNumber.
     */
    BigNumber Decrypt(const BigNumber& ciphertext, const PrivateKey& private_key);

    /* Converts a string to a BigNumber representation.
     *
     * Each character of the string is converted to its ASCII value and concatenated.
     *
     * Args:
     *   message: The string message to convert.
     * Returns:
     *   A BigNumber representing the ASCII values of the string.
     */
    BigNumber StringToBigNumber(const std::string& message);

    /* Converts a BigNumber back to the original string representation.
     *
     * The BigNumber is interpreted as concatenated ASCII values, which are converted back to characters.
     *
     * Args:
     *   big_number: The BigNumber representing the ASCII values of the string.
     * Returns:
     *   The original string message.
     */
    std::string BigNumberToString(const BigNumber& big_number);

}  // namespace RSA

#endif  // RSA_H_
