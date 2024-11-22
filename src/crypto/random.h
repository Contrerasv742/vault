#ifndef RANDOM_H
#define RANDOM_H

#include <boost/multiprecision/cpp_int.hpp>
#include <random>

using boost::multiprecision::cpp_int;

class RandomGenerator {
public:
    static cpp_int generate(const cpp_int& min, const cpp_int& max); 
};

#endif // RANDOM_H
