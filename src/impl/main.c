
/*
 * main.c
 *
 * Copyright 2021 Hussam Aldeen <h-ssom1997@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../headers/client.h"
#include "../headers/host.h"
#include "../headers/cli_interaction.h"

/**
 * Checks if the quit command (q) is given.
 *
 * @param input The char* struct to be checked.
 * @return an int value, 0 for True. 1 for false.
 */
int checkQuitCommand(char* input) {
    char cmd = input[0];
    if (cmd == 'q') {
        return 0;
    }
    return 1;
}

/**
 * Converts a char* struct to a short type.
 * Used to extract the port number from argv.
 *
 * @param pchar The char* struct give.
 * @return the short integer.
 */
short char2short(char* pchar) {
    short number = pchar[0] << 8 | pchar[1];
    return number;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <C/H> <IP> <PORT>\n", argv[0]);
        exit(5);
    }

    int isRunning = 1;

    if (0 == strcmp(argv[1], "C")) {
        // Client mode.
        struct sockaddr_in clientAddress;
        clientAddress.sin_family = AF_INET;
        clientAddress.sin_addr.s_addr = INADDR_ANY;  // inet_addr(argv[2]);
        clientAddress.sin_port = htons(8888);  // htons(char2short(argv[3]));

        int socketDescriptor = connectToHost(clientAddress);

        setupIO();

        while (isRunning) {
            char* message = receiveText();
            /*
                "Hello This is a test, I will make a long message to test that "
                "the "
                "steam is working ok and to check any possible problems Let's "
                "keep "
                "going so that so that we reach 516 bytes I wonder how big the "
                "message is now. I'm gonna test now anyways. Hello This is a "
                "test, "
                "I will make a long message to test that the steam is working "
                "ok "
                "and to check any possible problems Let's keep going so that "
                "so "
                "that we reach 516 bytes I wonder how big the message is now. "
                "I'm "
                "gonna test now anyways. Hello This is a test, I will make a "
                "long message to test that the steam is working ok and to "
                "check any possible problems Let's keep going so that so that "
                "we reach 516 bytes I wonder how big the message is now. I'm "
                "gonna test now anyways. Hello This is a test, I will make a "
                "long message to test that the steam is working ok and to "
                "check any possible problems Let's keep going so that so that "
                "we reach 516 bytes I wonder how big the message is now. I'm "
                "gonna test now anyways. \n";  // receiveText();
                */

            isRunning = checkQuitCommand(message);
            // printf("Here\n");
            sendMessageToHost(message, socketDescriptor);
            free(message);

            char* receiveBuffer = malloc(sizeof(char) * MAX_MESSAGE_SIZE);
            int bytesReceived =
                receiveMessageFromHost(receiveBuffer, socketDescriptor);

            if (bytesReceived > 0) {
                showMessage(receiveBuffer);
            }

            // printf("Number of bytes read is %d", bytesReceived);

            free(receiveBuffer);
        }

        if (close(socketDescriptor) == -1)
            perror("socket close failed in main. \r\n");

    } else if (0 == strcmp(argv[1], "H")) {
        // Host mode.
        struct sockaddr_in bindAddress;
        bindAddress.sin_family = AF_INET;
        bindAddress.sin_addr.s_addr = INADDR_ANY;  // inet_addr(argv[2]);
        bindAddress.sin_port = htons(8888);  // htons(char2short(argv[3]));

        int serverSocketDescirptor = setupHost(bindAddress);

        printf("Listening at address %du and port %d\n",
               bindAddress.sin_addr.s_addr, bindAddress.sin_port);
        if (listen(serverSocketDescirptor, 3) < 0) {
            perror(
                "## ERROR in main: There was a problem while listening for "
                "connections.\n");
            exit(7);
        }

        int clientSocket = accept(serverSocketDescirptor, NULL, NULL);
        if (clientSocket < 0) {
            perror(
                "## ERROR in main: There was a problem accepting the client "
                "connection.\n");
            exit(8);
        }

        setupIO();

        while (isRunning) {
            char* message = receiveText();
            isRunning = checkQuitCommand(message);
            sendMessageToAll(message, clientSocket);
            free(message);

            char* receiveBuffer = malloc(sizeof(char) * MAX_MESSAGE_SIZE);
            int bytesReceived =
                receiveMessageFromClient(receiveBuffer, clientSocket);

            if (bytesReceived > 0) {
                // printf("message was received\n");
                showMessage(receiveBuffer);
            }
            free(receiveBuffer);
        }

        if (close(serverSocketDescirptor) == -1)
            perror("## ERROR in main: socket close failed in main. \r\n");

        if (close(clientSocket) == -1)
            perror("## ERROR in main: socket close failed in main. \r\n");

        if (shutdown(serverSocketDescirptor, SHUT_WR) == -1)
            perror("## ERROR in main: socket shutdown failed in main. \r\n");
    }

    closeIO();
    return 0;
}