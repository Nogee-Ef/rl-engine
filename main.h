#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* OS */
void displaySetup(void);
void moveCursor(int x, int y);
int getInput(void);

/* Tiles */
typedef struct {
    int x;
    int y;
    char ch;
    int fg;
    int bg;
    int walkable;
} Tile;

Tile** createTilesMap();
void freeMap(Tile** map);
void generateFloor(Tile** map, int maxRooms);

/* Display */
#define CLEAR "\x1b[2J\x1b[3J" // Clears the terminal AND the scroll back.
#define HIDE "\x1b[?25l" // Hides the cursor.
#define SHOW "\x1b[?25h" // Shows the cursor.

// Colors
#define RESET "\x1b[0m" // Resets color to its default value.

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define WHITE 37

void drawAt(int x, int y, int fg, int bg, char toPrint);
void drawTileMap(Tile** map);

/* ECS */
#define MAXENTITIES 100

typedef struct {
    int id;
    int x;
    int y;
} PositionComponent;

typedef struct {
    int id;
    char ch;
    int fg;
    int bg;
} RenderableComponent;

typedef struct {
    int entityCount;
    PositionComponent *posComponents;
    int *posIndex;
    int posSize;
    RenderableComponent *renderComponents;
    int *renderIndex;
    int renderSize;
} Registry;

// typedef struct {
//     int x;
//     int y;
// } Position;

Registry* ecsInitWorld(void);
void ecsFreeWorld(Registry* registry);
int ecsInitEntity(Registry* registry);
void ecsAddPosition(Registry* registry, int entityID, int x, int y);
void ecsAddRenderable(Registry* registry, int entityID, char ch, int fg, int bg);
// void ecsRenderSystem(Registry registry);

/* Input */
void handleInput(int input, Tile** map);

/* Externs */
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern int playerID;
extern Registry* world;

#endif