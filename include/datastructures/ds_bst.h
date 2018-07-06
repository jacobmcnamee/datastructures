#ifndef DS_BST_H
#define DS_BST_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_bst_s ds_bst_t;

ds_bst_t *ds_bst_create(int (*compare)(const void *a, const void *b));
void ds_bst_destroy(ds_bst_t **bst);
bool ds_bst_empty(ds_bst_t *bst);
size_t ds_bst_size(ds_bst_t *bst);
void ds_bst_insert(ds_bst_t *bst, void *data);
bool ds_bst_search(ds_bst_t *bst, void *data);
bool ds_bst_remove(ds_bst_t *bst, void *data);

#endif /* DS_BST_H */
