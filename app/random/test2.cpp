
#include <iostream>
#include <random>
#include "random/ranlxd.h"


int main() {

    Ranlxd<> default_ranlxd{1}; // Uses default p = 389, r = 11
    std::cout << "Generated number: " << default_ranlxd() << std::endl;

    Ranlxd<24, 10> custom_ranlxd{1}; // Uses custom p = 24, r = 10
    std::cout << "Generated number: " << custom_ranlxd() << std::endl;

    std::ranlux48 ranlux48{1};
    std::cout << "Generated number: " << static_cast<double>(ranlux48()) / (uint_fast64_t{1} << 48) << std::endl;

    // Generating 10000 random numbers with Ranlxd<> then binning into 30 buckets for a histogram
    std::vector<int> histogram(30, 0);
    for (int i = 0; i < 10000; i++) {
        double random_number = default_ranlxd();
        int bucket = static_cast<int>(random_number * 30);
        histogram[bucket]++;
    }
    // Print histogram
    for (int i = 0; i < 30; i++) {
        std::cout << i << ": " << histogram[i] << std::endl;
    }

    return 0;
}
