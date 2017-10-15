#ifndef DS_STACK_H
#define DS_STACK_H

#include <datastructures/common.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ds_stack_s ds_stack_t;

ds_stack_t *ds_stack_create(size_t capacity);
void ds_stack_destroy(ds_stack_t **stack);
void ds_stack_resize(ds_stack_t *stack, size_t capacity);
size_t ds_stack_capacity(ds_stack_t *stack);
bool ds_stack_empty(ds_stack_t *stack);
size_t ds_stack_size(ds_stack_t *stack);
void ds_stack_push(ds_stack_t *stack, void *data);
void *ds_stack_pop(ds_stack_t *stack);

#endif /* DS_STACK_H */
