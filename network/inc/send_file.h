#ifndef SEND_FILE_H
#define SEND_FILE_H

#include "libmx.h"
#include "protocol.h"
#include "send_request.h"

char* send_file(char* path_to_file, char* after_file_request, char* ip, int port);

#endif
