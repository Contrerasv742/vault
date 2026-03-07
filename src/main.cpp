#include <sodium.h>
#include <cstdlib>
#include <iostream>
#include <print>
#include "crypto/encrypt.h"
#include "passwordManager.h"

using namespace std;

int example() {
    if (sodium_init() < 0) {
        print("Failed to initialize libsodium\n");
        return 1;
    }

    const char *password = "my_master_password";
    const char *json = "{\"passwords\": [{\"site\": \"example.com\"}]}";

    encrypted_data_t encrypted;

    // Encrypt
    if (encrypt(json, password, &encrypted) != 0) {
        print("Encryption failed\n");
        return 1;
    }

    print("Encrypted successfully\n");
    cout << "Encrypted Data:\n\t{}" << encrypted.ciphertext << std::endl;

    // Decrypt
    char *decrypted = decrypt(&encrypted, password);
    if (decrypted) {
        print("Decrypted: {}\n", decrypted);
        free(decrypted);
    } else {
        print("Decryption failed\n");
    }

    free(encrypted.ciphertext);
    return 0;
}

int main(void) {
    if (sodium_init() < 0) {
        print("Failed to initialize libsodium\n");
        return 1;
    }

    const char *password = "my_master_password";

    PasswordManager pm{"password.json"};
    Password amazon{"amazon", "goofy", "pants"};

    pm.addPassword(amazon);
}
