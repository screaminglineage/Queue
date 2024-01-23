#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stddef.h>

#define MAX 512

typedef struct {
    int items[MAX];
    size_t len;
    size_t front;
    size_t rear;    
} Deque;

Deque deque_init();
void deque_del(Deque *d);
bool deque_push_back(Deque *deque, int item);
bool deque_push_front(Deque *deque, int item);
bool deque_pop_front(Deque *deque, int *item);
bool deque_pop_back(Deque *deque, int *item);

void deque_iter(Deque *deque);

#endif // DEQUE_H
