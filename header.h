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
    int x;
    int y;
} Position;

typedef struct {
    char ch;
    int fg;
    int bg;
} Renderable;

typedef struct {
    Position position;
    Renderable renderable;
} Entity;

typedef struct {
    int walkable;
} Movement;

// entity.c commands
Entity* createEntity(int x, int y, char ch, int fg, int bg);

/* Input Defines */
// input.c commands
void handleInput(int input, Tile** map);

/* Hash Table Defines*/
typedef struct Entry { /* table entry: */
    char *key;
    char *value;
    struct Entry *next; /* next entry in chain */
} Entry;

typedef struct {
    Entry **entries;
    unsigned tableSize;
} HashTable;

// hashtable.c commands
HashTable *createHashtable(unsigned tableSize);
Entry *lookup(char *key, HashTable hashTable);
Entry *install(char *key, char *value, HashTable hashTable);

/* Externs */
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;

#endif