#include "select_action.h"

int select_action(char* request, char* response) {

    // *response = NULL;


    cJSON* request_obj = cJSON_Parse(request);

    if (request_obj == NULL) {
        printf("parse error\n");
        return 1;
    }

    cJSON* action_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "ACTION");
    if (action_obj == NULL) {
        printf("action obj error\n");
        return 1;
    }
    char* action = action_obj->valuestring;

    if ( strcmp(action, "SIGN UP") == 0 ) {

        sign_up(request, response);

    }

    else if ( strcmp(action, "SIGN IN") == 0 ) {

        sign_in(request, response);

    } else if ( strcmp(action, "SET AVATAR") == 0 ) {
        
        char* response_buff = set_avatar(request_obj);
        strcpy(response, response_buff);
        free(response_buff);
    
    } else if ( strcmp(action, "GET FILE FOR WRITE") == 0 ) {

        file_for_write(response);
    
    } else if ( strcmp(action, "SAVE FILE") == 0 ) {

        save_file(request, response);
    
    } else if ( strcmp(action, "FILE END") == 0 ) {

        file_end(request, response);

    } else if (strcmp(action, "GET FILE") == 0) {
        
        char* response_buff = send_file_server(request);
        strcpy(response, response_buff);
        free(response_buff);

    } else if (strcmp(action, "SEND MSG") == 0) {
        
        char* response_buff = add_message(request_obj);
        strcpy(response, response_buff);
        free(response_buff);
             
    } else if (strcmp(action, "GET MSGS") == 0) {

        char* response_buff = get_messages(request_obj);
        strcpy(response, response_buff);
        free(response_buff);

    } else if ( strcmp(action, "QUIZ" ) == 0 ) {

        // subaction: get question, check answer
        char* response_buff = quiz_server(request_obj);
        strcpy(response, response_buff);
        free(response_buff);

    } else if ( strcmp(action, "START_CHAT" ) == 0 ) {

        start_chat(request, response);

    } 

    cJSON_Delete(request_obj);

    return 0;
}