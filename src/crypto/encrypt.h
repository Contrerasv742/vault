#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <sodium.h>
#include <cstddef>

struct encrypted_data_t {
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    size_t ciphertext_len;
    unsigned char *ciphertext;
};

int derive_key(const char *password, const unsigned char *salt, 
               unsigned char *key);

int encrypt(const char *data, const char *password,
                 encrypted_data_t *output);

char *decrypt(const encrypted_data_t *input, const char *password);

#endif // ENCRYPT_H
