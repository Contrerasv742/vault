#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string caesar(const std::string& plaintext);

std::string vigenere(const std::string& plaintext); 

std::string rot13(const std::string& plaintext);

int encrypt();

int decrypt();

#endif // ENCRYPTION_H
