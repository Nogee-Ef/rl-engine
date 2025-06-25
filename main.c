#include "main.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Tile** map;
int playerID;
Registry* world;
int running;

int main(void) {
    // Display setup functions.
    displaySetup();

    // ECS set up functions.
    world = ecsInitWorld();

    // Set up the Tile Map.
    map = createTilesMap();
    generateFloor(map, 5); // generateFloor handles initializing the player.

    // Test entity.
    int npcID = ecsInitEntity(world);
    ecsAddPosition(world, npcID, 30, 15);
    ecsAddRenderable(world, npcID, '@', BRIGHT(YELLOW), BLACK);
    
    renderTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.
    ecsRenderSystem(world);

    pushMessage("Thanks for playing!", BRIGHT(BLUE));
    displayMessageLog();

    renderFrame(0, 0, MAP_WIDTH, MAP_HEIGHT);
    renderFrame(0, MAP_HEIGHT + 1, MAP_WIDTH, 4);
    printDisplayBuffer();
    

    // Main game loop.
    running = TRUE;
    while (running) {
        ecsTurnSystem(world, map);

        // Render functions.
        renderTileMap(map);
        ecsRenderSystem(world);
        displayMessageLog();
        renderFrame(0, 0, MAP_WIDTH, MAP_HEIGHT);
        printDisplayBuffer();
    }

    // Cleanup and Exit.
    freeMap(map);
    ecsFreeWorld(world);
    
    printf(SHOW);
    printf(CLEAR);
    onExit();

    return 0;
}