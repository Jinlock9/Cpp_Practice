#include <stdexcept>

#include "Database.h"

namespace Records {
    Employee& Database::addEmployee(const std::string& firstName,
                                    const std::string& lastName) {
        Employee theEmployee { firstName, lastName };
        theEmployee.setEmployeeNumber(m_nextEmployeeNumber++);
        theEmployee.hire();
        m_employees.push_back(theEmployee);

        return m_employees.back();
    }
}