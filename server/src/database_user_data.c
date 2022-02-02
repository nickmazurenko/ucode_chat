#include "database.h"

size_t insert_data_user_data(t_model_user_data* model_user_data) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO UsersData(About, Status, TNumber, Email, Era, Money) VALUES('%s', %i, '%s', '%s', %i, %zu);";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_user_data->about, model_user_data->status, model_user_data->t_number, model_user_data->email, model_user_data->era, model_user_data->money);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t user_data_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return user_data_id;
}

int update_user_money(char *username, int add_money) {
    errno = 0;
    perror("there\n");
    size_t user_data_id = get_user_data_id(username);
    size_t money = get_user_money(username);
    if (add_money < 0 && abs(add_money) > money) 
        money = 0;
    else
        money += add_money;

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *update_request = "UPDATE UsersData SET Money = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, money);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
        // exit(1);
    }

    sqlite3_close(db);

    return 0;
}

size_t get_user_money(char *username) {
    size_t money = 0;
    size_t user_data_id = get_user_data_id(username);

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *select_request = "SELECT Money FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_money, &money, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    // sqlite3_close(db);

    return money;
}

int callback_get_user_money(void *data, int argc, char **argv, char **azColName) {

    if (argc == 0) {
        printf("error: callback_get_user_money: no user data with given id\n");
        fflush(stdout);
        return 1;
    }
    else {
        *((size_t *)data) = atol(argv[0]);
    }

    return 0;
}

