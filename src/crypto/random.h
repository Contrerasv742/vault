#ifndef RANDOM_H
#define RANDOM_H

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

class RandomGenerator {
public:
    /* @brief generates a random number between @param min and @param max
     * @return returns a random <cpp_int>
     * */
    static cpp_int generate(const cpp_int& min, const cpp_int& max);
};

#endif  // RANDOM_H
