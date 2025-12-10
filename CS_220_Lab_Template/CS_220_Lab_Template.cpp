#include <iostream>
#include "sqlite3.h"
#include <string>
#include <algorithm>
#include <Windows.h>
#include "Functions.h"

using namespace std;

int main()
{
    int choice = 0;

    sqlite3* dbPtr = nullptr;
    int returnCode = sqlite3_open("5eSpells.db", &dbPtr);
    system("cls");
    if (returnCode) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(dbPtr) << std::endl;
    }
    else {
        std::cerr << "Opened database successfully.\n" << std::endl;
    }

    while (true)
    {
        std::cout << "Menu\n";
        std::cout << "1) Create Database.\n";
        std::cout << "2) Import Data.\n";
        std::cout << "3) Perform Simple <SELECT statement of your choosing>.\n";
        std::cout << "4) Perform Complex <SELECT statement of your choosing>.\n";
        std::cout << "5) Perform User-defined SELECT statement.\n";
        std::cout << "6) Exit\n";
        std::cout << "Enter choice: ";

		cin >> choice;
        switch (choice)
        {
        case 1:
            CreateDatabase(dbPtr);
            break;
        case 2:
            ImportData(dbPtr);
            break;
        case 3:
            SimpleSelect(dbPtr);
            break;
        case 4:
            ComplexSelect(dbPtr);
            break;
        case 5:
            system("cls");
            std::cout << "Enter the statement you would like to run: ";
            {
                std::string userQuery;
                std::string trash;
                std::getline(cin, trash);
                std::getline(cin, userQuery);
                UserDefinedSelect(dbPtr, userQuery);
            }
            break;
        case 6:
            Exit();
            sqlite3_close(dbPtr);
            return 0;
        default:
            system("cls");
            std::cout << "Invalid choice. Please select 1-6.\n\n";
            break;
        }
    }
    return 0;
}
