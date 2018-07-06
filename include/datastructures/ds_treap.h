#ifndef DS_TREAP_H
#define DS_TREAP_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_treap_s ds_treap_t;

ds_treap_t *ds_treap_create(int (*compare)(const void *a, const void *b));
void ds_treap_destroy(ds_treap_t **treap);
bool ds_treap_empty(ds_treap_t *treap);
size_t ds_treap_size(ds_treap_t *treap);
void ds_treap_insert(ds_treap_t *treap, void *data);
bool ds_treap_search(ds_treap_t *treap, void *data);
bool ds_treap_remove(ds_treap_t *treap, void *data);

#endif /* DS_TREAP_H */
