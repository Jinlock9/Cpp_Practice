#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>

#include "Employee.h"

using namespace HR;

namespace Records {
    const int FirstEmployNumber { 1'000 };

    class Database {
        public:
            Employee& addEmployee(const std::string& firstName,
                                  const std::string& lastName);
            Employee& getEmployee(int employeeNumber);
            Employee& getEmployee(const std::string& firstName,
                                  const std::string& lastName);

            void displayAll() const;
            void displayCurrent() const;
            void displayFormer() const;
        
        private:
            std::vector<Employee> m_employees;
            int m_nextEmployeeNumber { FirstEmployNumber };
    };
}
#endif // __DATABASE_H__