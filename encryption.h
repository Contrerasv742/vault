#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

// Helper Methods
uint32_t generate_random(uint32_t min, uint32_t max);

int encrypt();

int decrypt();

// Encryption Algorithms
std::string caesar(const std::string& plaintext);

std::string vigenere(const std::string& plaintext); 

std::string rot13(const std::string& plaintext);

std::string rsa(const std::string& plaintext);

#endif // ENCRYPTION_H
