#pragma once
#include <vector>
#include <string>

using namespace std;

std::string escapeSqlString(const std::string& s);
vector<string> splitCsvRow(const string& line);
int callback(void* data, int argc, char** argv, char** azColName);
int Insert(int argc, char** argv);
void CreateTable(sqlite3* dbPtr, string createTableCommand);
vector<vector<string>> ReadCSV(ifstream inputCSV);
void CreateDatabase(sqlite3* dbPtr);
void ImportClasses(sqlite3* dbPtr);
void ImportSpells(sqlite3* dbPtr);
void ImportSpellLists(sqlite3* dbPtr);
void ImportData(sqlite3* dbPtr);
void SimpleSelect(sqlite3* dbPtr);
void ComplexSelect(sqlite3* dbPtr);
void UserDefinedSelect(sqlite3* dbPtr, string inputStatement);
void Exit();
