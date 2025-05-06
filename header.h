#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0

/* Tiles Defines */
typedef struct {
    int x;
    int y;
    char ch;
    int fg;
    int bg;
    int walkable;
} Tile;

// tiles.c commands
Tile** createTilesMap();
void freeMap(Tile** map);
void generateFloor(Tile** map, int maxRooms);

/* Display Defines */
#define CLEAR "\x1B[2J\x1b[3J" // Clears the terminal AND the scroll back.
#define HIDE "\x1B[?25l" // Hides the cursor.

// Colors
#define RESET "\x1B[0m" // Resets color to its default value.

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define WHITE 37

// display.c commands
void displaySetup(void);
void drawAt(int x, int y, int fg, int bg, char toPrint);
void drawTileMap(Tile** map);

/* Entity Defines */
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

// entity.c commands
Entity* createEntity(int x, int y, char ch, int fg, int bg);

/* Input Defines */
// input.c commands
void handleInput(int input, Tile** map);

/* Externs */
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;

#endif