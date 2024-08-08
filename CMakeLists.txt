cmake_minimum_required(VERSION 3.20)

# Set the project name
project(OpenQCD++)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # This is necessary for the std::execution policies.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the compilers
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Ensure the GCC standard library is used
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")



# Add the executables
add_executable(randomize app/parallel_computations/randomize.cpp modules/lattice/LatticeField.cpp)
add_executable(apply_func app/parallel_computations/apply_func.cpp modules/lattice/LatticeField.cpp)
add_executable(reduce_if app/parallel_computations/reduce_if.cpp modules/lattice/LatticeField.cpp)

# Include directories
target_include_directories(randomize PRIVATE include)
target_include_directories(apply_func PRIVATE include)
target_include_directories(reduce_if PRIVATE include)
