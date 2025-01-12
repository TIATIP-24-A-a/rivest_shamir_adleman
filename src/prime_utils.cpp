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
            BigNumber candidate(random.GetRange(min.ToInt(), max.ToInt()));
            if (IsPrime(candidate)) {
                return candidate;
            }
        }
    }
} // namespace PrimeUtils
