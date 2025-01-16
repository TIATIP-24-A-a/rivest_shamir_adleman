#ifndef RSA_H_
#define RSA_H_
#include <string>
#include "bn_wrapper.h"

namespace RSA_APP {
    /* Represents an RSA public key.
   *
   * Members:
   *   n: The RSA modulus, the product of two primes.
   *   e: The public exponent, used for encryption.
   */
    struct PublicKey {
        BN_ptr n;
        BN_ptr e;
    };

    /* Represents an RSA private key.
     *
     * Members:
     *   n: The RSA modulus, identical to the public key modulus.
     *   d: The private exponent, used for decryption.
     */
    struct PrivateKey {
        BN_ptr n;
        BN_ptr d;
    };

    /* Represents a pair of RSA keys.
     *
     * Members:
     *   public_key: The RSA public key.
     *   private_key: The RSA private key.
     */
    struct KeyPair {
        PublicKey public_key;
        PrivateKey private_key;
    };

    /* Generates a public and private key pair for RSA encryption.
    *
    * This function creates an RSA key pair with the specified number of bits.
    * The keys are generated using random prime numbers and are suitable
    * for encryption and decryption.
    *
    * Args:
    *   bits: The number of bits for the RSA modulus (n). Must be a positive integer.
    * Returns:
    *   A KeyPair structure containing the public and private keys.
    * Throws:
    *   std::runtime_error if key generation fails.
    */
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

    /* Encodes a string in Base64 format.
     *
     * Converts the input string into its Base64 representation.
     *
     * Args:
     *   input: The string to be encoded in Base64.
     * Returns:
     *   A Base64-encoded string.
     */
    std::string base64_encode(const std::string& input);

    /* Formats a BigNumber into a human-readable string representation.
     *
     * Converts the BigNumber into a string with appropriate formatting
     * for display or output.
     *
     * Args:
     *   number: The BigNumber to be formatted.
     * Returns:
     *   A string representation of the formatted BigNumber.
     */
    std::string format_big_number(const BN_ptr& number);

    /* Prints the RSA public and private keys to the console.
     *
     * Displays the RSA public and private keys in a formatted and human-readable manner.
     *
     * Args:
     *   key_pair: The RSA KeyPair containing the public and private keys.
     */
    void print_rsa_keys(const KeyPair& key_pair);

}  // namespace RSA_APP

#endif  // RSA_H_
