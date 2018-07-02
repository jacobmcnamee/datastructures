#ifndef DS_HEAP_H
#define DS_HEAP_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_heap_s ds_heap_t;

ds_heap_t *ds_heap_create(size_t capacity,
                          int (*compare)(const void *a, const void *b));
void ds_heap_destroy(ds_heap_t **heap);
void ds_heap_resize(ds_heap_t *heap, size_t capacity);
size_t ds_heap_capacity(ds_heap_t *heap);
bool ds_heap_empty(ds_heap_t *heap);
size_t ds_heap_size(ds_heap_t *heap);
void ds_heap_insert(ds_heap_t *heap, void *data);
void *ds_heap_pop(ds_heap_t *heap);

#endif /* DS_HEAP_H */
