#ifndef DS_DOUBLE_LIST_H
#define DS_DOUBLE_LIST_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_double_list_s ds_double_list_t;

ds_double_list_t *ds_double_list_create(void);
void ds_double_list_destroy(ds_double_list_t **double_list);
bool ds_double_list_empty(ds_double_list_t *double_list);
size_t ds_double_list_size(ds_double_list_t *double_list);
void ds_double_list_push_front(ds_double_list_t *double_list, void *data);
void *ds_double_list_pop_front(ds_double_list_t *double_list);
void ds_double_list_push_back(ds_double_list_t *double_list, void *data);
void *ds_double_list_pop_back(ds_double_list_t *double_list);
void ds_double_list_insert(ds_double_list_t *double_list, size_t index,
                           void *data);
void *ds_double_list_remove(ds_double_list_t *double_list, size_t index);
void *ds_double_list_get(ds_double_list_t *double_list, size_t index);
void ds_double_list_iterate_forward_begin(ds_double_list_t *double_list);
void *ds_double_list_iterate_forward_next(ds_double_list_t *double_list);
void ds_double_list_iterate_reverse_begin(ds_double_list_t *double_list);
void *ds_double_list_iterate_reverse_next(ds_double_list_t *double_list);

#endif /* DS_DOUBLE_LIST_H */
