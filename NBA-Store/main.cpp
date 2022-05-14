//
//  main.cpp
//  NBA-Store
//
//  Created by Mwai Banda on 5/13/22.
//

#include <iostream>
#include "sqlite3.h"
#include "NBAStore.hpp"

int main(int argc, const char * argv[]) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mwaibanda/Repository/Main Projects/Command Line Projects/NBA-Store/NBA-Store/NBA.db", &db);
    
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    } else {
        fprintf(stderr, "Opened database successfully\n");
        NBAStore store = NBAStore(db);
        store.initMenu();
   
        
    }
    return 0;
}
