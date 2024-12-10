#ifndef RSA_H
#define RSA_H

// TODO: Ensure we are actually keeping objects and their respective variables private and public

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

/**
 * @file rsa.h
 * @brief Implementation of RSA encryption algorithm using boost multiprecision
 */

/**
 * @class RSA
 * @brief Provides RSA encryption and decryption capabilities with large number support
 */
class RSA {
private:
    cpp_int p, q, n, e, d, lambda_n;
    
public:
    /**
     * @brief Constructor that initializes RSA with generated key pairs
     * @details Generates public and private key pairs using prime numbers
     *          Sets up n (modulus), e (public exponent), and d (private exponent)
     */
    RSA();

    /**
     * @brief Encrypts a message using RSA public key
     * @param msg Plain text message to encrypt
     * @return Encrypted message as string
     */
    std::string encrypt(const std::string& msg);

    /**
     * @brief Decrypts a message using RSA private key
     * @param encrypted_msg Encrypted message to decrypt
     * @return Decrypted plain text message
     */
    std::string decrypt(const std::string& encrypted_msg);

    /**
     * @brief Checks if a number is prime
     * @param num Number to check for primality
     * @return true if number is prime, false otherwise
     */
    bool prime(cpp_int num);

    /**
     * @brief Generates a random prime number within specified range
     * @param min Lower bound for prime number generation
     * @param max Upper bound for prime number generation
     * @return Random prime number within the specified range
     */
    cpp_int generate_random_prime(cpp_int min, cpp_int max);

    /**
     * @brief Calculates Greatest Common Divisor of two numbers
     * @param a First number
     * @param b Second number
     * @return GCD of a and b
     */
    cpp_int gcd(cpp_int a, cpp_int b);

    /**
     * @brief Calculates Least Common Multiple of two numbers
     * @param a First number
     * @param b Second number
     * @return LCM of a and b
     */
    cpp_int lcm(cpp_int a, cpp_int b);

    /**
     * @brief Calculates Carmichael's totient function for two prime numbers
     * @param p First prime number
     * @param q Second prime number
     * @return Carmichael's totient λ(n)
     */
    cpp_int carmichael_totient(cpp_int p, cpp_int q);

    /**
     * @brief Finds suitable public exponent e
     * @param lambda_n Carmichael's totient value
     * @return Public exponent e that satisfies:
     *         1. 1 < e < lambda_n
     *         2. gcd(e, lambda_n) = 1
     */
    cpp_int find_e(cpp_int lambda_n);

    /**
     * @brief Calculates modular multiplicative inverse
     * @param a Number to find inverse of
     * @param m Modulus
     * @return Modular multiplicative inverse of a modulo m
     */
    cpp_int mod_inverse(cpp_int a, cpp_int m);

    /**
     * @brief Performs modular exponentiation
     * @param base Base number
     * @param exponent Power to raise the base to
     * @param modulus Modulus for the operation
     * @return (base^exponent) mod modulus
     */
    cpp_int mod_pow(cpp_int base, cpp_int exponent, cpp_int modulus);

    /**
     * @brief Gets the RSA modulus n (public key component)
     * @return Value of n (p * q)
     */
    cpp_int get_n() {return n;};

    /**
     * @brief Gets the public exponent e
     * @return Value of public exponent e
     */
    cpp_int get_e() {return e;};

    /**
     * @brief Gets the private exponent d
     * @return Value of private exponent d
     */
    cpp_int get_d() {return d;};
};

#endif // RSA_H
