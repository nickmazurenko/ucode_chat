#include "database.h"

size_t insert_data_user_data(t_model_user_data* model_user_data) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO UsersData(About, Status, TNumber, Email, Era, Money, AvatarId) VALUES('%s', %i, '%s', '%s', %i, %zu, %zu);";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_user_data->about, model_user_data->status, model_user_data->t_number, model_user_data->email, model_user_data->era, model_user_data->money, model_user_data->avatar_id);

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

int update_user_avatar(char* username, int avatar_id) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);


    int err_status = 0;

    char *update_request = "UPDATE UsersData SET AvatarId = '%i' WHERE Id=%zu;";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, avatar_id, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }


    return 0;
}

int update_user_money(char *username, int add_money) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    size_t money = get_user_money(username);
    if (add_money < 0 && abs(add_money) > money) 
        money = 0;
    else
        money += add_money;

    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET Money = '%zu' WHERE Id=%zu;";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, money, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }


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

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_size_t, &money, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    // sqlite3_close(db);

    return money;
}

int callback_get_user_size_t(void *data, int argc, char **argv, char **azColName) {

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

//////////////////////////////////////////////////////////////////

int update_user_about(char *username, char *about) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET About = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, about, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_about(char *username) {
    char *about = mx_strnew(ABOUT_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT About FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &about, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return about;
}

int callback_get_user_str(void *data, int argc, char **argv, char **azColName) {

    if (argc == 0) {
        printf("error: callback_get_user_about: no user data with given id\n");
        fflush(stdout);
        return 1;
    }
    else {
        *((char**)data) = argv[0];
    }

    return 0;
}

//////////////////////////////////////////////////////////////////

int update_user_tnumber(char *username, char *tnumber) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET TNumber = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, tnumber, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_tnumber(char *username) {
    char *tnumber = mx_strnew(T_NUMBER_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT TNumber FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &tnumber, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return tnumber;
}

//////////////////////////////////////////////////////////////////

int update_user_email(char *username, char *email) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET Email = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, email, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_email(char *username) {
    char *email = mx_strnew(EMAIL_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT Email FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &email, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return email;
}


