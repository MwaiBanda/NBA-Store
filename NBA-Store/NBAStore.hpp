//
//  NBAStore.hpp
//  NBA-Store
//
//  Created by Mwai Banda on 5/13/22.
//

#ifndef NBAStore_hpp
#define NBAStore_hpp

#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
#include "Division.h"
#include "Team.h"
#include "Game.h"
#include "Arena.h"

using namespace std;

class NBAStore {
public:
    NBAStore(sqlite3 *db);
    ~NBAStore();
    int initMenu();

    static const int MAX_DIVISIONS;
    static const int MAX_CONFERENCE_TEAMS;
    static const int MAX_CONFERENCE_ARENAS;
    static const int MAX_GAMES;
    
private:
    sqlite3* db;
    sqlite3_stmt *pRes;
    
    int mainMenu();
    int divisionsSubMenu();
    void printMainMenuOptions();
    void printMenuOptions();
    int easternConference();
    int westernConference();
    Division* getEasternDivisions(sqlite3* db);
    Division* getWesternDivisions(sqlite3* db);
    Team* getEasternTeams(sqlite3* db);
    Team* getWesternTeams(sqlite3* db);
    Game* getGames(sqlite3* db);
    Arena* getEasternArenas(sqlite3* db);
    Arena* getWesternArenas(sqlite3* db);
    
};

#endif /* NBAStore_hpp */
