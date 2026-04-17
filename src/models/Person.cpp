#include "models/Person.h"
#include <stdexcept>

namespace models {

Person::Person(const std::string& id, const std::string& name, int age) 
    : id(id), name(name) {
    if (!isValidAge(age)) {
        throw std::invalid_argument("Invalid age provided!");
    }
    this->age = age;
}

Person::~Person() {}

} // namespace models
