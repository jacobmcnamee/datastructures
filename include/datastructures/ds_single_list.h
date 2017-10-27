#ifndef DS_SINGLE_LIST_H
#define DS_SINGLE_LIST_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_single_list_s ds_single_list_t;

ds_single_list_t *ds_single_list_create(void);
void ds_single_list_destroy(ds_single_list_t **single_list);
bool ds_single_list_empty(ds_single_list_t *single_list);
size_t ds_single_list_size(ds_single_list_t *single_list);
void ds_single_list_push_front(ds_single_list_t *single_list, void *data);
void *ds_single_list_pop_front(ds_single_list_t *single_list);
void ds_single_list_insert(ds_single_list_t *single_list, size_t index,
                           void *data);
void *ds_single_list_remove(ds_single_list_t *single_list, size_t index);
void *ds_single_list_get(ds_single_list_t *single_list, size_t index);
void ds_single_list_iterate_begin(ds_single_list_t *single_list);
void *ds_single_list_iterate_next(ds_single_list_t *single_list);

#endif /* DS_SINGLE_LIST_H */
