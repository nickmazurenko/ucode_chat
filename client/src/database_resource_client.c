#include "database_client.h"


size_t insert_data_resource(t_model_resource* model_resource) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Resources(Path, Name) VALUES('%s', '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_resource->path, model_resource->name);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t resource_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return resource_id;

}