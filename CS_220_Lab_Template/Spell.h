#pragma once

#include <string>

class Spell
{
private:
    std::string spellName;
    int level;
    std::string school;
    std::string castingTime;
    std::string range;
    bool verbal;
    bool somatic;
    bool material;
    bool concentration;
    std::string duration;
    bool costlyMaterialComponent;
    bool costlyMaterialComponentConsumed;
    bool ritual;
    std::string source;

public:
    // Getters
    const std::string& getSpellName() const { return spellName; }
    int getLevel() const { return level; }
    const std::string& getSchool() const { return school; }
    const std::string& getCastingTime() const { return castingTime; }
    const std::string& getRange() const { return range; }
    bool isVerbal() const { return verbal; }
    bool isSomatic() const { return somatic; }
    bool isMaterial() const { return material; }
    bool isConcentration() const { return concentration; }
	std::string getDuration() const { return duration; }
    bool hasCostlyMaterialComponent() const { return costlyMaterialComponent; }
    bool isCostlyMaterialComponentConsumed() const { return costlyMaterialComponentConsumed; }
    bool isRitual() const { return ritual; }
    const std::string& getSource() const { return source; }

    // Setters
    void setSpellName(const std::string& name) { spellName = name; }
    void setLevel(int lvl) { level = lvl; }
    void setSchool(const std::string& sch) { school = sch; }
    void setCastingTime(const std::string& time) { castingTime = time; }
    void setRange(const std::string& rng) { range = rng; }
    void setVerbal(bool value) { verbal = value; }
    void setSomatic(bool value) { somatic = value; }
    void setMaterial(bool value) { material = value; }
    void setConcentration(bool value) { concentration = value; }
	void setDuration(const std::string& dur) { duration = dur; }
    void setCostlyMaterialComponent(bool value) { costlyMaterialComponent = value; }
    void setCostlyMaterialComponentConsumed(bool value) { costlyMaterialComponentConsumed = value; }
    void setRitual(bool value) { ritual = value; }
    void setSource(const std::string& src) { source = src; }
};
