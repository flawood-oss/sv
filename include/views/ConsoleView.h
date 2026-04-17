#pragma once
#include "models/Person.h"
#include <vector>
#include <memory>

namespace views {

class ConsoleView {
public:
    bool displayLogin(const std::string& correctUser, const std::string& correctPass) const;
    void displayMenu() const;
    void displayHeader(const std::string& title) const;
    void displayMessage(const std::string& msg) const;
    void displayPeople(const std::vector<std::unique_ptr<models::Person>>& people) const;
    void displaySearchResults(const std::vector<models::Person*>& results) const;
    
    // Statistics display
    void displayStats(int total, double avgAge, double avgIncome, double totalBudget) const;
    
    // Helper to get input
    std::string getInput(const std::string& prompt) const;
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
};

} // namespace views
