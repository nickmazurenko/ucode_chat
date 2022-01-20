#include "select_action.h"

int select_action(char* request, char* response) {

    *response = NULL;
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
        
        set_avatar(request);
    
    } else if ( strcmp(action, "GET FILE FOR WRITE") == 0 ) {

        file_for_write(response);
    
    } else if ( strcmp(action, "SAVE FILE") == 0 ) {

        save_file(request, response);
    
    } else if ( strcmp(action, "FILE END") == 0 ) {

        file_end(request, response);

    } else if (strcmp(action, "GET FILE") == 0) {
        
        char* response_buff = send_file_server(request);
        strcpy(response, response_buff);
    }

    cJSON_Delete(request_obj);

    return 0;
}