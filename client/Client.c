
#include "Client.h"

void initClient(Client *c) {
    if(!c) return;

    c->tcp_client = NULL;
    c->mthread = (MThread *)malloc(sizeof(MThread));
    if(!c->mthread) return;

    atomic_store(&c->isConnected, false);
    atomic_store(&c->isLoggedIn, false);
    atomic_store(&c->isInSession, false);
    atomic_store(&c->shouldExit, false);
}

bool connectToServer(Client* c) {
    if(!c) return false;

    c->tcp_client = createTcpClient();
    if(!c->tcp_client) return false;

    atomic_store(&c->isConnected, true);
    c->mthread->run = runClient;
    c->mthread->arg = (void *)c;
    mtStart(c->mthread);

    return true;
}