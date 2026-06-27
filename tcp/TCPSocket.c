#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "TCPSocket.h"
#include "Common.h"

void initTcp(TCPSocket *tcp) {
    memset(&tcp->peer_addr, 0, sizeof(struct sockaddr_in));
    tcp->sockfd = -1;
}

TCPSocket *createTcpServer(uint16_t port, const char *ip) {
    TCPSocket *sock = (TCPSocket *)malloc(sizeof(TCPSocket));
    if(!sock) return NULL;
    initTcp(sock);

    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock->sockfd < 0) return NULL;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    if(bind(sock->sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    return sock;
}

TCPSocket *listenAndAccept(TCPSocket *tcp) {
    if(!tcp || (tcp->sockfd < 0)) return NULL;

    if(listen(tcp->sockfd, MAX_CLIENT) < 0) return NULL;

    TCPSocket *server = (TCPSocket *)malloc(sizeof(TCPSocket));
    initTcp(server);

    socklen_t len = sizeof(struct sockaddr_in);
    server->sockfd = accept(tcp->sockfd, (struct sockaddr *)&server->peer_addr, &len);
    if(server->sockfd < 0) {
        free(server);
        server = NULL;

        return NULL;
    }

    return server;
}