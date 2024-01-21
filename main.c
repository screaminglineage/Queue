#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
  int *items;
  size_t capacity;
  size_t front;
  size_t rear;
} Queue;

// TODO: automatically move elements back to the start
// if front moves too far away
void queue_push(Queue *queue, int item) {
  if (queue->rear >= queue->capacity) {
    queue->capacity = (queue->capacity == 0)? 1: queue->capacity*2;
    queue->items = realloc(queue->items, queue->capacity*sizeof(queue->items[0]));
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
    memcpy(queue->items, queue->items + queue->front, len*sizeof(queue->items[0]));
    queue->front = 0;
    queue->rear = len;
  }

  *item = queue->items[queue->front++];
  return true;
}


int main() {
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
  while(queue_pop(&queue, &x)) {
    printf("%d, len = %zu\n", x, queue.rear - queue.front);
  }

  return 0;
}
