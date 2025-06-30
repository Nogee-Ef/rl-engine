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

void ecsFreeWorld(Registry* registry) {
    free(registry->posComponents);
    free(registry->posIndex);
    free(registry->renderComponents);
    free(registry->renderIndex);
    free(registry);
}

// Returns the entity ID of the newly initialized entity
int ecsInitEntity(Registry* registry) {
    if (registry->entityCount < MAXENTITIES) {
        return ++registry->entityCount;
    }
    else {
        // Error: maximum entity count exceeded.
        return 0;
    }
}

void ecsAddPosition(Registry* registry, int entityID, int x, int y) {
    registry->posComponents[registry->posSize] = (PositionComponent){ .id = entityID, .x = x, .y = y };
    registry->posIndex[entityID] = registry->posSize;
    registry->posSize++;
}

void ecsAddRenderable(Registry* registry, int entityID, char ch, int fg, int bg) {
    registry->renderComponents[registry->renderSize] = (RenderableComponent){ .id = entityID, .ch = ch, .fg = fg, .bg = bg };
    registry->renderIndex[entityID] = registry->renderSize;
    registry->renderSize++;
}

void ecsRenderSystem(Registry* registry, Map* map) {
    /* 
    At some point it may be advantageous to check which set has fewer entries and iterate through that?
    For now it can be assumed that the Position and Renderable lists are the same size.
    */
    for (int i = 0; i < registry->posSize; i++) {
        if (map->tiles[registry->posComponents[i].y][registry->posComponents[i].x].visible != map->visibility) {
            continue;
        }
        renderAt(
            registry->posComponents[i].x, registry->posComponents[i].y, 
            registry->renderComponents[registry->renderIndex[registry->posComponents[i].id]].fg, 
            registry->renderComponents[registry->renderIndex[registry->posComponents[i].id]].bg, 
            &registry->renderComponents[registry->renderIndex[registry->posComponents[i].id]].ch
        );
    }
}

void ecsTurnSystem(Registry* registry, Map* map) {
    if (!handleInput(getInput(), map)) {
        return;
    }
    for (int i = 0; i < registry->posSize; i++) {
        if (registry->posComponents[i].id != playerID) {
            Path aiPath = getPathTo(
                map, 
                registry->posComponents[i].x, 
                registry->posComponents[i].y, 
                registry->posComponents[registry->posIndex[playerID]].x, 
                registry->posComponents[registry->posIndex[playerID]].y
            );
            moveEntity(
                map,
                aiPath.path[aiPath.pathLength - 1][0] - registry->posComponents[i].x, 
                aiPath.path[aiPath.pathLength - 1][1] - registry->posComponents[i].y, 
                registry->posComponents[i].id
            );
        }
    }
}