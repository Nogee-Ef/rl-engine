#include "main.h"
#include <string.h>

#define BUFFER_HEIGHT 32 // Map height + frame height + message log height
#define BUFFER_WIDTH 102 // Map width + frame width

typedef struct {
    char ch[4];
    int fg;
    int bg;
} Glyph;

static Glyph** display_buffer;
void initDisplayBuffer(void) {
    display_buffer = calloc(BUFFER_HEIGHT, sizeof(Glyph*));
    for (int y = 0; y < BUFFER_HEIGHT; y ++) {
        display_buffer[y] = calloc(BUFFER_WIDTH, sizeof(Glyph));
        for (int x = 0; x < BUFFER_WIDTH; x++) {
                strcpy(display_buffer[y][x].ch, " ");
                display_buffer[y][x].fg = WHITE;
                display_buffer[y][x].bg = BLACK;
        }
    }
}

void freeDisplayBuffer(void) {
    for (int y = 0; y < BUFFER_HEIGHT; y++) {
        free(display_buffer[y]);
    }
    free(display_buffer);
}

void printDisplayBuffer(void) {
    moveCursor(0,0);
    for (int y = 0; y < BUFFER_HEIGHT; y++) {
        for (int x = 0; x < BUFFER_WIDTH; x++) {
            printf("\x1b[%dm\x1b[%dm%s",display_buffer[y][x].fg, display_buffer[y][x].bg + 10, display_buffer[y][x].ch);
        }
        printf("\n");
    }
}

void renderAt(int x, int y, int fg, int bg, char to_print[4]) {
    if (y > -1 && y < BUFFER_HEIGHT && x > -1 && x < BUFFER_WIDTH) {
                strcpy(display_buffer[y][x].ch, to_print);
                display_buffer[y][x].fg = fg;
                display_buffer[y][x].bg = bg;
    }
}

void renderFrame(int origin_x, int origin_y, int width, int height) {
    renderAt(origin_x, origin_y, WHITE, BLACK, "┌");
    renderAt(origin_x + width, origin_y, WHITE, BLACK, "┐");
    renderAt(origin_x, origin_y + height, WHITE, BLACK, "└");
    renderAt(origin_x + width, origin_y + height, WHITE, BLACK, "┘");
    for (int i = 1; i < width; i++) {
        renderAt(origin_x + i, origin_y, WHITE, BLACK, "─");
        renderAt(origin_x + i, origin_y + height, WHITE, BLACK, "─");
    }
    for (int n = 1; n < height; n++) {
        renderAt(origin_x, origin_y + n, WHITE, BLACK, "│");
        renderAt(origin_x + width, origin_y + n, WHITE, BLACK, "│");
    }
}

void renderTileMap(Map* map) {
    map->visibility++;
    computeFov(map, world->pos_components[world->pos_index[player_id]].x, world->pos_components[world->pos_index[player_id]].y, 12);
    for (int y = 0; y < map->HEIGHT; y ++) {
        for (int x = 0; x < map->WIDTH; x++) {
            if (map->tiles[y][x].visible == 0) {
                continue;
            } else if (map->tiles[y][x].visible == map->visibility) {
                renderAt(x + 1, y + 1, map->tiles[y][x].fg, map->tiles[y][x].bg, &map->tiles[y][x].ch);
            } else {
                renderAt(x + 1, y + 1, BRIGHT(BLACK), map->tiles[y][x].bg, &map->tiles[y][x].ch);
            }
        }
    }
}

void drawAt(int x, int y, int fg, int bg, char to_print[4]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, to_print, RESET);
}

void drawString(int x, int y, int fg, int bg, char string[100]) {
    moveCursor(x, y);
    printf("\x1b[%dm\x1b[%dm%s%s", fg, bg + 10, string, RESET);
}

typedef struct {
    char text[100];
    int fg;
} Message;

static Message message_log[80];
static int num_messages = 0;

void pushMessage(char message[100], int fg) {
    if (num_messages < 80) {
        num_messages++;
        strcpy(message_log[num_messages].text, message);
        message_log[num_messages].fg = fg;
    }
}

void displayMessageLog(void) {
    for (int i = num_messages; i > num_messages - 3; i--) {
        if (i > 0) {
            const int length = (int)strlen(message_log[i].text);
            for (int l = 0; l < 80; l++) {
                if (l < length) {
                    const char TO_PRINT[4] = {message_log[i].text[l]};
                    strcpy(display_buffer[30 + i - num_messages][l + 1].ch, TO_PRINT);
                    display_buffer[30 + i - num_messages][l + 1].fg = message_log[i].fg;
                } else {
                    // Clear the rest of the buffer.
                    strcpy(display_buffer[30 + i - num_messages][l + 1].ch, " ");
                }                
            }
        }
    }
}