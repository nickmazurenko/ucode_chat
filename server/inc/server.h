#ifndef SERVER_H
#define SERVER_H

#include "libmx.h"
#include "model.h"
#include "network.h"


// #if      defined(_MSC_VER) \
//         ||defined(__WIN32__) \
//         ||defined(_WIN32)\
//         ||defined(__WIN32)\
//         ||defined(WIN32)\
//         ||defined(__WINNT)\
//         ||defined(__WINNT__)\
//         ||defined(_WINNT)\
//         ||defined(WINNT)
// #include <winsock2.h>
// #include <windows.h>
// #include <Ws2tcpip.h>
// #elif   defined(__linux) \
//        ||defined(__linux__)\
//        ||defined(linux)\
//        ||defined(_linux)
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #elif defined(__unix) \
//        ||defined(_unix) \
//        ||defined(__unix__) \
//        ||defined(unix) 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
       // #if      defined(__APPLE__) 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//       #endif
// #else
// # error Cannot determine OS type
// #endif


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


#include "select_action.h"

#define BUFFER_SIZE 4096
#define S_PORT 10001
#define MAX_CONNECTIONS 10

void run_server();

#endif
