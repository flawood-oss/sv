#pragma once
#include "models/Person.h"

namespace models {

class Lecturer : public Person {
private:
    double baseSalary;
    int publications;

public:
    Lecturer(const std::string& id, const std::string& name, int age, double baseSalary, int publications);
    
    double calculateIncome() const override;
    void displayInfo() const override;

    double getBaseSalary() const { return baseSalary; }
    int getPublications() const { return publications; }
    void setBaseSalary(double salary);
};

} // namespace models
