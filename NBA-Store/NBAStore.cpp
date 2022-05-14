//
//  NBAStore.cpp
//  NBA-Store
//
//  Created by Mwai Banda on 5/13/22.
//

#include "NBAStore.hpp"

const int NBAStore::MAX_DIVISIONS = 3;
const int NBAStore::MAX_CONFERENCE_TEAMS = 9;
const int NBAStore::MAX_GAMES = 8;

NBAStore::NBAStore(sqlite3 *db) {
    this->db = db;
}

NBAStore::~NBAStore(){
   
}

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

int NBAStore::divisionsSubMenu() {
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
    cout << "3. View Players" << endl;
    cout << "4. View Games" << endl;
    cout << "6. View Arenas" << endl;
    cout << "Enter Choice: ";
}

int NBAStore::easternConference() {
    int choice = divisionsSubMenu();
    while (true)
    {
        switch (choice)
        {
            case 1: getEasternDivisions(db); break;
            case 2: getEasternTeams(db); break;
            case 4: getGames(db); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = divisionsSubMenu();
    }
}

int NBAStore::westernConference() {
    int choice = divisionsSubMenu();
    while (true)
    {
        switch (choice)
        {
            case 1: getWesternDivisions(db); break;
            case 2: getWesternTeams(db); break;
            case 4: getGames(db); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = divisionsSubMenu();
    }
}

Division* NBAStore::getEasternDivisions(sqlite3* db){
    Division* divisions = new Division[MAX_DIVISIONS];
    string query = "SELECT Divisions.ID, Divisions.Name "\
    "FROM EasternConference "\
    "JOIN Divisions "\
    "ON Divisions.ID = EasternConference.DivisionID;";
    string errorMsg;
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

Team* NBAStore::getEasternTeams(sqlite3 *db){
    Team* teams = new Team[MAX_CONFERENCE_TEAMS];
    string query = "SELECT Teams.ID, Teams.Name, Coaches.Name, Cities.Name, Mascots.Name, Arenas.Name "\
    "FROM EasternConference "\
    "JOIN Divisions "\
    "ON Divisions.ID = EasternConference.DivisionID "\
    "JOIN Teams "\
    "ON Teams.DivisionID = Divisions.ID "\
    "JOIN Coaches "\
    "ON Coaches.ID = Teams.Coach "\
    "JOIN Mascots "\
    "ON Mascots.ID = Teams.Mascot "\
    "JOIN Cities "\
    "ON Cities.ID = Teams.City "\
    "JOIN Arenas "\
    "ON Arenas.ID = Teams.Arena;";
    string errorMsg;
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
            Team team = Team();
            team.ID = sqlite3_column_int(pRes, 0);
            team.name = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            team.coach = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 2));
            team.city = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 3));
            team.mascot = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 4));
            team.arena = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 5));
            teams[count] = team;
            count++;
        }
        
        
        sqlite3_reset(pRes);
    }
    return teams;
}


Team* NBAStore::getWesternTeams(sqlite3 *db){
    Team* teams = new Team[MAX_CONFERENCE_TEAMS];
    string query = "SELECT Teams.ID, Teams.Name, Coaches.Name, Cities.Name, Mascots.Name, Arenas.Name "\
    "FROM WesternConference "\
    "JOIN Divisions "\
    "ON Divisions.ID = WesternConference.DivisionID "\
    "JOIN Teams "\
    "ON Teams.DivisionID = Divisions.ID "\
    "JOIN Coaches "\
    "ON Coaches.ID = Teams.Coach "\
    "JOIN Mascots "\
    "ON Mascots.ID = Teams.Mascot "\
    "JOIN Cities "\
    "ON Cities.ID = Teams.City "\
    "JOIN Arenas "\
    "ON Arenas.ID = Teams.Arena;";
    string errorMsg;
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
            Team team = Team();
            team.ID = sqlite3_column_int(pRes, 0);
            team.name = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            team.coach = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 2));
            team.city = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 3));
            team.mascot = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 4));
            team.arena = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 5));
            teams[count] = team;
            count++;
        }
        
        
        sqlite3_reset(pRes);
    }
    return teams;
}


Game* NBAStore::getGames(sqlite3 *db){
    Game* games = new Game[MAX_GAMES];
    string query = "SELECT Games.ID, Games.Name, Games.Description, Games.Date, Arenas.Name,  Teams.Name, Games.Score "\
    "FROM Games "\
    "JOIN Arenas "\
    "ON Arenas.ID = Games.ArenaID "\
    "JOIN Teams "\
    "ON Teams.ID = Games.Winner;";
    string errorMsg;
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
            cout  << count + 1 << ". " << sqlite3_column_text(pRes, 1) << endl << sqlite3_column_text(pRes, 2)<< endl;
            cout << endl;
            Game game = Game();
            game.ID = sqlite3_column_int(pRes, 0);
            game.name = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            game.description = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 2));
            game.date = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 3));
            game.arena = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 4));
            game.winner = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 5));
            game.score = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 6));
            games[count] = game;
            count++;
        }
        
        
        sqlite3_reset(pRes);
    }
    return games;
}
