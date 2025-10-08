#include "server.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

//---------------------------------------------------------------------
//                             VARIABLE
//---------------------------------------------------------------------

int server_fd;

//---------------------------------------------------------------------
//                             FUNCTION
//---------------------------------------------------------------------

char* parse_msg(const char *msg) {
    const char *ptr = strchr(msg, ' ');
    if (!ptr) return strdup("error");

    const char *start = ptr + 1;
    const char *end = msg + strlen(msg) - 1;

    int len = end - start + 1;
    if (len <= 0) return strdup("error");

    char *buffer = malloc(len + 1);
    if (!buffer) return strdup("error");

    strncpy(buffer, start, len);
    buffer[len] = '\0';

    return buffer;
}

void handle_sigint(int sig) {
    printf("\n[server] Caught signal %d, shutting down...\n", sig);
    if (server_fd > 0) close(server_fd);
    exit(0);
}

int start_listening(int port, queue *hot_queue) {
    int client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    signal(SIGINT, handle_sigint);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return -1;
    }

    printf("[Server] Start to listen on port [%d]\n", port);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("[connection] accept");
            continue;
        }

        printf("[connection] Client connected.\n");

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_read <= 0) {
                printf("[connection] Client disconnected.\n");
                break;
            }

            buffer[strcspn(buffer, "\r\n")] = 0; 
            //-------------------------------------------
            //                   PUSH
            //-------------------------------------------
            if (strncmp(buffer, "push", 4) == 0){
                char* value = parse_msg(buffer);
                if (strncmp(buffer, "erro", 4) != 0) {
                    int transaction_status = push_to_queue(hot_queue, value);
                    if (transaction_status == 0) {
                        sprintf(buffer, "-err FULL\n");
                    }else{
                        sprintf(buffer, "+ok\n");
                    }
                } else {
                    sprintf(buffer, "-err invalid format\n");
                }

                send(client_fd, buffer, strlen(buffer), 0);
            }

            //-------------------------------------------
            //                   PULL
            //-------------------------------------------
            if (strncmp(buffer, "pull", 4) == 0){
                char* value = pull_from_queue(hot_queue);
                if (strncmp(buffer, "EMPTY", 4) == 0){
                    sprintf(buffer, "+ok EMPTY\n");
                } else {
                    sprintf(buffer, "+ok %s\n", value);
                }

                send(client_fd, buffer, strlen(buffer), 0);
            }

            //-------------------------------------------
            //                   BYE
            //-------------------------------------------
            if (strcmp(buffer, "bye") == 0) {
                printf("[connection] Connection close by client\n");
                close(client_fd);
                break;
            }
        }
    }

    close(server_fd);
    return 0;
}
