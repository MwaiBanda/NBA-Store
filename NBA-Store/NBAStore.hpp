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

class NBAStore {
public:
    NBAStore(sqlite3 *db);
    void initMenu();
private:
    sqlite3 *db;
};

#endif /* NBAStore_hpp */
