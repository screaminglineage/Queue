#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t capacity;
    size_t front;
    size_t rear;
} Queue;

void queue_push(Queue *queue, int item);
bool queue_pop(Queue *queue, int *item);
void queue_del(Queue *queue);

#endif  // QUEUE_H
