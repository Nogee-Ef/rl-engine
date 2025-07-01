#include "main.h"

Tile** createMapTiles(int width, int height) {
    Tile** tiles = calloc(height, sizeof(Tile*));
    for (int y = 0; y < height; y ++) {
        tiles[y] = calloc(width, sizeof(Tile));
        for (int x = 0; x < width; x++) {
                tiles[y][x].ch = '#';
                tiles[y][x].fg = WHITE;
                tiles[y][x].bg = BLACK;
                tiles[y][x].walkable = FALSE;
                tiles[y][x].visible = 0;
        }
    }

    return tiles;
}

void freeMapTiles(Map* map) {
    for (int y = 0; y < map->HEIGHT; y++) {
        free(map->tiles[y]);
    }
    free(map->tiles);
}

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Room;

Room createRoom(int x, int y, int height, int width) {
    Room new_room;
    new_room.x = x;
    new_room.y = y;
    new_room.height = height;
    new_room.width = width;

    return new_room;
}

void addRoomToMap(Map* map, Room room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            map->tiles[y][x].ch = '.';
            map->tiles[y][x].walkable = TRUE;
        }
    }
}

void connectRoomCenters(Map* map, int start_x, int start_y, int end_x, int end_y) {
    int temp_x = start_x;
    int temp_y = start_y;

    while (TRUE) {
        if (abs((temp_x - 1) - end_x) < abs(temp_x - end_x))
        temp_x--;
        else if (abs((temp_x + 1) - end_x) < abs(temp_x - end_x))
            temp_x++;
        else if (abs((temp_y + 1) - end_y) < abs(temp_y - end_y))
            temp_y++;
        else if (abs((temp_y - 1) - end_y) < abs(temp_y - end_y))
            temp_y--;
        else
            break;
        
        map->tiles[temp_y][temp_x].ch = '.';
        map->tiles[temp_y][temp_x].walkable = TRUE;
    }
}

void generateFloor(Map* map, int max_rooms) {
    int y, x, height, width;
    Room* rooms = calloc(max_rooms, sizeof(Room));
    for (int n = 0; n < max_rooms; n++) {
        y = (rand() % (map->HEIGHT - 10)) + 1;
        x = (rand() % (map->WIDTH - 20)) + 1;
        height = (rand() % 7) + 3;
        width = (rand() % 15) + 5;
        rooms[n] = createRoom(x, y, height, width);
        addRoomToMap(map, rooms[n]);

        if (n > 0) {
            connectRoomCenters(map, rooms[n-1].x + (int)(rooms[n-1].width / 2), rooms[n-1].y + (int)(rooms[n-1].height / 2), rooms[n].x + (int)(rooms[n].width / 2), rooms[n].y + (int)(rooms[n].height / 2));
        }
    }

    player_id = ecsInitEntity(world);
    ecsAddPosition(world, player_id, rooms[0].x + (int)(rooms[0].width / 2), rooms[0].y + (int)(rooms[0].height / 2));
    ecsAddRenderable(world, player_id, '@', BRIGHT(WHITE), BLACK);

    free(rooms);
}