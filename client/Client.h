#ifndef CLIENT_H
#define CLIENT_H

#include <stdatomic.h>
#include <stdbool.h>

#include "TCPSocket.h"
#include "MThread.h"

typedef struct{
    TCPSocket *tcp_client;
    MThread *mthread;
    char *client_name;
    atomic_bool isConnected;  
    atomic_bool isLoggedIn;   
    atomic_bool isInSession;  
    atomic_bool shouldExit;
} Client;

void initClient(Client *c);
bool connectToServer(Client* c);


#endif