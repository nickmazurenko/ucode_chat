#ifndef USER_DATA_REQUEST_H
#define USER_DATA_REQUEST_H


#include "model_user.h"
#include "cJSON.h"
#include "send_request.h"
#include "protocol.h"
#include "model_user_data.h"

t_model_user_data* send_user_data_request(char *username);

#endif
