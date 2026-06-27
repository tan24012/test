#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "TCPSocket.h"

void initTcp(TCPSocket *tcp) {
    memset(&tcp->addr, 0, sizeof(struct sockaddr_in));
    memset(&tcp->peer_addr, 0, sizeof(struct sockaddr_in));
    tcp->sockfd = -1;
}

TCPSocket *createTcpServer(uint16_t port, const char *ip) {
    TCPSocket *sock = (TCPSocket *)malloc(sizeof(TCPSocket));
    if(!sock) return NULL;
    initTcp(sock);

    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock->sockfd < 0) return NULL;

    sock->addr.sin_family = AF_INET;
    sock->addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &sock->addr.sin_addr) <= 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    if(bind(sock->sockfd, (struct sockaddr *)&sock->addr, sizeof(sock->addr)) < 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    return sock;
}
