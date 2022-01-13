#include "server.h"
#include "cJSON.h"

void run_server() {

    cJSON* object = cJSON_CreateObject();

    char* key = mx_strdup("hello");
    cJSON* value = cJSON_CreateString("hello\0HELLO");

    cJSON_AddItemToObject(object, key, value);
    // cJSON_AddItemToObject(object, "by", "by");

    char* string = cJSON_Print(object);

    printf(string);

    object = cJSON_Parse(string);

    value = cJSON_GetObjectItem(object, "hello");
    printf(value->string + 7);


}
