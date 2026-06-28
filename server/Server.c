#include <stdio.h>
#include <stdlib.h>

#include "Server.h"

void initServer(Server *s) {
    s->tcp_server = NULL;

    s->listenThread = (MThread *)malloc(sizeof(MThread));
    if(!s->listenThread) return;
    mtInit(s->listenThread);

    // s->loginAndSign = NULL;

    atomic_store(&s->listenStatus, false);

    s->listenThread->run = runListening;
    s->listenThread->arg = (void *)s;
    mtStart(s->listenThread);
}

void runListening(void *arg) {
    if(!arg) return;
    Server* serv = (Server*)arg;
    atomic_store(&serv->listenStatus, true);

    TCPSocket *listen_sock = createTcpServer();
    if(!listen_sock) {
        atomic_store(&serv->listenStatus, false);
        return;
    }
    printf("Server is listening\n");

    while(atomic_load(&serv->listenStatus) == true)
	{
		TCPSocket* temp_sock = listenAndAccept(serv->listen_sock);

		if (!temp_sock)
			continue;
		else {
            printf("server accept client\n");
			// addPeer(serv->loginAndSign, temp_sock);
		}
	}

	printf("Server stopped running\n");
}