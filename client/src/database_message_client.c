#include "database_client.h"

size_t insert_data_message(t_model_message* model_message) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Messages(Id, FromUser, ToUser, Type, Data, Date, Status) VALUES('%i', '%s', '%s', %i, '%s', '%s', %i);";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_message->id, model_message->from_user, model_message->to_user, model_message->data_type, model_message->data, model_message->date, model_message->status);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t message_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return message_id;

}

int callback_get_messages(void *data, int argc, char **argv, char **azColName) {
    printf("\n\n\nid %i\n", argc);
    fflush(stdout);
    t_db_array_data* db_array_data = (t_db_array_data*)data;

    if (db_array_data->first) {
        db_array_data->array = malloc(sizeof(t_model_message*) * argc);
        db_array_data->first = false;
    }

    t_model_message** array = (t_model_message**) db_array_data->array;
    int columns_number = 7;
    array[db_array_data->size] = new_model_message();

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
        }

    }

    db_array_data->size++;

    return 0;
}

t_model_message** get_all_messages_from_chat(char *from_user, int *size) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql_query = NULL;

    char *current_user = get_from_protocol_string(get_cookies(), "USERNAME");

    char *select_request = "SELECT * FROM Messages WHERE ((FromUser=('%s') OR FromUser=('%s')) AND (ToUser=('%s') OR ToUser=('%s')));";
    // char *select_request = "SELECT * FROM Messages WHERE FromUser=('%s');";

    asprintf(&sql_query, select_request, from_user, current_user, from_user, current_user);
    // asprintf(&sql_query, select_request, "f");

    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(db, sql_query, callback_get_messages, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    t_model_message** messages = (t_model_message**)select_result->array;

    // cJSON* str_array = cJSON_CreateArray();

    // for (int message_index = 0; message_index < select_result->size; message_index++) {
    //     char* message_str = to_string_model_message(messages[message_index]);
    //     cJSON* item = cJSON_CreateString(message_str);
    //     free(message_str);
    //     cJSON_AddItemToArray(str_array, item);
    // }
    *size = select_result->size;
    sqlite3_close(db);
    free(select_result);
    return messages;
}