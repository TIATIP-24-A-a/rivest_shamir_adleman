#include "rsa.h"
#include "prime_utils.h"
#include <stdexcept>
#include <numeric>  // For std::gcd

namespace RSA {

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

}  // namespace RSA
