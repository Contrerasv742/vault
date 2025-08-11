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

    print("{}", passwords.view()); 

    passwords.removePassword(google);
    passwords.removePassword(x);

    println("{}", passwords.view()); 

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
        println("\nTesting message: \"{}\"\n", message) ;
        println("Message length: {}", message.length());

        try {
            // Encrypt
            string encrypted = rsa.encrypt(message);
            println("Encrypted (space-separated blocks): {}", encrypted);

            // Decrypt
            string decrypted = rsa.decrypt(encrypted);
            println("Decrypted: \"{}\"", decrypted); 

            // Verify
            if (message == decrypted) {
                println("✓ Test passed - successful encryption/decryption");
            } else {
                println("✗ Test failed - decrypted message doesn't match original");
            }

        } catch (const exception& e) {
            println("✗ Test failed with error: {}", e.what()); 
        }
    }

    return 0;
}
