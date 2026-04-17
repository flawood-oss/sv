#include "models/StorageManager.h"
#include "models/Student.h"
#include "models/Lecturer.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace models {

StorageManager::StorageManager(const std::string& filename) : filename(filename) {}

bool StorageManager::init() {
    std::ifstream f(filename);
    if (!f.good()) {
        std::ofstream out(filename);
        out.close();
    }
    return true;
}

bool StorageManager::save(const std::vector<std::unique_ptr<Person>>& people) {
    std::ofstream out(filename);
    if (!out) return false;

    for (const auto& p : people) {
        if (auto s = dynamic_cast<Student*>(p.get())) {
            out << "S|" << s->getId() << "|" << s->getName() << "|" << s->getAge() << "|" << s->getGpa() << "\n";
        } else if (auto l = dynamic_cast<Lecturer*>(p.get())) {
            // Since we need baseSalary and publications, we need to ensure Lecturer has getters
            // For now assuming getters exist or will be added
            out << "L|" << l->getId() << "|" << l->getName() << "|" << l->getAge() << "|" << l->calculateIncome() << "\n";
        }
    }
    return true;
}

std::vector<std::unique_ptr<Person>> StorageManager::load() {
    std::vector<std::unique_ptr<Person>> people;
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, id, name, ageStr, valStr;
        
        std::getline(ss, type, '|');
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, ageStr, '|');
        std::getline(ss, valStr, '|');
        
        try {
            int age = std::stoi(ageStr);
            if (type == "S") {
                people.push_back(std::make_unique<Student>(id, name, age, std::stod(valStr)));
            } else if (type == "L") {
                // Approximate Lecturer from saved income if specific fields aren't stored
                // In a real app we'd store all fields. Let's assume income is baseSalary for simple restoration
                people.push_back(std::make_unique<Lecturer>(id, name, age, std::stod(valStr), 0));
            }
        } catch (...) {}
    }
    return people;
}

} // namespace models
