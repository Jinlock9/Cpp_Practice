export module employee;

import <string>

namespace Records {
    const int DefaultStartingSalary { 30'000 };
    export const int DefaultRaiseAndDemeritAmount { 10'000 };

    export class Employee {
        public:
            Employee(const std::string& firstName,
                     const std::string);
                    
            void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
            void demote(int demeritAmount = DefualtRaiseAndDemeritAmout);
            void hire();
            void fire();
            void display() const;

            // Getter and Setter
            void setFirstname(const std::string& firstName);
            const std::string& getFirstName() const;

            void setLastName(const std::string& lastName);
            const std::string& getLastName() const;

            void setEmployeeNumber(int employeeNumber);
            int getEmployeeNumber() const;
            
    }
}