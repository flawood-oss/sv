#pragma once
#include <string>
#include <iostream>

namespace models {

class Person {
protected:
    std::string id;
    std::string name;
    int age;

public:
    Person(const std::string& id, const std::string& name, int age);
    virtual ~Person();

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }

    virtual double calculateIncome() const = 0;
    virtual void displayInfo() const = 0;
    
    static bool isValidAge(int age) { return age > 0 && age < 150; }
};

} // namespace models
