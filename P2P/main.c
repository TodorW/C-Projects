#include "peer.h"
int main() {
    peer_t peer;
    peer.id = 1;
    strcpy(peer.ip, "127.0.0.1");
    peer.port = 8080;
    start_peer(&peer);
    return 0;}
