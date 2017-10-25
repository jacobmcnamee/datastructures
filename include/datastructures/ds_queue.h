#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_queue_s ds_queue_t;

ds_queue_t *ds_queue_create(size_t capacity);
void ds_queue_destroy(ds_queue_t **queue);
void ds_queue_resize(ds_queue_t *queue, size_t capacity);
size_t ds_queue_capacity(ds_queue_t *queue);
bool ds_queue_empty(ds_queue_t *queue);
size_t ds_queue_size(ds_queue_t *queue);
void ds_queue_push(ds_queue_t *queue, void *data);
void *ds_queue_pop(ds_queue_t *queue);

#endif /* DS_QUEUE_H */
