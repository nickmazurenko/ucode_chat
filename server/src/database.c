#include "database.h"


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

bool is_new_user(char *username) {
    int err_status = 0;

    sqlite3 *db;
    
    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } 

    char *sql_query = NULL;

    char *check_request = "SELECT * FROM Users WHERE Username=('%s');";

    asprintf(&sql_query, check_request, username);

    char *err_msg = NULL;
    
    int count = 0;

    if((err_status = sqlite3_exec(db, sql_query, callback_count, &count, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);


    if(count == 0)
        return true;
    return false;
}


bool is_user(char *username, char *password) {
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } 

    char *sql_query = NULL;

    char *check_request = "SELECT * FROM Users WHERE (Username=('%s') AND Password=('%s'));";

    asprintf(&sql_query, check_request, username, password);

    char *err_msg = NULL;
    
    int count = 0;

    if((err_status = sqlite3_exec(db, sql_query, callback_count, &count, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
    
    if(count == 0)
        return false;
    return true;
}

void insert_data_user(char *username, char *password) {
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    } 

    char *insert_request = "INSERT INTO Users(Username, Password) VALUES('%s', '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, username, password);

    
    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
        // exit(1);
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


