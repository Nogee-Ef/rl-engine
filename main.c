#include "main.h"

Map map;
int player_id;
Registry* world;
bool running;

int main(void) {
    // Display setup functions.
    displaySetup();

    // ECS set up functions.
    world = ecsInitWorld();

    // Set up the Tile Map.
    Map map = (Map){ .tiles = createMapTiles(100, 25), .WIDTH = 100, .HEIGHT = 25, .visibility = 0 };
    generateFloor(&map, 5); // generateFloor handles initializing the player.

    // Test entity.
    int npc_id = ecsInitEntity(world);
    ecsAddPosition(world, npc_id, 30, 15);
    ecsAddRenderable(world, npc_id, '@', BRIGHT(YELLOW), BLACK);
    
    initDisplayBuffer();
    renderTileMap(&map); // Draw the initial map so the screen doesn't appear blank before the first input.
    ecsRenderSystem(world, &map);

    pushMessage("Thanks for playing!", CYAN);
    displayMessageLog();

    renderFrame(0, 0, map.WIDTH + 1, map.HEIGHT + 1);
    renderFrame(0, map.HEIGHT + 2, map.WIDTH + 1, 4);
    printDisplayBuffer();
    

    // Main game loop.
    running = TRUE;
    while (running) {
        ecsTurnSystem(world, &map);

        // Render functions.
        renderTileMap(&map);
        ecsRenderSystem(world, &map);
        displayMessageLog();
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