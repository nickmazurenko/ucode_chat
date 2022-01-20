#include "database.h"

size_t insert_data_stone(t_model_stone* model_stone) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Resources(Path) VALUES('%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_stone->path);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t stone_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return stone_id;

}