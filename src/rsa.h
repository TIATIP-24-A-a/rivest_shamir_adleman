#ifndef RSA_H_
#define RSA_H_

namespace RSA {

    /* Represents an RSA public key with modulus and exponent. */
    struct PublicKey {
        int n;  // Modulus
        int e;  // Public exponent
    };

    /* Represents an RSA private key with modulus and private exponent. */
    struct PrivateKey {
        int n;  // Modulus
        int d;  // Private exponent
    };

    /* Represents an RSA key pair, consisting of a public key and a private key. */
    struct KeyPair {
        PublicKey public_key;
        PrivateKey private_key;
    };

    /* Generates an RSA public-private key pair.
     *
     * This function generates two distinct prime numbers (p and q) within the
     * specified range, computes the modulus (n), Euler's totient (phi_n), and
     * finds the public (e) and private (d) exponents.
     *
     * Args:
     *   min: The minimum value for prime generation (inclusive).
     *   max: The maximum value for prime generation (inclusive).
     * Returns:
     *   A KeyPair structure containing the public and private keys.
     * Throws:
     *   std::invalid_argument if the range is invalid or no primes are found.
     */
    KeyPair GenerateKeyPair(int min, int max);

}  // namespace RSA

#endif  // RSA_H_
