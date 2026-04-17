#include "models/Lecturer.h"
#include <iostream>

namespace models {

Lecturer::Lecturer(const std::string& id, const std::string& name, int age, double baseSalary, int publications)
    : Person(id, name, age), baseSalary(baseSalary), publications(publications) {}

double Lecturer::calculateIncome() const {
    // Thu nhập = Lương cứng + Thưởng bài báo (100$ mỗi bài)
    return baseSalary + (publications * 100.0);
}

void Lecturer::displayInfo() const {
    std::cout << "[Lecturer] ID: " << id 
              << " | Name: " << name 
              << " | Age: " << age 
              << " | Publications: " << publications 
              << " | Total Income: $" << calculateIncome() << std::endl;
}

void Lecturer::setBaseSalary(double salary) {
    if (salary < 0) throw std::invalid_argument("Salary cannot be negative");
    this->baseSalary = salary;
}

} // namespace models
