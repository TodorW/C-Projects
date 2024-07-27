#include "peer.h"
void start_peer(peer_t *peer) {
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);}
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(peer->port);
    inet_pton(AF_INET, peer->ip, &server_addr.sin_addr);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);}
    if (listen(sockfd, 3) < 0) {
        perror("listen failed");
        exit(1);}
    printf("Peer %d started. Listening on port %d...\n", peer->id, peer->port);
    while (1) {
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (new_sockfd < 0) {
            perror("accept failed");
            continue;}
        handle_connection(new_sockfd);}}
void connect_to_peer(peer_t *peer, char *ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);}
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(1);}
    printf("Connected to peer %s:%d\n", ip, port);
    send(sockfd, peer, sizeof(peer_t), 0);
    peer_t remote_peer;
    recv(sockfd, &remote_peer, sizeof(peer_t), 0);
    printf("Remote peer info: id=%d, ip=%s, port=%d\n", remote_peer.id, remote_peer.ip, remote_peer.port);}
void share_file(peer_t *peer, file_t *file) {
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);}
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(peer->port);
    inet_pton(AF_INET, peer->ip, &server_addr.sin_addr);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(1);}
    send(sockfd, file, sizeof(file_t), 0);
    printf("File shared: %s\n", file->file_name);}
    void download_file(peer_t *peer, file_t *file) {
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);}
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(peer->port);
    inet_pton(AF_INET, peer->ip, &server_addr.sin_addr);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(1);}
    send(sockfd, file, sizeof(file_t), 0);
    char buffer[1024];
    int bytes_received;
    FILE *fp = fopen(file->file_name, "wb");
    if (fp == NULL) {
        perror("fopen failed");
        exit(1);}
    while ((bytes_received = recv(sockfd, buffer, 1024, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, fp);}
    fclose(fp);
    printf("File downloaded: %s\n", file->file_name);}
void handle_connection(int sockfd) {
    peer_t remote_peer;
    recv(sockfd, &remote_peer, sizeof(peer_t), 0);
    printf("Remote peer info: id=%d, ip=%s, port=%d\n", remote_peer.id, remote_peer.ip, remote_peer.port);
    char command[256];
    recv(sockfd, command, 256, 0);
    if (strcmp(command, "share") == 0) {
        file_t file;
        recv(sockfd, &file, sizeof(file_t), 0);
        share_file(&remote_peer, &file);
    } else if (strcmp(command, "download") == 0) {
        file_t file;
        recv(sockfd, &file, sizeof(file_t), 0);
        download_file(&remote_peer, &file);}}
