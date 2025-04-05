#include "header.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Tile** map;
Entity* player;

int main(void) {
    // Display setup functions.
    displaySetup();

    // Set up the Tile Map.
    map = createTilesMap();
    generateFloor(map, 5); // generateFloor handles initializing the player.
    drawTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.

    // Set up the player.
    drawAt(player->position.x, player->position.y, player->renderable.fg, player->renderable.bg, player->renderable.ch);

    // Main game loop.
    int input;
    while (input = _getch()) {
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        drawAt(player->position.x, player->position.y, player->renderable.fg, player->renderable.bg, player->renderable.ch);
    }

    // Cleanup and Exit.
    freeMap(map);
    free(player);
    printf(CLEAR);
    return 0;
}