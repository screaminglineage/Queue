#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Deque.h"


Deque deque_init() {
    return (Deque){0};
}

void deque_del(Deque *d) {
    d->len = 0;
    d->front = 0;
    d->rear = 0;
}

void deque_iter(Deque *deque) {
    for (size_t i = 0; i < deque->len; i++) {
        size_t index = (deque->front + i) % MAX;
        printf("%d ", deque->items[index]);
    }
    putchar('\n');
}


bool deque_push_back(Deque *deque, int item) {
    if (deque->len == MAX) {
        return false;
    }

    deque->items[deque->rear] = item;
    deque->rear = (deque->rear + 1) % MAX;
    deque->len++;
    return true;
}

bool deque_push_front(Deque *deque, int item) {
    if (deque->len == MAX) {
        return false;
    }

    if (deque->front == 0) {
        deque->front = MAX - 1;
    } else {
        deque->front = deque->front - 1;
    }
    deque->items[deque->front] = item;
    deque->len++;
    return true;
}


bool deque_pop_front(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }

    *item = deque->items[deque->front];
    deque->front = (deque->front + 1) % MAX;
    deque->len--;
    return true;
}

bool deque_pop_back(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }
    if (deque->rear == 0) {
        deque->rear = MAX - 1;
    } else {
        deque->rear = deque->rear - 1;
    }

    *item = deque->items[deque->rear];
    deque->len--;
    return true;
}






