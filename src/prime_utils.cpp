#include "prime_utils.h"
#include <cmath>
#include <stdexcept>

namespace PrimeUtils {

    bool IsPrime(int number) {
        if (number < 2) {
            return false;
        }
        for (int i = 2; i <= std::sqrt(number); ++i) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }

    int GeneratePrime(int min, int max) {
        if (min > max || min < 2) {
            throw std::invalid_argument("Invalid range for prime generation.");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(min, max);

        while (true) {
            int candidate = dist(gen);
            if (IsPrime(candidate)) {
                return candidate;
            }
        }
    }

}  // namespace PrimeUtils
