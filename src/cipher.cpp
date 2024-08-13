#include "main.h"
#include "encryption.h"

std::unordered_map<std::string, CipherFunction> cipherOptable = {
    {"caesar", caesar},
    {"vigenere", vigenere},
    {"rot13", rot13}
};

ExtendedVector<std::string> commands = {"encrypt", "decrypt", "help", "exit", "pericos"};

void print_commands() {
    std::cout << "Commands:" << std::endl;
    for (const auto& command : commands) {
        std::cout << "\t+ " << command << std::endl;
    }
    std::cout << std::endl;
}

void print_ciphers() {
    std::cout << "Ciphers:" << std::endl;
    for (const auto& cipher : cipherOptable) {
        std::cout << "\t+ " << cipher.first << std::endl;
    }
    std::cout << std::endl;
}

void fatal_error(std::string msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

std::string get_command() {
    std::string command;
    while (true) {
        std::cout << "Enter a command:\n\t";
        std::cin >> command;
        std::cout << std::endl;

        if (command.empty() || !commands.find(command)) {
            std::cerr << "Invalid Command" << std::endl;
            print_commands();
            continue;
        }

        if (command == "help") {
            print_commands();
            continue;
        }

        if (command == "exit") {
            exit(0);
        }

        break; 
    }
    return command;
}

int process_command(std::string command) {
    if (command == "decrypt") {
        return decrypt();
    } else if (command == "encrypt") {
        return encrypt();
    } else if(command == "retrieve") {
        // Implement retrieve functionality
    }
    return 0; 
}
