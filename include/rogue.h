#ifndef ROGUE_H // This prevents rogue.h from being compiled multiple times.
#define ROGUE_H

#include <curses.h>
#include <stdlib.h>

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
    char ch;
    bool walkable;
} Tile;


typedef struct
{
    Position pos;
    char ch;
} Entity;

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// draw.c functions
void drawMap(void);
void drawEntity(Entity* entity);
void drawEverything(void);

// map.c functions
Tile** createMapTiles(void);
Position setupMap(void);
void freeMap(void);

// player.c functions
Entity* createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

// externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;
extern Tile** map;

#endif