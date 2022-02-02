#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <libmx.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "model_user.h"
#include "model_user_data.h"
#include "model_message.h"
#include "model_resource.h"
#include "model_stone.h"

typedef struct s_db_array_data {

    void* array;
    bool  first;
    int   size;

}              t_db_array_data;

void init_tables();

#define DB "db.sqlite"

sqlite3* get_database();

int callback_print_db(void *not_used, int argc, char **argv, char **azColName);
void init_User_table();
int callback_count(void *not_used, int argc, char **argv, char **azColName);
bool is_user(char *username, char *password);
bool is_new_user(char *username);

t_db_array_data* create_db_array_data();

// User Table
size_t insert_data_user(char *username, char *password);
bool is_verified_user(char* username, char* token);
t_model_user* get_user_by_name(char* username);
size_t get_user_data_id(char *username);
size_t get_user_money(char *username);

// User Data Table
size_t insert_data_user_data(t_model_user_data* model_user_data);
int update_user_money(char *username, int add_money);
int callback_get_user_money(void *data, int argc, char **argv, char **azColName);

// Message Table
size_t insert_data_message(t_model_message* model_message);
cJSON* get_all_new_messages_of(char* username);
cJSON* get_all_messages_of(char* username);

// Resource Table
size_t insert_data_resource(t_model_resource* model_resource);

// Stones Table
size_t insert_data_stone(t_model_stone* model_stone);




#endif
