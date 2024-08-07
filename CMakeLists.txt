cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenQCD++)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executables
add_executable(init_print_lattice app/init_print_lattice/main.cpp modules/lattice/LatticeField.cpp)
add_executable(randomize app/randomize/main.cpp modules/lattice/LatticeField.cpp)
add_executable(compute_plaquette app/compute_plaquette/main.cpp modules/lattice/LatticeField.cpp modules/gauge/GaugeField.cpp)

# Include directories
target_include_directories(init_print_lattice PRIVATE include)
target_include_directories(randomize PRIVATE include)
target_include_directories(compute_plaquette PRIVATE include)