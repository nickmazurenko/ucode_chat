#include "messages_server.h"
#include "file_for_write.h"

char* add_message(cJSON* request) {

    char* username = get_from_protocol_string(request, "FROM");
    char* token    = get_from_protocol_string(request, "TOKEN");

    cJSON* response = create_protocol();
 
    if (is_verified_user(username, token)) {
        char* message_json = get_from_protocol_string(request, "DATA");
        t_model_message* model_message = from_string_model_message(message_json);
        strcpy(model_message->date, get_from_protocol_string(request, "DATE"));
        model_message->status = MESSAGE_SENT;

        int msg_id = insert_data_message(model_message);

        model_message->id = msg_id;

        add_to_protocol_string(response, "DATA", to_string_model_message(model_message));

        free_model_message(&model_message);

        
        
    } else {
        add_to_protocol_string(response, "DATA", "ERROR");
    }
    
    char* response_json = cJSON_Print(response);
    cJSON_Delete(response);

    return response_json;

}

char* get_messages(cJSON* request) {


    char* username = get_from_protocol_string(request, "FROM");
    char* token    = get_from_protocol_string(request, "TOKEN");

    cJSON* response = create_protocol();
    cJSON* messages = NULL;


    char* response_json = NULL;

    if (is_verified_user(username, token)) {

        char* subaction = get_from_protocol_string(request, "SUBACTION");



        if (subaction == NULL) {
            
            add_to_protocol_string(response, "STATUS", "ERROR");
            printf("Error: Get messages: Subaction is null\n"); fflush(stdout);

        } else {

            if (strcmp(subaction, "GET ALL MSGS") == 0) {
                
                messages = json_get_all_messages_of(username);

            } else if (strcmp(subaction, "GET NEW MSGS") == 0) {

                messages = json_get_new_messages_of(username);

            } else {
                
                add_to_protocol_string(response, "STATUS", "ERROR");
                printf("Error: Get messages: Subaction is undefined\n");
                fflush(stdout);
            }

        }

        if (messages) {
        
            char* messages_str = cJSON_Print(messages);

            char* file_name = get_next_file_for_write();
            char* path_to_file = "./server/resources/tmp/";
            
            path_to_file = mx_strjoin(path_to_file, file_name);

            FILE* file = fopen(path_to_file, "w");

            fwrite(messages_str, sizeof(char), strlen(messages_str), file);


            fclose(file);

            free(path_to_file);
            path_to_file = "/resources/tmp/";
            path_to_file = mx_strjoin(path_to_file, file_name);

            add_to_protocol_string(response, "DATA", path_to_file);
            add_to_protocol_string(response, "STATUS", "OK");

            free(file_name);
            free(path_to_file);

            cJSON_Delete(messages);

        }

    } else {
        add_to_protocol_string(response, "STATUS", "ERROR");
    }

    response_json = cJSON_Print(response);


    return response_json;
}

bool start_chat(char *request, char *response) {
    bool result = false;


    cJSON* request_obj = cJSON_Parse(request);
    if(request_obj == NULL){
        perror("parse error sign in");
    }

    char *username_to_find = get_from_protocol_string(request_obj, "DATA");

    if(request_obj == NULL){
        perror("get obj error sign in");
    }


    cJSON *start_chat_status = create_protocol();

    // check user in db
        perror("START_CHAT_ERROR");

    if (!is_new_user(username_to_find)) {
        add_to_protocol_string(start_chat_status, "STATUS", "SUCCESS");
        result = true;
    } else {
        result = false;
        add_to_protocol_string(start_chat_status, "STATUS", "ERORR");
    }

    strcpy(response, cJSON_Print(start_chat_status));

    cJSON_Delete(request_obj);
    cJSON_Delete(start_chat_status);
    // cJSON_Delete(user_json);

    return result;
}
