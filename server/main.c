#include <string.h>
#include <stdio.h>

#include "Server.h"

int main() {
    Server server;
    initServer(&server);

    char command[10];
    printf("Enter command\n");

    while(strcmp(command, "close") != 0) {
        scanf("%s", command);
    }
}

