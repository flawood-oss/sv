#include "controllers/AppController.h"
#include "models/Student.h"
#include "models/Lecturer.h"

namespace controllers {

AppController::AppController() : running(true) {}

void AppController::run() {
    // Initial login
    bool authenticated = false;
    while (!authenticated) {
        authenticated = view.displayLogin(model.getAdminUser(), model.getAdminPass());
        if (!authenticated) {
            std::string retry = view.getInput("Retry login? (y/n): ");
            if (retry != "y" && retry != "Y") return;
        }
    }

    while (running) {
        view.displayMenu();
        int choice = view.getIntInput("");

        switch (choice) {
            case 1: handleAddStudent(); break;
            case 2: handleAddLecturer(); break;
            case 3: view.displayPeople(model.getAll()); break;
            case 4: handleSearch(); break;
            case 5: handleRemove(); break;
            case 6: 
                model.sortByIncome();
                view.displayMessage("Sorted by income descending.");
                view.displayPeople(model.getAll());
                break;
            case 7: handleStats(); break;
            case 8: handleExport(); break;
            case 9: handleSettings(); break;
            case 0: running = false; break;
            default: view.displayMessage("Invalid choice!");
        }
    }
}

void AppController::handleAddStudent() {
    view.displayHeader("ADD NEW STUDENT");
    try {
        std::string id = view.getInput("Enter Student ID (e.g. S001): ");
        std::string name = view.getInput("Enter Full Name: ");
        int age = view.getIntInput("Enter Age: ");
        double gpa = view.getDoubleInput("Enter GPA: ");
        
        model.addPerson(std::make_unique<models::Student>(id, name, age, gpa));
        view.displayMessage("Student registration successful.");
    } catch (const std::exception& e) {
        view.displayMessage("Registration failed: " + std::string(e.what()));
    }
}

void AppController::handleAddLecturer() {
    view.displayHeader("ADD NEW LECTURER");
    try {
        std::string id = view.getInput("Enter Lecturer ID (e.g. L001): ");
        std::string name = view.getInput("Enter Full Name: ");
        int age = view.getIntInput("Enter Age: ");
        double salary = view.getDoubleInput("Enter Base Salary: ");
        int pubs = view.getIntInput("Enter Publications count: ");
        
        model.addPerson(std::make_unique<models::Lecturer>(id, name, age, salary, pubs));
        view.displayMessage("Lecturer registration successful.");
    } catch (const std::exception& e) {
        view.displayMessage("Registration failed: " + std::string(e.what()));
    }
}

void AppController::handleSearch() {
    view.displayHeader("SEARCH RECORDS");
    std::string name = view.getInput("Enter partial or full name: ");
    std::vector<models::Person*> results = model.searchByName(name);
    view.displaySearchResults(results);
}

void AppController::handleRemove() {
    view.displayHeader("REMOVE PERSONNEL");
    std::string id = view.getInput("Enter ID to permanently remove: ");
    if (model.removePerson(id)) {
        view.displayMessage("Personnel record removed successfully.");
    } else {
        view.displayMessage("Error: Personnel ID not found in system.");
    }
}

void AppController::handleStats() {
    auto stats = model.getStats();
    view.displayStats(stats.total, stats.avgAge, stats.avgIncome, model.calculateTotalBudget());
}

void AppController::handleExport() {
    view.displayHeader("EXPORT DATA");
    std::string filename = view.getInput("Output filename (e.g. report_apr17.txt): ");
    model.exportToText(filename);
    view.displayMessage("Report successfully exported to " + filename);
}

void AppController::handleSettings() {
    view.displayHeader("SYSTEM SETTINGS");
    std::string confirm = view.getInput("Change current Admin credentials? (y/n): ");
    if (confirm == "y" || confirm == "Y") {
        std::string newUser = view.getInput("New Username: ");
        std::string newPass = view.getInput("New Password: ");
        
        if (newUser.length() < 3 || newPass.length() < 3) {
            view.displayMessage("Error: Username/Password must be at least 3 characters.");
            return;
        }
        
        model.updateCredentials(newUser, newPass);
        view.displayMessage("Credentials updated successfully. They will apply from next login.");
    }
}

} // namespace controllers
