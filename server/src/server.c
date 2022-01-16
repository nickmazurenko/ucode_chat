#include "server.h"
#include "cJSON.h"
#include "string.h"
#include "database.h"
#include <sys/stat.h>


char* read_request(int conn_fd) {

    size_t conn_size = 1024;
    
    // struct stat* s = malloc(sizeof(struct stat));
    
    // int status = fstat(conn_fd, s);
    // printf("status: %i\n", status);
    // conn_size = s->st_size;
    
    // printf("conn size: %lu\n", conn_size);
    char* request = mx_strnew(conn_size + 1);

    int read_number = 0;
    while ( (read_number = read(conn_fd, request, conn_size)) > 0){
        // bzero(request, BUFFER_SIZE);
        request[read_number] = '\0';
        break;
    }
    return request;
}

void run_server() {

    init_User_table();

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
        struct sockaddr client;
        memset(&client, 0, sizeof(struct sockaddr));
        socklen_t client_len = (socklen_t)sizeof client;
        conn_fd = accept(listen_fd, (struct sockaddr*)&client, &client_len);

        char* request = read_request(conn_fd);
        printf("request:%s\n", request);
        
        select_action(request);

        strcpy(response_buffer, "200 OK\r\n\r\n");
        printf("response: %s\n", response_buffer);
        // send(conn_fd, response_buffer, strlen(response_buffer), 0); 
        write(conn_fd, response_buffer, strlen(response_buffer));

        close(conn_fd);
        memset(response_buffer, '\0', BUFFER_SIZE);
        // free(request);
        // sleep(1);
    }
    

}
