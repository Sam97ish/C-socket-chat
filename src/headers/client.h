#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <netinet/in.h>


/**
 * Initilizes the client socket using the specified protocol and then connects
 * to the provided address.
 *
 * @param clientAddress socketaddr_out struct which specifies the protocol, the
 * address and the port in which the client socket will be connected to.
 * @return The socket descriptor.
 */
int connectToHost(struct sockaddr_in clientAddress);

/**
 * Sends a message to the host using the client socket descriptor.
 *
 * @param message The message to be sent to the host.
 * @param clientSocket The client socket descriptor to be used to send the
 * message.
 */
void sendMessageToHost(char* message, int clientSocket);

/**
 * Receives a message from the host using the client socket descriptor.
 *
 * @param clientSocket The client socket decriptor to be used to receive the
 * message.
 * @param message A buffer to store the message received from host.
 * @return The number of bytes received from the host.
 */
int receiveMessageFromHost(char* message, int clientSocket);

#endif  // CLIENT_H