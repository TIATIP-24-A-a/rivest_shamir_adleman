#ifndef RSA_H_
#define RSA_H_
#include <string>

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
     *   message: The message to encrypt.
     *   public_key: The RSA public key.
     * Returns:
     *   The encrypted message (ciphertext).
     */
    int Encrypt(int message, const PublicKey& public_key);

    /* Decrypts a ciphertext using the RSA private key.
     *
     * Args:
     *   ciphertext: The encrypted message to decrypt.
     *   private_key: The RSA private key.
     * Returns:
     *   The decrypted message (plaintext).
     */
    int Decrypt(int ciphertext, const PrivateKey& private_key);

    /* Converts a string to an integer representation.
     *
     * Args:
     *   message: The string message to convert.
     * Returns:
     *   The integer representation of the string.
     */
    long long StringToInt(const std::string& message);

}  // namespace RSA

#endif  // RSA_H_
