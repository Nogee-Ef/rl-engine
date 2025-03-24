#include "header.h"

Entity* createEntity(int x, int y, char ch, int fg, int bg) {
    Entity* newEntity = calloc(1, sizeof(Entity));
    Position pos;
    Renderable render;
    
    pos.x = x;
    pos.y = y;
    newEntity->position = pos;

    render.ch = ch;
    render.fg = fg;
    render.bg = bg;
    newEntity->renderable = render;

    return newEntity;
}