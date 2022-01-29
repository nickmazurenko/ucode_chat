#include "messages_requests.h"

char* send_message(t_model_message* model_message, cJSON* protocol) {

    char* message_json = to_string_model_message(model_message);

    char* response = NULL;
    char* request = NULL;

    add_to_protocol_string(protocol, "ACTION", "SEND MSG");

    if (model_message->data_type == MESSAGE_TEXT) {

        

        add_to_protocol_string(protocol, "DATA", message_json);
        request = cJSON_Print(protocol);
        // TODO: check request size
        
        response = send_request(request, get_server_ip(), PORT);
        free(message_json);
        free(request);
        free(message_json);
    
    } else if (model_message->data_type == MESSAGE_FILE) {

        // after file json data == model_message


    } else if (model_message->data_type == MESSAGE_STONE) {
        // after file json data == model_message

    }

    return response;

}
