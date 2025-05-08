#include "main.h"

void moveEntity(Tile** map, int dx, int dy) {
    // Check if the position is within the bounds of the map.
    if (player->position.x + dx > 0 && player->position.x + dx < MAP_WIDTH && player->position.y + dy > 0 && player->position.y + dy < MAP_HEIGHT) {
        // Check if the position is on a walkable tile
        if (map[player->position.y + dy][player->position.x + dx].walkable) {
            // Move the entity
            player->position.x = player->position.x + dx;
            player->position.y = player->position.y + dy;
        }
    }
}

void handleInput(int input, Tile** map) {
    /*
    Position coordList[10] = { [-1, 1], };
    if (input > 48 && input < 57) {
        moveEntity(map, coordList[input-49].x, coordList[input-49].y);
    }
    */
    switch (input) {
        case 49: // NUMPAD Down Left
            moveEntity(map, -1, 1);
            break;
        case 50: // NUMPAD Down
            moveEntity(map, 0, 1);
            break;
        case 51: // NUMPAD Down Right
            moveEntity(map, 1, 1);
            break;
        case 52: // NUMPAD Left
            moveEntity(map, -1, 0);
            break;
        // case 53: NUMPAD Wait
        case 54: // NUMPAD Right
            moveEntity(map, 1, 0);
            break;
        case 55: // NUMPAD Up Left
            moveEntity(map, -1, -1);
            break;
        case 56: //NUMPAD Up
            moveEntity(map, 0, -1);
            break;
        case 57: // NUMPAD Up Right
            moveEntity(map, 1, -1);
            break;
        case 75: // Arrow Left
            moveEntity(map, -1, 0);
            break;
        case 77: // Arrow Right
            moveEntity(map, 1, 0);
            break;
    }
}