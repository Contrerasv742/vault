#ifndef PASSWORD_H
#define PASSWORD_H
#include <sodium.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
using namespace std;

/**
 * @class Password
 * @brief Represents a single password entry with encryption capabilities
 */
class Password {
private:
    json json_;

    unsigned char salt_[crypto_pwhash_SALTBYTES];
    unsigned char nonce_[crypto_secretbox_NONCEBYTES];

public:
    /**
     * @brief Constructor for creating a new password entry
     * @param company The company/website name associated with the password
     * @param username The username for this password entry
     * @param password The plain text password to be encrypted
     * @return A new Password object with password data
     */
    Password(string company, string username, string password) {
        // Initialize salt and nonce with random data
        randombytes_buf(salt_, sizeof(salt_));
        randombytes_buf(nonce_, sizeof(nonce_));

        // Create new password entry
        json_ = {
            {"company", company},
            {"username", username},
            {"password", password},
            {"created_at", time(nullptr)},
            // Store public key components for future decryption
            {"salt", salt_},
        };
    }

    /**
     * @brief Returns the password entry as JSON
     * @return json object containing the password and associated data
     */
    json readJSON() { return json_; };

    /**
     * @brief Decrypts and returns the stored password
     * @return The decrypted password string
     */
    // string decryptPassword();
};

#endif // PASSWORD_H

