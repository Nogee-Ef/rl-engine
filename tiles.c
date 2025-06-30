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
    Room newRoom;
    newRoom.x = x;
    newRoom.y = y;
    newRoom.height = height;
    newRoom.width = width;

    return newRoom;
}

void addRoomToMap(Map* map, Room room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            map->tiles[y][x].ch = '.';
            map->tiles[y][x].walkable = TRUE;
        }
    }
}

void connectRoomCenters(Map* map, int startX, int startY, int endX, int endY) {
    int tempX = startX;
    int tempY = startY;

    while (TRUE) {
        if (abs((tempX - 1) - endX) < abs(tempX - endX))
        tempX--;
        else if (abs((tempX + 1) - endX) < abs(tempX - endX))
            tempX++;
        else if (abs((tempY + 1) - endY) < abs(tempY - endY))
            tempY++;
        else if (abs((tempY - 1) - endY) < abs(tempY - endY))
            tempY--;
        else
            break;
        
        map->tiles[tempY][tempX].ch = '.';
        map->tiles[tempY][tempX].walkable = TRUE;
    }
}

void generateFloor(Map* map, int maxRooms) {
    int y, x, height, width;
    Room* rooms = calloc(maxRooms, sizeof(Room));
    for (int n = 0; n < maxRooms; n++) {
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

    playerID = ecsInitEntity(world);
    ecsAddPosition(world, playerID, rooms[0].x + (int)(rooms[0].width / 2), rooms[0].y + (int)(rooms[0].height / 2));
    ecsAddRenderable(world, playerID, '@', BRIGHT(WHITE), BLACK);

    free(rooms);
}