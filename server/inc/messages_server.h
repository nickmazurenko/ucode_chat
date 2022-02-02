#ifndef MESSAGES_SERVER_H
#define MESSAGES_SERVER_H

#include "cJSON.h"
#include "libmx.h"
#include "string.h"
#include "model_message.h"
#include "protocol.h"
#include "database.h"

char* add_message(cJSON* request);
char* get_messages(cJSON* request);
bool start_chat(char *request, char *response);

#endif
