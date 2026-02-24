#include <iostream>
#include <print>

#include "crypto/rsa.h"
#include "passwordManager.h"
#include "test.h"
using namespace std;

int passwordManagerTest() {
    /* Testing */
    PasswordManager passwords = PasswordManager("passwords.json");

    Password google = Password("Google", "Victor", "agent?3");
    Password x = Password("X.com", "Neel", "Walse");

    passwords.addPassword(google);
    passwords.addPassword(x);

    cout << passwords.view() << endl;

    passwords.removePassword(google);
    passwords.removePassword(x);

    cout << passwords.view() << endl;

    return 0;
}

int rsaDebugTest() {
    RSA rsa = RSA();

    // Test different message lengths
    vector<string> test_messages = {
            "CheggSack",         // Single character
            "Hello",             // Short message
            "Hello, World! 123"  // Longer message with special chars
    };

    for (const auto& message : test_messages) {
        cout << "\nTesting message: \"" << message << "\"\n";
        cout << "Message length: " << message.length() << "\n";

        try {
            // Encrypt
            string encrypted = rsa.encrypt(message);
            cout << "Encrypted (space-separated blocks): " << encrypted << "\n";

            // Decrypt
            string decrypted = rsa.decrypt(encrypted);
            cout << "Decrypted: \"" << decrypted << "\"\n";

            // Verify
            if (message == decrypted) {
                cout << "✓ Test passed - successful encryption/decryption\n";
            } else {
                cout << "✗ Test failed - decrypted message doesn't match "
                        "original\n";
            }

        } catch (const exception& e) {
            cout << "✗ Test failed with error: " << e.what() << "\n";
        }
    }

    return 0;
}
