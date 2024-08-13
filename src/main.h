#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional> 
#include <algorithm>
#include <vector> 
#include "encryption.h"

// Helper Template
template<typename T>
class ExtendedVector : public std::vector<T> {
public:
    using std::vector<T>::vector;
    bool find(const T& value) const {
        return std::find(this->begin(), this->end(), value) != this->end();
    }
};

// Update the CipherFunction type to match the encryption.h declarations
using CipherFunction = std::function<std::string(const std::string&)>;

extern std::unordered_map<std::string, CipherFunction> cipherOptable;
extern ExtendedVector<std::string> commands;

// Helper Functions
int process_command(std::string command);

void fatal_error(std::string msg);

void print_commands();

void print_ciphers();

#endif //CIPHER_H
