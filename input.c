#include "main.h"

int moveEntity(Map* map, int dx, int dy, int entity_id) {
    if (
        world->pos_components[world->pos_index[entity_id]].x + dx < 0 || world->pos_components[world->pos_index[entity_id]].x + dx > map->WIDTH || 
        world->pos_components[world->pos_index[entity_id]].y + dy < 0 || world->pos_components[world->pos_index[entity_id]].y + dy > map->HEIGHT
    ) {
        return 0;
    }
    if (!map->tiles[world->pos_components[world->pos_index[entity_id]].y + dy][world->pos_components[world->pos_index[entity_id]].x + dx].walkable) {
        pushMessage("That way is obstructed.", BRIGHT(BLACK));
        return 0;
    }
    // Check if there is another entity occupying this position
    for (int i = 0; i < world->pos_size; i++) {
        if (
            world->pos_components[i].id != entity_id && // The entity can't bump into itself if it sits still.
            world->pos_components[i].y == world->pos_components[world->pos_index[entity_id]].y + dy &&
            world->pos_components[i].x == world->pos_components[world->pos_index[entity_id]].x + dx
        ) {
            char to_print[100];
            sprintf(to_print, "Entity %d bumps into entity %d", entity_id, world->pos_components[i].id);
            pushMessage(to_print, WHITE);
            return 1;
        }
    }

    world->pos_components[world->pos_index[entity_id]].x += dx;
    world->pos_components[world->pos_index[entity_id]].y += dy;
    return 1;
}

static const int COORD_LIST[10][2] = { 
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

int handleInput(int input, Map* map) {
    if (input == 'q') {
        running = FALSE;
        return 1;
    }
    else if (input > 48 && input < 58) {
        return moveEntity(map, COORD_LIST[input-49][0], COORD_LIST[input-49][1], player_id);
    }
    pushMessage("Invalid input.", YELLOW);
    return 0;
    //     case 75: // Arrow Left
    //         moveEntity(map, -1, 0);
    //         break;
    //     case 77: // Arrow Right
    //         moveEntity(map, 1, 0);
    //         break;
}