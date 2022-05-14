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

using namespace std;

class NBAStore {
public:
    NBAStore(sqlite3 *db);
    int initMenu();

private:
    sqlite3* db;
    
    int mainMenu();
    int subMenu();
    void printMainMenuOptions();
    void printMenuOptions();
    int easternConference();
    int westernConference();
    Division* getEasternDivisions(sqlite3* db);
    Division* getWesternDivisions(sqlite3* db);

    static const int MAX_DIVISIONS;
    
};

#endif /* NBAStore_hpp */
