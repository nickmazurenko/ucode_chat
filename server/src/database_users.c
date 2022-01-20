#include "database.h"

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

size_t insert_data_user(char *username, char *password) {
    

    t_model_user_data* user_data = new_model_user_data();
    size_t user_data_id = insert_data_user_data(user_data);
    free_model_user_data(&user_data);

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Users(Username, Password, UserData) VALUES('%s', '%s', '%zu');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, username, password, user_data_id);

    
    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t user_id = sqlite3_last_insert_rowid(db);

    sqlite3_close(db);

    return user_id;
}