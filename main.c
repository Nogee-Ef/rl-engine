#include "main.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Tile** map;
int playerID;
Registry world;

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
        world.posComponents[world.posIndex[playerID]].x,
        world.posComponents[world.posIndex[playerID]].y,
        // It seems like the player's renderComponent is not being correctly retrieved. For debugging, I've replaced the code to retrieve that data with the expected values.
        WHITE, //world.renderComponents[world.renderIndex[playerID]].fg,
        BLACK, // world.renderComponents[world.renderIndex[playerID]].bg,
        '@' //world.renderComponents[world.renderIndex[playerID]].ch);
    ); 

    // Main game loop.
    int input;
    while ((input = getInput())) {
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        drawAt(
            world.posComponents[world.posIndex[playerID]].x,
            world.posComponents[world.posIndex[playerID]].y, 
            WHITE, //world.renderComponents[world.renderIndex[playerID]].fg,
            BLACK, // world.renderComponents[world.renderIndex[playerID]].bg,
            '@' //world.renderComponents[world.renderIndex[playerID]].ch);
        ); 
    }

    // Cleanup and Exit.
    freeMap(map);
    printf(SHOW);
    printf(CLEAR);
    return 0;
}
