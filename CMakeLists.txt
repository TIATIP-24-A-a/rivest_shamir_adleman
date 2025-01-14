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
        src/rsa.cpp
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
add_executable(bn_wrapper_tests
        test/bn_wrapper_test.cpp
        src/bn_wrapper.cpp
)
target_link_libraries(bn_wrapper_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Enable testing
enable_testing()
add_test(NAME RSAUnitTests COMMAND rsa_tests)
