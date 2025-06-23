#include "main.h"
#include <string.h>

typedef struct {
    char ch;
    int fg;
    int bg;
} Glyph;

static Glyph** displayBuffer;
void initDisplayBuffer(void) {
    displayBuffer = calloc(MAP_HEIGHT, sizeof(Glyph*));
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        displayBuffer[y] = calloc(MAP_WIDTH, sizeof(Glyph));
        for (int x = 0; x < MAP_WIDTH; x++) {
                displayBuffer[y][x].ch = ' ';
                displayBuffer[y][x].fg = WHITE;
                displayBuffer[y][x].bg = BLACK;
        }
    }
}

void freeDisplayBuffer(void) {
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        free(displayBuffer[y]);
    }
    free(displayBuffer);
}

void printDisplayBuffer(void) {
    moveCursor(0,0);
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("\x1b[%dm\x1b[%dm%c",displayBuffer[y][x].fg, displayBuffer[y][x].bg + 10, displayBuffer[y][x].ch);
        }
        printf("\n");
    }
}

void drawAt(int x, int y, int fg, int bg, char toPrint) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%c%s", fg, bg + 10, toPrint, RESET);
    // if (y > 0 && y < MAP_HEIGHT && x > 0 && x < MAP_WIDTH) {
    //     displayBuffer[y][x] = (Glyph){.ch = toPrint, .fg = fg, .bg = bg};
    // }
}

void drawString(int x, int y, int fg, int bg, char string[100]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, string, RESET);
}

// void drawFrame(int originX, int originY, int width, int height) {
//     drawAt(originX, originY, WHITE, BLACK, "┌");
//     drawAt(originX + width, originY, WHITE, BLACK, "┐");
//     drawAt(originX, originY + height, WHITE, BLACK, "└");
//     drawAt(originX + width, originY + height, WHITE, BLACK, "┘");
//     for (int i = 1; i < width; i++) {
//         drawAt(originX + i, originY, WHITE, BLACK, "─");
//         drawAt(originX + i, originY + height, WHITE, BLACK, "─");
//     }
//     for (int n = 1; n < height; n++) {
//         drawAt(originX, originY + n, WHITE, BLACK, "│");
//         drawAt(originX + width, originY + n, WHITE, BLACK, "│");
//     }
// }

void drawTileMap(Tile** map) {
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            drawAt(x, y, map[y][x].fg, map[y][x].bg, map[y][x].ch);
        }
    }
}

typedef struct {
    char text[100];
    int fg;
} Message;

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