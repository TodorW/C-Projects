#ifndef PEER_H
#define PEER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX_PEERS 10
#define MAX_FILE_NAME 256
typedef struct {
    int id;
    char ip[INET_ADDRSTRLEN];
    int port;
} peer_t;
typedef struct {
    char file_name[MAX_FILE_NAME];
    char file_path[MAX_FILE_NAME];
} file_t;
void start_peer(peer_t *peer);
void connect_to_peer(peer_t *peer, char *ip, int port);
void share_file(peer_t *peer, file_t *file);
void download_file(peer_t *peer, file_t *file);
#endif  // PEER_H
