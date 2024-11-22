#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <random>

#include "cipher.h"
#include "../main.h"

std::unordered_map<std::string, CipherFunction> cipherOptable = {
        {"caesar", caesar},
        {"vigenere", vigenere},
        {"rot13", rot13},
        {"rsa", rsa}};

ExtendedVector<std::string> commands = {"encrypt", "decrypt", "help", "exit",
                                        "pericos"};

void fatal_error(std::string msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

std::string caesar(const std::string &plaintext, const std::string &shift) {
    int rotation;

    try {
        rotation = std::stoi(shift);
    } catch (const std::exception &e) {
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

std::string vigenere(const std::string &plaintext, const std::string &key) {
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

std::string rot13(const std::string &plaintext, const std::string &unused) {
    return caesar(plaintext, "13");
}

std::string rsa(const std::string &plaintext, const std::string &unused) {
    return "Buns.\n";
}
