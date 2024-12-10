#ifndef PARSER_H
#include <fstream>
#include <vector>

class Password {
private:
    std::string company_;
    std::string username_;
    std::string password_;
    bool favorite_;

public:
    Password(std::string company, std::string username, std::string password)
        : company_(company),
          username_(username),
          password_(password),
          favorite_(false){};
};

class Parser {
private:
    std::string filename_;
    std::ifstream file_;
    std::vector<Password> passwords_;

public:
    Parser(std::string filename);
    std::string view();
    int find(std::string item);
    int add();
    int remove();
    int readFile();
    void createPasswordFile();

    ~Parser() { file_.close(); }
};

#endif  // PARSER_H
