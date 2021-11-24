#include "../headers/client.h"
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/cli_interaction.h"

int connectToHost(struct sockaddr_in clientAddress) {
    // create client socket.
    int socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDesc == -1) {
        perror("## ERROR in initClient: could not create the client socket.\n");
        exit(3);
    }

    // connect to host.
    if (connect(socketDesc, (struct sockaddr*)&clientAddress,
                sizeof(clientAddress)) < 0) {
        perror("## ERROR in connect: Could not connect client to host.\n");
        exit(4);
    }

    printf("$$ Client connected to host at %du port %d.\n",
           clientAddress.sin_addr.s_addr, clientAddress.sin_port);
    return socketDesc;
}

void sendMessageToHost(char* message, int clientSocket) {
    ssize_t totalData = 0;
    ssize_t length = strlen(message);

    while (totalData < length) {
        ssize_t actualDataSent =
            send(clientSocket, message + totalData, length - totalData, 0);
        if (actualDataSent < 0) {
            perror(
                "## ERROR in sendMessageToHost: There was a problem sending "
                "the "
                "last message.\n");
        }
        totalData += actualDataSent;
        // printf("TotalData so far is %lu while the length is %lu \n",
        // totalData, length);
    }
}

int receiveMessageFromHost(char* message, int clientSocket) {
    ssize_t totalData = 0;
    char* tempMessage = malloc(sizeof(char) * MAX_MESSAGE_SIZE);

    while (1) {
        int bytesReceived =
            recv(clientSocket, tempMessage, MAX_MESSAGE_SIZE, 0);
        if (bytesReceived < 0) {
            perror(
                "## ERROR in receiveMessageFromHost: There was a problem "
                "receiving "
                "a message from the host. \n");
        }

        /*
        #ifdef __STDC_LIB_EXT1__
                if (strncpy_s(message + totalData, tempMessage + totalData,
                              strlen(tempMessage)) != 0) {
                    perror(
                        "## ERROR in receiveMessageFromHost: There was a problem
        " "while saving the received message to the buffer.\n");
                }
        #endif
        */
        totalData += bytesReceived;
        if (bytesReceived == 0) break;  // End of stream.
    }

    return totalData;
}
