#include "main.h"
#include "cipher.h"
#include <cstdlib>
#include <random>
#include <iomanip>

std::unordered_map<std::string, CipherFunction> cipherOptable = {
  {"caesar", caesar},
  {"vigenere", vigenere},
  {"rot13", rot13},
  {"rsa", rsa}
};

ExtendedVector<std::string> commands = {"encrypt", "decrypt", "help", "exit", "pericos"};

void fatal_error(std::string msg) {
  std::cerr << msg << std::endl;
  exit(1);
}

std::string caesar(const std::string& plaintext, const std::string& shift) {
  int rotation;

  try {
    rotation = std::stoi(shift); 
  } catch (const std::exception& e) {
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

std::string vigenere(const std::string& plaintext, const std::string& key) {
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

std::string rot13(const std::string& plaintext, const std::string& unused) {
  return caesar(plaintext, "13");
}


bool prime(uint32_t num) {
  return true; 
}

uint32_t generate_random_prime(uint32_t min, uint32_t max) {
  /*
  int num = 6;

  while (!prime(num)) {
    // Random Number Generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a Distribution
    std::uniform_int_distribution<> dis(min, max);

    num = dis(gen);
    break; // TODO: Implement Prime Checker
  }

  */

  // Random Number Generator
  std::random_device rd;
  std::mt19937 gen(rd());

  // Create a Distribution
  std::uniform_int_distribution<> dis(min, max);

  int num = dis(gen);

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

uint64_t lcm(uint64_t a, uint64_t b) {
  return (a / gcd(a, b)) * b;
}

uint64_t carmichael_totient(uint64_t p, uint64_t q) {
  return lcm(p - 1, q - 1);
}

uint64_t find_e(uint64_t lambda_n) {
  const uint64_t common_e[] = {65537, 257, 17};

  for (auto e : common_e) {
    if (e < lambda_n && gcd(e, lambda_n) == 1) {
      return e;
    }
  }

  for (uint64_t e = 65537; e < lambda_n; e += 2) {
    if (gcd(e, lambda_n) == 1) {
      return e;
    }
  }

  return 0;
}

std::string rsa(const std::string& plaintext, const std::string& key) {
  // I: Calculate two large primes
  uint32_t min = 1000000;
  uint32_t max = min * 10; 

  uint32_t p = generate_random_prime(min, max);
  uint32_t q = generate_random_prime(min, max);

  // II: Generate n
  uint32_t n = p * q;

  // III: compute lambda_n
  uint64_t lambda_n = carmichael_totient(p, q);

  // IV: choose euler number
  uint64_t e = find_e(lambda_n);

  if (e == 0) {
    fatal_error("Failed to find a coprime e.");
  }

  // V: determine d
  double d = (1/e); //% lambda_n;

  // Extra: Printing to observe numbers
  std::stringstream ss;

  ss << "p: " << p << "\n";
  ss << "q: " << q << "\n";
  ss << "n: " << n << "\n";
  ss << "λ(n): " << lambda_n << "\n";
  ss << "e: " << e << "\n";
  ss << "d: " << std::fixed << std::setprecision(8) << d << "\n";

  std::string output = ss.str();

  return output;
}
