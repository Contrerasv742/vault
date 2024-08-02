#include "encryption.h"
#include "main.h"
#include <cstdlib>
#include <random>

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
      char shifted = static_cast<char>((c + rotation - base) % 26 + base);
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
      char shifted = static_cast<char>((c + rotation - base) % 26 + base);
      encryption += shifted;
    } else {
      encryption += c;
    }
  }

  return encryption;
}

std::string rot13(const std::string& plaintext) {
  // TODO: Find a way to pass to std::cin after calling to a function
  return caesar(plaintext);
}

uint32_t generate_random(uint32_t min, uint32_t max){
  // Random Number Generator
  std::random_device rd;
  std::mt19937 gen(rd());
  
  // Create a Distribution
  std::uniform_int_distribution<> dis(min, max);

  return dis(gen);
}

std::string rsa(const std::string& plaintext) {
  // I: Calculate two large primes
  uint32_t min = 1000000;
  uint32_t max = min * 10; 

  uint32_t p = generate_random(min, max);
  uint32_t q = generate_random(min, max);
    
  // II: Generate n
  uint32_t n = p * q;

  // III: compute n of Carmichael totient function

  // IV: choose euler number

  // V: determine d

  // Extra: Printing to observe numbers
  std::cout << "p: " << p << "\n";
  std::cout << "q: " << q << "\n";
  std::cout << "n: " << n << "\n";

  return plaintext + "";
}
