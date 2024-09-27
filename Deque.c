#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Deque.h"

// returns the back of the deque
// make sure that capacity isnt 0 when called
static inline size_t deque_get_back(Deque *deque) {
    return (deque->front + deque->len) % deque->capacity;
}

static inline void deque_resize(Deque *deque) {
    size_t new_capacity = (deque->capacity == 0)
                              ? DEQUE_INITIAL_CAPACITY
                              : deque->capacity * DEQUE_GROWTH_FACTOR;

    size_t size = sizeof(deque->items[0]);
    int *temp = malloc(size * new_capacity);
    assert(temp && "Error: couldnt allocate memory, please refer to "
                   "https://downloadmoreram.com/");

    size_t back = (deque->capacity == 0) ? 0 : deque_get_back(deque);
    if (deque->len > 0) {
        if (deque->front < back) {
            memcpy(temp, &deque->items[deque->front], size * deque->len);

        } else {
            size_t elems_at_end = deque->capacity - deque->front;
            memcpy(temp, &deque->items[deque->front], size * elems_at_end);
            memcpy(&temp[elems_at_end], &deque->items[0], size * back);
        }
    }
    free(deque->items);
    deque->items = temp;
    deque->front = 0;
    deque->capacity = new_capacity;
}

void deque_push_back(Deque *deque, int item) {
    if (deque->len == deque->capacity) {
        deque_resize(deque);
    }

    size_t back = deque_get_back(deque);
    deque->items[back] = item;
    deque->len++;
    if (deque->len == deque->capacity) {
        // set rear to 1 after last element if queue is full
        // and it is incremented beyond the length
        back = (back + 1) % (deque->capacity + 1);
    } else {
        back = (back + 1) % deque->capacity;
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

    size_t back = deque_get_back(deque);

    // ensures that -1 wraps around to (deque->capacity - 1)
    back = (back - 1 + deque->capacity) % deque->capacity;

    *item = deque->items[back];
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
    *item = deque->items[(deque_get_back(deque) - 1 + deque->capacity) %
                         deque->capacity];
    return true;
}

bool deque_print(Deque *deque) {
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
