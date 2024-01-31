#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t len;
    size_t front;
    size_t rear;    
    size_t capacity;
} Deque;

Deque deque_init();
void deque_del(Deque *d);
bool deque_push_back(Deque *deque, int item);
bool deque_push_front(Deque *deque, int item);
bool deque_pop_front(Deque *deque, int *item);
bool deque_pop_back(Deque *deque, int *item);

void deque_iter(Deque *deque);

#endif // DEQUE_H
