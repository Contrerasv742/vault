
#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Password {
private:
    std::string company_;
    std::string username_;
    std::string password_;

public:
    Password(std::string company, std::string username, std::string password) : company_(company), username_(username), password_(password) {};
    // Encrypt();

};

class PasswordManager {
private:
    json json_data_;
    std::string filename_;

public:
    PasswordManager(const std::string filename);

    std::string view();

    int readJSON();

    int createPasswordFile();

    int addPassword(const std::string& company, const std::string& username,
                    const std::string& password);

    int updateFile(const json& data);

    int passwordExists(std::string filename);

    int passwordExists(Password password);

    int removePassword(Password password);
};

#endif  // PASSWORDMANAGER_H
