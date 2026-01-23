#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include "crypto/cipher.h"
using namespace std;

// Initialize the global variables defined in the header
unordered_map<string, CipherFunction> cipherOptable;

ExtendedVector<string> commands = {"encrypt", "decrypt", "help", "exit"};

// Helper function definition
void fatal_error(string msg) {
    cerr << msg << endl;
    exit(1);
}

// Initialize the cipher table
void init_cipher_table() {
    cipherOptable = {
        {"caesar", caesar},
        {"vigenere", vigenere},
        {"rot13", rot13},
        {"rsa", rsa}
    };
}

string caesar(const string &plaintext, const string &shift) {
    int rotation;

    try {
        rotation = stoi(shift);
    } catch (const exception &e) {
        cerr << "Invalid input. Using shift value of 0." << endl;
        rotation = 0;
    }

    string encryption = "";

    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char shifted = static_cast<char>((c + rotation - base) % 26 + base);
            encryption += shifted;
        } else {
            encryption += c;
        }
    }

    return encryption;
}

string vigenere(const string &plaintext, const string &key) {
    string encryption = "";

    for (size_t i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        int rotation = static_cast<int>(key[i % key.length()]);

        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char shifted = static_cast<char>((c + rotation - base) % 26 + base);
            encryption += shifted;
        } else {
            encryption += c;
        }
    }

    return encryption;
}

string rot13(const string &plaintext, const string &unused) {
    return caesar(plaintext, "13");
}

string rsa(const string &plaintext, const string &unused) {
    return "Buns.\n";
}
