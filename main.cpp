#include <iostream>
#include <functional> 
#include <string>
#include <unordered_map>
#include "encryption.h"
#include <vector> 

using CipherFunction = std::function<std::string(const std::string&, const std::string&)>;

std::unordered_map<std::string, CipherFunction> cipherOptable = {
  {"caesar", caesar},
  {"vigenere", vigenere},
  {"rot13", rot13}
};


std::vector<std::string> options = {"encrypt", "decrypt", "help", "exit"};

void help() {
  std::cout << "Options: " << std::endl; 
  for (auto command: options) {
    std::cout << "\t+ " << command << std::endl;
  }
}

// TODO: 
//  Make the Main function cleaner
//  Implement Encryption prompts
//  Manage Encryptions in a local file
int main() {
  std::cout << "Hello how can I help you today?" << std::endl; 
  
  help();
  return 0; 

  // Main Loop
  while (true) {
    // Doing command
    std::string option;
    std::cin >> option; 

    std::string cipher;
    std::cout << "Enter your cipher: ";
    std::cin >> cipher;

    if (cipher.empty() || cipherOptable.find(cipher) == cipherOptable.end()) {
      std::cerr << "Invalid Cipher" << std::endl;
      return 1;
    }

    // Example usage
    std::string plaintext = "Hello, World!";
    std::string key = "secretkey";

    for (const auto& entry : cipherOptable) {
      std::cout << entry.first << ": " 
        << entry.second(plaintext, key) << std::endl;
    }

    std::cout << cipher << ": " << cipherOptable[cipher](plaintext, key);
  }

  return 0;
}
