#include "cipher.h"

#include <cstdlib>
#include <iomanip>
#include <random>

#include "main.h"

std::unordered_map<std::string, CipherFunction> cipherOptable = {
        {"caesar", caesar},
        {"vigenere", vigenere},
        {"rot13", rot13},
        {"rsa", rsa}};

ExtendedVector<std::string> commands = {"encrypt", "decrypt", "help", "exit",
                                        "pericos"};

void fatal_error(std::string msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

std::string caesar(const std::string &plaintext, const std::string &shift) {
    int rotation;

    try {
        rotation = std::stoi(shift);
    } catch (const std::exception &e) {
        std::cerr << "Invalid input. Using shift value of 0." << std::endl;
        rotation = 0;
    }

    std::string encryption = "";

    for (char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char shifted = static_cast<char>((c + rotation - base) % 26 + base);
            encryption += shifted;
        } else {
            encryption += c;
        }
    }

    return encryption;
}

std::string vigenere(const std::string &plaintext, const std::string &key) {
    std::string encryption = "";

    for (size_t i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        int rotation = static_cast<int>(key[i % key.length()]);

        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char shifted = static_cast<char>((c + rotation - base) % 26 + base);
            encryption += shifted;
        } else {
            encryption += c;
        }
    }

    return encryption;
}

std::string rot13(const std::string &plaintext, const std::string &unused) {
    return caesar(plaintext, "13");
}

bool prime(uint32_t num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    uint32_t sqrt_num = (uint32_t)sqrt(num);
    for (uint32_t i = 3; i <= sqrt_num; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

uint32_t generate_random_prime(uint32_t min, uint32_t max) {
    // Random Number Generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a Distribution
    std::uniform_int_distribution<> dis(min, max);

    // Find a prime number
    uint32_t num;
    do {
        num = dis(gen);
    } while (!prime(num));

    return num;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }

    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) { return (a / gcd(a, b)) * b; }

uint64_t carmichael_totient(uint64_t p, uint64_t q) {
    return lcm(p - 1, q - 1);
}

uint64_t find_e(uint64_t lambda_n) {
    const uint64_t common_e[] = {65537, 257, 17};

    // I: common e chosen
    for (auto e : common_e) {
        if (e < lambda_n && gcd(e, lambda_n) == 1) {
            return e;
        }
    }

    // II: Find suitable e starting from a larger number
    for (uint64_t e = 65537; e < lambda_n; e += 2) {
        if (gcd(e, lambda_n) == 1) {
            return e;
        }
    }

    return 0;
}

uint64_t mod_inverse(int a, int m) {
    if(gcd(a, m) > 1){

        // modulo inverse does not exist
        return -1;
    }

    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }

    return -1;
}

std::string rsa(const std::string &plaintext, const std::string &key) {
    // I: Calculate two large unique primes
    uint32_t min = 1000000;
    uint32_t max = min * 10;

    uint32_t p = generate_random_prime(min, max);
    uint32_t q;

    // Ensure that the primes are unique
    do {
        q = generate_random_prime(min, max);
    } while (q == p);

    // II: Generate n (key_length)
    uint64_t n = (uint64_t) p * q;

    // III: compute lambda_n
    uint64_t lambda_n = carmichael_totient(p, q);

    // IV: choose euler number
    uint64_t e = find_e(lambda_n);
    if (e == 0) { 
        std::runtime_error("Failed to find a suitable e.");
    }

    if (e == 0) {
        fatal_error("Failed to find a coprime e.");
    }

    // V: determine d
    uint64_t d = mod_inverse(e, lambda_n);

    // Extra: Printing to observe numbers
    std::stringstream ss;

    ss << "p: " << p << "\n";
    ss << "q: " << q << "\n";
    ss << "n: " << n << "\n";

    // 0000 0000 0000 0111
    ss << "λ(n): " << lambda_n << "\n";
    ss << "e: " << e << "\n";
    ss << "d: " << std::fixed << std::setprecision(16) << d << "\n";

    std::string output = ss.str();

    return output;
}

uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    if (modulus == 1) return 0;
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

// Encrypt a message
std::string rsa_encrypt(uint64_t e, uint64_t n, const std::string& msg) {
    std::vector<uint64_t> encrypted;
    
    // Process each character
    for (char c : msg) {
        // Convert char to number and encrypt
        uint64_t m = static_cast<uint64_t>(static_cast<unsigned char>(c));
        if (m >= n) {
            throw std::runtime_error("Message value too large for given n");
        }
        
        // c^e mod n
        uint64_t encrypted_block = mod_pow(m, e, n);
        encrypted.push_back(encrypted_block);
    }
    
    // Convert encrypted numbers to string representation
    std::string result;
    for (uint64_t num : encrypted) {
        result += std::to_string(num) + " ";
    }
    return result;
}

// Decrypt a message
std::string rsa_decrypt(uint64_t d, uint64_t n, const std::string& encrypted_msg) {
    std::string result;
    std::stringstream ss(encrypted_msg);
    uint64_t num;
    
    // Process each encrypted block
    while (ss >> num) {
        // c^d mod n
        uint64_t decrypted_block = mod_pow(num, d, n);
        
        // Convert back to character
        if (decrypted_block > 255) {
            throw std::runtime_error("Decrypted value outside ASCII range");
        }
        result += static_cast<char>(decrypted_block);
    }
    
    return result;
}
