#ifndef __SPREADSHEETCELL_H__
#define __SPREADSHEETCELL_H__

#include <string>
#include <string_view>

class SpreadsheetCell {
    double m_value = 0;

public:
    // SpreadsheetCell() : m_value(0) {} // : m_value {0} {}
    SpreadsheetCell() = default;
    SpreadsheetCell(double value) : m_value {value} {}
    explicit SpreadsheetCell(std::string_view value); // explicit: Do not allow implicit conversion.
    SpreadsheetCell(const SpreadsheetCell& src);

    ~SpreadsheetCell();

    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

    SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

private:
    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;
};

#endif // __SPREADSHEETCELL_H__