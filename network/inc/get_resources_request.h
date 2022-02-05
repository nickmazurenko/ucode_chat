#ifndef GET_AVATAR_REQUEST_H
#define GET_AVATAR_REQUEST_H
#include "send_request.h"
#include "send_file.h"
#include "model_resource.h"
#include "cJSON.h"
#include "get_file.h"
// #include "database_client.h"

// char* send_get_avatar_request(char* username);
t_model_resource* send_get_avatar_request(char* username);

t_model_resource* send_get_resource_request(char *id);

#endif
