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
  
    drawTileMap(map); // Draw the initial map so the screen doesn't appear blank before the first input.
    drawAt(
        world->posComponents[world->posIndex[playerID]].x,
        world->posComponents[world->posIndex[playerID]].y,
        world->renderComponents[world->renderIndex[playerID]].fg,
        world->renderComponents[world->renderIndex[playerID]].bg,
        world->renderComponents[world->renderIndex[playerID]].ch
    );

    // Main game loop.
    int input;
    while (TRUE) {
        input = getInput();
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        drawAt(
            world->posComponents[world->posIndex[playerID]].x,
            world->posComponents[world->posIndex[playerID]].y, 
            world->renderComponents[world->renderIndex[playerID]].fg,
            world->renderComponents[world->renderIndex[playerID]].bg,
            world->renderComponents[world->renderIndex[playerID]].ch
        );
    }

    // Cleanup and Exit.
    freeMap(map);
    ecsFreeWorld(world);
    printf(SHOW);
    printf(CLEAR);

    return 0;
}