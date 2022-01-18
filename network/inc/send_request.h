#ifndef SEND_REQUEST_H
#define SEND_REQUEST_H

#include "libmx.h"

//////////////////////////////

#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
/////////////////////////////

// #include <sys/socket.h>
#include <sys/types.h>
// #include <netinet/in.h>
// #include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
// #include <arpa/inet.h>

#include "protocol.h"


#define BUFFER_SIZE 4096
#define SEND_SIZE   5120

char* send_request(char*  request, char* ip, int port);


#endif
