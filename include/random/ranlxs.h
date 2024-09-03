// This declares the classes involving the RANLUX-24 random number generator as per the C++ standard
// library implementations. TODO: Get this working with parallel exec ? Or fallback to modernized
// SSE/AVX implementations?
#ifndef RANLXS_H
#define RANLXS_H

#include <random>
#include <string>
#include <fstream>

// Templated Ranlxs class
template<size_t p = 223, size_t r = 23>
class Ranlxs {
public:
    Ranlxs(int seed) : generator(seed) {}

    // This function generates a random number between 0 and 1
    float operator()() {
        return static_cast<float>(generator()) / (uint_fast32_t{1} << 24);
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
    std::discard_block_engine<std::ranlux24_base, p, r>& get_gen() {
        return generator;
    }

    // Overload for calling dist(gen) with a Ranlxd object
    template<typename Distribution>
    typename Distribution::result_type operator()(Distribution& d) {
        return d(generator);
    }

private:
    std::discard_block_engine<std::ranlux24_base, p, r> generator;
};

#endif // RANLXS_H
