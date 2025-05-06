#include "header.h"

void enableVirtualTerminalProcessing(void) {
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(hOuput, &dwMode);
    SetConsoleMode(hOuput, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void drawAt(int x, int y, int fg, int bg, char toPrint) {
    // Move the cursor to position x, y
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Print the string.
    printf("\x1b[%dm\x1b[%dm%c%s", fg, bg + 10, toPrint, RESET);
}

void drawTileMap(Tile** map) {
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            drawAt(x, y, map[y][x].fg, map[y][x].bg, map[y][x].ch);
        }
    }
}

void displaySetup(void) {
    enableVirtualTerminalProcessing();
    SetConsoleOutputCP(CP_UTF8);
    printf(HIDE);
    printf(CLEAR);
}