#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <libmx.h>
#include <string.h>

#define DB "db.sqlite"

int callback_print_db(void *not_used, int argc, char **argv, char **azColName);
void init_User_table();
int callback_count(void *not_used, int argc, char **argv, char **azColName);
bool is_user(char *username, char *password);
bool is_new_user(char *username);
void insert_data_user(char *username, char *password);

#endif
