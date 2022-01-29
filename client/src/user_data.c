#include "user_data.h"

static cJSON* cookies = NULL;

void generate_cookies() {


    cookies = cJSON_CreateObject();

    add_to_protocol_string(cookies, "USERNAME", "");
    add_to_protocol_string(cookies, "TOKEN",    "");

}

cJSON* get_cookies() {

    return cookies;

}