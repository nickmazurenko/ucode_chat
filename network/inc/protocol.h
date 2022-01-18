#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "libmx.h"
#include "cJSON.h"
#include "string.h"
#include "time.h"
#include "stdio.h"

#define BUFSIZ 1024
#define SEND_SIZE 5120
#define BUFFER_SIZE 4096

#define PORT 5000

cJSON* create_protocol();
cJSON* add_to_protocol(cJSON* protocol, char* key, cJSON* value);
cJSON* add_file_to_protocol(cJSON* protocol, char* key, char* file_bytes, size_t file_size);
char*  get_file_from_protocol(cJSON* protocol, char* key, size_t* file_size);

char* screen_file(char* file_bytes, size_t file_size, size_t *screened_size);
char* unscreen_file(char* screened, size_t screened_size, size_t* file_size);

char* get_server_ip();


#endif
