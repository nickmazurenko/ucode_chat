#ifndef MESSAGES_REQUESTS
#define MESSAGES_REQUESTS

#include "send_request.h"
#include "model_message.h"
#include "cJSON.h"

char* send_message(t_model_message* model_message, cJSON* protocol);

#endif
