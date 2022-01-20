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
