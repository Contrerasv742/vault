#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional> 
#include <algorithm>
#include <vector> 
#include "encryption.h"

// Optable for Functions
using CipherFunction = std::function<std::string(const std::string&, const std::string&)>;

std::unordered_map<std::string, CipherFunction> cipherOptable = {
  {"caesar", caesar},
  {"vigenere", vigenere},
  {"rot13", rot13}
};

// Helper Variables
template<typename T>
class ExtendedVector : public std::vector<T> {
public:
    // Use the constructors of std::vector
    using std::vector<T>::vector;

    // Add a find method
    bool find(const T& value) const {
        return std::find(this->begin(), this->end(), value) != this->end();
    }
};

ExtendedVector<std::string> options = {"encrypt", "decrypt", "help", "exit", "pericos"};

#endif //CIPHER_H
