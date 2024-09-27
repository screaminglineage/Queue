#include "deque.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t capacity;
    size_t front;
    size_t rear;
} Queue;

void queue_push(Queue *queue, int item) {
    // resize if capacity is reached
    if (queue->rear >= queue->capacity) {
        queue->capacity = (queue->capacity == 0) ? 1 : queue->capacity * 2;
        queue->items =
            realloc(queue->items, queue->capacity * sizeof(queue->items[0]));
    }
    queue->items[queue->rear++] = item;
}

bool queue_pop(Queue *queue, int *item) {
    // queue empty
    if (queue->front == queue->rear) {
        return false;
    }

    size_t len = queue->rear - queue->front;
    // may be optimised to only copy when len is too big
    // only copies if the region behind front is larger than len
    // making them non-overlapping which allows memcpy to be used
    if (/*len > 16 && */ (queue->front - 1) > len) {
        memcpy(queue->items, queue->items + queue->front,
               len * sizeof(queue->items[0]));
        queue->front = 0;
        queue->rear = len;
    }

    *item = queue->items[queue->front++];
    return true;
}

void queue_del(Queue *queue) {
    free(queue->items);
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = 0;
}

void deque_test(void);
void queue_test(void);

int main() {
    // queue_test();
    // putchar('\n');

    deque_test();
    putchar('\n');

    return 0;
}

void queue_test() {
    Queue queue = {NULL, 0, 0, 0};
    queue_push(&queue, 23);
    queue_push(&queue, 93);
    queue_push(&queue, 82);
    queue_push(&queue, 75);
    queue_push(&queue, 1000);
    queue_push(&queue, 1000);
    queue_push(&queue, 1000);
    queue_push(&queue, 1000);
    queue_push(&queue, 1000);

    int x = 0;
    while (queue_pop(&queue, &x)) {
        printf("%d, len = %zu\n", x, queue.rear - queue.front);
    }
    queue_del(&queue);
}

void deque_test() {
    Deque d = deque_init();
    deque_push_back(&d, 23);
    deque_push_back(&d, 93);
    deque_push_back(&d, 82);
    deque_push_back(&d, 75);
    deque_push_back(&d, 5);
    deque_push_back(&d, 1000);

    int x = 0;
    deque_pop_front(&d, &x);
    printf("%d ", x);

    deque_pop_front(&d, &x);
    printf("%d ", x);

    deque_pop_front(&d, &x);
    printf("%d \n", x);

    deque_push_back(&d, 56);
    deque_push_back(&d, 39);
    deque_push_back(&d, 100);
    deque_push_back(&d, 267);

    deque_pop_back(&d, &x);
    printf("%d \n", x);
    deque_pop_back(&d, &x);
    printf("%d \n", x);

    deque_push_front(&d, 13);
    deque_push_front(&d, 27);
    deque_push_front(&d, 68);
    deque_push_front(&d, 73);

    for (int i = 0; i < 8; i++) {
        deque_push_back(&d, i);
    }

    deque_print(&d);

    deque_del(&d);
}
