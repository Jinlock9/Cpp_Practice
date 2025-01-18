# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Targets and files
TARGET = main
MODULES = ./modules/Employee.cpp ./modules/Database.cpp
HEADERS = ./modules/Employee.h ./modules/Database.h
SRC = main.cpp ${MODULES}
OBJS = $(SRC:.cpp=.o)
DEPS = ${HEADERS}

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
