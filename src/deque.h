#ifndef INCLUDE_SRC_DEQUE_H_
#define INCLUDE_SRC_DEQUE_H_

#include <malloc.h>
#include <stdbool.h>

#define DEQUE_INITIAL_CAPACITY 4
#define DEQUE_GROWTH_FACTOR 2

// #define arr_size(arr) sizeof((arr))/sizeof(*(arr))
// #define deque_init(arr) (Deque){ .items = (arr), .len = arr_size((arr)),
// .capacity = arr_size((arr)) .front = 0 }
#define deque_init()                                                           \
    (Deque) { 0 }


#define deque_del(deque)                                                       \
    do {                                                                       \
        free((deque)->items);                                                  \
        (deque)->len = 0;                                                      \
        (deque)->front = 0;                                                    \
        (deque)->capacity = 0;                                                 \
    } while (0)


#define deque_get_back(deque)                                                  \
    ((deque)->front + (deque)->len) % (deque)->capacity


#define deque_resize(deque)                                                    \
    do {                                                                       \
        size_t new_capacity = ((deque)->capacity == 0)                         \
                                  ? DEQUE_INITIAL_CAPACITY                     \
                                  : (deque)->capacity * DEQUE_GROWTH_FACTOR;   \
                                                                               \
        size_t size = sizeof((deque)->items[0]);                               \
        int *temp = malloc(size * new_capacity);                               \
        assert(temp && "Error: couldnt allocate memory, please refer to "      \
                       "https://downloadmoreram.com/");                        \
                                                                               \
        size_t back = ((deque)->capacity == 0) ? 0 : deque_get_back((deque));  \
        if ((deque)->len > 0) {                                                \
            if ((deque)->front < back || (deque)->front == 0) {                \
                memcpy(temp, &(deque)->items[(deque)->front],                  \
                       size *(deque)->len);                                    \
                                                                               \
            } else {                                                           \
                size_t elems_at_end = (deque)->capacity - (deque)->front;      \
                memcpy(temp, &(deque)->items[(deque)->front],                  \
                       size *elems_at_end);                                    \
                memcpy(&temp[elems_at_end], &(deque)->items[0], size *back);   \
            }                                                                  \
        }                                                                      \
        free((deque)->items);                                                  \
        (deque)->items = temp;                                                 \
        (deque)->front = 0;                                                    \
        (deque)->capacity = new_capacity;                                      \
    } while (0)


#define deque_push_back(deque, item)                                           \
    do {                                                                       \
        if ((deque)->len == (deque)->capacity) {                               \
            deque_resize((deque));                                             \
        }                                                                      \
                                                                               \
        size_t back = deque_get_back((deque));                                 \
        (deque)->items[back] = (item);                                         \
        (deque)->len++;                                                        \
        if ((deque)->len == (deque)->capacity) {                               \
            /* set rear to 1 after last element if queue is full */            \
            /* and it is incremented beyond the length */                      \
            back = (back + 1) % ((deque)->capacity + 1);                       \
        } else {                                                               \
            back = (back + 1) % (deque)->capacity;                             \
        }                                                                      \
    } while (0)


#define deque_push_front(deque, item)                                          \
    do {                                                                       \
        if ((deque)->len == (deque)->capacity) {                               \
            deque_resize((deque));                                             \
        }                                                                      \
        (deque)->front =                                                       \
            ((deque)->front - 1 + (deque)->capacity) % (deque)->capacity;      \
        (deque)->items[(deque)->front] = (item);                               \
        (deque)->len++;                                                        \
    } while (0)


// Use typeof if in C23 (Allows passing in NULL to the pop functions)
// For some reason gcc gives 201710L rather than 202311L for -std=c23
// even though the following doc says otherwise
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201710L
#define deque_pop_front(deque, item)                                           \
    do {                                                                       \
        typeof((deque)->items) i = (item);                                     \
        if (i != NULL) {                                                       \
            *i = (deque)->items[(deque)->front];                               \
        }                                                                      \
        (deque)->front = ((deque)->front + 1) % (deque)->capacity;             \
        (deque)->len--;                                                        \
    } while (0)

#define deque_pop_back(deque, item)                                            \
    do {                                                                       \
        size_t back = deque_get_back((deque));                                 \
        /* ensures that -1 wraps around to ((deque)->capacity - 1) */          \
        back = (back - 1 + (deque)->capacity) % (deque)->capacity;             \
                                                                               \
        typeof((deque)->items) i = (item);                                     \
        if (i != NULL) {                                                       \
            *i = (deque)->items[back];                                         \
        }                                                                      \
        (deque)->len--;                                                        \
    } while (0)

#define deque_peek_front(deque, item)                                          \
    do {                                                                       \
        typeof((deque)->items) i = (item);                                     \
        if (i != NULL) {                                                       \
            *i = (deque)->items[(deque)->front];                               \
        }                                                                      \
    } while (0)

#define deque_peek_back(deque, item)                                           \
    do {                                                                       \
        typeof((deque)->items) i = (item);                                     \
        if (i != NULL) {                                                       \
            /* ensures that -1 wraps around to ((deque)->capacity - 1) */      \
            *i = (deque)->items[(deque_get_back((deque)) - 1 +                 \
                                 (deque)->capacity) %                          \
                                (deque)->capacity];                            \
        }                                                                      \
    } while (0)

#else
#define deque_pop_front(deque, item)                                           \
    do {                                                                       \
        if ((item) != NULL) {                                                  \
            *item = (deque)->items[(deque)->front];                            \
        }                                                                      \
        (deque)->front = ((deque)->front + 1) % (deque)->capacity;             \
        (deque)->len--;                                                        \
    } while (0)

#define deque_pop_back(deque, item)                                            \
    do {                                                                       \
        size_t back = deque_get_back((deque));                                 \
        /* ensures that -1 wraps around to ((deque)->capacity - 1) */          \
        back = (back - 1 + (deque)->capacity) % (deque)->capacity;             \
                                                                               \
        if ((item) != NULL) {                                                  \
            *(item) = (deque)->items[back];                                    \
        }                                                                      \
        (deque)->len--;                                                        \
    } while (0)

#define deque_peek_front(deque, item)                                          \
    do {                                                                       \
        if ((item) != NULL) {                                                  \
            *(item) = (deque)->items[(deque)->front];                          \
        }                                                                      \
    } while (0)

#define deque_peek_back(deque, item)                                           \
    do {                                                                       \
        if ((item) != NULL) {                                                  \
            /* ensures that -1 wraps around to ((deque)->capacity - 1) */      \
            *(item) = (deque)->items[(deque_get_back((deque)) - 1 +            \
                                      (deque)->capacity) %                     \
                                     (deque)->capacity];                       \
        }                                                                      \
    } while (0)

#endif // __STDC_VERSION__

/* TODO: Document the macros
 *
void deque_push_back(Deque *deque, int item);
void deque_push_front(Deque *deque, int item);
bool deque_pop_front(Deque *deque, int *item);
bool deque_pop_back(Deque *deque, int *item);
bool deque_peek_front(Deque *deque, int *item);
bool deque_peek_back(Deque *deque, int *item);
bool deque_print(Deque *deque);
*/

#endif // INCLUDE_SRC_DEQUE_H_
