#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "TCPSocket.h"
#include "Common.h"

void initTcp(TCPSocket *tcp) {
    memset(&tcp->peer_addr, 0, sizeof(struct sockaddr_in));
    tcp->sockfd = -1;
}

TCPSocket *createTcpServer() {
    TCPSocket *sock = (TCPSocket *)malloc(sizeof(TCPSocket));
    if(!sock) return NULL;
    initTcp(sock);

    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock->sockfd < 0) return NULL;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)SERVER_PORT);
    if(inet_pton(AF_INET, SERVER_IP, &addr.sin_addr) <= 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    int opt = 1;
    setsockopt(sock->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

TCPSocket* createTcpClient() {
    TCPSocket *sock = (TCPSocket *)malloc(sizeof(TCPSocket));
    if(!sock) return NULL;
    initTcp(sock);

    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock->sockfd < 0) {
        free(sock);
        sock = NULL;

        return NULL;
    }

    sock->peer_addr.sin_family = AF_INET;
    sock->peer_addr.sin_port = htons((uint16_t)SERVER_PORT);
    if(inet_pton(AF_INET, SERVER_IP, &sock->peer_addr.sin_addr) <= 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    if(connect(sock->sockfd, (struct sockaddr *)&sock->peer_addr, 
                sizeof(struct sockaddr_in)) < 0) {
        close(sock->sockfd);
        free(sock);
        sock = NULL;

        return NULL;
    }

    return sock;
}

int sendMsg(int fd, char *msg) {
    if(fd < 0 || !msg) return 0;
    
    uint32_t msgLen = (uint32_t)strlen(msg);
    uint32_t netMsgLen = htonl(msgLen);
    uint32_t total = 0;

    if(send(fd, (void *)&netMsgLen, sizeof(uint32_t), 0) <= 0) return 0;
    
    while(total < msgLen) {
        ssize_t numSend = send(fd, (char *)msg + total, msgLen - total, 0);

        if(numSend <= 0) return total;

        total += (uint32_t)numSend;
    }

    return total;
}