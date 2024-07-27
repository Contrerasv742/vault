#include "main.h"

void help() {
  std::cout << "Options: " << std::endl; 
  for (auto command: options) {
    std::cout << "\t+ " << command << std::endl;
  }
}
void fatal_error(std::string msg) {
  std::cerr << msg << std::endl;
  exit(1);
}

std::string get_command() {
  std::string option;
  while (true) {
    std::cout << "Enter a command: " << std::endl; 
    std::cin >> option; 

    // Validating Option 
    if (option.empty() || options.find(option)) {
      std::cerr << "Invalid Cipher" << std::endl;
      continue;
    }
    break;
  }

  return option; 
}

std::string get_option() {
  std::string cipher;
  while (true) {
    std::cout << "Enter your cipher: ";
    std::cin >> cipher;

    // Validating Cipher
    if (cipher.empty() || cipherOptable.find(cipher) == cipherOptable.end()) {
      std::cerr << "Invalid Cipher" << std::endl;
      continue;
    }
    break;
  }

  return cipher;
}

// TODO: 
//  Implement Encryption prompts
//  Manage Encryptions in a local file
int main() {
  std::cout << "Hello how can I help you today?" << std::endl; 

  // Main Loop
  while (true) {
    // Helper Variables
    std::string command = get_command();
    std::string option = get_option(); 

    // Example usage
    std::string plaintext = "Hello, World!";
    std::string key = "secretkey";

    /*
    for (const auto& entry : cipherOptable) {
      std::cout << entry.first << ": " 
        << entry.second(plaintext, key) << std::endl;
    }
    */

    std::cout << option << ": " << cipherOptable[option](plaintext, key);
  }

  return 0;
}
