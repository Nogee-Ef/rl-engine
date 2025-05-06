#include "header.h"
#include <stdlib.h>

// typedef struct {
//     int x;
//     int y;
// } PositionComponent;

// typedef struct {
//     char ch;
//     int fg;
//     int bg;
// } RenderableComponent;

typedef struct {
    int x;
    int y;
} Position;

// typedef struct {
//     int id;
//     Position facing;
//     Position netMomentum;
//     int gear;
//     int maxGear;
// } MomentumComponent;

#define MAXENTITIES 100

typedef struct {
    int entityCount;
    PositionComponent *posComponents;
    int *posIndex;
    int posSize;
    RenderableComponent *renderComponents;
    int *renderIndex;
    int renderSize;
} Registry;

Registry ecsInitWorld(void) {
    PositionComponent positionList[MAXENTITIES];
    int positionIndex[MAXENTITIES];
    RenderableComponent renderList[MAXENTITIES];
    int renderableIndex[MAXENTITIES];

    Registry world = { .entityCount = 0, 
        .posComponents = positionList, .posIndex = positionIndex, .posSize = 0,
        .renderComponents = renderList, .renderIndex = renderableIndex, .renderSize = 0,
    };

    return world;
}

// Returns the entity ID of the newly initialized entity
int ecsInitEntity(Registry registry) {
    if (registry.entityCount < MAXENTITIES) {
        return registry.entityCount++;
    }
    else return 0; // Error: maximum entity count exceeded.
}

void ecsAddPosition(Registry registry, int entityID, int x, int y) {
    PositionComponent newPosition = { .id = entityID, .x = x, .y = y };
    registry.posComponents[registry.posSize] = newPosition; // Add the new component to the end of the dense array.
    registry.posIndex[entityID] = registry.posSize; // Add the new component's position in the dense array to the index array.
    registry.posSize++; // Increase the recorded size of the dense array.
}

void ecsAddRenderable(Registry registry, int entityID, char ch, int fg, int bg) {
    RenderableComponent newRenderable = { .id = entityID, .ch = ch, .fg = fg, .bg = bg };
    registry.renderComponents[registry.renderSize] = newRenderable;
    registry.renderIndex[entityID] = registry.renderSize;
    registry.renderSize++;
}

void ecsRenderSystem(Registry registry) {
    for (int i = 0; i < registry.renderSize; i++) { // At some point it may be advantageous to check which set has fewer entries and iterate through that.
        drawAt(
            registry.posComponents[i].x, registry.posComponents[i].y, 
            registry.renderComponents[registry.renderIndex[registry.posComponents[i].id]].fg, 
            registry.renderComponents[registry.renderIndex[registry.posComponents[i].id]].bg, 
            registry.renderComponents[registry.renderIndex[registry.posComponents[i].id]].ch
        );
    }
}

// void momentumSystem(Registry registry) {
//     for (int i = 0; i < registry.momentumSize; i++) {
//         // Increase net momentum in the direction the entity is facing.
//         if (abs(registry.momentumComponents[i].netMomentum[0]) < registry.momentumComponents[i].gear){
//             registry.momentumComponents[i].netMomentum[0] += registry.momentumComponents[i].facing[0];
//         }
//         if (abs(registry.momentumComponents[i].netMomentum[1]) < registry.momentumComponents[i].gear) {
//             registry.momentumComponents[i].netMomentum[1] += registry.momentumComponents[i].facing[1];
//         }
//     }
// }