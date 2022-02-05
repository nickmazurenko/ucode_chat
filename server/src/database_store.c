#include "database.h"

size_t insert_data_store(t_model_store* model_store) {
    
    int err_status = 0;

    char *insert_request = "INSERT INTO Store (Path, Name, Price, Era) VALUES('%s', '%s', '%zu', '%zu');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_store->path, model_store->name, model_store->price, model_store->era);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        // sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t store_item_id = sqlite3_last_insert_rowid(get_database());

    return store_item_id;

}


int callback_get_store(void *data, int argc, char **argv, char **azColName) {
    t_model_store *store = (t_model_store*)data;

    if(argc != 0) {
        for(int column_index = 0; column_index < argc; column_index++) {
            if(!mx_strcmp(azColName[column_index], "Id"))
                store->id = atoi(argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Path"))
                mx_strcpy(store->path, argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Name"))
                mx_strcpy(store->name, argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Price"))
                store->price = atoi(argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Era"))
                store->era = atoi(argv[column_index]);
        }
    }

    return 0;
}


t_model_store *get_store_by_era(int era) {

    int err_status = 0;

    char *select_request = "SELECT * FROM Store WHERE Era=('%i');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, era);

    t_model_store *model_store = new_model_store();
    // model_resource->id = id;
    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_store, model_store, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return model_store;

}

void fill_database_store() {
    t_model_store *next_era_for_stone_age = new_model_store();
    strcpy(next_era_for_stone_age->name, "next era for stone age");
    strcpy(next_era_for_stone_age->path, "../resources/store/images/");
    next_era_for_stone_age->price = 70;
    next_era_for_stone_age->era = 0;
    size_t next_era_for_stone_age_int = insert_data_store(next_era_for_stone_age);

    t_model_store *clear_stone = new_model_store();
    strcpy(clear_stone->name, "clear stone");
    strcpy(clear_stone->path, "../resources/store/images/");
    clear_stone->price = 7;
    clear_stone->era = 0;
    size_t clear_stone_int = insert_data_store(clear_stone);

    t_model_store *rock1 = new_model_store();
    strcpy(rock1->name, "rock1");
    strcpy(rock1->path, "../resources/store/images/");
    rock1->price = 15;
    rock1->era = 0;
    size_t rock1_int = insert_data_store(rock1);

    t_model_store *rock2 = new_model_store();
    strcpy(rock2->name, "rock2");
    strcpy(rock2->path, "../resources/store/images/");
    rock2->price = 15;
    rock2->era = 0;
    size_t rock2_int = insert_data_store(rock2);

    t_model_store *rock3 = new_model_store();
    strcpy(rock3->name, "rock3");
    strcpy(rock3->path, "../resources/store/images/");
    rock3->price = 15;
    rock3->era = 0;
    size_t rock3_int = insert_data_store(rock3);

    t_model_store *rock4 = new_model_store();
    strcpy(rock4->name, "rock4");
    strcpy(rock4->path, "../resources/store/images/");
    rock4->price = 15;
    rock4->era = 0;
    size_t rock4_int = insert_data_store(rock4);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_egypt = new_model_store();
    strcpy(next_era_for_egypt->name, "next era for egypt");
    strcpy(next_era_for_egypt->path, "../resources/store/images/");
    next_era_for_egypt->price = 80;
    next_era_for_egypt->era = 1;
    size_t next_era_for_egypt_int = insert_data_store(next_era_for_egypt);

    t_model_store *new_words_5 = new_model_store();
    strcpy(new_words_5->name, "5 new words");
    strcpy(new_words_5->path, "../resources/store/images/");
    new_words_5->price = 10;
    new_words_5->era = 1;
    size_t new_words_5_int = insert_data_store(new_words_5);

    t_model_store *new_words_10 = new_model_store();
    strcpy(new_words_10->name, "10 new words");
    strcpy(new_words_10->path, "../resources/store/images/");
    new_words_10->price = 18;
    new_words_10->era = 1;
    size_t new_words_10_int = insert_data_store(new_words_10);

    t_model_store *new_words_15 = new_model_store();
    strcpy(new_words_15->name, "15 new words");
    strcpy(new_words_15->path, "../resources/store/images/");
    new_words_15->price = 26;
    new_words_15->era = 1;
    size_t new_words_15_int = insert_data_store(new_words_15);

    t_model_store *new_words_20 = new_model_store();
    strcpy(new_words_20->name, "20 new words");
    strcpy(new_words_20->path, "../resources/store/images/");
    new_words_20->price = 35;
    new_words_20->era = 1;
    size_t new_words_20_int = insert_data_store(new_words_20);

    t_model_store *new_words_50 = new_model_store();
    strcpy(new_words_50->name, "50 new words");
    strcpy(new_words_50->path, "../resources/store/images/");
    new_words_50->price = 70;
    new_words_50->era = 1;
    size_t new_words_50_int = insert_data_store(new_words_50);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_middle_ages = new_model_store();
    strcpy(next_era_for_middle_ages->name, "next era for middle ages");
    strcpy(next_era_for_middle_ages->path, "../resources/store/images/");
    next_era_for_middle_ages->price = 90;
    next_era_for_middle_ages->era = 2;
    size_t next_era_for_middle_ages_int = insert_data_store(next_era_for_middle_ages);

    t_model_store *color1 = new_model_store();
    strcpy(color1->name, "color1");
    strcpy(color1->path, "../resources/store/images/");
    color1->price = 20;
    color1->era = 2;
    size_t color1_int = insert_data_store(color1);

    t_model_store *color2 = new_model_store();
    strcpy(color2->name, "color2");
    strcpy(color2->path, "../resources/store/images/");
    color2->price = 20;
    color2->era = 2;
    size_t color2_int = insert_data_store(color2);

    t_model_store *color3 = new_model_store();
    strcpy(color3->name, "color3");
    strcpy(color3->path, "../resources/store/images/");
    color3->price = 20;
    color3->era = 2;
    size_t color3_int = insert_data_store(color3);

    t_model_store *middle_ages_background1 = new_model_store();
    strcpy(middle_ages_background1->name, "middle ages background1");
    strcpy(middle_ages_background1->path, "../resources/store/images/");
    middle_ages_background1->price = 40;
    middle_ages_background1->era = 2;
    size_t middle_ages_background1_int = insert_data_store(middle_ages_background1);

    t_model_store *middle_ages_background2 = new_model_store();
    strcpy(middle_ages_background2->name, "middle ages background2");
    strcpy(middle_ages_background2->path, "../resources/store/images/");
    middle_ages_background2->price = 40;
    middle_ages_background2->era = 2;
    size_t middle_ages_background2_int = insert_data_store(middle_ages_background2);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_enlightment = new_model_store();
    strcpy(next_era_for_enlightment->name, "next era for enlightment");
    strcpy(next_era_for_enlightment->path, "../resources/store/images/");
    next_era_for_enlightment->price = 100;
    next_era_for_enlightment->era = 3;
    size_t nnext_era_for_enlightment_int = insert_data_store(next_era_for_enlightment);

    t_model_store *send_files_unlock = new_model_store();
    strcpy(send_files_unlock->name, "unlock sending files");
    strcpy(send_files_unlock->path, "../resources/store/images/");
    send_files_unlock->price = 90;
    send_files_unlock->era = 3;
    size_t send_files_unlock_int = insert_data_store(send_files_unlock);
    
    t_model_store *no_mistakes = new_model_store();
    strcpy(no_mistakes->name, "educate");
    strcpy(no_mistakes->path, "../resources/store/images/");
    no_mistakes->price = 75;
    no_mistakes->era = 3;
    size_t no_mistakes_int = insert_data_store(no_mistakes);
    
    t_model_store *enlightment_background1 = new_model_store();
    strcpy(enlightment_background1->name, "enlightment background1");
    strcpy(enlightment_background1->path, "../resources/store/images/");
    enlightment_background1->price = 40;
    enlightment_background1->era = 3;
    size_t enlightment_background1_int = insert_data_store(enlightment_background1);

    t_model_store *enlightment_background2 = new_model_store();
    strcpy(enlightment_background2->name, "enlightment background2");
    strcpy(enlightment_background2->path, "../resources/store/images/");
    enlightment_background2->price = 40;
    enlightment_background2->era = 3;
    size_t enlightment_background2_int = insert_data_store(enlightment_background2);

    t_model_store *enlightment_background3 = new_model_store();
    strcpy(enlightment_background3->name, "enlightment background3");
    strcpy(enlightment_background3->path, "../resources/store/images/");
    enlightment_background3->price = 40;
    enlightment_background3->era = 3;
    size_t enlightment_background3_int = insert_data_store(enlightment_background3);

    ///////////////////////////////////////////////////

    t_model_store *prize = new_model_store();
    strcpy(prize->name, "gift");
    strcpy(prize->path, "../resources/store/images/");
    prize->price = 238;
    prize->era = 4;
    size_t prize_int = insert_data_store(prize);

}
