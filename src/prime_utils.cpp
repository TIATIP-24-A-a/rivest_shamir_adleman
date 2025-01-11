#include "prime_utils.h"
#include <cmath>

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

}  // namespace PrimeUtils
