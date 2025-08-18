#include "passwordManager.h"
#include <fstream>
#include <iostream>
#include <print>
using namespace std;

string Password::decryptPassword() {
    rsa_.get_e() =
            cpp_int(password_json_["public_key"]["e"].get<string>());
    rsa_.get_n() =
            cpp_int(password_json_["public_key"]["n"].get<string>());
    rsa_.get_d() =
            cpp_int(password_json_["private_key"]["d"].get<string>());

    return rsa_.decrypt(password_json_["password"]);
}

PasswordManager::PasswordManager(const string filename)
    : filename_(filename) {
    ifstream file(filename, ios::in | ios::out);

    if (!file.is_open()) {
        println("Creating file."); 
        createPasswordFile();
    } else {
        println("Grabbing old file information.");
        readJSON();
    }

    file.close();
}

Password::Password(string company, string username,
                   string password) {
    rsa_ = RSA();

    // Create new password entry
    password_json_ = {{"company", company},
                      {"username", username},
                      {"password", rsa_.encrypt(password)},
                      {"created_at", time(nullptr)},
                      // Store public key components for future decryption
                      {"public_key",
                       {{"e", rsa_.get_e().str()}, {"n", rsa_.get_n().str()}}},
                      {"private_key",
                       {{"d", rsa_.get_d().str()}, {"n", rsa_.get_n().str()}}}};
};

string PasswordManager::view() {
    try {
        // Try to read JSON if empty
        if (json_data_.empty()) {
            readJSON();
        }

        return json_data_.dump(4);
    } catch (const exception& e) {
        return "Error attempting to read json data" + string(e.what());
    }
}

int PasswordManager::readJSON() {
    try {
        ifstream file(filename_);

        if (!file.is_open()) {
            return -1;
        }

        json_data_ = json::parse(file);

        return 0;
    } catch (const json::parse_error& e) {
        // If file can't be parsed, create new structure
        json_data_ = {{"metadata",
                       {{"version", "1.0"},
                        {"created_at", time(nullptr)},
                        {"last_modified", time(nullptr)}}},
                      {"passwords", json::array()}};
        return -2;
    }
}

int PasswordManager::createPasswordFile() {
    try {
        // Create initial JSON structure
        json data = {{"metadata",
                      {{"version", "1.0"},
                       {"created_at", time(nullptr)},
                       {"last_modified", time(nullptr)}}},
                     {"passwords", json::array()}};

        // Save to class member
        json_data_ = data;

        return updateFile(data);
    } catch (const json::parse_error& e) {
        return -2;  // JSON parsing error
    } catch (const exception& e) {
        return -3;  // Other errors
    }
}

int PasswordManager::createKeyFile() {
    try {
        string master_file_name = filename_ + ".key";
        ofstream key_file(master_file_name);

        if (key_file.good()) {
            return -1;
        }

        json key_data = {{"d", master_rsa_.get_d().str()},
                         {"e", master_rsa_.get_e().str()},
                         {"n", master_rsa_.get_n().str()}};

        key_file << key_data.dump(4);

        return 0;

    } catch (exception& e) {
        return -1;
    }
}

int PasswordManager::updateFile(const json& data) {
    try {
        ofstream file(filename_);

        if (!file.is_open()) {
            return -1;
        }

        // Writing the complete structure
        json output = data.empty() ? json_data_ : data;

        // Ensure metadata exists
        if (!output.contains("metadata")) {
            output["metadata"] = {{"version", "1.0"},
                                  {"created_at", time(nullptr)},
                                  {"last_modified", time(nullptr)}};
        } else {
            // Update last modified timestamp
            json_data_["metadata"]["last_modified"] = time(nullptr);
        }

        file << output.dump(4);
        file.close();
        return 0;

    } catch (const exception& e) {
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
            cerr << "Attempting to add existing password." << endl;
            return -1;
        }

        // Ensure metadata exists
        if (!json_data_.contains("metadata")) {
            json_data_["metadata"] = {{"version", "1.0"},
                                      {"created_at", time(nullptr)},
                                      {"last_modified", time(nullptr)}};
        }

        // Update metadata
        json_data_["metadata"]["last_modified"] = time(nullptr);

        // Add new password
        json_data_["passwords"].push_back(password.readJSON());

        return updateFile(NULL);
    } catch (const json::exception& e) {
        return -2;
    } catch (const exception& e) {
        return -3;
    }
}

int PasswordManager::passwordExists(Password password) {
    auto& passwords = json_data_["passwords"];
    json entry_json = password.readJSON();  // Changed string to json

    auto it = find_if(
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

        auto it = find_if(
                passwords.begin(), passwords.end(),
                [&entry_json](
                        const json& entry) {  // Changed capture variable name
                    return entry["company"] == entry_json["company"] &&
                           entry["username"] == entry_json["username"] &&
                           entry["password"] == entry_json["password"];
                });

        if (it == passwords.end()) {
            cerr << "Password not in password manager." << endl;
            return -1;
        }

        // Remove the password
        passwords.erase(it);

        // Save changes to file
        return updateFile(json_data_);
    } catch (const json::exception& e) {
        cerr << "JSON error: " << e.what() << endl;
        return -2;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -3;
    }
}
