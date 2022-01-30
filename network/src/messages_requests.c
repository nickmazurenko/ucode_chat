#include "messages_requests.h"
#include "user_data.h"

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
    
    } else if (model_message->data_type == MESSAGE_FILE) {

        // after file json data == model_message


    } else if (model_message->data_type == MESSAGE_STONE) {
        // after file json data == model_message

    }

    return response;

}

char* get_my_new_messages() {
    // something like get my messages
    // ACTION: GET MESSAGES
    // SUBACTION: GET NEW MSGS
    // SUBACTION: GET FILE WITH MSGS

}

char* get_my_messages() {
    // create table if not exist
    // get filename with temp messages json
    // get this file
    // parse json to array
    // parse all array elements to model_messages
    // add all messages to db
    // ACTION: GET MSGS
    // SUBACTION: GET ALL MSGS
    // SUBACTION: GET FILE WITH MSGS
    cJSON* protocol = create_protocol();

    char* username = get_from_protocol_string(get_cookies(), "username");
    char* token    = get_from_protocol_string(get_cookies(), "token");
    
    if (username == NULL || token == NULL) {
        printf("username or token is null\n"); fflush(stdout);
        cJSON_Delete(protocol);
        return "";
    }

    add_to_protocol_string(protocol, "FROM", username);
    add_to_protocol_string(protocol, "TOKEN", token);

    add_to_protocol_string(protocol, "ACTION", "GET MSGS");
    add_to_protocol_string(protocol, "SUBACTION", "GET FILE FOR MSGS");



}
