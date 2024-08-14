#ifndef RANLUX_H
#define RANLUX_H

#include <random>
#include <string>

// Ranlxs class
class Ranlxs {
public:
    Ranlxs(int seed);

    float operator()();

    void reseed(int seed);

    void save_state_to_file_path(const std::string& path);

    void load_state_from_file_path(const std::string& path);

    std::ranlux24& get_gen();

private:
    std::ranlux24 generator;
};

// TODO: Ranlxd class

#endif // RANLUX_H
