#include "Server.h"

int main() {
    Server server;
    initServer(&server);

    char *command;
    printf("Enter command\n");

    while(strcmp(command, "close") != 0) {
        scanf("%s", command);
    }
}

