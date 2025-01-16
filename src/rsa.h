#ifndef RSA_APP_RSA_H_
#define RSA_APP_RSA_H_

#include <string>
#include "bn_wrapper.h"  // Includes the BigNumber class definition.

namespace rsa_app {

/**
 * Represents the RSA public key.
 */
struct PublicKey {
  BigNumber n;  // The modulus used in RSA (part of the public key).
  BigNumber e;  // The public exponent used in RSA.
};

/**
 * Represents the RSA private key.
 */
struct PrivateKey {
  BigNumber n;  // The modulus used in RSA (shared with the public key).
  BigNumber d;  // The private exponent used in RSA.
};

/**
 * Represents a complete RSA key pair.
 *
 * This key pair consists of a public key (for encryption)
 * and a private key (for decryption).
 */
struct KeyPair {
  PublicKey public_key;    // The RSA public key.
  PrivateKey private_key;  // The RSA private key.
};

/**
 * Generates an RSA key pair with the specified bit size.
 *
 * This method generates two large prime numbers `p` and `q`, calculates the
 * modulus `n = p * q`, the totient, and derives the public and private
 * exponents.
 *
 * @param bits The bit size of the RSA modulus (must be a multiple of 2,
 *             minimum 512).
 * @return A `KeyPair` containing the generated public and private keys.
 * @throws std::runtime_error if key generation fails or invalid input is
 *         provided.
 */
KeyPair GenerateKeyPair(int bits);

/**
 * Encrypts a message using the RSA public key.
 *
 * The encryption is performed using the mathematical formula:
 * `ciphertext = (message^e) % n`, where `e` is the public exponent
 * and `n` is the modulus.
 *
 * @param message The input message as a BigNumber to encrypt.
 * @param public_key The `PublicKey` used for encryption.
 * @return The encrypted message as a BigNumber.
 * @throws std::invalid_argument if the message size exceeds the modulus.
 */
BigNumber Encrypt(const BigNumber& message, const PublicKey& public_key);

/**
 * Decrypts a ciphertext using the RSA private key.
 *
 * The decryption is performed using the formula:
 * `plaintext = (ciphertext^d) % n`, where `d` is the private exponent
 * and `n` is the modulus.
 *
 * @param ciphertext The encrypted BigNumber message to decrypt.
 * @param private_key The `PrivateKey` used for decryption.
 * @return The decrypted plaintext message as a BigNumber.
 * @throws std::invalid_argument if the ciphertext size exceeds the modulus.
 */
BigNumber Decrypt(const BigNumber& ciphertext, const PrivateKey& private_key);

/**
 * Converts a string into its BigNumber representation.
 *
 * Each character in the string is converted to its respective ASCII value
 * and concatenated to form a single large number.
 *
 * @param message The input string to convert.
 * @return A BigNumber representing the ASCII values of the string.
 */
BigNumber StringToNumber(const std::string& message);

/**
 * Converts a BigNumber back to its original string representation.
 *
 * The BigNumber is interpreted as a sequence of ASCII values, with
 * each value converted back to its corresponding character.
 *
 * @param number The BigNumber representing the ASCII-encoded string.
 * @return The original string corresponding to the BigNumber input.
 */
std::string NumberToString(const BigNumber& number);

/**
 * Encodes an input string in Base64 format.
 *
 * Converts the input string into its Base64 representation for
 * safe transmission or storage.
 *
 * @param input The input string to encode.
 * @return A string containing the Base64-encoded version of the input.
 */
std::string Base64Encode(const std::string& input);

/**
 * Formats a BigNumber into a human-readable string representation.
 *
 * For example, this function can be used to prepare BigNumbers
 * for display or for exporting to files in applications.
 *
 * @param number The BigNumber to format.
 * @return A human-readable string representing the BigNumber.
 */
std::string FormatBigNumber(const BigNumber& number);

/**
 * Prints the RSA public and private keys to the console.
 *
 * Outputs the components of the public and private keys
 * in a readable format for debugging or demonstration purposes.
 *
 * @param key_pair The RSA key pair containing public and private keys.
 */
void PrintRsaKeys(const KeyPair& key_pair);

}  // namespace rsa_app

#endif  // RSA_APP_RSA_H_