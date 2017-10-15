#ifndef DS_ARRAY_H
#define DS_ARRAY_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_array_s ds_array_t;

ds_array_t *ds_array_create(size_t capacity);
void ds_array_destroy(ds_array_t **array);
void ds_array_resize(ds_array_t *array, size_t capacity);
size_t ds_array_capacity(ds_array_t *array);
void ds_array_set(ds_array_t *array, size_t index, void *data);
void *ds_array_get(ds_array_t *array, size_t index);

#endif /* DS_ARRAY_H */
