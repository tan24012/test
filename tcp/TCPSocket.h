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
TCPSocket *createTcpServer(uint16_t port, const char *ip);
TCPSocket *listenAndAccept(TCPSocket *tcp);
TCPSocket* createTcpClient(char* peerIP, int port);

#endif