#include "main.h"

static const int OCTANT_TRANSFORM[8][4] = {
    {1, 0, 0, 1},
    {0, 1, 1, 0},
    {0, -1, 1, 0},
    {-1, 0, 0, 1},
    {-1, 0, 0, -1},
    {0, -1, -1, 0},
    {0, 1, -1, 0},
    {1, 0, 0, -1},
};

static void scan(Map* map, int pov_x, int pov_y, int distance, float view_slope_high, float view_slope_low, int max_radius, int octant) {
    const int XX = OCTANT_TRANSFORM[octant][0];
    const int XY = OCTANT_TRANSFORM[octant][1];
    const int YX = OCTANT_TRANSFORM[octant][2];
    const int YY = OCTANT_TRANSFORM[octant][3];
    if (view_slope_high < view_slope_low) {
        return;
    }
    if (distance > max_radius) {
        return;
    }
    if (pov_x + distance * XY < 0 || pov_x + distance * XY > map->WIDTH || pov_y + distance * YY < 0 || pov_y + distance * YY > map->HEIGHT){
        return;
    }
    bool prev_tile_blocked = FALSE;
    for (int angle = distance; angle >= 0; angle--) {
        const float TILE_SLOPE_HIGH = (angle + 0.5f) / (float)distance;
        const float TILE_SLOPE_LOW = (angle - 0.5f) / (float)distance;
        const float TILE_SLOPE_CENTER = angle / (float)distance;
        const float PREV_TILE_SLOPE_LOW = (angle + 0.5f) / (float)distance;
        if (TILE_SLOPE_LOW > view_slope_high) {
            continue;
        } else if (TILE_SLOPE_HIGH < view_slope_low) {
            break;
        }
        const int MAP_X = pov_x + angle * XX + distance * XY;
        const int MAP_Y = pov_y + angle * YX + distance * YY;
        if (MAP_X < 0 || MAP_X > map->WIDTH || MAP_Y < 0 || MAP_Y > map->HEIGHT) {
            continue;
        }
        if (SQUARE(angle) + SQUARE(distance) <= SQUARE(max_radius) && (TILE_SLOPE_CENTER <= view_slope_high || !map->tiles[MAP_Y][MAP_X].walkable)) {
            map->tiles[MAP_Y][MAP_X].visible = map->visibility;
        }
        if (prev_tile_blocked && map->tiles[MAP_Y][MAP_X].walkable) {  // Wall -> floor.
            view_slope_high = PREV_TILE_SLOPE_LOW;  // Reduce the view size.
        }
        if (!prev_tile_blocked && !map->tiles[MAP_Y][MAP_X].walkable) {  // Floor -> wall.
            // Get the last sequence of floors as a view and recurse into them.
            scan(map, pov_x, pov_y, distance + 1, view_slope_high, TILE_SLOPE_HIGH, max_radius, octant);
        }
        prev_tile_blocked = !map->tiles[MAP_Y][MAP_X].walkable;
    }
    if (!prev_tile_blocked) {
        // Tail-recurse into the current view.
        scan(map, pov_x, pov_y, distance + 1, view_slope_high, view_slope_low, max_radius, octant);
    }
}

int computeFov(Map* map, int pov_x, int pov_y, int max_radius) {
    if (pov_x < 0 || pov_x > map->WIDTH || pov_y < 0 || pov_y > map->HEIGHT) {
        return 0;
    }
    if (max_radius <= 0) {
        int max_radius_x = MAX(map->WIDTH - pov_x, pov_x);
        int max_radius_y = MAX(map->HEIGHT - pov_y, pov_y);
        max_radius = (int)(sqrtf(max_radius_x * max_radius_x + max_radius_y * max_radius_y)) + 1;
    }
    for (int octant = 0; octant < 8; octant++) {
        scan(map, pov_x, pov_y, 1, 1.0, 0.0, max_radius, octant);
    }
    map->tiles[pov_y][pov_x].visible = map->visibility;

    return 1;
}