#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <malloc.h>

typedef struct {
    int *items;
    size_t len;
    size_t front;
    size_t capacity;
} Deque;


static inline Deque deque_init() {
    return (Deque){0};
}

static inline void deque_del(Deque *d) {
    free(d->items);
    d->len = 0;
    d->front = 0;
    d->capacity = 0;
}

void deque_push_back(Deque *deque, int item);
void deque_push_front(Deque *deque, int item);
bool deque_pop_front(Deque *deque, int *item);
bool deque_pop_back(Deque *deque, int *item);
bool deque_peek_front(Deque *deque, int *item);
bool deque_peek_back(Deque *deque, int *item);
bool deque_iter(Deque *deque);

#endif // DEQUE_H
