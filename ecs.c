#include "main.h"

Registry* ecsInitWorld(void) {
    Registry *newWorld = (Registry *)malloc(sizeof(Registry));
    *newWorld = (Registry){
        .entityCount = 0, 
        .posComponents = calloc(MAXENTITIES, sizeof(PositionComponent)), 
        .posIndex = calloc(MAXENTITIES, sizeof(int)), 
        .posSize = 0,
        .renderComponents = calloc(MAXENTITIES, sizeof(RenderableComponent)), 
        .renderIndex = calloc(MAXENTITIES, sizeof(int)), 
        .renderSize = 0,
    };

    return newWorld;
}

// Returns the entity ID of the newly initialized entity
int ecsInitEntity(Registry* registry) {
    if (registry->entityCount < MAXENTITIES) {
        return ++registry->entityCount;
    }
    else {
        return 0;
    }  // Error: maximum entity count exceeded.
}

void ecsAddPosition(Registry* registry, int entityID, int x, int y) {
    registry->posComponents[registry->posSize] = (PositionComponent){ .id = entityID, .x = x, .y = y }; // Add the new component to the end of the dense array.
    registry->posIndex[entityID] = registry->posSize; // Add the new component's position in the dense array to the index array.
    registry->posSize++; // Increase the recorded size of the dense array.
}

void ecsAddRenderable(Registry* registry, int entityID, char ch, int fg, int bg) {
    registry->renderComponents[registry->renderSize] = (RenderableComponent){ .id = entityID, .ch = ch, .fg = fg, .bg = bg };
    registry->renderIndex[entityID] = registry->renderSize;
    registry->renderSize++;
}