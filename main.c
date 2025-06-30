#include "main.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Map map;
int playerID;
Registry* world;
bool running;

int main(void) {
    // Display setup functions.
    displaySetup();

    // ECS set up functions.
    world = ecsInitWorld();

    // Set up the Tile Map.
    Map map = (Map){ .tiles = createMapTiles(), .WIDTH = MAP_WIDTH, .HEIGHT = MAP_HEIGHT, .visibility = 0 };
    generateFloor(&map, 5); // generateFloor handles initializing the player.

    // Test entity.
    int npcID = ecsInitEntity(world);
    ecsAddPosition(world, npcID, 30, 15);
    ecsAddRenderable(world, npcID, '@', BRIGHT(YELLOW), BLACK);
    
    initDisplayBuffer();
    renderTileMap(&map); // Draw the initial map so the screen doesn't appear blank before the first input.
    ecsRenderSystem(world, &map);

    pushMessage("Thanks for playing!", BRIGHT(BLUE));
    displayMessageLog();

    renderFrame(0, 0, map.WIDTH, map.HEIGHT);
    renderFrame(0, map.HEIGHT + 1, map.WIDTH, 4);
    printDisplayBuffer();
    

    // Main game loop.
    running = TRUE;
    while (running) {
        ecsTurnSystem(world, &map);

        // Render functions.
        renderTileMap(&map);
        ecsRenderSystem(world, &map);
        displayMessageLog();
        renderFrame(0, 0, map.WIDTH, map.HEIGHT);
        printDisplayBuffer();
    }

    // Cleanup and Exit.
    freeMapTiles(&map);
    ecsFreeWorld(world);
    freeDisplayBuffer();
    
    printf(SHOW);
    printf(CLEAR);
    onExit();

    return 0;
}