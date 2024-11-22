#include <iostream>

#include "test.h"
#include "crypto/rsa.h"
#include "passwordManager.h"

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

int rsaTest() {
    RSA rsa = RSA();

    std::string message = "Hello";
    // cpp_int e = 65537;
    // cpp_int d = 18446744073709551615;
    // cpp_int n = 22244133162893;
    
    try {
        // Encrypt
        std::string encrypted = rsa.rsa_encrypt(message);
        std::cout << "Encrypted: " << encrypted << std::endl;
        
        // Decrypt
        std::string decrypted = rsa.rsa_decrypt(encrypted);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
