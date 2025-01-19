# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Target and source files
TARGET = main
SRC = main.cpp

# Build the target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
