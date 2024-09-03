// This declares the classes involving the RANLUX-24 random number generator as per the C++ standard
// library implementations. TODO: Get this working with parallel exec ? Or fallback to modernized
// SSE/AVX implementations?
#ifndef RANLXD_H
#define RANLXD_H

#include <random>
#include <string>
#include <fstream>

// Templated Ranlxd class
template<size_t p = 389, size_t r = 11>
class Ranlxd {
public:
    Ranlxd(int seed) : generator(seed) {}

    // This function generates a random number between 0 and 1
    double operator()() {
        return static_cast<double>(generator()) / (uint_fast64_t{1} << 48);
    }

    // This function retrieves the current state of the generator
    void save_state_to_file_path(const std::string& path) {
        std::ofstream file(path);
        file << generator;
        file.close();
    }

    // Resume from state
    void load_state_from_file_path(const std::string& path) {
        std::ifstream file(path);
        file >> generator;
        file.close();
    }

    // Getter for the generator for special cases (e.g. re-seeding)
    std::discard_block_engine<std::ranlux48_base, p, r>& get_gen() {
        return generator;
    }

    // Overload for calling dist(gen) with a Ranlxd object
    template<typename Distribution>
    typename Distribution::result_type operator()(Distribution& d) {
        return d(generator);
    }

private:
    std::discard_block_engine<std::ranlux48_base, p, r> generator;
};

#endif // RANLXD_H
