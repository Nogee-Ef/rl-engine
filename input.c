#include "main.h"

/* TODO use some early returns to un-nest this mess. */
void moveEntity(Tile** map, int dx, int dy, int entityID) {
    // Check if the position is within the bounds of the map.
    if (
        world->posComponents[world->posIndex[entityID]].x + dx > 0 && world->posComponents[world->posIndex[entityID]].x + dx < MAP_WIDTH && 
        world->posComponents[world->posIndex[entityID]].y + dy > 0 && world->posComponents[world->posIndex[entityID]].y + dy < MAP_HEIGHT
    ) {
        // Check if the goal position is on a walkable tile
        if (map[world->posComponents[world->posIndex[entityID]].y + dy][world->posComponents[world->posIndex[entityID]].x + dx].walkable) {
            // Check if there is another entity occupying this position
            for (int i = 0; i < world->posSize; i++) {
                if (
                    world->posComponents[i].id != entityID && // The entity can't bump into itself if it sits still.
                    world->posComponents[i].y == world->posComponents[world->posIndex[entityID]].y + dy &&
                    world->posComponents[i].x == world->posComponents[world->posIndex[entityID]].x + dx
                ) {
                    char toPrint[100];
                    sprintf(toPrint, "Entity %d bumps into entity %d", entityID, world->posComponents[i].id);
                    pushMessage(toPrint, WHITE);
                    return;
                }
            }
            // Move the entity
            world->posComponents[world->posIndex[entityID]].x += dx;
            world->posComponents[world->posIndex[entityID]].y += dy;
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

int handleInput(int input, Tile** map) {
    if (input == 'q') {
        running = FALSE;
        return 1;
    }
    else if (input > 48 && input < 58) {
        moveEntity(map, coordList[input-49][0], coordList[input-49][1], playerID);
        return 1;
    }

    return 0;
    //     case 75: // Arrow Left
    //         moveEntity(map, -1, 0);
    //         break;
    //     case 77: // Arrow Right
    //         moveEntity(map, 1, 0);
    //         break;
}