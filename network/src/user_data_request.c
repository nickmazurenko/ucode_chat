#include "user_data_request.h"

t_model_user_data* send_user_data_request(char *username) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_USER_DATA");

    add_to_protocol_string(protocol, "DATA", username);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_user_data_model = cJSON_Parse(response);

    t_model_user_data *model_user_data = new_model_user_data();

    // printf("GET USER DATA RESSPONSE%s\n", response);
    // fflush(stdout);

    model_user_data = from_string_model_user_data(get_from_protocol_string(response_user_data_model, "DATA"));

    // char *client_path = mx_replace_substr(model_resource->path, "./server", "./client");

   return model_user_data;
}

size_t send_money_request(size_t user_data_id) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "GET_USER_MONEY");

    add_to_protocol_number(protocol, "DATA", user_data_id);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_money = cJSON_Parse(response);

    // t_model_user_data *model_user_data = new_model_user_data();
    size_t money = get_from_protocol_number(response_money, "DATA");

    
    // model_user_data = from_string_model_user_data(get_from_protocol_string(response_resource_model, "DATA"));

    // char *client_path = mx_replace_substr(model_resource->path, "./server", "./client");

   return money;
}
