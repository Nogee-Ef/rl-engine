#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#define TRUE true
#define FALSE false

#define SQUARE(a) ((a) * (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* OS */
void displaySetup(void);
void onExit(void);
void moveCursor(int x, int y);
int getInput(void);

/* Tiles */
typedef struct {
    int x;
    int y;
    char ch;
    int fg;
    int bg;
    bool walkable;
    int visible;
} Tile;

typedef struct {
    Tile** tiles;
    const int WIDTH;
    const int HEIGHT;
    int visibility;
} Map;

Tile** createMapTiles(int width, int height);
void freeMapTiles(Map* map);
void generateFloor(Map* map, int max_rooms);

/* Display */
#define CLEAR "\x1b[2J\x1b[3J" // Clears the terminal AND the scroll back.
#define HIDE "\x1b[?25l" // Hides the cursor.
#define SHOW "\x1b[?25h" // Shows the cursor.

#define RESET "\x1b[0m" // Resets color to its default value.

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#define BRIGHT(a) (a+60)

void initDisplayBuffer(void);
void freeDisplayBuffer(void);
void printDisplayBuffer(void);
void renderAt(int x, int y, int fg, int bg, char to_print[4]);
void renderFrame(int origin_x, int origin_y, int width, int height);
void renderTileMap(Map* map);
void drawAt(int x, int y, int fg, int bg, char to_print[4]);
void drawString(int x, int y, int fg, int bg, char string[100]);
void pushMessage(char message[100], int fg);
void displayMessageLog(void);

/* ECS */
#define MAX_ENTITIES 100

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
    int entity_count;
    PositionComponent *pos_components;
    int *pos_index;
    int pos_size;
    RenderableComponent *render_components;
    int *render_index;
    int render_size;
} Registry;

Registry* ecsInitWorld(void);
void ecsFreeWorld(Registry* registry);
int ecsInitEntity(Registry* registry);
void ecsAddPosition(Registry* registry, int entity_id, int x, int y);
void ecsAddRenderable(Registry* registry, int entity_id, char ch, int fg, int bg);
void ecsRenderSystem(Registry* registry, Map* map);
void ecsTurnSystem(Registry* registry, Map* map);

/* Input */
int handleInput(int input, Map* map);
int moveEntity(Map* map, int dx, int dy, int entity_id);

/* A* */
typedef struct {
    int path[100][2]; // Max path length is 100
    int path_length;
} Path;

Path getPathTo(Map* map, int start_x, int start_y, int goal_x, int goal_y);

/* FOV */
int computeFov(Map* map, int pov_x, int pov_y, int max_radius);

/* Externs */
extern bool running;
extern int player_id;
extern Registry* world;

#endif