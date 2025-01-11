#include "rsa.h"
#include "prime_utils.h"
#include <stdexcept>
#include <numeric>
#include <sstream>

namespace RSA {

/* Helper function for modular exponentiation.
 *
 * Efficiently computes (base^exponent) % modulus using the
 * method of exponentiation by squaring.
 *
 * Args:
 *   base: The base number.
 *   exponent: The exponent.
 *   modulus: The modulus.
 * Returns:
 *   The result of (base^exponent) % modulus.
 */
    int ModularExponentiation(int base, int exponent, int modulus) {
        int result = 1;
        base = base % modulus;
        while (exponent > 0) {
            if (exponent % 2 == 1) {  // If the exponent is odd
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1;  // Divide the exponent by 2
            base = (base * base) % modulus;  // Square the base
        }
        return result;
    }

    KeyPair GenerateKeyPair(int min, int max) {
        // Generate the first prime number (p).
        int p = PrimeUtils::GeneratePrime(min, max);

        // Generate the second prime number (q), ensuring it is distinct from p.
        int q = PrimeUtils::GeneratePrime(min, max);
        while (q == p) {
            q = PrimeUtils::GeneratePrime(min, max);
        }

        // Compute modulus (n) and Euler's totient (phi_n).
        int n = p * q;
        int phi_n = (p - 1) * (q - 1);

        // Choose a public exponent (e) such that gcd(e, phi_n) = 1.
        int e = 3;  // Start with a small odd number.
        while (std::gcd(e, phi_n) != 1) {
            e += 2;  // Increment by 2 to ensure e remains odd.
        }

        // Compute the private exponent (d) as the modular inverse of e mod phi_n.
        int d = 1;  // Start searching for d.
        while ((e * d) % phi_n != 1) {
            d++;
        }

        // Construct and return the RSA key pair.
        return {
                {n, e},  // PublicKey: {modulus, public exponent}
                {n, d}   // PrivateKey: {modulus, private exponent}
        };
    }

/* Encrypts a message using the RSA public key.
 *
 * Args:
 *   message: The message to encrypt.
 *   public_key: The RSA public key.
 * Returns:
 *   The encrypted message (ciphertext).
 */
    int Encrypt(int message, const PublicKey& public_key) {
        return ModularExponentiation(message, public_key.e, public_key.n);
    }

/* Decrypts a ciphertext using the RSA private key.
 *
 * Args:
 *   ciphertext: The encrypted message to decrypt.
 *   private_key: The RSA private key.
 * Returns:
 *   The decrypted message (plaintext).
 */
    int Decrypt(int ciphertext, const PrivateKey& private_key) {
        return ModularExponentiation(ciphertext, private_key.d, private_key.n);
    }

/* Converts a string to an integer representation by concatenating ASCII values.
 *
 * Args:
 *   message: The string message to convert.
 * Returns:
 *   The integer representation of the string.
 */
    std::string StringToInt(const std::string& message) {
        std::string result;
        for (char c : message) {
            result += std::to_string(static_cast<int>(c)); /* Convert each character to ASCII and concatenate. */
        }
        return result; /* Return the concatenated ASCII values as a string. */
    }

/* Converts a concatenated ASCII string representation back to the original string.
 *
 * Args:
 *   ascii_representation: The concatenated ASCII values as a string.
 * Returns:
 *   The original string message.
 */
    std::string IntToString(const std::string& ascii_representation) {
        std::string result;
        for (size_t i = 0; i < ascii_representation.length(); i += 3) {
            /* Extract a substring of 3 characters (one ASCII value). */
            std::string ascii_str = ascii_representation.substr(i, 3);

            /* Convert the substring to a character. */
            char c = static_cast<char>(std::stoi(ascii_str));

            /* Append the character to the result string. */
            result.push_back(c);
        }
        return result;
    }

}  // namespace RSA
