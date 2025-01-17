#include <iostream>
#include <format> // C++20

#include "Employee.h"

int main () {
    Employee anEmployee;
    anEmployee.firstInitial = 'J';
    anEmployee.lastInitial = 'D';
    anEmployee.employeeNumber = 42;
    anEmployee.salaray = 80000;

    std::cout << std::format("Employee: {} {}", anEmployee.firstInitial, anEmployee.lastInitial) << std::endl;
    std::cout << std::format("Number: {}", anEmployee.employeeNumber) << std::endl;
    std::cout << std::format("Salaray: ${}", anEmployee.salaray) << std::endl;

    // g++ -std=c++20 -o Employee Employee.cpp
    // clang++ -std=c++20 -o Employee Employee.cpp

    return 0;
}