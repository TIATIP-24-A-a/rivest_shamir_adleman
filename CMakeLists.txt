cmake_minimum_required(VERSION 3.10)
project(RSAAlgorithm)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Main program executable
add_executable(rsa_program
        src/main.cpp
        src/prime_utils.cpp
        src/rsa.cpp
        src/big_number.cpp
        src/secure_random.h
)

# Test executable
add_executable(rsa_tests
        test/rsa_test.cpp
        src/prime_utils.cpp
        src/rsa.cpp
        src/big_number.cpp
)

# Test executable
add_executable(prime_tests
        test/prime_utils_test.cpp
        src/prime_utils.cpp
        src/big_number.cpp
)

# Test executable
add_executable(big_number_tests
        test/big_number_test.cpp
        src/big_number.cpp
)

# Test executable
add_executable(secure_random_tests
        test/secure_random_test.cpp
        src/secure_random.cpp
)

# Enable testing
enable_testing()
add_test(NAME RSAUnitTests COMMAND rsa_tests)
