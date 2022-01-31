#ifndef MESSAGES_REQUESTS
#define MESSAGES_REQUESTS

#include "send_request.h"
#include "model_message.h"
#include "cJSON.h"

char* send_message(t_model_message* model_message, cJSON* protocol);
cJSON* get_all_my_messages(cJSON* cookies);
cJSON* get_my_new_messages(cJSON* cookies);

#endif
