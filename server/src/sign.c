#include "sign.h"

bool sign_up(char* request) {

    bool result = false;

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);

    // add to db
    if (is_new_user(user->name)) {
        insert_data_user(user->name, user->password);
        result = true;
    } 

    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);
    fflush(stdout);

    cJSON_Delete(request_obj);
    free_model_user(&user);

    return result;
}

bool sign_in(char* request) {

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);

    // check user in db

    if (is_user(user->name, user->password)) {

        printf("successfull\n");

    } else {
        printf("error\n");
    }

    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);

    cJSON_Delete(request_obj);
}