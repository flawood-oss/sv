#include "views/ConsoleView.h"
#include <iostream>
#include <iomanip>

namespace views {

void ConsoleView::displayHeader(const std::string& title) const {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

bool ConsoleView::displayLogin(const std::string& correctUser, const std::string& correctPass) const {
    displayHeader("SYSTEM LOGIN");
    std::string user = getInput("Username: ");
    std::string pass = getInput("Password: ");
    
    if (user == correctUser && pass == correctPass) {
        displayMessage("Login Successful! Welcome, " + user + ".");
        return true;
    } else {
        displayMessage("Invalid credentials. Please try again.");
        return false;
    }
}

void ConsoleView::displayMenu() const {
    displayHeader("MAIN MENU - UNIVERSITY HR");
    std::cout << " 1. [Add] New Student" << std::endl;
    std::cout << " 2. [Add] New Lecturer" << std::endl;
    std::cout << " 3. [View] All Personnel" << std::endl;
    std::cout << " 4. [Search] Student/Lecturer by Name" << std::endl;
    std::cout << " 5. [Remove] Personnel by ID" << std::endl;
    std::cout << " 6. [Sort] Sort Personnel by Income" << std::endl;
    std::cout << " 7. [Stats] View Aggregated Statistics" << std::endl;
    std::cout << " 8. [Export] Save Personnel Report (.txt)" << std::endl;
    std::cout << " 9. [Settings] Change Admin Credentials" << std::endl;
    std::cout << " 0. [Exit] Secure Logout & Close" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Select valid option > ";
}

void ConsoleView::displayMessage(const std::string& msg) const {
    std::cout << " >> " << msg << std::endl;
}

void ConsoleView::displayPeople(const std::vector<std::unique_ptr<models::Person>>& people) const {
    if (people.empty()) {
        std::cout << " [!] Records empty. Please add personnel." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Full Name" 
              << std::setw(8) << "Age" 
              << "Annual Income ($)" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (const auto& p : people) {
        std::cout << std::left << std::setw(10) << p->getId() 
                  << std::setw(20) << p->getName() 
                  << std::setw(8) << p->getAge() 
                  << std::fixed << std::setprecision(2) << p->calculateIncome() << std::endl;
    }
    std::cout << std::string(60, '-') << std::endl;
}

void ConsoleView::displaySearchResults(const std::vector<models::Person*>& results) const {
    if (results.empty()) {
        std::cout << " [!] Zero matches found for that criteria." << std::endl;
        return;
    }
    
    std::cout << "\n --- MATCHING RECORDS FOUND (" << results.size() << ") ---" << std::endl;
    std::cout << "\n" << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Full Name" 
              << std::setw(8) << "Age" 
              << "Annual Income ($)" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (auto p : results) {
        std::cout << std::left << std::setw(10) << p->getId() 
                  << std::setw(20) << p->getName() 
                  << std::setw(8) << p->getAge() 
                  << std::fixed << std::setprecision(2) << p->calculateIncome() << std::endl;
    }
    std::cout << std::string(60, '-') << std::endl;
}

void ConsoleView::displayStats(int total, double avgAge, double avgIncome, double totalBudget) const {
    displayHeader("SYSTEM STATISTICS");
    std::cout << " - Total Personnel:  " << total << std::endl;
    std::cout << " - Average Age:      " << std::fixed << std::setprecision(1) << avgAge << " years" << std::endl;
    std::cout << " - Average Income:   $" << std::fixed << std::setprecision(2) << avgIncome << std::endl;
    std::cout << " - Total Budget Req: $" << std::fixed << std::setprecision(2) << totalBudget << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

std::string ConsoleView::getInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin >> std::ws, input);
    return input;
}

int ConsoleView::getIntInput(const std::string& prompt) const {
    std::cout << prompt;
    int input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << " Invalid format. Enter numeric value: ";
    }
    return input;
}

double ConsoleView::getDoubleInput(const std::string& prompt) const {
    std::cout << prompt;
    double input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << " Invalid format. Enter decimal value: ";
    }
    return input;
}

} // namespace views
