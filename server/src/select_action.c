#include "select_action.h"

int select_action(char* request) {

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

        sign_up(request);

    }

    else if ( strcmp(action, "SIGN IN") == 0 ) {

        sign_in(request);

    }

    cJSON_Delete(request_obj);

    return 0;
}