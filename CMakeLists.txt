cmake_minimum_required(VERSION 3.10)
project(RSAAlgorithm)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Source files
set(SOURCE_FILES
        src/main.cpp
        src/prime_utils.cpp
)

# Add the main program executable
add_executable(rsa_program ${SOURCE_FILES})

# Test files
set(TEST_FILES
        tests/rsa_test.cpp
        src/prime_utils.cpp  # Include the implementation for testing
)

# Add test executable
add_executable(rsa_tests ${TEST_FILES})

# Enable testing
enable_testing()
add_test(NAME RSAUnitTests COMMAND rsa_tests)
