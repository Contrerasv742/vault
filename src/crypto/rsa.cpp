#include "rsa.h"
#include "random.h"

#include <cstdlib>
#include <iomanip>
#include <random>

RSA::RSA() {
    // I: Calculate two large unique primes
    cpp_int min = 1000000;
    cpp_int max = min * 10;

    p = generate_random_prime(min, max);
    
    // Ensure that the primes are unique
    do {
        q = generate_random_prime(min, max);
    } while (q == p);

    // II: Generate n (key_length)
    n = (cpp_int) p * q;

    // III: compute lambda_n
    lambda_n = carmichael_totient(p, q);

    // IV: choose euler number
    e = find_e(lambda_n);

    if (e == 0) { 
        std::runtime_error("Failed to find a suitable e.");
    }

    // V: determine d
    d = mod_inverse(e, lambda_n);

    /*
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

    // return output;
    */
}

bool RSA::prime(cpp_int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    cpp_int sqrt_num = (cpp_int)sqrt(num);
    for (cpp_int i = 3; i <= sqrt_num; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

cpp_int RSA::generate_random_prime(cpp_int min, cpp_int max) {

    // Generate a random => check if prime
    cpp_int num;
    do {
        num = RandomGenerator::generate(min, max);
    } while (!prime(num));

    return num;
}

cpp_int RSA::gcd(cpp_int a, cpp_int b) {
    while (b != 0) {
        cpp_int t = b;
        b = a % b;
        a = t;
    }

    return a;
}

cpp_int RSA::lcm(cpp_int a, cpp_int b) { return (a / gcd(a, b)) * b; }

cpp_int RSA::carmichael_totient(cpp_int p, cpp_int q) {
    return lcm(p - 1, q - 1);
}

cpp_int RSA::find_e(cpp_int lambda_n) {
    const cpp_int common_e[] = {65537, 257, 17};

    // I: common e chosen
    for (auto e : common_e) {
        if (e < lambda_n && gcd(e, lambda_n) == 1) {
            return e;
        }
    }

    // II: Find suitable e starting from a larger number
    for (cpp_int e = 65537; e < lambda_n; e += 2) {
        if (gcd(e, lambda_n) == 1) {
            return e;
        }
    }

    return 0;
}

cpp_int RSA::mod_inverse(cpp_int a, cpp_int m) {
        cpp_int m0 = m;
    cpp_int y = 0, x = 1;
    
    if (m == 1)
        return 0;
    
    while (a > 1) {
        cpp_int q = a / m;
        cpp_int t = m;
        
        m = a % m;
        a = t;
        t = y;
        
        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += m0;
    
    return x;
}

cpp_int RSA::mod_pow(cpp_int base, cpp_int exponent, cpp_int modulus) {
    if (modulus == 1) return 0;
    cpp_int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

std::string RSA::rsa_encrypt(const std::string& msg) {
    std::vector<cpp_int> encrypted;
    
    // Process each character
    for (char c : msg) {
        // Convert char to number and encrypt
        cpp_int m = static_cast<cpp_int>(static_cast<unsigned char>(c));
        if (m >= n) {
            throw std::runtime_error("Message value too large for given n");
        }
        
        // c^e mod n
        cpp_int encrypted_block = mod_pow(m, e, n);
        encrypted.push_back(encrypted_block);
    }
    
    // Convert encrypted numbers to string representation
    std::string result;
    for (cpp_int num : encrypted) {
        result += num.str() + " ";
    }
    return result;
}

std::string RSA::rsa_decrypt(const std::string& encrypted_msg) {
    std::string result;
    std::stringstream ss(encrypted_msg);
    cpp_int num;
    
    // Process each encrypted block
    while (ss >> num) {
        // c^d mod n
        cpp_int decrypted_block = mod_pow(num, d, n);
        
        // Convert back to character
        if (decrypted_block > 255) {
            throw std::runtime_error("Decrypted value outside ASCII range");
        }
        result += static_cast<char>(decrypted_block);
    }
    
    return result;
}
