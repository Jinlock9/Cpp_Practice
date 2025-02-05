#include <iostream>
#include <memory>
#include <vector>
#include<initializer_list>
#include <stdexcept>

// g++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp SpreadsheetCell.cpp -o main

#include "SpreadsheetCell.h"

class EvenSequence {
    std::vector<int> sequence;

public:
    EvenSequence(std::initializer_list<int> args) {
        if (args.size() % 2 != 0) {
            throw std::invalid_argument("Not even"); 
        }
        sequence.assign(args);
    }

    void dump() {
        for (const auto& value : sequence) {
            std::cout << value << std::endl;
        }
    }
};

int main() {
    SpreadsheetCell cell0;
    std::cout << "cell 0: " << cell0.getValue() << std::endl;

    SpreadsheetCell cell1(0);
    cell1.setValue(1);
    std::cout << "cell 1: " << cell1.getValue() << std::endl;

    SpreadsheetCell* cell2 = new SpreadsheetCell(0);
    cell2->setString("2");
    std::cout << "cell 2: " << cell2->getValue() << std::endl;
    delete cell2;
    cell2 = nullptr;

    auto cell3 = std::make_unique<SpreadsheetCell>(0);
    cell3->setValue(3);
    std::cout << "cell 3: " << cell3->getValue() << std::endl;

    SpreadsheetCell* cell4 = nullptr;
    cell4 = new SpreadsheetCell("4");
    std::cout << "cell 4: " << cell4->getValue() << std::endl;
    delete cell4;
    cell4 = nullptr;

    SpreadsheetCell cell5(cell1);
    std::cout << "cell 5: " << cell5.getValue() << std::endl;
    SpreadsheetCell cell6 { cell5 };
    std::cout << "cell 6: " << cell6.getValue() << std::endl;

    EvenSequence s1 = {1, 2, 3, 4};
    s1.dump();
    try {
        EvenSequence p2 {5, 6, 7, 8, 9};
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}