#ifndef CLI_INTERACTION_H
#define CLI_INTERACTION_H

// Defines the maximum length a message between users can be.
#define MAX_MESSAGE_SIZE 1000

/**
 * Prints the text given to whichever output interface specified.
 * Used mainly to communicate program - user interactions.
 *
 * @param text The text to be shown to the user.
 */
void showText(char* text);

/**
 * Prints the message received from another user to the output interface
 * specified.
 *
 * @param text The message received from the other user and to be shown to the
 * current user.
 */
void showMessage(char* text);

/**
 * Receives a text input from the current user.
 * Used mainly to communicate program - user intercations.
 *
 * @return A char* struct containing the text received from the current user.
 */
char* receiveText();

void setupIO();

void closeIO();

#endif  // CLI_INTERACTION_H