#include "encryption.h"
#include "main.h"

std::string prompt(std::string msg) {
  std::string var;
  std::cout << "Enter " << msg << ": \n\t";
  std::getline(std::cin >> std::ws, var);
  return var;
}

int decrypt() {
  std::string cipher = get_cipher();
  std::string ciphertext = prompt("the encrypted message");
  std::string key = prompt("the key");

  // Assuming the cipher functions can handle both encryption and decryption
  std::string decryption = cipherOptable[cipher](ciphertext, key);
  std::cout << "Decryption: " << decryption << std::endl;
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
  std::string key = prompt("a key");

  // Encrypting
  std::string encryption = cipherOptable[cipher](plaintext, key);
  std::cout << "Encryption: " << encryption << std::endl; 

  return 0; 
}

// TODO: Address possible integer overflow
int count(std::string msg) {
  int total = 0;
  for (char c: msg) {
    total += static_cast<char>(c);
  }
  return total;
}

std::string caesar(const std::string& plaintext, const std::string& key) {
  int rotation = count(key) % 26;
  std::string encryption = "";

  for (char c : plaintext) {
    if (std::isalpha(c)) {
      char base = std::isupper(c) ? 'A' : 'a';
      char shifted = static_cast<char>((c - base + rotation) % 26 + base);
      encryption += shifted;
    } else {
      encryption += c;  // Non-alphabetic characters remain unchanged
    }
  }

  return encryption;
}

std::string vigenere(const std::string& plaintext, const std::string& key) {
  std::string encryption = "";
  
  for (int i = 0; i < plaintext.length(); i++) {
    int key_index = i % key.length(); 
    std::string text(1,plaintext[i]);
    std::string k(key[i]);
    encryption += caesar(text, k); 
  }

  return encryption;
}

std::string rot13(const std::string& plaintext, const std::string& key) {
  return "ROT13: " + plaintext + " (key: " + key + ")\n";
}
