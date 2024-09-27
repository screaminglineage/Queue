#include "src/int_deque.h"
#include "src/queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deque_test(void);
void queue_test(void);

int main() {
    printf("Queue Tests:\n");
    queue_test();
    putchar('\n');

    printf("Deque Tests:\n");
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
