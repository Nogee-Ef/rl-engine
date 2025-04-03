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
    drawTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.
    generateFloor(map, 5); // generateFloor handles initializing the player.

    // Set up the player.
    // player = createEntity(20, 20, '@', WHITE, BLACK);
    //Entity* npc = createEntity(10, 10, '@', YELLOW, BLACK);
    drawAt(player->position.x, player->position.y, player->renderable.fg, player->renderable.bg, player->renderable.ch);
    //drawAt(npc->position.x, npc->position.y, npc->renderable.fg, npc->renderable.bg, npc->renderable.ch);

    // Main game loop.
    int input;
    while (input = _getch()) {
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        drawAt(player->position.x, player->position.y, player->renderable.fg, player->renderable.bg, player->renderable.ch);
        // drawAt(npc->position.x, npc->position.y, npc->renderable.fg, npc->renderable.bg, npc->renderable.ch);
    }

    // Cleanup and Exit.
    freeMap(map);
    free(player);
    return 0;
}