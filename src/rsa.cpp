#include "rsa.h"
#include "prime_utils.h"
#include <stdexcept>
#include <numeric>
#include <sstream>

namespace RSA_APP {

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
 * Encrypts the given BigNumber message using the RSA public key.
 * The encryption formula is:
 *     ciphertext = (message^e) % n
 *
 * Args:
 *   message: The BigNumber message to encrypt.
 *   public_key: The RSA public key containing modulus (n) and exponent (e).
 * Returns:
 *   The encrypted message as a BigNumber.
 */
    BigNumber RSA::Encrypt(const BigNumber& message, const PublicKey& public_key) {
        // Current implementation might be using too large numbers
        // Consider adding size checks:
        if (message >= BigNumber(std::to_string(public_key.n))) {
            throw std::invalid_argument("Message is too large for the given key size");
        }

        BigNumber base = message;
        BigNumber exp(public_key.e);
        BigNumber mod(public_key.n);

        return base.ModularExponentiation(exp, mod);
    }

/* Decrypts a ciphertext using the RSA private key.
 *
 * Decrypts the given BigNumber ciphertext using the RSA private key.
 * The decryption formula is:
 *     plaintext = (ciphertext^d) % n
 *
 * Args:
 *   ciphertext: The BigNumber ciphertext to decrypt.
 *   private_key: The RSA private key containing modulus (n) and exponent (d).
 * Returns:
 *   The decrypted message as a BigNumber.
 */
    BigNumber Decrypt(const BigNumber& ciphertext, const PrivateKey& private_key) {
        BigNumber base = ciphertext;
        BigNumber exp(private_key.d);
        BigNumber mod(private_key.n);

        return base.ModularExponentiation(exp, mod);
    }

/* Converts a string to a BigNumber representation.
 *
 * Each character in the string is converted to its ASCII value and concatenated.
 * The resulting BigNumber represents the entire string as a large number.
 *
 * Args:
 *   message: The string message to convert.
 * Returns:
 *   A BigNumber representing the ASCII values of the string.
 */
    BigNumber StringToBigNumber(const std::string& message) {
        BigNumber result("0");  // Initialize the result as zero.
        BigNumber multiplier("1");  // Start with a multiplier of 1.

        for (auto it = message.rbegin(); it != message.rend(); ++it) {
            /* Convert character to its ASCII value as a BigNumber. */
            BigNumber ascii_value(static_cast<int>(*it));

            /* Add ASCII value multiplied by the current multiplier to the result. */
            result = result.Add(ascii_value.Multiply(multiplier));

            /* Update the multiplier to the next power of 1000. */
            multiplier = multiplier.Multiply(BigNumber("1000"));
        }

        return result;  // Return the BigNumber representation.
    }

/* Converts a BigNumber back to the original string representation.
 *
 * The BigNumber is interpreted as concatenated ASCII values.
 * Each ASCII value is converted back into its corresponding character to reconstruct the string.
 *
 * Args:
 *   big_number: The BigNumber representing the ASCII values of the string.
 * Returns:
 *   The original string message.
 */
    std::string BigNumberToString(const BigNumber& big_number) {
        BigNumber remaining = big_number;  // Create a copy to process.
        std::string result;

        const BigNumber divisor("1000");  // Divisor to extract ASCII values.

        while (remaining > BigNumber("0")) {
            /* Extract the last 3-digit ASCII value using modulo operation. */
            BigNumber ascii_value = remaining.Modulo(divisor);

            /* Convert the ASCII value to a character. */
            char character = static_cast<char>(ascii_value.ToInt());

            /* Prepend the character to the result string. */
            result.insert(result.begin(), character);

            /* Remove the extracted ASCII value from the number. */
            remaining = remaining.Divide(divisor);
        }

        return result;  // Return the reconstructed string.
    }

}  // namespace RSA_APP
