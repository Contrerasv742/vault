#include "crypto/encrypt.h"
#include <sodium.h>
#include <cstdlib>
#include <cstring>

int derive_key(const char *password, const unsigned char *salt,
               unsigned char *key) {
    if (crypto_pwhash(key, crypto_secretbox_KEYBYTES, password,
                      strlen(password), salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE,
                      crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        return -1;
    }
    return 0;
}

int encrypt(const char *data, const char *password,
                 encrypted_data_t *output) {
    unsigned char key[crypto_secretbox_KEYBYTES];
    size_t json_len = strlen(data);

    // Generate random salt for key derivation
    randombytes_buf(output->salt, sizeof(output->salt));

    // Derive key from password
    if (derive_key(password, output->salt, key) != 0) {
        return -1;
    }

    // Generate random nonce
    randombytes_buf(output->nonce, sizeof(output->nonce));

    // Allocate space for ciphertext (includes MAC)
    output->ciphertext_len = json_len + crypto_secretbox_MACBYTES;
    output->ciphertext =
            static_cast<unsigned char *>(malloc(output->ciphertext_len));

    if (!output->ciphertext) {
        sodium_memzero(key, sizeof(key));
        return -1;
    }

    // Encrypt
    if (crypto_secretbox_easy(
                output->ciphertext,
                reinterpret_cast<const unsigned char *>(data), json_len,
                output->nonce, key) != 0) {
        free(output->ciphertext);
        sodium_memzero(key, sizeof(key));
        return -1;
    }

    // Clear sensitive data
    sodium_memzero(key, sizeof(key));

    return 0;
}

char *decrypt(const encrypted_data_t *input, const char *password) {
    unsigned char key[crypto_secretbox_KEYBYTES];

    // Derive key from password and stored salt
    if (derive_key(password, input->salt, key) != 0) {
        return nullptr;
    }

    // Allocate space for plaintext
    size_t plaintext_len = input->ciphertext_len - crypto_secretbox_MACBYTES;
    char *data = static_cast<char *>(malloc(plaintext_len + 1));

    if (!data) {
        sodium_memzero(key, sizeof(key));
        return nullptr;
    }

    // Decrypt
    if (crypto_secretbox_open_easy(reinterpret_cast<unsigned char *>(data),
                                   input->ciphertext, input->ciphertext_len,
                                   input->nonce, key) != 0) {
        free(data);
        sodium_memzero(key, sizeof(key));
        return nullptr;
    }

    data[plaintext_len] = '\0';
    sodium_memzero(key, sizeof(key));

    return data;
}
