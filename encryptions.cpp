#include "encryption.h"

std::string caesar(const std::string& plaintext, const std::string& key) {

  return "Caesar: " + plaintext + " (key: " + key + ")";
}

std::string vigenere(const std::string& plaintext, const std::string& key) {
  return "Vigenere: " + plaintext + " (key: " + key + ")";
}

std::string rot13(const std::string& plaintext, const std::string& key) {
  return "ROT13: " + plaintext + " (key: " + key + ")";
}
