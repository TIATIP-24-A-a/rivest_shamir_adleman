cmake_minimum_required(VERSION 3.10)
project(RSAAlgorithm)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

    # Force OpenSSL paths
    set(OPENSSL_ROOT_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows")
    set(OPENSSL_USE_STATIC_LIBS TRUE)
    set(OPENSSL_MSVC_STATIC_RT TRUE)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenSSL BEFORE creating targets
find_package(OpenSSL REQUIRED)

# Include directories
include_directories(src)

# Main program executable
add_executable(rsa_program
        src/main.cpp
        src/prime_utils.cpp
        src/rsa.cpp
        src/big_number.cpp
        src/secure_random.h
        src/secure_random.cpp
        src/bn_wrapper.cpp
        src/bn_wrapper.h
)

# Link OpenSSL to all executables that need it
target_link_libraries(rsa_program PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Test executable
add_executable(rsa_tests
        test/rsa_test.cpp
        src/rsa.cpp
        src/bn_wrapper.cpp
)
target_link_libraries(rsa_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Test executable
add_executable(prime_tests
        test/prime_utils_test.cpp
        src/prime_utils.cpp
        src/big_number.cpp
        src/secure_random.cpp
)
target_link_libraries(prime_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Test executable
add_executable(big_number_tests
        test/big_number_test.cpp
        src/big_number.cpp
)
target_link_libraries(big_number_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Test executable
add_executable(secure_random_tests
        test/secure_random_test.cpp
        src/secure_random.cpp
        src/big_number.cpp
)
target_link_libraries(secure_random_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Test executable
add_executable(bn_wrapper_tests
        test/bn_wrapper_test.cpp
        src/bn_wrapper.cpp
)
target_link_libraries(bn_wrapper_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Enable testing
enable_testing()
add_test(NAME RSAUnitTests COMMAND rsa_tests)
