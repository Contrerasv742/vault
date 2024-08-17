#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <unordered_map>
#include <functional> 

// Helper Template
template<typename T>
class ExtendedVector : public std::vector<T> {
public:
    using std::vector<T>::vector;
    bool find(const T& value) const {
        return std::find(this->begin(), this->end(), value) != this->end();
    }
};

// Update CipherFunction to accept two parameters
using CipherFunction = std::function<std::string(const std::string&, const std::string&)>;

extern std::unordered_map<std::string, CipherFunction> cipherOptable;
extern ExtendedVector<std::string> commands;

// Helper Methods
bool prime(uint32_t num);

uint32_t generate_random_prime(uint32_t min, uint32_t max);

int encrypt();

int decrypt();

// Encryption Algorithms
std::string caesar(const std::string& plaintext, const std::string& shift);

std::string vigenere(const std::string& plaintext, const std::string& key); 

std::string rot13(const std::string& plaintext, const std::string& unused);

std::string rsa(const std::string& plaintext, const std::string& key);

#endif // ENCRYPTION_H
