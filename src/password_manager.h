/**
 * @file passwordManager.h
 * @brief Header file for Password Manager implementation providing secure
 * password storage
 */

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <nlohmann/json.hpp>
#include <string>
#include "crypto/rsa.h"
#include "password.h"

using json = nlohmann::json;

enum class PasswordManagerError {
    SUCCESS = 0,
    FILE_NOT_FOUND = -1,
    JSON_ERROR = -2,
    ALREADY_EXISTS = -3
};

/**
 * @class PasswordManager
 * @brief Manages a collection of encrypted passwords with file persistence
 */
class PasswordManager {
private:
    json json_data_;
    std::string filename_;
    RSA master_rsa_;
    std::string master_key_file_;

public:
    /**
     * @brief Constructor initializes the password manager with a storage file
     * @param filename Path to the password storage file
     */
    PasswordManager(const std::string filename);

    /**
     * @brief Displays all stored password entries
     * @return JSON string containing all password entries (encrypted)
     */
    std::string view();

    /**
     * @brief Reads password data from storage file
     * @return 0 on success, -1 if file cannot be opened, -2 on parse error
     */
    int readJSON();

    /**
     * @brief Creates a new password storage file
     * @return 0 on success, -2 on JSON error, -3 on other errors
     */
    int createPasswordFile();

    /**
     * @brief Creates a master key file for password encryption
     * @return 0 on success, -1 on file creation error
     */
    int createKeyFile();

    /**
     * @brief Adds a new password entry to storage
     * @param password Password object to be stored
     * @return 0 on success, -1 if password exists, -2 on JSON error, -3 on
     * other errors
     */
    int addPassword(Password password);

    /**
     * @brief Updates the password storage file
     * @param data JSON data to write to file (if empty, writes json_data_)
     * @return 0 on success, -1 if file cannot be opened, -2 on write error
     */
    int updateFile(const json& data);

    /**
     * @brief Checks if a password file exists
     * @param filename Name of file to check
     * @return 1 if exists, 0 if not
     */
    const int passwordExists(std::string filename);

    /**
     * @brief Checks if a password entry already exists
     * @param password Password object to check
     * @return 1 if exists, 0 if not
     */
    const int passwordExists(Password password);

    /**
     * @brief Removes a password entry from storage
     * @param password Password object to remove
     * @return 0 on success, -1 if not found, -2 on JSON error, -3 on other
     * errors
     */
    int removePassword(Password password);
};

#endif  // PASSWORD_MANAGER_H
