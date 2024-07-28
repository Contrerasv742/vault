#include "encryption.h"
#include "main.h"

int decrypt() {
  std::string cipher = get_cipher();

  return 0; 
}

int encrypt() {
  std::string cipher = get_cipher();

  // Example usage
  std::string plaintext = "Hello, World!";
  std::string key = "secretkey";
  std::cout << cipher << ": " << cipherOptable[cipher](plaintext, key);

  return 0; 
}

std::string caesar(const std::string& plaintext, const std::string& key) {

  return "Caesar: " + plaintext + " (key: " + key + ")\n";
}

std::string vigenere(const std::string& plaintext, const std::string& key) {
  return "Vigenere: " + plaintext + " (key: " + key + ")\n";
}

std::string rot13(const std::string& plaintext, const std::string& key) {
  return "ROT13: " + plaintext + " (key: " + key + ")\n";
}
