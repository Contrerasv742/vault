#include "parser.h"

Parser::Parser(std::string filename) : filename_(filename) {
  file_.open(filename);

  if (!file_.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
  }
} 


void Parser::view() {
  std::string line;
  while (std::getline(file_, line)) {
    std::cout << line << std::endl;
  }
}
