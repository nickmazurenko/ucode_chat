#include "database.h"

char* table_names[] = {
    "Users",
    "UsersData",
    "Messages",
    "Resources",
    "Stones",
    NULL
};

char* tables_init[] = {

    "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT, Password TEXT, UserData INTEGER) ;",
    "CREATE TABLE IF NOT EXISTS UsersData (Id INTEGER PRIMARY KEY AUTOINCREMENT, About TEXT, Status INTEGER, TNumber CHAR, Email TEXT, Era INTEGER, Money INTEGER, LastUpdate CHAR) ;",
    "CREATE TABLE IF NOT EXISTS Messages (Id INTEGER PRIMARY KEY AUTOINCREMENT, FromUser INTEGER, ToUser INTEGER, Type INTEGER, Data TEXT, Date CHAR, Status INTEGER) ;",
    "CREATE TABLE IF NOT EXISTS Resources (Id INTEGER PRIMARY KEY AUTOINCREMENT, Path TEXT, Name TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Stones (Id INTEGER PRIMARY KEY AUTOINCREMENT, Path TEXT) ;",
    NULL
};

void init_tables() {

    sqlite3 *db = NULL;
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *err_msg = NULL;

    for (int table_index = 0; tables_init[table_index] != NULL; table_index++) {
        if((err_status = sqlite3_exec(db, tables_init[table_index], 0, 0, &err_msg)) != SQLITE_OK) {
            fprintf(stderr, "SQL_error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
    }

    sqlite3_close(db);
}

void init_User_table() {
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }    

    char *init_request = "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT, Password TEXT) ;";
                         
    char *err_msg = NULL;

    if((err_status = sqlite3_exec(db, init_request, 0, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
}



int callback_print_db(void *not_used, int argc, char **argv, char **azColName) {
    not_used = 0;

    for(int row_idx = 0; row_idx < argc; row_idx++) {
        printf("%s = %s\n", azColName[row_idx], argv[row_idx] ? argv[row_idx] : "NULL");
        fflush(stdout);
    }
    printf("\n");

    return 0;
}

int callback_count(void *data, int argc, char **argv, char **azColName) {

    *((int*)data) = argc;

    return 0;
}


