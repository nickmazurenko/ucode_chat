#ifndef SERVER_H
#define SERVER_H

#include "libmx.h"
#include "model.h"
#include "network.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "select_action.h"

#define BUFFER_SIZE 1024
#define PORT 5000
#define MAX_CONNECTIONS 10

void run_server();

#endif
