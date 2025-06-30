#include "main.h"
#include <string.h>

#define BUFFER_HEIGHT 32 // Map height + frame height + message log height
#define BUFFER_WIDTH 102 // Map width + frame width

typedef struct {
    char ch[4];
    int fg;
    int bg;
} Glyph;

static Glyph** displayBuffer;
void initDisplayBuffer(void) {
    displayBuffer = calloc(BUFFER_HEIGHT, sizeof(Glyph*));
    for (int y = 0; y < BUFFER_HEIGHT; y ++) {
        displayBuffer[y] = calloc(BUFFER_WIDTH, sizeof(Glyph));
        for (int x = 0; x < BUFFER_WIDTH; x++) {
                strcpy(displayBuffer[y][x].ch, " ");
                displayBuffer[y][x].fg = WHITE;
                displayBuffer[y][x].bg = BLACK;
        }
    }
}

void freeDisplayBuffer(void) {
    for (int y = 0; y < BUFFER_HEIGHT; y++) {
        free(displayBuffer[y]);
    }
    free(displayBuffer);
}

void printDisplayBuffer(void) {
    moveCursor(0,0);
    for (int y = 0; y < BUFFER_HEIGHT; y++) {
        for (int x = 0; x < BUFFER_WIDTH; x++) {
            printf("\x1b[%dm\x1b[%dm%s",displayBuffer[y][x].fg, displayBuffer[y][x].bg + 10, displayBuffer[y][x].ch);
        }
        printf("\n");
    }
}

void renderAt(int x, int y, int fg, int bg, char toPrint[4]) {
    if (y > -1 && y < BUFFER_HEIGHT && x > -1 && x < BUFFER_WIDTH) {
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

void renderTileMap(Map* map) {
    map->visibility++;
    computeFov(map, world->posComponents[world->posIndex[playerID]].x, world->posComponents[world->posIndex[playerID]].y, 12);
    for (int y = 0; y < map->HEIGHT; y ++) {
        for (int x = 0; x < map->WIDTH; x++) {
            if (map->tiles[y][x].visible == 0) {
                continue;
            } else if (map->tiles[y][x].visible == map->visibility) {
                renderAt(x + 1, y + 1, map->tiles[y][x].fg, map->tiles[y][x].bg, &map->tiles[y][x].ch);
            } else {
                renderAt(x + 1, y + 1, BRIGHT(BLACK), map->tiles[y][x].bg, &map->tiles[y][x].ch);
            }
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
            const int length = (int)strlen(messageLog[i].text);
            for (int l = 0; l < 80; l++) {
                if (l < length) {
                    const char toPrint[4] = {messageLog[i].text[l]};
                    strcpy(displayBuffer[30 + i - numMessages][l + 1].ch, toPrint);
                    displayBuffer[30 + i - numMessages][l + 1].fg = messageLog[i].fg;
                } else {
                    // Clear the rest of the buffer.
                    strcpy(displayBuffer[30 + i - numMessages][l + 1].ch, " ");
                }                
            }
        }
    }
}