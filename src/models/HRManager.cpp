#include "models/HRManager.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

namespace models {

HRManager::HRManager() : storage("university_data.txt") {
    storage.init();
    people = storage.load();
    loadAuth();
}

HRManager::~HRManager() {
    storage.save(people);
    saveAuth();
}

void HRManager::addPerson(std::unique_ptr<Person> person) {
    people.push_back(std::move(person));
}

bool HRManager::removePerson(const std::string& id) {
    auto it = std::remove_if(people.begin(), people.end(),
        [&id](const std::unique_ptr<Person>& p) { return p->getId() == id; });
    
    if (it != people.end()) {
        people.erase(it, people.end());
        return true;
    }
    return false;
}

Person* HRManager::findPerson(const std::string& id) const {
    for (const auto& p : people) {
        if (p->getId() == id) return p.get();
    }
    return nullptr;
}

void HRManager::sortByIncome() {
    std::sort(people.begin(), people.end(),
        [](const std::unique_ptr<Person>& a, const std::unique_ptr<Person>& b) {
            return a->calculateIncome() > b->calculateIncome();
        });
}

double HRManager::calculateTotalBudget() const {
    double total = 0;
    for (const auto& p : people) {
        total += p->calculateIncome();
    }
    return total;
}

std::vector<Person*> HRManager::searchByName(const std::string& name) const {
    std::vector<Person*> results;
    std::string searchName = name;
    // Simple case-insensitive search
    std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
    
    for (const auto& p : people) {
        std::string pName = p->getName();
        std::transform(pName.begin(), pName.end(), pName.begin(), ::tolower);
        if (pName.find(searchName) != std::string::npos) {
            results.push_back(p.get());
        }
    }
    return results;
}

HRManager::Statistics HRManager::getStats() const {
    Statistics stats = {0, 0, 0, 0.0, 0.0};
    if (people.empty()) return stats;

    double totalAge = 0;
    double totalIncome = 0;
    stats.total = (int)people.size();

    for (const auto& p : people) {
        totalAge += p->getAge();
        totalIncome += p->calculateIncome();
        if (p->getId().substr(0, 1) == "S" || p->getId().substr(0, 1) == "s") {
            stats.students++;
        } else {
            stats.lecturers++;
        }
    }
    stats.avgAge = totalAge / stats.total;
    stats.avgIncome = totalIncome / stats.total;
    return stats;
}

void HRManager::exportToText(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return;

    out << "====================================================\n";
    out << "          UNIVERSITY PERSONNEL REPORT               \n";
    out << "====================================================\n\n";
    
    out << std::left << std::setw(10) << "ID" 
        << std::setw(20) << "Name" 
        << std::setw(8) << "Age" 
        << "Income ($)\n";
    out << "----------------------------------------------------\n";
    
    for (const auto& p : people) {
        out << std::left << std::setw(10) << p->getId() 
            << std::setw(20) << p->getName() 
            << std::setw(8) << p->getAge() 
            << std::fixed << std::setprecision(2) << p->calculateIncome() << "\n";
    }
    
    Statistics stats = getStats();
    out << "\n----------------------------------------------------\n";
    out << "SUMMARY STATISTICS\n";
    out << "Total People:     " << stats.total << "\n";
    out << "Average Age:      " << std::fixed << std::setprecision(1) << stats.avgAge << "\n";
    out << "Average Income:   $" << std::fixed << std::setprecision(2) << stats.avgIncome << "\n";
    out << "Total Budget:     $" << calculateTotalBudget() << "\n";
    out << "====================================================\n";
}

void HRManager::loadAuth() {
    std::ifstream in("auth.dat");
    if (in >> adminUser >> adminPass) {
        // Loaded successfully
    } else {
        // Default values
        adminUser = "admin";
        adminPass = "admin";
    }
}

void HRManager::saveAuth() {
    std::ofstream out("auth.dat");
    out << adminUser << " " << adminPass;
}

void HRManager::updateCredentials(const std::string& newUser, const std::string& newPass) {
    adminUser = newUser;
    adminPass = newPass;
    saveAuth();
}

} // namespace models
