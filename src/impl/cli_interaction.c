#include "../headers/cli_interaction.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void setupIO() {
    initscr();
    nodelay(stdscr, TRUE);
}

void closeIO() { endwin(); }

void showText(char* text) {
    wprintw(stdscr, "%s \r\n", text);
    refresh();
}

void showMessage(char* text) {
    wprintw(stdscr, "%s \r\n", text);
    refresh();
}

/**
 * Do not forget to free the textBuffer after the message is shown using
 * showMessage method.
 *
 * @return char* buffer which contains the message. Should be freed after usage.
 */
char* receiveText() {
    char* textBuffer = malloc(sizeof(char) * MAX_MESSAGE_SIZE);
    wgetnstr(stdscr, textBuffer, MAX_MESSAGE_SIZE);
    return textBuffer;
}