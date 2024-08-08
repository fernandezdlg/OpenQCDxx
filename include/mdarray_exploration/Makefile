# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

# Source files
SRCS = $(wildcard *.cpp)

# Header files
HDRS = mdarray.h

# Target executables
TARGETS = $(SRCS:.cpp=)

# Build rule
all: $(TARGETS)

%: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(TARGETS)
