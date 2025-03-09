# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Targets
TARGET := snake
OBJS := main.o map.o snake.o

# Default target
all: $(TARGET)

# Link target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile rules
main.o: main.cpp snake.hpp map.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

map.o: map.cpp map.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

snake.o: snake.cpp snake.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Rebuild from scratch
rebuild: clean all

.PHONY: all clean rebuild
