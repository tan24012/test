#ifndef SERVER_H
#define SERVER_H

#include <stdatomic.h>

#include "TCPSocket.h"
#include "MThread.h"

typedef struct {
    TCPSocket *tcp_server;
    MThread *listenThread;
    // LoginAndSignUp *loginAndSign;
    atomic_bool listenStatus;
} Server;

void initServer(Server *s);
void runListening(void *arg);


#endif