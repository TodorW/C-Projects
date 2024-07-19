#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_REQUEST_LENGTH 1024
#define MAX_RESPONSE_LENGTH 1024
void handle_request(int client_socket) {
    char request[MAX_REQUEST_LENGTH];
    char response[MAX_RESPONSE_LENGTH];
    char file_path[256];
    read(client_socket, request, MAX_REQUEST_LENGTH);
    printf("Request: %s\n", request);
    char* method = strtok(request, " ");
    char* url = strtok(NULL, " ");
    char* protocol = strtok(NULL, "\r\n");
    if (strcmp(method, "GET") == 0) {
        if (strcmp(url, "/") == 0) {
            strcpy(file_path, "index.html");
        } else {
            sprintf(file_path, ".%s", url);}
        FILE* file = fopen(file_path, "r");
        if (file != NULL) {
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
            send(client_socket, response, strlen(response), 0);
            char buffer[BUFFER_SIZE];
            while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
                send(client_socket, buffer, strlen(buffer), 0);}
            fclose(file);
        } else {
            sprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
            send(client_socket, response, strlen(response), 0);}
    } else {
        sprintf(response, "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/html\r\n\r\n");
        send(client_socket, response, strlen(response), 0);}
    close(client_socket);}
int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_length = sizeof(client_address);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return 1;}
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        return 1;}
    if (listen(server_socket, 3) < 0) {
        perror("listen");
        return 1;}
    printf("Server started on port %d...\n", PORT);
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_length);
        if (client_socket < 0) {
            perror("accept");
            return 1;}
        printf("Connection accepted...\n");
        handle_request(client_socket);}
    return 0;}
