#include "encryption.h"
#include "main.h"
#include <cstdlib>

std::string prompt(std::string msg) {
  std::string var;
  std::cout << "Enter " << msg << ": \n\t";
  std::getline(std::cin >> std::ws, var);
  return var;
}

int decrypt() {
  std::string cipher = prompt("");
  std::string ciphertext = prompt("the encrypted message");
  std::string key = prompt("the key");

  // Assuming the cipher functions can handle both encryption and decryption
  std::string decryption = cipherOptable[cipher](ciphertext);
  std::cout << "Decryption: " << decryption << "\n\n";
  return 0;
}

int encrypt() {
  std::string cipher;
  while (true) {
    cipher = prompt("a cipher");

    // Validating Cipher
    if (cipher.empty() || cipherOptable.find(cipher) == cipherOptable.end()) {
      std::cerr << "Invalid Cipher" << std::endl;
      print_ciphers();
      continue;
    }
    break;
  }

  // Getting Variables
  std::string plaintext = prompt("a message");

  // Encrypting
  std::string encryption = cipherOptable[cipher](plaintext);
  std::cout << "Encryption: " << encryption << std::endl; 

  return 0; 
}

std::string caesar(const std::string& plaintext) {
  std::string key = prompt("a shift value");

  int rotation;

  try {
    rotation = std::stoi(key); 
  } catch (const std::exception& e) {
    std::cerr << "Invalid input. Using shift value of 0." << std::endl;
    rotation = 0;
  }

  std::string encryption = "";

  for (char c : plaintext) {
    if (std::isalpha(c)) {
      char base = std::isupper(c) ? 'A' : 'a';
      char shifted = static_cast<char>((c - base + rotation) % 26 + base);
      encryption += shifted;
    } else {
      encryption += c;
    }
  }

  return encryption;
}

std::string vigenere(const std::string& plaintext) {
  std::string key = prompt("a key");
  std::string encryption = "";

  for (size_t i = 0; i < plaintext.length(); i++) {
    char c = plaintext[i];
    int rotation = static_cast<int>(key[i % key.length()]);

    if (std::isalpha(c)) {
      char base = std::isupper(c) ? 'A' : 'a';
      char shifted = static_cast<char>((c + rotation) % 26 + base);
      encryption += shifted;
    } else {
      encryption += c;
    }
  }

  return encryption;
}

std::string rot13(const std::string& plaintext) {
  std::string key = prompt("a key");
  return "ROT13: " + plaintext + " (key: " + key + ")\n\n";
}
