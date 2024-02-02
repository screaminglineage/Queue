#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "Deque.h"


Deque deque_init() {
    return (Deque){0};
}

void deque_del(Deque *d) {
    free(d->items);
    d->len = 0;
    d->front = 0;
    d->rear = 0;
    d->capacity = 0;
}

static inline void deque_resize(Deque *deque) {
    size_t new_capacity = (deque->capacity == 0)? 1: deque->capacity * 2;
    size_t size = sizeof(deque->items[0]);
    int *temp = malloc(size * new_capacity);
    assert(temp && "Critical Failure: Please refer to https://downloadmoreram.com/");

    if (deque->len > 0) {
        if (deque->front < deque->rear) {
            memcpy(temp, &deque->items[deque->front], size * deque->len);

        } else if (deque->front >= deque->rear) {
            size_t elems_at_end = deque->capacity - deque->front;
            memcpy(temp, &deque->items[deque->front], size * elems_at_end);
            memcpy(&temp[elems_at_end], &deque->items[0], size * deque->rear);
        }
    }
    free(deque->items);
    deque->items = temp;
    deque->front = 0;
    deque->rear = deque->len;
    deque->capacity = new_capacity;
}

void deque_push_back(Deque *deque, int item) {
    if (deque->len == deque->capacity) {
        deque_resize(deque);
    }

    deque->items[deque->rear] = item;
    deque->len++;
    if (deque->len == deque->capacity) {
        // set rear to 1 after last element if queue is full
        // and it is incremented beyond the length
        deque->rear = (deque->rear + 1) % (deque->capacity + 1);
    } else {
        deque->rear = (deque->rear + 1) % deque->capacity;
    }
}

void deque_push_front(Deque *deque, int item) {
    if (deque->len == deque->capacity) {
        deque_resize(deque);
    }

    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->items[deque->front] = item;
    deque->len++;
}

bool deque_pop_front(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }

    *item = deque->items[deque->front];
    deque->front = (deque->front + 1) % deque->capacity;
    deque->len--;
    return true;
}

bool deque_pop_back(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }

    // ensures that -1 wraps around to (deque->capacity - 1)
    deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;

    *item = deque->items[deque->rear];
    deque->len--;
    return true;
}

bool deque_peek_front(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }
    *item = deque->items[deque->front];
    return true;
}

bool deque_peek_back(Deque *deque, int *item) {
    if (deque->len == 0) {
        return false;
    }
    // ensures that -1 wraps around to (deque->capacity - 1)
    *item = deque->items[(deque->rear - 1 + deque->capacity) % deque->capacity];
    return true;
}

bool deque_iter(Deque *deque) {
    if (deque->len == 0) {
        return false;
    }

    for (size_t i = 0; i < deque->len; i++) {
        size_t index = (deque->front + i) % deque->capacity;
        printf("%d ", deque->items[index]);
    }
    putchar('\n');
    return true;
}

