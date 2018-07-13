#ifndef DS_SEGMENT_TREE_H
#define DS_SEGMENT_TREE_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_segment_tree_s ds_segment_tree_t;

ds_segment_tree_t *
ds_segment_tree_create(const void *data, size_t data_length,
                       size_t data_element_size,
                       void (*operate)(const void *a, const void *b,
                                       void *result));
void ds_segment_tree_destroy(ds_segment_tree_t **segment_tree);
void ds_segment_tree_query(ds_segment_tree_t *segment_tree, size_t left,
                           size_t right, void *result);
void ds_segment_tree_modify(ds_segment_tree_t *segment_tree, size_t index,
                            const void *data);

#endif /* DS_SEGMENT_TREE_H */
