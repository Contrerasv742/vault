#include "random.h"

cpp_int RandomGenerator::generate(const cpp_int& min, const cpp_int& max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Calculate range
    cpp_int range = max - min + 1;

    // Estimate number of bytes needed (conservative estimate)
    size_t bytes_needed = (msb(range) + 7) / 8 + 1;

    // Generate random bytes
    std::vector<unsigned char> bytes(bytes_needed);
    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = gen() & 0xFF;
    }

    // Convert to cpp_int
    cpp_int result = 0;
    for (unsigned char byte : bytes) {
        result = (result << 8) | byte;
    }

    // Ensure in range
    result = result % range + min;
    return result;
}
