#pragma once

#include <string>

class Class
{
private:
    std::string name;
    std::string casterType;

public:
    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setCasterType(const std::string& newCasterType) { casterType = newCasterType; }

    // Getters
    const std::string& getName() const { return name; }
    const std::string& getCasterType() const { return casterType; }
};
