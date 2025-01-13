#include "rsa.h"
#include <iostream>
#include <string>

/* Main function to demonstrate RSA encryption and decryption.
 *
 * This program:
 * 1. Generates RSA keys.
 * 2. Accepts a user input message.
 * 3. Converts the message to a BigNumber.
 * 4. Encrypts the message using the public key.
 * 5. Decrypts the message using the private key.
 * 6. Verifies the decrypted message matches the original.
 */
int main() {
    try {
        // Step 1: Generate RSA keys
        std::cout << "Generating RSA keys...\n";
        RSA_APP::KeyPair key_pair = RSA_APP::generate_key_pair(2096);

        // Step 2: Input a message
        std::string message;
        std::cout << "\nEnter a message to encrypt: ";
        std::getline(std::cin, message);

        // Step 3: Convert the message to a BigNumber
        BN_ptr number_message = RSA_APP::string_to_number(message);
        std::cout << "Message as BigNumber: " << number_message.get_word() << "\n";

        // Step 4: Encrypt the message using the public key
        BN_ptr encrypted_message = RSA_APP::encrypt(number_message, key_pair.public_key);
        std::cout << "Encrypted Message: " << encrypted_message.to_string() << "\n";

        // Step 5: Decrypt the message using the private key
        BN_ptr decrypted_message = RSA_APP::decrypt(encrypted_message, key_pair.private_key);
        std::cout << "Decrypted BigNumber: " << decrypted_message.to_string() << "\n";

        // Step 6: Convert the decrypted BigNumber back to a string
        std::string decrypted_text = RSA_APP::number_to_string(decrypted_message);
        std::cout << "Decrypted Message (original): " << decrypted_text << "\n";

        // Verify correctness
        if (decrypted_text == message) {
            std::cout << "\nEncryption and decryption succeeded!\n";
        } else {
            std::cout << "\nEncryption and decryption failed. Something went wrong!\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }

    return 0;
}
