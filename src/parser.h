#ifndef PARSER_H
#include <iostream>
#include <fstream>

class Parser {

private:
  std::string filename_;
  std::ifstream file_;
  
public:
  Parser(std::string filename);
  void view();

};

#endif // PARSER_H
