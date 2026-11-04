#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include "layers.h"

static int socket_fd = -1;

void set_socket_fd(int fd) {
    socket_fd = fd;
}

void log_layer(const char *layer, const char *data) {
    printf("[%s] Data: %s\n", layer, data);
}

/* TRANSMIT SIDE */
void Application_Send(const char *msg) {
    log_layer("Application", msg);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "APP{%s}", msg);
    Presentation_Send(buffer);
}

void Presentation_Send(const char *data) {
    log_layer("Presentation", data);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "PRS{%s}", data);
    Session_Send(buffer);
}

void Session_Send(const char *data) {
    log_layer("Session", data);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "SES{%s}", data);
    Transport_Send(buffer);
}

void Transport_Send(const char *data) {
    log_layer("Transport", data);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "TCP{%s}", data);
    Network_Send(buffer);
}

void Network_Send(const char *data) {
    log_layer("Network", data);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "IP{%s}", data);
    DataLink_Send(buffer);
}

void DataLink_Send(const char *data) {
    log_layer("DataLink", data);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "MAC{%s}", data);
    Physical_Send(buffer);
}

void Physical_Send(const char *data) {
    log_layer("Physical", data);

    if (socket_fd >= 0) {
        send(socket_fd, data, strlen(data), 0);
        printf("\n=== ENCAPSULATED DATA SENT THROUGH TCP SOCKET ===\n\n");
    } else {
        printf("\n=== LOCAL SIMULATION: NO SOCKET CONNECTED ===\n\n");
        Physical_Receive(data);
    }
}

/* RECEIVE SIDE */
static void unwrap(const char *data, size_t prefix_len,
                   char *out, size_t out_size) {
    size_t len = strlen(data);

    if (out_size == 0) return;

    if (len < prefix_len + 1) {
        out[0] = '\0';
        return;
    }

    size_t payload_len = len - prefix_len - 1;
    if (payload_len >= out_size) payload_len = out_size - 1;

    memcpy(out, data + prefix_len, payload_len);
    out[payload_len] = '\0';
}

void Physical_Receive(const char *data) {
    char inner[256];
    log_layer("Physical (RX)", data);
    unwrap(data, 4, inner, sizeof(inner));
    DataLink_Receive(inner);
}

void DataLink_Receive(const char *data) {
    char inner[256];
    log_layer("DataLink (RX)", data);
    unwrap(data, 3, inner, sizeof(inner));
    Network_Receive(inner);
}

void Network_Receive(const char *data) {
    char inner[256];
    log_layer("Network (RX)", data);
    unwrap(data, 4, inner, sizeof(inner));
    Transport_Receive(inner);
}

void Transport_Receive(const char *data) {
    char inner[256];
    log_layer("Transport (RX)", data);
    unwrap(data, 4, inner, sizeof(inner));
    Session_Receive(inner);
}

void Session_Receive(const char *data) {
    char inner[256];
    log_layer("Session (RX)", data);
    unwrap(data, 4, inner, sizeof(inner));
    Presentation_Receive(inner);
}

void Presentation_Receive(const char *data) {
    char inner[256];
    log_layer("Presentation (RX)", data);
    unwrap(data, 4, inner, sizeof(inner));
    Application_Receive(inner);
}

void Application_Receive(const char *data) {
    log_layer("Application (RX)", data);
    printf("\n=== FINAL MESSAGE DELIVERED TO APPLICATION ===\n");
}
