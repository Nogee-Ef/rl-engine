#include "main.h"

void moveEntity(Tile** map, int dx, int dy) {
    // Check if the position is within the bounds of the map.
    if (
        world->posComponents[world->posIndex[playerID]].x + dx > 0 && world->posComponents[world->posIndex[playerID]].x + dx < MAP_WIDTH && 
        world->posComponents[world->posIndex[playerID]].y + dy > 0 && world->posComponents[world->posIndex[playerID]].y + dy < MAP_HEIGHT
    ) {
        // Check if the goal position is on a walkable tile
        if (map[world->posComponents[world->posIndex[playerID]].y + dy][world->posComponents[world->posIndex[playerID]].y + dx].walkable) {
            // Move the entity
            world->posComponents[world->posIndex[playerID]].x += dx;
            world->posComponents[world->posIndex[playerID]].y += dy;
        }
    }
}

// I could make this an array of arrays of integers, static int** coordList[10] = { [-1, 1], }
static Position coordList[10] = { 
    (Position){ .x = -1, .y = 1}, // NUMPAD Down Left
    (Position){ .x = 0, .y = 1}, // NUMPAD Down
    (Position){ .x = 1, .y = 1}, // NUMPAD Down Right
    (Position){ .x = -1, .y = 0}, // NUMPAD Left
    (Position){ .x = 0, .y = 0}, // NUMPAD Center / Wait
    (Position){ .x = 1, .y = 0}, // NUMPAD Right
    (Position){ .x = -1, .y = -1}, // NUMPAD Up Left
    (Position){ .x = 0, .y = -1}, // NUMPAD Up
    (Position){ .x = 1, .y = -1}, // NUMPAD Up Right
};
void handleInput(int input, Tile** map) {
    if (input > 48 && input < 57) {
        moveEntity(map, coordList[input-49].x, coordList[input-49].y);
    }
    // switch (input) {
    //     case 49: // NUMPAD Down Left
    //         moveEntity(map, -1, 1);
    //         break;
    //     case 50: // NUMPAD Down
    //         moveEntity(map, 0, 1);
    //         break;
    //     case 51: // NUMPAD Down Right
    //         moveEntity(map, 1, 1);
    //         break;
    //     case 52: // NUMPAD Left
    //         moveEntity(map, -1, 0);
    //         break;
    //     // case 53: NUMPAD Wait
    //     case 54: // NUMPAD Right
    //         moveEntity(map, 1, 0);
    //         break;
    //     case 55: // NUMPAD Up Left
    //         moveEntity(map, -1, -1);
    //         break;
    //     case 56: //NUMPAD Up
    //         moveEntity(map, 0, -1);
    //         break;
    //     case 57: // NUMPAD Up Right
    //         moveEntity(map, 1, -1);
    //         break;
    //     case 75: // Arrow Left
    //         moveEntity(map, -1, 0);
    //         break;
    //     case 77: // Arrow Right
    //         moveEntity(map, 1, 0);
    //         break;
    // }
}