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
)

# Test executable
add_executable(rsa_tests
        test/rsa_test.cpp
        src/prime_utils.cpp
        src/rsa.cpp
        src/big_number.cpp
)

# Enable testing
enable_testing()
add_test(NAME RSAUnitTests COMMAND rsa_tests)
