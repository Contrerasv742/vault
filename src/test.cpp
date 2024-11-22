#include <iostream>

#include "test.h"
#include "cipher.h"
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
    std::string output = rsa("","");
    std::cout << output << std::endl;

    std::string message = "Hello";
    uint64_t e = 65537;  // public exponent
    uint64_t d = 18446744073709551615;
    uint64_t n = 22244133162893;
    
    try {
        // Encrypt
        std::string encrypted = rsa_encrypt(e, n, message);
        std::cout << "Encrypted: " << encrypted << std::endl;
        
        // Decrypt
        std::string decrypted = rsa_decrypt(d, n, encrypted);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
