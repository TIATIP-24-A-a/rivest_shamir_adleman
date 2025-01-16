#include "rsa.h"
#include <iostream>
#include <string>

/**
 * Main function demonstrating RSA encryption and decryption.
 *
 * This program:
 * 1. Generates an RSA key pair (public and private keys).
 * 2. Accepts a user-input message for encryption.
 * 3. Converts the message into a BigNumber representation.
 * 4. Encrypts the message using the RSA public key.
 * 5. Decrypts the message using the RSA private key.
 * 6. Converts the decrypted message back to its original format.
 * 7. Verifies that the decrypted message matches the original message.
 */
int main() {
    try {
        // Step 1: Generate RSA keys
        std::cout << "Generating RSA keys...\n";
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(4096);

        std::cout << "\nGenerated RSA Keys:\n";
        print_rsa_keys(key_pair);

        // Step 2: Accept user input for the message to encrypt
        std::string message;
        std::cout << "\nEnter a message to encrypt: ";
        std::getline(std::cin, message);

        // Step 3: Convert the input message to a BigNumber representation
        BN_ptr number_message = RSA_APP::string_to_number(message);
        std::cout << "Message as BigNumber: " << number_message.to_string() << "\n";

        // Step 4: Encrypt the BigNumber message using the public key
        BN_ptr encrypted_message = RSA_APP::encrypt(number_message, key_pair.public_key);
        std::cout << "Encrypted Message: " << encrypted_message.to_string() << "\n";

        // Step 5: Decrypt the encrypted BigNumber message using the private key
        BN_ptr decrypted_message = RSA_APP::decrypt(encrypted_message, key_pair.private_key);
        std::cout << "Decrypted BigNumber: " << decrypted_message.to_string() << "\n";

        // Step 6: Convert the decrypted BigNumber back to the original string
        std::string decrypted_text = RSA_APP::number_to_string(decrypted_message);
        std::cout << "Decrypted Message (original): " << decrypted_text << "\n";

        // Step 7: Verify that the encrypted and decrypted process was successful
        if (decrypted_text == message) {
            std::cout << "\nEncryption and decryption succeeded!\n";
        } else {
            std::cout << "\nEncryption and decryption failed. Something went wrong!\n";
        }
    } catch (const std::exception& e) {
        // Handle any errors that occurred during the RSA operations
        std::cerr << "An error occurred: " << e.what() << "\n";
    } catch (...) {
        // Handle unexpected errors
        std::cerr << "An unknown error occurred.\n";
    }

    return 0;
}