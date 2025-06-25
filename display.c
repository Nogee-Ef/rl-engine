#include "main.h"
#include <string.h>

typedef struct {
    char ch[4];
    int fg;
    int bg;
} Glyph;

static Glyph** displayBuffer;
void initDisplayBuffer(void) {
    displayBuffer = calloc(MAP_HEIGHT+1, sizeof(Glyph*));
    for (int y = 0; y < MAP_HEIGHT+1; y ++) {
        displayBuffer[y] = calloc(MAP_WIDTH+1, sizeof(Glyph));
        for (int x = 0; x < MAP_WIDTH+1; x++) {
                strcpy(displayBuffer[y][x].ch, " ");
                displayBuffer[y][x].fg = WHITE;
                displayBuffer[y][x].bg = BLACK;
        }
    }
}

void freeDisplayBuffer(void) {
    for (int y = 0; y < MAP_HEIGHT+1; y++)
    {
        free(displayBuffer[y]);
    }
    free(displayBuffer);
}

void printDisplayBuffer(void) {
    moveCursor(0,0);
    for (int y = 0; y < MAP_HEIGHT+1; y++)
    {
        for (int x = 0; x < MAP_WIDTH+1; x++) {
            printf("\x1b[%dm\x1b[%dm%s",displayBuffer[y][x].fg, displayBuffer[y][x].bg + 10, displayBuffer[y][x].ch);
        }
        printf("\n");
    }
}

void renderAt(int x, int y, int fg, int bg, char toPrint[4]) {
    if (y > -1 && y < MAP_HEIGHT+1 && x > -1 && x < MAP_WIDTH+1) {
                strcpy(displayBuffer[y][x].ch, toPrint);
                displayBuffer[y][x].fg = fg;
                displayBuffer[y][x].bg = bg;
    }
}

void renderFrame(int originX, int originY, int width, int height) {
    renderAt(originX, originY, WHITE, BLACK, "┌");
    renderAt(originX + width, originY, WHITE, BLACK, "┐");
    renderAt(originX, originY + height, WHITE, BLACK, "└");
    renderAt(originX + width, originY + height, WHITE, BLACK, "┘");
    for (int i = 1; i < width; i++) {
        renderAt(originX + i, originY, WHITE, BLACK, "─");
        renderAt(originX + i, originY + height, WHITE, BLACK, "─");
    }
    for (int n = 1; n < height; n++) {
        renderAt(originX, originY + n, WHITE, BLACK, "│");
        renderAt(originX + width, originY + n, WHITE, BLACK, "│");
    }
}

void renderTileMap(Tile** map) {
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            renderAt(x, y, map[y][x].fg, map[y][x].bg, &map[y][x].ch);
        }
    }
}

void drawAt(int x, int y, int fg, int bg, char toPrint[4]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, toPrint, RESET);
}

void drawString(int x, int y, int fg, int bg, char string[100]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, string, RESET);
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
            drawString(0, 28 + i - numMessages, messageLog[i].fg, BLACK, messageLog[i].text);
        }
    }
}