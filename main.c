#include "header.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Tile** map;
Entity* player;

int main(void) {
    // Setup functions.
    enableVirtualTerminalProcessing();
    SetConsoleOutputCP(CP_UTF8);
    printf(HIDE);
    printf(CLEAR);

    // Set up the Tile Map.
    map = createTilesMap();
    drawTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.

    // Set up the player.
    player = createEntity(20, 20, '@', WHITE, BLACK);
    Entity* npc = createEntity(10, 10, '@', YELLOW, BLACK);

    // Main game loop.
    int input;
    while (input = _getch()) {
        if (input == 'q') break;
        handleInput(input);

        drawTileMap(map);
        drawAt(player.position.x, player.position.y, player.renderable.fg, player.renderable.bg, player.renderable.ch);
        drawAt(npc.position.x, npc.position.y, npc.renderable.fg, npc.renderable.bg, npc.renderable.ch);
    }

    // Cleanup and Exit.
    freeMap(map);
    free(player);
        // At some point it may be wise to revert the Virtual Terminal Processing and Console codepage changes.
    return 0;
}