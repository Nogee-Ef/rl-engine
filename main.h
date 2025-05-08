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
#define CLEAR "\x1B[2J\x1b[3J" // Clears the terminal AND the scroll back.
#define HIDE "\x1B[?25l" // Hides the cursor.

// Colors
#define RESET "\x1B[0m" // Resets color to its default value.

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define WHITE 37

void drawAt(int x, int y, int fg, int bg, char toPrint);
void drawTileMap(Tile** map);

/* Entity */
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
    PositionComponent position;
    RenderableComponent renderable;
} Entity;

typedef struct {
    int walkable;
} Movement;

Entity* createEntity(int x, int y, char ch, int fg, int bg);

/* Input */
void handleInput(int input, Tile** map);

/* Externs */
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;

#endif