#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string caesar(const std::string& plaintext, const std::string& key);

std::string vigenere(const std::string& plaintext, const std::string& key); 

std::string rot13(const std::string& plaintext, const std::string& key);

int encrypt();

int decrypt();

#endif // ENCRYPTION_H
