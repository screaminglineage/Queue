# Queue

Simple dyanamically allocated queues in C

The Deque implementation with macros can be used as a generic Deque with any data type.
Just `#include "src/deque.h"` and define the the Deque struct as follows, `items` can be of any type.

```c
typedef struct {
    <TYPE> *items;
    size_t len;
    size_t front;
    size_t capacity;
} Deque;
```


## Build Instructions

```console
gcc -Wall -Wpedantic src/queue.c example.c -o example
./example
```

## TODO
 - Make the Deque generic (using either void* or macros)

