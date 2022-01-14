#include "send_request.h"

char* read_response(int sock_fd) {

    char* response = mx_strnew(RESPONSE_BUFFER_SIZE);
    int read_size = 0;

    while ( (read_size = read(sock_fd, response, RESPONSE_BUFFER_SIZE - 1)) > 0 )
    {
        response[RESPONSE_BUFFER_SIZE - 1] = '\0';
    }
    
    return response;
}

char* send_request(char*  request, char* ip, int port) {

    // printf("%s", request);

    int sock_fd = 0;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, '0', sizeof(serv_addr));

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return NULL;
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port);

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return NULL;
    }

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Error : Connect Failed \n");
        return NULL;
    }

    request[strlen(request)] = '\r';
    request[strlen(request)] = '\n';

    sendto(sock_fd, request, strlen(request), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    char* response = read_response(sock_fd);
    // char* response = NULL;

    return response;
}
