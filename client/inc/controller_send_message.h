#ifndef CONTROLLER_SEND_MESSAGE
#define CONTROLLER_SEND_MESSAGE

#include "model_message.h"
#include "protocol.h"
#include "user_data.h"
#include "libmx.h"
#include "string.h"
#include "messages_requests.h"
#include "user_data.h"


int controller_send_message(char* to, e_message_data_types data_type, char* data);

#endif
