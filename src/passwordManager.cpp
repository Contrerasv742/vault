#include "passwordManager.h"
#include <fstream>
#include <iostream>


std::string Password::decryptPassword() { 
    rsa_.get_e() = cpp_int(password_json_["public_key"]["e"].get<std::string>());
    rsa_.get_n() = cpp_int(password_json_["public_key"]["n"].get<std::string>());
    rsa_.get_d() = cpp_int(password_json_["private_key"]["d"].get<std::string>());

    return rsa_.decrypt(password_json_["password"]);
}

PasswordManager::PasswordManager(const std::string filename)
    : filename_(filename) {
    std::ifstream file(filename, std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cout << "Creating file." << std::endl;
        createPasswordFile();
    } else {
        std::cout << "Grabbing old file information." << std::endl;
        readJSON();
    }

    file.close();
}

Password::Password(std::string company, std::string username,
                   std::string password) {
    rsa_ = RSA();

    // Create new password entry
    password_json_ = {{"company", company},
                      {"username", username},
                      {"password", rsa_.encrypt(password)},
                      {"created_at", std::time(nullptr)},
                      // Store public key components for future decryption
                        {"public_key", {
                            {"e", rsa_.get_e().str()},
                            {"n", rsa_.get_n().str()}
                        }},
                        {"private_key", {
                            {"d", rsa_.get_d().str()},
                            {"n", rsa_.get_n().str()}
                        }}
                    };
};

std::string PasswordManager::view() {
    try {
        // Try to read JSON if empty
        if (json_data_.empty()) {
            readJSON();
        }

        return json_data_.dump(4);
    } catch (const std::exception& e) {
        return "Error attempting to read json data" + std::string(e.what());
    }
}

int PasswordManager::readJSON() {
    try {
        std::ifstream file(filename_);

        if (!file.is_open()) {
            return -1;
        }

        json_data_ = json::parse(file);

        return 0;
    } catch (const json::parse_error& e) {
        // If file can't be parsed, create new structure
        json_data_ = {{"metadata",
                       {{"version", "1.0"},
                        {"created_at", std::time(nullptr)},
                        {"last_modified", std::time(nullptr)}}},
                      {"passwords", json::array()}};
        return -2;
    }
}

int PasswordManager::createPasswordFile() {
    try {
        // Create initial JSON structure
        json data = {{"metadata",
                      {{"version", "1.0"},
                       {"created_at", std::time(nullptr)},
                       {"last_modified", std::time(nullptr)}}},
                     {"passwords", json::array()}};

        // Save to class member
        json_data_ = data;

        return updateFile(data);
    } catch (const json::parse_error& e) {
        return -2;  // JSON parsing error
    } catch (const std::exception& e) {
        return -3;  // Other errors
    }
}


int PasswordManager::createKeyFile() {
    try {
        std::string master_file_name = filename_ + ".key";
        std::ifstream key_file(master_file_name);

        if (key_file.good()) {
            return -1;
        }

        json key_data = {
                {"d", master_rsa_.get_d().str()},
                {"e", master_rsa_.get_e().str()},
                {"n", master_rsa_.get_n().str()}
            };

        key_file << key_data.dump(4);

        return 0;

    } catch (std::exception &e) {
        return -1;
    } 
}

int PasswordManager::updateFile(const json& data) {
    try {
        std::ofstream file(filename_);

        if (!file.is_open()) {
            return -1;
        }

        // Writing the complete structure
        json output = data.empty() ? json_data_ : data;

        // Ensure metadata exists
        if (!output.contains("metadata")) {
            output["metadata"] = {{"version", "1.0"},
                                  {"created_at", std::time(nullptr)},
                                  {"last_modified", std::time(nullptr)}};
        } else {
            // Update last modified timestamp
            json_data_["metadata"]["last_modified"] = std::time(nullptr);
        }

        file << output.dump(4);
        file.close();
        return 0;

    } catch (const std::exception& e) {
        return -2;
    }
}

int PasswordManager::addPassword(Password password) {
    try {
        // First read existing data if not already loaded
        if (json_data_.empty()) {
            readJSON();
        }

        // Ensure we don't add duplicates
        if (passwordExists(password) > 0) {
            std::cerr << "Attempting to add existing password." << std::endl;
            return -1;
        }

        // Ensure metadata exists
        if (!json_data_.contains("metadata")) {
            json_data_["metadata"] = {{"version", "1.0"},
                                      {"created_at", std::time(nullptr)},
                                      {"last_modified", std::time(nullptr)}};
        }

        // Update metadata
        json_data_["metadata"]["last_modified"] = std::time(nullptr);

        // Add new password
        json_data_["passwords"].push_back(password.readJSON());

        return updateFile(NULL);
    } catch (const json::exception& e) {
        return -2;
    } catch (const std::exception& e) {
        return -3;
    }
}

int PasswordManager::passwordExists(Password password) {
    auto& passwords = json_data_["passwords"];
    json entry_json = password.readJSON();  // Changed std::string to json

    auto it = std::find_if(
            passwords.begin(), passwords.end(),
            [&entry_json](const json& entry) {  // Changed capture variable name
                return entry["company"] == entry_json["company"] &&
                       entry["username"] == entry_json["username"] &&
                       entry["password"] == entry_json["password"];
            });

    return !(it == passwords.end());
}

int PasswordManager::removePassword(Password password) {
    try {
        auto& passwords = json_data_["passwords"];
        json entry_json = password.readJSON();

        auto it = std::find_if(
                passwords.begin(), passwords.end(),
                [&entry_json](
                        const json& entry) {  // Changed capture variable name
                    return entry["company"] == entry_json["company"] &&
                           entry["username"] == entry_json["username"] &&
                           entry["password"] == entry_json["password"];
                });

        if (it == passwords.end()) {
            std::cerr << "Password not in password manager." << std::endl;
            return -1;
        }

        // Remove the password
        passwords.erase(it);

        // Save changes to file
        return updateFile(json_data_);
    } catch (const json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return -2;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -3;
    }
}
