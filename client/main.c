#include <string.h>
#include <stdio.h>

#include "Client.h"

int main() {
    Client client;
    initClient(&client);

    char command[10];
    printf("Enter command\n");  // ?

    while(strcmp(command, "close") != 0) {
        scanf("%s", command);   // ?
        
        if(strcmp(command, "c") == 0) {
            if(!atomic_load(&client.isConnected)) {
                if(connectToServer(&client)) {
                    printf("connect to server sucessesfully\n");
                }
                else 
                   printf("connect to server fail\n"); 
            }
        }

        if(strcmp(command, "close") == 0) {
            
        }
    }
}

