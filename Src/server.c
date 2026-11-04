#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "layers.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Server waiting on port %d...\n", PORT);

    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("\n=== SERVER RECEIVED ENCAPSULATED DATA ===\n");
        Physical_Receive(buffer);

        const char *reply = "Server received and decapsulated the message";
        send(client_fd, reply, strlen(reply), 0);
    } else {
        perror("recv");
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
