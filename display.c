#include "main.h"

void drawAt(int x, int y, int fg, int bg, char toPrint) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%c%s", fg, bg + 10, toPrint, RESET);
}

void drawTileMap(Tile** map) {
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            drawAt(x, y, map[y][x].fg, map[y][x].bg, map[y][x].ch);
        }
    }
}