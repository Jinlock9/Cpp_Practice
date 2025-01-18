#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

#include <string>

namespace HR {
    enum class Title { Manager, Senior, Junior };

    const int DefaultStartingSalary { 30'000 };
    const int DefaultRaiseAndDemeritAmount { 10'000 };

    class Employee {
        public:
            Employee(const std::string& firstName,
                    const std::string& lastName);

            void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
            void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);
            void hire();
            void fire();
            void display() const;

            // Getter and Setter
            void setFirstName(const std::string& firstName);
            const std::string& getFirstName() const;

            void setLastName(const std::string& lastName);
            const std::string& getLastName() const;

            void setTitle(const Title title);
            Title getTitle() const;
            void printTitle() const;

            void setEmployeeNumber(int employeeNumber);
            int getEmployeeNumber() const;

            void setSalary(int newSalary);
            int getSalary() const;

            bool isHired() const;

        private:
            std::string m_firstName;
            std::string m_lastName;
            Title m_title { Title::Junior };
            int m_employeeNumber { -1 };
            int m_salary { DefaultStartingSalary };
            bool m_hired { false };
    };
}

#endif // __EMPLOYEE_H__