#ifndef MESSAGES_SERVER_H
#define MESSAGES_SERVER_H

#include "cJSON.h"
#include "libmx.h"
#include "string.h"
#include "model_message.h"
#include "protocol.h"
#include "database.h"

char* add_message(cJSON* request);

#endif
