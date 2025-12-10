#pragma once

#include <string>

class SpellList
{
private:
    std::string spellName;
    std::string className;

public:
    // Setters
    void setSpellName(const std::string& newSpellName) { spellName = newSpellName; }
    void setClassName(const std::string& newClassName) { className = newClassName; }

    // Getters
    const std::string& getSpellName() const { return spellName; }
    const std::string& getClassName() const { return className; }
};
