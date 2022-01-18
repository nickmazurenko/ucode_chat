#include "file_for_write.h"
#include "select_action.h"

void update_last_tmp_id(size_t new_last_tmp_id) {

    char* path_to_last_tmp_id = "./server/resources/tmp/last_tmp_id.csv";
    FILE* last_tmp_id = fopen(path_to_last_tmp_id, "w");
    char* size_str = mx_strnew(BUFSIZ);
    sprintf(size_str, "%zu", new_last_tmp_id);
    fwrite(size_str, sizeof(char), strlen(size_str), last_tmp_id);
    fclose(last_tmp_id);
}

char* get_next_file_for_write() {
    char* path_to_last_tmp_id = "./server/resources/tmp/last_tmp_id.csv";
    FILE* last_tmp_id = fopen(path_to_last_tmp_id, "r");
    char* size_str = mx_strnew(BUFSIZ);
    fread(size_str, sizeof(char), BUFSIZ, last_tmp_id);
    fclose(last_tmp_id);
    size_t last_id = atoll(size_str);
    update_last_tmp_id(++last_id);
    return size_str;
}

char* file_for_write(char* response) {
    char* next_file = get_next_file_for_write();
    strcpy(response, next_file);
    strcat(response, "\r\n");
    free(next_file);
    return response;
}

char* save_file(char* request, char* response) {


    char* path_to_file = "./server/resources/tmp/";

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* path_to_file_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "PATH TO FILE");
    path_to_file = mx_strjoin(path_to_file, path_to_file_obj->valuestring);
    FILE* file = fopen(path_to_file, "a");

    if (file == NULL) {
        char* create_file_command = "touch ";
        create_file_command = mx_strjoin(create_file_command, path_to_file);
        system(create_file_command);
        FILE* file = fopen(path_to_file, "a");
    }

    cJSON* file_data_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    cJSON* screened_file_size_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "FILE PART SIZE");
    size_t unscreened_size = 0;
    char* file_data_unscreened = unscreen_file(file_data_obj->valuestring, screened_file_size_obj->valuedouble, &unscreened_size);


    fwrite(file_data_unscreened, sizeof(char), unscreened_size, file);
    fclose(file);

    cJSON_Delete(request_obj);

    strcpy(response, "OK\r\n");
    return response;
}

char* file_end(char* request, char* response) {
    printf("%s\n", request);

    cJSON* protocol = cJSON_Parse(request);

    if (protocol == NULL) {
        printf("parse error\n");
        return NULL;
    }

    cJSON* after_save_action = cJSON_GetObjectItemCaseSensitive(protocol, "DATA");

    select_action(after_save_action->valuestring, response);

    cJSON_Delete(protocol);

    return response;
}