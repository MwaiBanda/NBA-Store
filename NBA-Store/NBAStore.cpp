//
//  NBAStore.cpp
//  NBA-Store
//
//  Created by Mwai Banda on 5/13/22.
//

#include "NBAStore.hpp"

NBAStore::NBAStore(sqlite3 *db) {
    this->db = db;
}

const int NBAStore::MAX_DIVISIONS = 3;

int NBAStore::initMenu() {
    int choice = mainMenu();
    while (true)
    {
        switch (choice)
        {
            case 1: easternConference(); break;
            case 2: westernConference(); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = mainMenu();
    }
}

int NBAStore::mainMenu(){
    int choice = 0;
    printMainMenuOptions();
    cin >> choice;
    while ((!cin || choice < 1 || choice > 6) && choice  != -1)
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000,'\n');
        }
        cout << "That is not a valid choice." << endl << endl;
        printMainMenuOptions();
        cin >> choice;
    }
    return choice;
}

int NBAStore::subMenu() {
    int choice = 0;
    printMenuOptions();
    cin >> choice;
    while ((!cin || choice < 1 || choice > 6) && choice  != -1)
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000,'\n');
        }
        cout << "That is not a valid choice." << endl << endl;
        printMenuOptions();
        cin >> choice;
    }
    return choice;
}

void NBAStore::printMainMenuOptions() {
    cout << "Welcome to the Please choose an option (enter -1 to quit):  " << endl;
    cout << "1. Eastern Conference" << endl;
    cout << "2. Southern Conference" << endl;
    cout << "Enter Choice: ";
}
void NBAStore::printMenuOptions() {
    cout << "\nPlease choose an option (enter -1 to go back):  " << endl;
    cout << "1. View Divisions" << endl;
    cout << "2. View Teams" << endl;
    cout << "4. View Players" << endl;
    cout << "5. View Games" << endl;
    cout << "6. View Arenas" << endl;
    cout << "Enter Choice: ";
}

int NBAStore::easternConference() {
    int choice = subMenu();
    while (true)
    {
        switch (choice)
        {
            case 1: getEasternDivisions(db); break;
            case 2: westernConference(); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = subMenu();
    }
}

int NBAStore::westernConference() {
    int choice = subMenu();
    while (true)
    {
        switch (choice)
        {
            case 1: getWesternDivisions(db); break;
            case 2: westernConference(); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = subMenu();
    }
}

Division* NBAStore::getEasternDivisions(sqlite3* db){
    Division* divisions = new Division[MAX_DIVISIONS];
    string query = "SELECT Divisions.ID, Divisions.Name "\
    "FROM EasternConference "\
    "JOIN Divisions "\
    "ON Divisions.ID = EasternConference.DivisionID;";
    string errorMsg;
    sqlite3_stmt *pRes;
    int count = 0;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        errorMsg = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        cout << "There was an error: " << errorMsg << endl;
    }
    else
    {
        cout << endl;
        while (sqlite3_step(pRes) == SQLITE_ROW)
        {
            cout  << count + 1 << ". " << sqlite3_column_text(pRes, 1);
            cout << endl;
            Division division = Division();
            division.ID = sqlite3_column_int(pRes, 0);
            division.name = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            divisions[count] = division;
            count++;
        }
        
        
        sqlite3_reset(pRes);
    }
    return divisions;
}

Division* NBAStore::getWesternDivisions(sqlite3* db){
    Division* divisions = new Division[MAX_DIVISIONS];
    string query = "SELECT Divisions.ID, Divisions.Name "\
    "FROM WesternConference "\
    "JOIN Divisions "\
    "ON Divisions.ID = WesternConference.DivisionID;";
    string errorMsg;
    sqlite3_stmt *pRes;
    int count = 0;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        errorMsg = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        cout << "There was an error: " << errorMsg << endl;
    }
    else
    {
        cout << endl;
        while (sqlite3_step(pRes) == SQLITE_ROW)
        {
            cout  << count + 1 << ". " << sqlite3_column_text(pRes, 1);
            cout << endl;
            Division division = Division();
            division.ID = sqlite3_column_int(pRes, 0);
            division.name = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            divisions[count] = division;
            count++;
        }
        
        
        sqlite3_reset(pRes);
    }
    return divisions;
}
