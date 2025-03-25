#include "header.h"

void moveEntity(Tile** map, int x, int y) {
    // Check if the position is within the bounds of the map.
    if (player->position.x + x > 0 && player->position.x + x < MAP_WIDTH && player->position.y + y > 0 && player->position.y + y < MAP_HEIGHT) {
        // Check if the position is on a walkable tile
        if (map[player->position.y + y][player->position.x + x].walkable) {
            // Move the entity
            player->position.x = player->position.x + x;
            player->position.y = player->position.y + y;
        }
    }
}

void handleInput(int input, Tile** map) {
    switch (input) {
        case 49: // NUMPAD Down Left
            player->position.x -= 1;
            player->position.y += 1;
            break;
        case 51: // NUMPAD Down Right
            player->position.x += 1;
            player->position.y += 1;
            break;
        case 52: // NUMPAD Left
            player->position.x -= 1;
            break;
        case 54: // NUMPAD Right
            player->position.x += 1;
            break;
        case 55: // NUMPAD Up Left
            player->position.x -= 1;
            player->position.y -= 1;
            break;
        case 57: // NUMPAD Up Right
            player->position.x += 1;
            player->position.y -= 1;
            break;
        case 75: // Arrow Left
            moveEntity(map, -1, 0);
            // player->position.x -= 1;
            break;
        case 77: // Arrow Right
            moveEntity(map, 1, 0);
            // player->position.x += 1;
            break;
    }
}