#include "main.h"

#define MAX_NODES 2500

typedef struct {
    int parent_x;
    int parent_y;
    int x;
    int y;
    float cost_in_steps;
    float sum_cost;
} Node;

typedef struct {
    Node nodes[MAX_NODES];
    int queue_size;
} PriorityQueue;

void swapNode(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* queue, int index) {
    if (index && queue->nodes[(index - 1) / 2].sum_cost > queue->nodes[index].sum_cost) {
        swapNode(&queue->nodes[(index - 1) / 2], &queue->nodes[index]);
        heapifyUp(queue, (index - 1) / 2);
    }
}

void enqueue(PriorityQueue* queue, Node new_node) {
    if (queue->queue_size == MAX_NODES) {
        return;
    }

    queue->nodes[queue->queue_size++] = new_node;
    heapifyUp(queue, queue->queue_size - 1);
}

void heapifyDown(PriorityQueue* queue, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->queue_size
        && queue->nodes[left].sum_cost < queue->nodes[smallest].sum_cost)
        smallest = left;

    if (right < queue->queue_size
        && queue->nodes[right].sum_cost < queue->nodes[smallest].sum_cost)
        smallest = right;

    if (smallest != index) {
        swapNode(&queue->nodes[index], &queue->nodes[smallest]);
        heapifyDown(queue, smallest);
    }
}

Node dequeue(PriorityQueue* queue) {
    // if (!queue->queueSize) {
    //     return;
    // }

    Node top_node = queue->nodes[0];
    queue->nodes[0] = queue->nodes[--queue->queue_size];
    heapifyDown(queue, 0);
    return top_node;
}

Node* peek(PriorityQueue* queue) {
    if (!queue->queue_size) {
        return NULL;
    }
    return &queue->nodes[0];
}

Path getPathTo(Map* map, int start_x, int start_y, int goal_x, int goal_y) {
    PriorityQueue priority_queue;
    priority_queue.queue_size = 0;

    Node** open_list = calloc(map->HEIGHT, sizeof(Node*));
    for (int y = 0; y < map->HEIGHT; y ++) {
        open_list[y] = calloc(map->WIDTH, sizeof(Node));
        for (int x = 0; x < map->WIDTH; x++) {
                open_list[y][x].x = x;
                open_list[y][x].y = y;
                open_list[y][x].sum_cost = FLT_MAX;
        }
    }

    open_list[start_y][start_x].cost_in_steps = 0;
    open_list[start_y][start_x].sum_cost = (float)(0);
    enqueue(&priority_queue, (Node){ .x = start_x, .y = start_y, .cost_in_steps = 0, .sum_cost = 0});

    Node goal_node;
    while (priority_queue.queue_size > 0) {
        Node current_node = dequeue(&priority_queue);
        if (current_node.x == goal_x && current_node.y == goal_y) {
            goal_node = current_node;
            break;
        }
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (current_node.x + i > map->WIDTH || current_node.x + i < 0 || current_node.y + j > map->HEIGHT || current_node.y + j < 0) {
                    continue;
                }    
                if (!map->tiles[current_node.y + j][current_node.x + i].walkable) {
                    continue;
                }

                float step_cost = current_node.cost_in_steps + 1; // You could weight the step cost for obstructed tiles.
                if (i != 0 && j != 0) {
                    step_cost += 0.4f; //Approximating the root-2 cost of moving diagonally.
                }
                float heuristic_cost = sqrtf((float)(SQUARE((current_node.x + i) - goal_x)) + (float)(SQUARE((current_node.y + j) - goal_y)));
                float total_cost = step_cost + heuristic_cost;

                if (total_cost < open_list[current_node.y + j][current_node.x + i].sum_cost) {
                    Node successor_node = { 
                        .parent_x = current_node.x, .parent_y = current_node.y, .x = current_node.x + i,
                        .y = current_node.y + j, .cost_in_steps = step_cost, .sum_cost = total_cost
                    };
                    open_list[current_node.y + j][current_node.x + i] = successor_node;
                    enqueue(&priority_queue, successor_node);
                }
            }
        }
    }

    Path new_path;
    new_path.path_length = 0;
    Node* target_node = &goal_node;
    while(TRUE) {
        if (target_node->x == start_x && target_node->y == start_y) {
            break;
        }
        new_path.path[new_path.path_length][0] = target_node->x;
        new_path.path[new_path.path_length][1] = target_node->y;
        target_node = &open_list[target_node->parent_y][target_node->parent_x];
        new_path.path_length++;
    }
    return new_path;
}