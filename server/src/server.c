#include "server.h"
#include "cJSON.h"
#include "string.h"
#include "database.h"
#include <sys/stat.h>


char* read_request(int conn_fd, char* request, int* read_number) {

    size_t buff_size = 14336;
    


    while ( (*read_number = read(conn_fd, request, buff_size - 1)) > 0 )
    {
        // bzero(request, BUFFER_SIZE);
        // request[read_number] = '\0';
        // read_number = read(conn_fd, request, buff_size);
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
    serv_addr.sin_port = htons(S_PORT);

    bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listen_fd, MAX_CONNECTIONS);

    printf("server runned\n");

    char* request = mx_strnew(14336);

    while (1)
    {
        struct sockaddr_in client;
        memset(&client, 0, sizeof(struct sockaddr));
        socklen_t client_len = (socklen_t)sizeof client;
        char client_addres[BUFFER_SIZE + 1];

        conn_fd = accept(listen_fd, (struct sockaddr*)&client, &client_len);

        // inet_ntop(AF_INET, &client, client_addres, BUFFER_SIZE);
        int read_number = 0;
        read_request(conn_fd, request, &read_number);
        
        select_action(request, response_buffer);

        if (strlen(response_buffer) == 0)
            strcpy(response_buffer, "200 OK\r\n\r\n");
        // send(conn_fd, response_buffer, strlen(response_buffer), 0); 
        size_t response_buffer_length = strlen(response_buffer);
        write(conn_fd, response_buffer, response_buffer_length);
        // sendto(conn_fd, response_buffer, strlen(response_buffer), 0, (struct sockaddr *)&client, sizeof(client_addres));

        close(conn_fd);
        memset(response_buffer, '\0', response_buffer_length);
        memset(request, '\0', read_number);
        sleep(1);
    }
    

}
