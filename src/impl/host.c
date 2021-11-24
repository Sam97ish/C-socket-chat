#include "../headers/host.h"
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/cli_interaction.h"

int setupHost(struct sockaddr_in serverAddress) {
    // create server socket.
    int socketDesc = socket(AF_INET, SOCK_STREAM, 0);

    if (socketDesc == -1) {
        perror("## ERROR in setupHost: could not create the server socket.\n");
        exit(2);
    }

    // prepare to bind the socket to the specified port.
    if (bind(socketDesc, (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        perror(
            "## ERROR setupHost: Could not bind the server to specified "
            "address "
            "and port.\n");
        exit(3);
    }

    printf("$$ Host is bound successfully at address %du and port %d.\n",
           serverAddress.sin_addr.s_addr, serverAddress.sin_port);

    return socketDesc;
}

void sendMessageToAll(char* message, int socket) {
    size_t totalData = 0;
    size_t length = strlen(message);
    while (totalData < length) {
        size_t actualDataSent =
            send(socket, message + totalData, length - totalData, 0);
        if (actualDataSent < 0) {
            perror(
                "## ERROR in sendMessageToAll: There was a problem sending the "
                "previous message to "
                "clients.\n");
        }
        totalData += actualDataSent;
    }
}

int receiveMessageFromClient(char* message, int socket) {
    size_t totalData = 0;

    while (1) {
        int bytesReceived = recv(socket, message, MAX_MESSAGE_SIZE, 0);
        if (bytesReceived < 0) {
            perror(
                "## ERROR in receiveMessageFromClient: There was a problem "
                "receiving a message from the "
                "client.\n");
        }

        /*
        #ifdef __STDC_LIB_EXT1__
                if (strncpy_s(message + totalData, tempMessage + totalData,
                              strlen(tempMessage)) != 0) {
                    perror(
                        "## ERROR in receiveMessageFromClient: There was a
        problem " "while saving the received message to the buffer.\n");
                }
        #endif
        */

        totalData += bytesReceived;

        if (bytesReceived == 0) break;  // End of stream.
    }

    return totalData;
}