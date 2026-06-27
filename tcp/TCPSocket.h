#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct {
    struct sockaddr_in peer_addr;
    int sockfd;
} TCPSocket;

void initTcp(TCPSocket *tcp);
TCPSocket *createTcpServer();
TCPSocket *listenAndAccept(TCPSocket *tcp);
TCPSocket* createTcpClient();

#endif