#include "set_avatar_request.h"
#include "protocol.h"

char* send_set_avatar_request(char* file_bytes, size_t file_size) {



    cJSON* protocol = create_protocol();

    cJSON* action_value = cJSON_CreateString("SET AVATAR");
    add_to_protocol(protocol, "ACTION", action_value);

    add_file_to_protocol(protocol, "AVATAR", file_bytes, file_size);


    char* protocol_str = cJSON_Print(protocol);
    printf("length = %lu\n", strlen(protocol_str));

    char* response = send_request(protocol_str, "127.0.0.1", 5000);

    return response;
}
