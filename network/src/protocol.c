#include "protocol.h"

cJSON* create_protocol() {

    cJSON* protocol = cJSON_CreateObject();

    char* date = mx_strnew(1025);
    time_t now_time = time(NULL);
    snprintf(date, 1024, "%.24s", ctime(&now_time));
    cJSON* date_value = cJSON_CreateString(date);

    cJSON_AddItemToObject(protocol, "DATE", date_value);

    free(date);
    
    return protocol;
}

cJSON* add_to_protocol(cJSON* protocol, char* key, cJSON* value) {

    cJSON_AddItemToObject(protocol, key, value);

    return protocol;
}

char* screen_file(char* file_bytes, size_t file_size, size_t *screened_size) {

    // screen '\0'
    size_t current_size = file_size + BUFSIZ;
    char* screened = mx_strnew(current_size);

    size_t screened_index = 0;
    for (size_t file_index = 0; file_index < file_size; file_index++) {

        if (current_size <= screened_index - 1) {
            current_size += BUFSIZ;
            screened = realloc(screened, current_size);
        }

        if (file_bytes[file_index] == '\0') {
            screened[screened_index++] = '\\';
            screened[screened_index++] = '0';
        } else if (file_bytes[file_index] == '\\') {
            screened[screened_index++] = '\\';
            screened[screened_index++] = '\\';
        } else {
            screened[screened_index++] = file_bytes[file_index];
        }
    }
    *screened_size = screened_index;
    return screened;
}

char* unscreen_file(char* screened, size_t screened_size, size_t* file_size) {

    char* unscreened = mx_strnew(screened_size);

    *file_size = 0;
    
    size_t file_index = 0;
    for (size_t screened_index = 0; screened_index < screened_size; screened_index++) {

        if (screened[screened_index] == '\\' && screened_index + 1 < screened_size && screened[screened_index + 1] == '\\') {
            unscreened[file_index++] = '\\';
            screened_index++;
        } else if (screened[screened_index] == '\\' && screened_index + 1 < screened_size && screened[screened_index + 1] == '0') {
            unscreened[file_index++] = '\0';
            screened_index++;
        } else {
            unscreened[file_index++] = screened[screened_index];
        }

    }
    *file_size = file_index;
    return unscreened;
}

cJSON* add_file_to_protocol(cJSON* protocol, char* key, char* file_bytes, size_t file_size) {


    size_t screened_size = 0;
    char* screened = screen_file(file_bytes, file_size, &screened_size);

    cJSON* file_value = cJSON_CreateString(screened);

    cJSON_AddItemToObject(protocol, key, file_value);

    return protocol;
}

char*  get_file_from_protocol(cJSON* protocol, char* key, size_t* file_size) {

    cJSON* file_obj = cJSON_GetObjectItemCaseSensitive(protocol, key);

    char* file_str = unscreen_file(file_obj->valuestring, strlen(file_obj->valuestring), file_size);

    return file_str;
}
