#include "messages_server.h"

char* add_message(cJSON* request) {

    char* username = get_from_protocol_string(request, "FROM");
    char* token    = get_from_protocol_string(request, "TOKEN");

    cJSON* response = create_protocol();

    if (is_verified_user(username, token)) {
        char* message_json = get_from_protocol_string(request, "DATA");
        t_model_message* model_message = from_string_model_message(message_json);
        strcpy(model_message->date, get_from_protocol_string(request, "DATE"));
        model_message->status = MESSAGE_SENT;

        insert_data_message(model_message);

        free_model_message(&model_message);

        add_to_protocol_string(response, "DATA", "OK");

    } else {
        add_to_protocol_string(response, "DATA", "ERROR");
    }

    char* response_json = cJSON_Print(response);
    cJSON_Delete(response);

    return response_json;

}