#include "sign_requests.h"

char* create_sign_request(t_model_user* model_user, char* action) {

    char* data = to_string_model_user(model_user);

    cJSON* protocol = cJSON_CreateObject();
    
    cJSON* data_value = cJSON_CreateString(data);
    cJSON* action_value = cJSON_CreateString(action);
    char* date = mx_strnew(1025);
    time_t now_time = time(NULL);
    snprintf(date, 1024, "%.24s", ctime(&now_time));
    cJSON* date_value = cJSON_CreateString(date);

    cJSON_AddItemToObject(protocol, "DATE", date_value);
    cJSON_AddItemToObject(protocol, "ACTION", action_value);
    cJSON_AddItemToObject(protocol, "DATA", data_value);

    return cJSON_Print(protocol);
}

bool send_sign_up_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN UP");
    char* response = send_request(request, "127.0.0.1", 5000);
    
    printf("%s\n", response);

    return true;
}

bool send_sign_in_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN IN");
    char* response = send_request(request, "127.0.0.1", 5000);
    
    printf("%s\n", response);

    return true;
}
