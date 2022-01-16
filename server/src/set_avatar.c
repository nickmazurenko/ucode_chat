#include "set_avatar.h"

char* set_avatar(char* request) {

    cJSON* request_obj = cJSON_Parse(request);

    size_t file_size = 0;
    char* file_bytes = get_file_from_protocol(request_obj, "AVATAR", &file_size);
    printf("file_bytes: %s\n", file_bytes);
    int file = open("avatar", O_WRONLY);
    write(file, file_bytes, file_size);

    system("open avatar");
    close(file);
    cJSON_Delete(request_obj);

}