#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "layers.h"

#define PORT 8080

int main(void) {
    int sock;
    struct sockaddr_in server_address;
    char response[1024] = {0};
    const char *message = "Hello from the OSI client!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1",
                  &server_address.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    set_socket_fd(sock);
    Application_Send(message);

    ssize_t n = recv(sock, response, sizeof(response) - 1, 0);
    if (n > 0) {
        response[n] = '\0';
        printf("Client received: %s\n", response);
    }

    close(sock);
    return 0;
}
