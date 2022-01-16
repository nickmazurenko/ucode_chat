#ifndef SET_AVATAR_REQUEST_H
#define SET_AVATAR_REQUEST_H

#include "libmx.h"
#include "protocol.h"
#include "send_request.h"

char* send_set_avatar_request(char* file_bytes, size_t file_size);

#endif
