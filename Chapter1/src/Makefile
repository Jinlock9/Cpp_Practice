# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Targets and files
TARGET = main
SRC = main.cpp Employee.cpp
OBJS = $(SRC:.cpp=.o)
DEPS = Employee.h

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)

# Phony targets
.PHONY: all clean
