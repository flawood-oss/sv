#pragma once
#include "models/Person.h"

namespace models {

class Student : public Person {
private:
    double gpa;

public:
    Student(const std::string& id, const std::string& name, int age, double gpa);
    
    double calculateIncome() const override; 
    void displayInfo() const override;

    double getGpa() const { return gpa; }
    void setGpa(double gpa);
};

} // namespace models
