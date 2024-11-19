
#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

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
};

#endif  // PASSWORDMANAGER_H
