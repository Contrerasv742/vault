#include <iostream>

#include "crypto/rsa.h"
#include "passwordManager.h"
#include "test.h"

int passwordManagerTest() {
    /* Testing */
    PasswordManager passwords = PasswordManager("passwords.json");

    Password google = Password("Google", "Victor", "agent?3");
    Password x = Password("X.com", "Neel", "Walse");

    passwords.addPassword(google);
    passwords.addPassword(x);

    std::cout << passwords.view() << std::endl;

    passwords.removePassword(google);
    passwords.removePassword(x);

    std::cout << passwords.view() << std::endl;

    return 0;
}

int rsaDebugTest() {
    RSA rsa = RSA();

    // Test different message lengths
    std::vector<std::string> test_messages = {
            "CheggSack",         // Single character
            "Hello",             // Short message
            "Hello, World! 123"  // Longer message with special chars
    };

    for (const auto& message : test_messages) {
        std::cout << "\nTesting message: \"" << message << "\"\n";
        std::cout << "Message length: " << message.length() << "\n";

        try {
            // Encrypt
            std::string encrypted = rsa.encrypt(message);
            std::cout << "Encrypted (space-separated blocks): " << encrypted
                      << "\n";

            // Decrypt
            std::string decrypted = rsa.decrypt(encrypted);
            std::cout << "Decrypted: \"" << decrypted << "\"\n";

            // Verify
            if (message == decrypted) {
                std::cout
                        << "✓ Test passed - successful encryption/decryption\n";
            } else {
                std::cout << "✗ Test failed - decrypted message doesn't match "
                             "original\n";
            }

        } catch (const std::exception& e) {
            std::cout << "✗ Test failed with error: " << e.what() << "\n";
        }
    }

    return 0;
}
