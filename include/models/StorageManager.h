#pragma once
#include <string>
#include <vector>
#include <memory>
#include "models/Person.h"

namespace models {

class StorageManager {
public:
    StorageManager(const std::string& filename);
    
    bool save(const std::vector<std::unique_ptr<Person>>& people);
    std::vector<std::unique_ptr<Person>> load();
    bool init();

private:
    std::string filename;
};

} // namespace models
