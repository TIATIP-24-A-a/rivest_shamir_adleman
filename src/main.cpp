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
        rsa_app::KeyPair key_pair = rsa_app::GenerateKeyPair(4096);

        std::cout << "\nGenerated RSA Keys:\n";
        rsa_app::PrintRsaKeys(key_pair);

        // Step 2: Accept user input for the message to encrypt
        std::string message;
        std::cout << "\nEnter a message to encrypt: ";
        std::getline(std::cin, message);

        // Step 3: Convert the input message to a BigNumber representation
        BigNumber number_message = rsa_app::StringToNumber(message);
        std::cout << "Message as BigNumber: " << number_message.ToString() << "\n";

        // Step 4: Encrypt the BigNumber message using the public key
        BigNumber encrypted_message = rsa_app::Encrypt(number_message, key_pair.public_key);
        std::cout << "Encrypted Message: " << encrypted_message.ToString() << "\n";

        // Step 5: Decrypt the encrypted BigNumber message using the private key
        BigNumber decrypted_message = rsa_app::Decrypt(encrypted_message, key_pair.private_key);
        std::cout << "Decrypted BigNumber: " << decrypted_message.ToString() << "\n";

        // Step 6: Convert the decrypted BigNumber back to the original string
        std::string decrypted_text = rsa_app::NumberToString(decrypted_message);
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