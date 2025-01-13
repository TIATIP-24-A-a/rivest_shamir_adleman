/*
 *
 *
 * FOR EDUCATIONAL PURPOSES ONLY
 *
 *
 *
 */
#include "prime_utils.h"
#include <cmath>

#include "secure_random.h"

namespace PrimeUtils
{
    bool IsPrime(const BigNumber& n)
    {
        if (n <= BigNumber("1")) return false;
        if (n <= BigNumber("3")) return true;

        // Write n-1 as d * 2^r
        BigNumber d = n - BigNumber("1");
        int r = 0;
        while ((d % BigNumber("2")) == BigNumber("0"))
        {
            d = d.Divide(BigNumber("2"));
            r++;
        }

        std::vector<BigNumber> bases = {
            BigNumber("2"), BigNumber("3"), BigNumber("5"),
            BigNumber("7"), BigNumber("11"), BigNumber("13")
        };

        for (const BigNumber& a : bases)
        {
            if (a >= n - BigNumber("1")) continue;

            BigNumber x = a.ModularExponentiation(d, n);
            if (x == BigNumber("1") || x == n - BigNumber("1")) continue;

            bool might_be_prime = false;
            for (int j = 0; j < r - 1; j++)
            {
                x = x.ModularExponentiation(BigNumber("2"), n);
                if (x == n - BigNumber("1"))
                {
                    might_be_prime = true;
                    break;
                }
            }

            if (!might_be_prime) return false;
        }

        return true;
    }

    BigNumber GeneratePrime(const BigNumber& min, const BigNumber& max) {
        if (min > max || min < BigNumber("2")) {
            throw std::invalid_argument("Invalid range for prime generation");
        }

        SecureRandom random;
        while (true) {
            BigNumber candidate = random.GetBigNumberRange(min, max);
            if (IsPrime(candidate)) {
                return candidate;
            }
        }
    }

    BigNumber GeneratePrimeWithBitLength(int bitLength) {
        if (bitLength < 8) {
            throw std::invalid_argument("Bit length too small");
        }

        BigNumber two("2");
        // min = 2^(bitLength - 1)
        BigNumber min = two.Pow(bitLength - 1);
        // max = 2^bitLength - 1
        BigNumber max = two.Pow(bitLength).Subtract(BigNumber("1"));

        return GeneratePrime(min, max);
    }

    bool IsRSASafe(const BigNumber& prime) {
        // Check if (p-1)/2 is prime (strong prime condition)
        return IsPrime((prime - BigNumber("1")) / BigNumber("2"));
    }

    BigNumber GenerateRSASafePrime(int bitLength) {
        if (bitLength < 512) {  // Enforce minimum security
            throw std::invalid_argument("Bit length too small for RSA");
        }

        BigNumber min = BigNumber("2").ModularExponentiation(BigNumber(std::to_string(bitLength - 1)), BigNumber("1"));
        BigNumber max = BigNumber("2").ModularExponentiation(BigNumber(std::to_string(bitLength)), BigNumber("1")) - BigNumber("1");

        SecureRandom random;
        while (true) {
            BigNumber q = GeneratePrime(min / BigNumber("2"), max / BigNumber("2"));
            BigNumber p = q * BigNumber("2") + BigNumber("1");
            if (IsPrime(p) && p <= max) {
                return p;
            }
        }
    }

    bool PrimeUtils::IsPrimeOpenSSL(const BIGNUM* n) {
        BN_CTX* ctx = BN_CTX_new();
        int result = BN_is_prime_ex(const_cast<BIGNUM*>(n), BN_prime_checks, ctx, nullptr);
        BN_CTX_free(ctx);
        return result == 1;
    }
} // namespace PrimeUtils
