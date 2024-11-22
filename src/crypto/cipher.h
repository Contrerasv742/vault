#ifndef CIPHER_H
#define CIPHER_H

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


// TODO: Created in own file
std::string rsa(const std::string &plaintext, const std::string &shift);

#endif  // CIPHER_H
