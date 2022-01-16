#include "sign_requests.h"

char* create_sign_request(t_model_user* model_user, char* action) {

    char* data = to_string_model_user(model_user);

    cJSON* protocol = create_protocol();
    
    cJSON* data_value = cJSON_CreateString(data);
    cJSON* action_value = cJSON_CreateString(action);

    add_to_protocol(protocol, "ACTION", action_value);
    add_to_protocol(protocol, "DATA", data_value);

    char* protocol_str = cJSON_Print(protocol);

    cJSON_Delete(protocol);

    return protocol_str;
}

bool send_sign_up_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN UP");
    char* response = send_request(request, "127.0.0.1", 5000);
    
    // check sign up

    printf("%s\n", response);

    return true;
}

bool send_sign_in_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN IN");
    char* response = send_request(request, "127.0.0.1", 5000);

    // check sign in

    printf("%s\n", response);

    return true;
}
