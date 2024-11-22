#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <nlohmann/json.hpp>
#include <string>
#include "crypto/rsa.h"

using json = nlohmann::json;

class Password {
private:
    json password_json_;
    RSA rsa_;

public:
    Password(std::string company, std::string username, std::string password);

    json readJSON() { return password_json_; };


    std::string decryptPassword(); 
};

class PasswordManager {
private:
    json json_data_;
    std::string filename_;
    RSA master_rsa_;
    std::string master_key_file_;

public:
    PasswordManager(const std::string filename);

    std::string view();

    int readJSON();

    int createPasswordFile();

    int createKeyFile();

    int addPassword(Password password);

    int updateFile(const json& data);

    int passwordExists(std::string filename);

    int passwordExists(Password password);

    int removePassword(Password password);
};

#endif  // PASSWORDMANAGER_H
