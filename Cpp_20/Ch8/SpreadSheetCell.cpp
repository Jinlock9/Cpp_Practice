#include "SpreadsheetCell.h"

#include <charconv>
#include <iostream>

SpreadsheetCell::SpreadsheetCell(std::string_view value) 
    : SpreadsheetCell{stringToDouble(value)} {}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src) : m_value {src.m_value} {}

SpreadsheetCell::~SpreadsheetCell() {
    std::cout << getValue() << " Destructor Called." << std::endl;
}

void SpreadsheetCell::setValue(double value) {
    m_value = value;
}

double SpreadsheetCell::getValue() const {
    return m_value;
}

void SpreadsheetCell::setString(std::string_view value) {
    m_value = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const {
    return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double value) const {
    return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value) const {
    double number = 0;
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs) {
    if (this == &rhs) {
        return *this;
    }
    m_value = rhs.m_value;
    return *this;
}