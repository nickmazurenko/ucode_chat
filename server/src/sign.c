#include "sign.h"

bool sign_up(char* request) {

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);

    // add to db

    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);

    cJSON_Delete(request_obj);

}

bool sign_in(char* request) {

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);

    // add to db

    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);

    cJSON_Delete(request_obj);
}