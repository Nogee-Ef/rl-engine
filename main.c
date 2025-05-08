#include "main.h"
#include "ecs.h"

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

    // ECS set up functions.
    Registry world = ecsInitWorld();

    // Initialize the player through the ECS.
    const int playerID = ecsInitEntity(world);
    ecsAddPosition(world, playerID, player->position.x, player->position.y);
    ecsAddRenderable(world, playerID, player->renderable.fg, player->renderable.bg, player->renderable.ch);

    drawAt(world.posComponents[world.posIndex[playerID]].x,   // Draw the player using the information from the ECS lists.
        world.posComponents[world.posIndex[playerID]].y,
        // It seems like the player's renderComponent is not being correctly retrieved.
        WHITE, //world.renderComponents[world.renderIndex[playerID]].fg,
        world.renderComponents[world.renderIndex[playerID]].bg,
        '@'); //world.renderComponents[world.renderIndex[playerID]].ch);

    // Main game loop.
    int input;
    while ((input = getInput())) {
        if (input == 'q') break;
        handleInput(input, map);

        drawTileMap(map);
        drawAt(world.posComponents[world.posIndex[playerID]].x, // Draw the player using the information from the ECS lists.
            world.posComponents[world.posIndex[playerID]].y, 
            world.renderComponents[world.renderIndex[playerID]].fg,
            world.renderComponents[world.renderIndex[playerID]].bg,
            world.renderComponents[world.renderIndex[playerID]].ch);
        // drawAt(player->position.x, player->position.y, player->renderable.fg, player->renderable.bg, player->renderable.ch);
    }

    // Cleanup and Exit.
    freeMap(map);
    free(player);
    printf(CLEAR);
    return 0;
}