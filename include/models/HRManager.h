#pragma once
#include "models/Person.h"
#include "models/StorageManager.h"
#include <vector>
#include <memory>

namespace models {

class HRManager {
private:
    std::vector<std::unique_ptr<Person>> people;
    StorageManager storage;
    std::string adminUser;
    std::string adminPass;

    void loadAuth();
    void saveAuth();

public:
    HRManager();
    ~HRManager();

    void addPerson(std::unique_ptr<Person> person);
    bool removePerson(const std::string& id);
    Person* findPerson(const std::string& id) const;
    
    const std::vector<std::unique_ptr<Person>>& getAll() const { return people; }
    
    void sortByIncome();
    double calculateTotalBudget() const;

    // Authentication
    const std::string& getAdminUser() const { return adminUser; }
    const std::string& getAdminPass() const { return adminPass; }
    void updateCredentials(const std::string& newUser, const std::string& newPass);

    // Advanced Features
    std::vector<Person*> searchByName(const std::string& name) const;
    struct Statistics {
        int total;
        int students;
        int lecturers;
        double avgAge;
        double avgIncome;
    };
    Statistics getStats() const;
    void exportToText(const std::string& filename) const;
};

} // namespace models
