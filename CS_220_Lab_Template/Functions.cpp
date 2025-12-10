#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include "sqlite3.h"
#include "Class.h"
#include "Spell.h"
#include "SpellList.h"

using namespace std;

std::vector<std::string> splitCsvRow(const std::string& line) {
    std::vector<std::string> out;
    std::string cur;
    bool inQuotes = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            // toggle quote state; allow "" as escaped quote
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                cur.push_back('"');
                ++i;
            }
            else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes) {
            out.push_back(cur);
            cur.clear();
        }
        else {
            cur.push_back(c);
        }
    }
    out.push_back(cur);
    for (auto& s : out) {
        // remove surrounding quotes if present and trim
        std::string t = s;
        if (t.size() >= 2 && t.front() == '"' && t.back() == '"') {
            t = t.substr(1, t.size() - 2);
        }
        s = t;
    }
    return out;
}

std::vector<std::string> splitByComma(const std::string& inputString) {
    std::vector<std::string> output;
    std::stringstream ss(inputString);
    std::string token;
    while (std::getline(ss, token, ',')) {
        output.push_back(token);
    }
    return output;
}

std::string escapeSqlString(const std::string& s) {
    std::string result;
    for (char c : s) {
        if (c == '\'') result += "''";
        else result += c;
    }
    return "'" + result + "'";
}

vector<vector<string>> ReadCSV(string inputFile) {
    vector<vector<string>> readInfo;
    ifstream inputCSV;
    inputCSV.open(inputFile);
    while (!inputCSV.eof()) {
        string line;
        getline(inputCSV, line);
        readInfo.push_back(splitByComma(line));
    }
    return readInfo;
}

void ImportClasses(sqlite3* dbPtr) {
    vector<vector<string>> classInfo = ReadCSV("Classes.csv");
    vector<Class> classes;
    for (int i = 0; i < classInfo.size(); i++) {
        Class newClass;
        newClass.setName(classInfo[i][0]);
        newClass.setCasterType(classInfo[i][1]);
        classes.push_back(newClass);
    }

    for (int i = 0; i < classes.size(); i++) {
        std::stringstream insertCommand;
        char* errorMessage;
        insertCommand << "INSERT INTO Classes VALUES";
        insertCommand << "('" << classes[i].getName() << "', '" 
            << classes[i].getCasterType() << "');";
        int returnCode = sqlite3_exec(dbPtr, insertCommand.str().c_str(), NULL, 0, &errorMessage);
        if (returnCode != SQLITE_OK) {
            std::cerr << "SQL error inserting class: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
		}
    }
    std::cout << "Finished importing Classes.\n";
}

void ImportSpells(sqlite3* dbPtr) {
    vector<vector<string>> spellInfo = ReadCSV("Spells.csv");
    vector<Spell> spells;
    for (int i = 0; i < spellInfo.size(); i++) {
        Spell newSpell;
        newSpell.setSpellName(spellInfo[i][0]);
        newSpell.setLevel(stoi(spellInfo[i][1]));
		newSpell.setSchool(spellInfo[i][2]);
		newSpell.setCastingTime(spellInfo[i][3]);
		newSpell.setRange(spellInfo[i][4]);
        newSpell.setVerbal(static_cast<bool>(stoi(spellInfo[i][5])));
		newSpell.setSomatic(static_cast<bool>(stoi(spellInfo[i][6])));
		newSpell.setMaterial(static_cast<bool>(stoi(spellInfo[i][7])));
		newSpell.setConcentration(static_cast<bool>(stoi(spellInfo[i][8])));
		newSpell.setDuration(spellInfo[i][9]);
		newSpell.setCostlyMaterialComponent(static_cast<bool>(stoi(spellInfo[i][10])));
		newSpell.setCostlyMaterialComponentConsumed(static_cast<bool>(stoi(spellInfo[i][11])));
		newSpell.setRitual(static_cast<bool>(stoi(spellInfo[i][12])));
		newSpell.setSource(spellInfo[i][13]);
        spells.push_back(newSpell);
    }

    for (int i = 0; i < spells.size(); i++) {
        std::stringstream insertCommand;
        char* errorMessage;
        insertCommand << "INSERT INTO Spells VALUES";
        insertCommand << "(" << escapeSqlString(spells[i].getSpellName()) << ", "
			<< spells[i].getLevel() << ", "
            << escapeSqlString(spells[i].getSchool()) << ", "
			<< escapeSqlString(spells[i].getCastingTime()) << ", "
			<< escapeSqlString(spells[i].getRange()) << ", "
			<< spells[i].isVerbal() << ", "
			<< spells[i].isSomatic() << ", "
			<< spells[i].isMaterial() << ", "
			<< spells[i].isConcentration() << ", "
			<< escapeSqlString(spells[i].getDuration()) << ", "
			<< spells[i].hasCostlyMaterialComponent() << ", "
			<< spells[i].isCostlyMaterialComponentConsumed() << ", "
			<< spells[i].isRitual() << ", "
			<< escapeSqlString(spells[i].getSource()) << ");";
        int returnCode = sqlite3_exec(dbPtr, insertCommand.str().c_str(), NULL, 0, &errorMessage);
        if (returnCode != SQLITE_OK) {
            std::cerr << "SQL error inserting spell: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        }
    }
    std::cout << "Finished importing Spells.\n";
}

void ImportSpellLists(sqlite3* dbPtr) {
    vector<vector<string>> spellListInfo = ReadCSV("SpellLists.csv");
    vector<SpellList> spellLists;
    for (int i = 0; i < spellListInfo.size(); i++) {
        SpellList newSpellList;
        newSpellList.setSpellName(spellListInfo[i][0]);
        newSpellList.setClassName(spellListInfo[i][1]);
        spellLists.push_back(newSpellList);
    }

    for (int i = 0; i < spellLists.size(); i++) {
        std::stringstream insertCommand;
        char* errorMessage;
        insertCommand << "INSERT INTO SpellLists VALUES";
        insertCommand << "('" << spellLists[i].getSpellName() << "', '"
            << spellLists[i].getClassName() << "');";
        int returnCode = sqlite3_exec(dbPtr, insertCommand.str().c_str(), NULL, 0, &errorMessage);
        if (returnCode != SQLITE_OK) {
            std::cerr << "SQL error inserting spell list: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        }
    }
    std::cout << "Finished importing Spell Lists.\n";
}

int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = ";
        if (argv[i] == NULL) {
            std::cout << "NULL\n";
        }
        else {
            std::cout << argv[i] << '\n';;
        }
    }

    std::cout << "\n";
    return 0;
}

int Insert(int argc, char** argv) {
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open("example.db", &DB);
    std::string query = "SELECT * FROM PERSON;";

    std::cout << "STATE OF TABLE BEFORE INSERT" << std::endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    std::string sql("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
        "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
        "INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cout << "Error Insert - " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Records created Successfully!" << std::endl;
    }

    std::cout << "STATE OF TABLE AFTER INSERT" << std::endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    sql = "DELETE FROM PERSON WHERE ID = 2;";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cout << "Error DELETE" << std::endl;
        sqlite3_free(errorMessage);
    }
    else
        std::cout << "Record deleted Successfully!" << std::endl;

    std::cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << std::endl;
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
    return (0);
}

void CreateTable(sqlite3* dbPtr, std::string createTableCommand)
{
    char* errorMessage = nullptr;
    
    int returnCode = sqlite3_exec(dbPtr, createTableCommand.c_str(), NULL, 0, &errorMessage);
    if (returnCode != SQLITE_OK) {
        std::cerr << "SQL error creating a table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

void CreateDatabase(sqlite3* dbPtr) {
    system("cls");
    // Classes table
    std::string createClassesTable = "CREATE TABLE Classes("
        "ClassName TEXT PRIMARY KEY, "
        "CasterType TEXT"
        ");";
    CreateTable(dbPtr, createClassesTable);

    // Spell Lists Table
    std::string createSpellListsTable = "CREATE TABLE SpellLists("
        "SpellName TEXT REFERENCES Spells (Name), "
        "ClassName TEXT REFERENCES Classes (ClassName)"
        ");";
	CreateTable(dbPtr, createSpellListsTable);

    // Spells table
    std::string createSpellsTable = "CREATE TABLE Spells("
        "Name TEXT PRIMARY KEY, "
        "Level TEXT, "
        "School TEXT, "
        "CastingTime TEXT, "
        "Range TEXT, "
        "Verbal TEXT, "
        "Somatic TEXT, "
        "Material TEXT, "
        "Concentration TEXT, "
        "Duration TEXT, "
        "CostlyMaterialComponent TEXT, "
        "CostlyMaterialComponentConsumed TEXT, "
        "Ritual TEXT, "
        "Source TEXT"
        ");";
    CreateTable(dbPtr, createSpellsTable);
}

void ImportData(sqlite3* dbPtr) {
    system("cls");
    const int NUMBER_OF_TABLES = 3;
    std::array<std::string, NUMBER_OF_TABLES> fileNames = { "Classes.csv", "SpellLists.csv", "Spells.csv" };
    std::array<std::string, NUMBER_OF_TABLES> tableNames = { "Classes", "SpellLists", "Spells" };

    if (dbPtr == nullptr) {
        std::cout << "Database not created. Please create a database first\n\n";
    }
    else {
        ImportClasses(dbPtr);
        ImportSpells(dbPtr);
        ImportSpellLists(dbPtr);
    }

	std::cout << "Data imported successfully!\n\n\n";
}

void SimpleSelect(sqlite3* dbPtr) {
    char* errorMessage = nullptr;
    int returnCode;
    const std::string sql = "SELECT * FROM Classes;";

    std::cout << "SIMPLE SELECT: Contents of table 'Classes'\n\n\n";

    returnCode = sqlite3_exec(dbPtr, sql.c_str(), callback, NULL, &errorMessage);
    if (returnCode != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    std::cout << endl;
}

void ComplexSelect(sqlite3* dbPtr) {
    char* errorMessage = nullptr;
    int returnCode;

    std::cout << "COMPLEX SELECT: All spells on the Wizard's spell list\n\n\n";
    std::string wizard = "";
    wizard += '"';
	wizard.append("Wizard");
    wizard += '"';
    const std::string sql = "SELECT Spells.*, SpellLists.ClassName FROM Spells, SpellLists WHERE Spells.Name = SpellLists.SpellName AND SpellLists.ClassName = " + wizard;

    returnCode = sqlite3_exec(dbPtr, sql.c_str(), callback, NULL, &errorMessage);
    if (returnCode != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    std::cout << endl;
}

void UserDefinedSelect(sqlite3* dbPtr, std::string inputStatement) {
    char* errorMessage = nullptr;
    int returnCode;


    returnCode = sqlite3_exec(dbPtr, inputStatement.c_str(), callback, NULL, &errorMessage);
    if (returnCode != SQLITE_OK) {
        cerr << "\nSQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    std::cout << endl;
}

void Exit() {
    system("cls");
    std::cout << "Goodbye." << endl;
    std::cout.flush();
}
