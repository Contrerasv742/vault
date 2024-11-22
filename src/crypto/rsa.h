#ifndef RSA_H
#define RSA_H

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

class RSA {
private:
    cpp_int p, q, n, e, d, lambda_n;
    
public:

    /* @param plaintext (unused)
     * @param key (unused)
     * @algorithm:
     *      generate two keys:
     *          public key: shown
     *          private key: verifies if the public correct
     *      TODO: Continue algorithm...
     * @return string (unused)
     * */
    RSA();

    std::string encrypt(const std::string& msg);

    std::string decrypt(const std::string& encrypted_msg);

    // RSA Helper Functions
    bool prime(cpp_int num);

    cpp_int generate_random_prime(cpp_int min, cpp_int max);

    cpp_int gcd(cpp_int a, cpp_int b);

    cpp_int lcm(cpp_int a, cpp_int b);

    cpp_int carmichael_totient(cpp_int p, cpp_int q);

    /* @param lamba_n
     * @algorithm:
     *      (1 < e < lambda_n) && (gcd(e,lambda_n) == 1)
     * @return e
     * */
    cpp_int find_e(cpp_int lambda_n);

    cpp_int mod_inverse(cpp_int a, cpp_int m);

    cpp_int mod_pow(cpp_int base, cpp_int exponent, cpp_int modulus);

    cpp_int get_n() {return n;};

    cpp_int get_e() {return e;};

    cpp_int get_d() {return d;};
};

#endif // RSA_H
