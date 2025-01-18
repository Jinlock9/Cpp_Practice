#include <iostream>
#include <stdexcept>
#include <exception>
#include <format>
#include <string>

#include "modules/Database.h"
#include "modules/Employee.h"

using namespace HR;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);

int main() {
    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///        EMPLOYEE DATABASE        ///" << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
    Database employeeDB;
    bool done { false };

    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "///            * MENU *             ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;

    while (!done) {
        int selection { displayMenu() };
        std::cout << std::endl;
        switch (selection) {
            case 7:
                done = true;
                break;
            case 1:
                doHire(employeeDB);
                break;
            case 2:
                doFire(employeeDB);
                break;
            case 3:
                doPromote(employeeDB);
                break;
            case 4:
                employeeDB.displayAll();
                break;
            case 5:
                employeeDB.displayCurrent();
                break;
            case 6:
                employeeDB.displayFormer();
                break;
            default:
                std::cerr << "Unknown command." << std::endl;
                break;
        }
    }

    std::cout << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///         Database Closed         ///" << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
    return 0;
}

int displayMenu() {
    int selection;

    std::cout << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///  *  Choose an Option:           ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "/// (1) Hire a new employee         ///" << std::endl;
    std::cout << "/// (2) Fire an employee            ///" << std::endl;
    std::cout << "/// (3) Promote an employee         ///" << std::endl;
    std::cout << "/// (4) List all employees          ///" << std::endl;
    std::cout << "/// (5) List all current employees  ///" << std::endl;
    std::cout << "/// (6) List all former employees   ///" << std::endl;
    std::cout << "/// (7) Quit                        ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;  
    std::cout << "/// Input Number : ";

    std::cin >> selection;

    return selection;
}

void doHire(Database& db) {
    std::string firstName;
    std::string lastName;

    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///         Hiring Process:         ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "/// * First Name : ";
    std::cin >> firstName;
    std::cout << "/// * Last Name  : ";
    std::cin >> lastName;

    auto& employee { db.addEmployee(firstName, lastName) };
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << std::endl;
    std::cout << std::format("Hired employee {} {} with employee number {}.",
                             firstName, lastName, employee.getEmployeeNumber()) << std::endl;
    std::cout << std::endl;
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "///          Process Done!          ///" << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
}

void doFire(Database& db) {
    int employeeNumber;

    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///         Firing Process:         ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "/// * Employee Number : ";
    std::cin >> employeeNumber;

    std::cout << std::endl;
    try {
        auto& emp { db.getEmployee(employeeNumber) };
        emp.fire();
        std::cout << std::format("Employee {} fired.", employeeNumber) << std::endl;
    } catch (const std::logic_error& e) {
        std::cerr << std::format("System Error: {}", e.what()) << std::endl; 
    }
    std::cout << std::endl;

    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "///          Process Done!          ///" << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
}

void doPromote(Database& db) {
    int employeeNumber;
    int raiseAmount;

    std::cout << "///////////////////////////////////////" << std::endl;
    std::cout << "///        Promoting Process:       ///" << std::endl;
    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "/// * Employee Number      : ";
    std::cin >> employeeNumber;

    try {
        auto& emp { db.getEmployee(employeeNumber) };

        std::cout << "/// * Salaray Raise Amount : ";
        std::cin >> raiseAmount;
        emp.promote(raiseAmount);
        switch (emp.getTitle()) {
            case Title::Junior:
                emp.setTitle(Title::Senior);
                std::cout << std::format("Promoted to {}", emp.getTitleString()) << std::endl;
                break;
            case Title::Senior:
                emp.setTitle(Title::Manager);
                std::cout << std::format("Promoted to {}", emp.getTitleString()) << std::endl;
                break;
            default:
                break;
        }
    } catch (const std::logic_error& e) {
        std::cerr << std::format("System Error: {}", e.what()) << std::endl; 
    }

    std::cout << "///---------------------------------///" << std::endl;
    std::cout << "///          Process Done!          ///" << std::endl;
    std::cout << "///////////////////////////////////////" << std::endl;
}