#include "main.h"

void moveEntity(Tile** map, int dx, int dy) {
    
    // Check if the position is within the bounds of the map.
    if (
        world->posComponents[world->posIndex[playerID]].x + dx > 0 && world->posComponents[world->posIndex[playerID]].x + dx < MAP_WIDTH && 
        world->posComponents[world->posIndex[playerID]].y + dy > 0 && world->posComponents[world->posIndex[playerID]].y + dy < MAP_HEIGHT
    ) {
        // Check if the goal position is on a walkable tile
        if (map[world->posComponents[world->posIndex[playerID]].y + dy][world->posComponents[world->posIndex[playerID]].x + dx].walkable) {
            // Move the entity
            world->posComponents[world->posIndex[playerID]].x += dx;
            world->posComponents[world->posIndex[playerID]].y += dy;
        }
    }
}

static int coordList[10][2] = { 
    {-1, 1}, // NUMPAD Down Left
    { 0, 1}, // NUMPAD Down
    { 1, 1}, // NUMPAD Down Right
    { -1, 0}, // NUMPAD Left
    { 0, 0}, // NUMPAD Center / Wait
    { 1, 0}, // NUMPAD Right
    { -1, -1}, // NUMPAD Up Left
    { 0, -1}, // NUMPAD Up
    { 1, -1}, // NUMPAD Up Right
};

void handleInput(int input, Tile** map) {
    if (input > 48 && input < 57) {
        moveEntity(map, coordList[input-49][0], coordList[input-49][1]);
    }
    //     case 75: // Arrow Left
    //         moveEntity(map, -1, 0);
    //         break;
    //     case 77: // Arrow Right
    //         moveEntity(map, 1, 0);
    //         break;
}