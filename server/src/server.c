#include "server.h"
#include "cJSON.h"
#include "string.h"

char* read_request(int conn_fd) {

    char* request = mx_strnew(BUFFER_SIZE);

    int read_number = 0;
    while ( (read_number = read(conn_fd, request, BUFFER_SIZE - 1)) > 0){
        // bzero(request, BUFFER_SIZE);
        request[read_number] = '\0';
        break;
    }
    
    return request;
}

void run_server() {

    int listen_fd = 0, conn_fd = 0;
    struct sockaddr_in serv_addr;
    char* response_buffer = mx_strnew(BUFFER_SIZE);

    memset(&serv_addr, '0', sizeof(serv_addr));


    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listen_fd, MAX_CONNECTIONS);

    while (1)
    {
        conn_fd = accept(listen_fd, (struct socketaddr*)NULL, NULL);

        char* request = read_request(conn_fd);

        strcpy(response_buffer, "200 OK\r\n\r\n");
        printf("response: %s\n", response_buffer);
        // send(conn_fd, response_buffer, strlen(response_buffer), 0); 
        write(conn_fd, response_buffer, strlen(response_buffer));

        close(conn_fd);
        memset(response_buffer, '\0', BUFFER_SIZE);

        printf("request:%s\n", request);
        sleep(1);
    }
    

}
