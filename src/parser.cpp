#include "parser.h"

#include <iostream>
#include <sstream>

Parser::Parser(std::string filename) : filename_(filename) {
    // Open File
    file_.open(filename);

    if (!file_.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        // If file doesn't exist we should instead create a new passowrd.json
        // file
        createPasswordFile();
    }

    // Grab passwords from file
    int rc = readFile();
}

std::string Parser::view() {
    std::stringstream contents;
    std::string line;

    // Grab line by line content from JSON
    while (std::getline(file_, line)) {
        contents << line << '\n';
    }

    return contents.str();
}

int Parser::readFile() { return 0; }
