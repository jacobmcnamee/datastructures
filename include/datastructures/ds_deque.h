#ifndef DS_DEQUE_H
#define DS_DEQUE_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_deque_s ds_deque_t;

ds_deque_t *ds_deque_create(size_t capacity);
void ds_deque_destroy(ds_deque_t **deque);
void ds_deque_resize(ds_deque_t *deque, size_t capacity);
size_t ds_deque_capacity(ds_deque_t *deque);
bool ds_deque_empty(ds_deque_t *deque);
size_t ds_deque_size(ds_deque_t *deque);
void ds_deque_push_front(ds_deque_t *deque, void *data);
void ds_deque_push_back(ds_deque_t *deque, void *data);
void *ds_deque_pop_front(ds_deque_t *deque);
void *ds_deque_pop_back(ds_deque_t *deque);

#endif /* DS_DEQUE_H */
