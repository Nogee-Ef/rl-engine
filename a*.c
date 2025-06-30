#include "main.h"

#define MAX_NODES 2500

typedef struct {
    int parentX;
    int parentY;
    int x;
    int y;
    float costInSteps;
    float sumCost;
} Node;

typedef struct {
    Node nodes[MAX_NODES];
    int queueSize;
} PriorityQueue;

void swapNode(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* queue, int index) {
    if (index && queue->nodes[(index - 1) / 2].sumCost > queue->nodes[index].sumCost) {
        swapNode(&queue->nodes[(index - 1) / 2], &queue->nodes[index]);
        heapifyUp(queue, (index - 1) / 2);
    }
}

void enqueue(PriorityQueue* queue, Node newNode) {
    if (queue->queueSize == MAX_NODES) {
        return;
    }

    queue->nodes[queue->queueSize++] = newNode;
    heapifyUp(queue, queue->queueSize - 1);
}

void heapifyDown(PriorityQueue* queue, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->queueSize
        && queue->nodes[left].sumCost < queue->nodes[smallest].sumCost)
        smallest = left;

    if (right < queue->queueSize
        && queue->nodes[right].sumCost < queue->nodes[smallest].sumCost)
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

    Node topNode = queue->nodes[0];
    queue->nodes[0] = queue->nodes[--queue->queueSize];
    heapifyDown(queue, 0);
    return topNode;
}

Node* peek(PriorityQueue* queue) {
    if (!queue->queueSize) {
        return NULL;
    }
    return &queue->nodes[0];
}

Path getPathTo(Map* map, int startX, int startY, int goalX, int goalY) {
    PriorityQueue pq;
    pq.queueSize = 0;

    Node** openList = calloc(MAP_HEIGHT, sizeof(Node*));
    for (int y = 0; y < MAP_HEIGHT; y ++) {
        openList[y] = calloc(MAP_WIDTH, sizeof(Node));
        for (int x = 0; x < MAP_WIDTH; x++) {
                openList[y][x].x = x;
                openList[y][x].y = y;
                openList[y][x].sumCost = FLT_MAX;
        }
    }

    openList[startY][startX].costInSteps = 0;
    openList[startY][startX].sumCost = (float)(0);
    enqueue(&pq, (Node){ .x = startX, .y = startY, .costInSteps = 0, .sumCost = 0});

    Node goalNode;
    while (pq.queueSize > 0) {
        Node currentNode = dequeue(&pq);
        if (currentNode.x == goalX && currentNode.y == goalY) {
            goalNode = currentNode;
            break;
        }
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (currentNode.x + i > MAP_WIDTH || currentNode.x + i < 0 || currentNode.y + j > MAP_HEIGHT || currentNode.y + j < 0) {
                    continue;
                }    
                if (!map->tiles[currentNode.y + j][currentNode.x + i].walkable) {
                    continue;
                }

                float stepCost = currentNode.costInSteps + 1; // You could weight the step cost for obstructed tiles.
                if (i != 0 && j != 0) {
                    stepCost += 0.4f; //Approximating the root-2 cost of moving diagonally.
                }
                float heuristicCost = sqrtf((float)(SQUARE((currentNode.x + i) - goalX)) + (float)(SQUARE((currentNode.y + j) - goalY)));
                float totalCost = stepCost + heuristicCost;

                if (totalCost < openList[currentNode.y + j][currentNode.x + i].sumCost) {
                    Node successorNode = { 
                        .parentX = currentNode.x, .parentY = currentNode.y, .x = currentNode.x + i,
                        .y = currentNode.y + j, .costInSteps = stepCost, .sumCost = totalCost
                    };
                    openList[currentNode.y + j][currentNode.x + i] = successorNode;
                    enqueue(&pq, successorNode);
                }
            }
        }
    }

    Path newPath;
    newPath.pathLength = 0;
    Node* targetNode = &goalNode;
    while(TRUE) {
        if (targetNode->x == startX && targetNode->y == startY) {
            break;
        }
        newPath.path[newPath.pathLength][0] = targetNode->x;
        newPath.path[newPath.pathLength][1] = targetNode->y;
        targetNode = &openList[targetNode->parentY][targetNode->parentX];
        newPath.pathLength++;
    }
    return newPath;
}