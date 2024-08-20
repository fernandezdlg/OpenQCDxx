cmake_minimum_required(VERSION 3.20)

# Set the project name
project(OpenQCD++Tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # This is necessary for the std::execution policies.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the compilers
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Ensure the GCC standard library is used
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Include the 'include' folder
include_directories(../include)

# Add the executables
add_executable(su_3 SU_3/su_3_tests.cpp)
