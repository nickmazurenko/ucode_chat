#include "database.h"

size_t insert_data_message(t_model_message* model_message) {

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *insert_request = "INSERT INTO Messages(FromUser, ToUser, Type, Data, Date, Status) VALUES('%s', '%s', %i, '%s', '%s', %i);";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_message->from_user, model_message->to_user, model_message->data_type, model_message->data, model_message->date, model_message->status);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t message_id = sqlite3_last_insert_rowid(get_database());
    // sqlite3_close(db);

    return message_id;

}

int callback_get_messages(void *data, int argc, char **argv, char **azColName) {

    t_db_array_data* db_array_data = (t_db_array_data*)data;

    if (db_array_data->first) {
        db_array_data->capacity = 10;
        db_array_data->array = malloc(sizeof(t_model_message*) * db_array_data->capacity);
        db_array_data->first = false;
    }

    if (db_array_data->size == db_array_data->capacity) {
        db_array_data->capacity += 10;
        db_array_data->array = realloc((t_model_message**)db_array_data->array, db_array_data->capacity * sizeof(t_model_message*));
    }

    t_model_message** array = (t_model_message**) db_array_data->array;
    int columns_number = 7;
    array[db_array_data->size] = (t_model_message*)new_model_message();
    for (int column_index = 0; column_index < columns_number; column_index++) {
        if (strcmp(azColName[column_index], "Id") == 0) {
            array[db_array_data->size]->id = atoi(argv[column_index]);
        } else if (strcmp(azColName[column_index], "FromUser") == 0) {
            strcpy(array[db_array_data->size]->from_user, argv[column_index]);
        } else if (strcmp(azColName[column_index], "ToUser") == 0) {
            strcpy(array[db_array_data->size]->to_user, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Type") == 0) {
            array[db_array_data->size]->data_type = atoi(argv[column_index]);
        } else if (strcmp(azColName[column_index], "Data") == 0) {
            strcpy(array[db_array_data->size]->data, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Date") == 0) {
            strcpy(array[db_array_data->size]->date, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Status") == 0) {
            array[db_array_data->size]->status = atoi(argv[column_index]);
        } else {
            perror("there we go but dont want\n");
        }

    }

    db_array_data->size++;

    return 0;
}

int update_message_status(size_t message_id, e_message_status message_status) {
    int err_status = 0;
    char *sql_query = NULL;
    char *update_request = "UPDATE Messages SET Status=%i WHERE Id=%zu;";
    asprintf(&sql_query, update_request, message_status, message_id);
    char *err_msg = NULL;

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, NULL, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        // sqlite3_close(db);
        exit(1);
    }
    return 0;
}

cJSON* get_all_new_messages_of(char* username) {
    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *sql_query = NULL;
    char *select_request = "SELECT * FROM Messages WHERE (ToUser=('%s') AND FromUser!=('%s') AND (STATUS=0));";
    asprintf(&sql_query, select_request, username, username);
    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_messages, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        exit(1);
    }

    t_model_message** messages = (t_model_message**)select_result->array;

    cJSON* str_array = cJSON_CreateArray();
    for (int message_index = 0; message_index < select_result->size; message_index++) {
        // if (messages[message_index]->status == MESSAGE_SENT) {
            if (messages[message_index]->status == MESSAGE_SENT) {
                update_message_status(messages[message_index]->id, MESSAGE_RECEIVED);
            }
            char* message_str = to_string_model_message(messages[message_index]);
            cJSON* item = cJSON_CreateString(message_str);
            free(message_str);
            cJSON_AddItemToArray(str_array, item);
        // }
        // TODO: set status in MESSAGE_RECEIVED after send
    }

    // sqlite3_close(db);

    return str_array;
}

cJSON* get_all_messages_of(char* username) {

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *sql_query = NULL;
    char *select_request = "SELECT * FROM Messages WHERE (FromUser=('%s') OR ToUser=('%s'));";
    asprintf(&sql_query, select_request, username, username);
    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_messages, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        // sqlite3_close(db);
        exit(1);
    }

    t_model_message** messages = (t_model_message**)select_result->array;
    cJSON* str_array = cJSON_CreateArray();

    for (int message_index = 0; message_index < select_result->size; message_index++) {
        
        if (messages[message_index]->status == MESSAGE_SENT) {
            update_message_status(messages[message_index]->id, MESSAGE_RECEIVED);
        }

        char* message_str = to_string_model_message(messages[message_index]);
        cJSON* item = cJSON_CreateString(message_str);
        free(message_str);
        cJSON_AddItemToArray(str_array, item);
    }

    // sqlite3_close(db);

    return str_array;
}