#include "main.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Tile** map;
int playerID;
Registry* world;

int main(void) {
    // Display setup functions.
    displaySetup();

    // ECS set up functions.
    world = ecsInitWorld();

    // Set up the Tile Map.
    map = createTilesMap();
    generateFloor(map, 5); // generateFloor handles initializing the player.

    // Test entity.
    int npc = ecsInitEntity(world);
    ecsAddPosition(world, npc, 30, 15);
    ecsAddRenderable(world, npc, '@', BRIGHT(YELLOW), BLACK);
    
    drawTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.
    ecsRenderSystem(world);

    pushMessage("Thanks for playing!", BRIGHT(BLUE));
    displayMessageLog();

    // Main game loop.
    int input;
    while (TRUE) {
        input = getInput();
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        ecsRenderSystem(world);
        displayMessageLog();
    }

    // Cleanup and Exit.
    freeMap(map);
    ecsFreeWorld(world);
    printf(SHOW);
    printf(CLEAR);

    return 0;
}