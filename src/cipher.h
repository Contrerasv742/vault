#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

// Helper Template
template <typename T>
class ExtendedVector : public std::vector<T> {
public:
    using std::vector<T>::vector;
    bool find(const T &value) const {
        return std::find(this->begin(), this->end(), value) != this->end();
    }
};

using CipherFunction =
        std::function<std::string(const std::string &, const std::string &)>;

extern std::unordered_map<std::string, CipherFunction> cipherOptable;

extern ExtendedVector<std::string> commands;

// Helper Methods
bool prime(uint32_t num);

uint32_t generate_random_prime(uint32_t min, uint32_t max);

int encrypt();

int decrypt();

// Encryption Algorithms
/* @param plaintext     mesage to encrypt
 * @param key           shift value
 * @algorithm:
 *     shifts plaintext (key) number of times
 * @return encrypted message
 * */
std::string caesar(const std::string &plaintext, const std::string &shift);

/* @param plaintext mesage to encrypt
 * @param key       string converted to rotation values
 * @algorithm:
 *      uses key to generate a shift (similar to caesar)
 * @return encrypted message
 * */
std::string vigenere(const std::string &plaintext, const std::string &key);

// Encryption Algorithms
/* @param plaintext     mesage to encrypt
 * @param key           (Unused)
 * @algorithm:
 *      cesar cypher with shift = 13
 * @return encrypted message
 * */
std::string rot13(const std::string &plaintext, const std::string &unused);

/* @param plaintext (unused)
 * @param key (unused)
 * @algorithm:
 *      generate two keys:
 *          public key: shown
 *          private key: verifies if the public correct
 *      TODO: Continue algorithm...
 * @return string (unused)
 * */
std::string rsa(const std::string &plaintext, const std::string &key);

// RSA Helper Functions

/* @param lamba_n
 * @algorithm:
 *      (1 < e < lambda_n) && (gcd(e,lambda_n) == 1)
 * @return e
 * */
uint64_t find_e(uint64_t lambda_n);

std::string rsa_encrypt(uint64_t e, uint64_t n, const std::string& msg); 

std::string rsa_decrypt(uint64_t d, uint64_t n, const std::string& encrypted_msg); 

#endif  // ENCRYPTION_H
