#include "main.h"

Registry* ecsInitWorld(void) {
    Registry *new_world = (Registry *)malloc(sizeof(Registry));
    *new_world = (Registry){
        .entity_count = 0, 
        .pos_components = calloc(MAX_ENTITIES, sizeof(PositionComponent)), 
        .pos_index = calloc(MAX_ENTITIES, sizeof(int)), 
        .pos_size = 0,
        .render_components = calloc(MAX_ENTITIES, sizeof(RenderableComponent)), 
        .render_index = calloc(MAX_ENTITIES, sizeof(int)), 
        .render_size = 0,
    };

    return new_world;
}

void ecsFreeWorld(Registry* registry) {
    free(registry->pos_components);
    free(registry->pos_index);
    free(registry->render_components);
    free(registry->render_index);
    free(registry);
}

// Returns the entity ID of the newly initialized entity
int ecsInitEntity(Registry* registry) {
    if (registry->entity_count < MAX_ENTITIES) {
        return ++registry->entity_count;
    }
    else {
        // Error: maximum entity count exceeded.
        return 0;
    }
}

void ecsAddPosition(Registry* registry, int entity_id, int x, int y) {
    registry->pos_components[registry->pos_size] = (PositionComponent){ .id = entity_id, .x = x, .y = y };
    registry->pos_index[entity_id] = registry->pos_size;
    registry->pos_size++;
}

void ecsAddRenderable(Registry* registry, int entity_id, char ch, int fg, int bg) {
    registry->render_components[registry->render_size] = (RenderableComponent){ .id = entity_id, .ch = ch, .fg = fg, .bg = bg };
    registry->render_index[entity_id] = registry->render_size;
    registry->render_size++;
}

void ecsRenderSystem(Registry* registry, Map* map) {
    /* 
    At some point it may be advantageous to check which set has fewer entries and iterate through that?
    For now it can be assumed that the Position and Renderable lists are the same size.
    */
    for (int i = 0; i < registry->pos_size; i++) {
        if (map->tiles[registry->pos_components[i].y][registry->pos_components[i].x].visible != map->visibility) {
            continue;
        }
        renderAt(
            registry->pos_components[i].x + 1, registry->pos_components[i].y + 1, 
            registry->render_components[registry->render_index[registry->pos_components[i].id]].fg, 
            registry->render_components[registry->render_index[registry->pos_components[i].id]].bg, 
            &registry->render_components[registry->render_index[registry->pos_components[i].id]].ch
        );
    }
}

void ecsTurnSystem(Registry* registry, Map* map) {
    if (!handleInput(getInput(), map)) {
        return;
    }
    for (int i = 0; i < registry->pos_size; i++) {
        if (registry->pos_components[i].id != player_id) {
            Path ai_path = getPathTo(
                map, 
                registry->pos_components[i].x, 
                registry->pos_components[i].y, 
                registry->pos_components[registry->pos_index[player_id]].x, 
                registry->pos_components[registry->pos_index[player_id]].y
            );
            moveEntity(
                map,
                ai_path.path[ai_path.path_length - 1][0] - registry->pos_components[i].x, 
                ai_path.path[ai_path.path_length - 1][1] - registry->pos_components[i].y, 
                registry->pos_components[i].id
            );
        }
    }
}