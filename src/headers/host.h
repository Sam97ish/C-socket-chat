#ifndef HOST_H
#define HOST_H
#include <sys/socket.h>
#include <netinet/in.h>


/**
 * Initilizes the server socket using the specified protocol.
 *
 * @param serverSocket socketaddr_in struct which specifies the address and the
 * port in which the socket will be bound to. declare and fill the s_family,
 * s_port, s_address and whatever else your socket needs to be bound.
 * @return The socket descriptor.
 */
int setupHost(struct sockaddr_in serverAddress);

/**
 * Sends the given message to all the clients connected.
 *
 * @param message the message to be sent through the socket.
 * @param socket The socket descriptor to send the message to.
 */
void sendMessageToAll(char* message, int socket);

/**
 * Receives a message from a client who is connected to this host.
 *
 * @param message The buffer to store the message received.
 * @param socket The socket decriptor of the socket that is handling this
 * client.
 * @return The number of bytes received from the client.
 */
int receiveMessageFromClient(char* message, int socket);

#endif  // HOST_H