#include "main.h"
#include <string.h>

void drawAt(int x, int y, int fg, int bg, char toPrint) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%c%s", fg, bg + 10, toPrint, RESET);
}

void drawString(int x, int y, int fg, int bg, char string[100]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, string, RESET);
}

void drawTileMap(Tile** map) {
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            drawAt(x, y, map[y][x].fg, map[y][x].bg, map[y][x].ch);
        }
    }
}

static Message messageLog[80];
static int numMessages = 0;

void pushMessage(char message[100], int fg) {
    if (numMessages < 80) {
        numMessages++;
        strcpy(messageLog[numMessages].text, message);
        messageLog[numMessages].fg = fg;
    }
}

void displayMessageLog(void) {
    for (int i = numMessages; i > numMessages - 3; i--) {
        if (i > 0) {
            drawString(0, 27 + i - numMessages, messageLog[i].fg, BLACK, messageLog[i].text);
        }
    }
}