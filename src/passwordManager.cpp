#include "passwordManager.h"
#include <fstream>
#include <iostream>

PasswordManager::PasswordManager(const std::string filename)
    : filename_(filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        createPasswordFile();
    } else {
        readJSON();
    }

    file.close();
}

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
        json data = json::parse(R"(
            {
                "metadata": {
                    "version": "1.0",
                    "created_at": null,
                    "last_modified": null
                },
                "passwords": []
            }
        )");

        // Update dynamic fields
        data["metadata"]["created_at"] = std::time(nullptr);
        data["metadata"]["last_modified"] = std::time(nullptr);

        // Save to class member
        json_data_ = data;

        return updateFile(data);
    } catch (const json::parse_error& e) {
        return -2;  // JSON parsing error
    } catch (const std::exception& e) {
        return -3;  // Other errors
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
        }

        file << output.dump(4);
        file.close();
        return 0;

    } catch (const std::exception& e) {
        return -2;
    }
}

int PasswordManager::addPassword(const std::string& company,
                                 const std::string& username,
                                 const std::string& password) {
    try {
        // First read existing data if not already loaded
        if (json_data_.empty()) {
            readJSON();
        }

        // Create new password entry
        json new_password = {{"company", company},
                             {"username", username},
                             {"password", password},
                             {"created_at", std::time(nullptr)}};

        // Ensure metadata exists
        if (!json_data_.contains("metadata")) {
            json_data_["metadata"] = {{"version", "1.0"},
                                      {"created_at", std::time(nullptr)},
                                      {"last_modified", std::time(nullptr)}};
        }

        // Update metadata
        json_data_["metadata"]["last_modified"] = std::time(nullptr);

        // Add new password
        json_data_["passwords"].push_back(new_password);

        return updateFile(NULL);

    } catch (const json::exception& e) {
        return -2;
    } catch (const std::exception& e) {
        return -3;
    }
}
