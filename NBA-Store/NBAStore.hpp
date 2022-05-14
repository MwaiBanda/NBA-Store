//
//  NBAStore.hpp
//  NBA-Store
//
//  Created by Mwai Banda on 5/13/22.
//

#ifndef NBAStore_hpp
#define NBAStore_hpp

#include <stdio.h>
#include "sqlite3.h"
#include <iostream>

using namespace std;

class NBAStore {
public:
    NBAStore(sqlite3 *db);
    int initMenu();
    
private:
    int mainMenu();
    int subMenu();
    void printMainMenuOptions();
    void printMenuOptions();
    int easternConference();
    int westernConference();
    sqlite3 *db;
};

#endif /* NBAStore_hpp */
