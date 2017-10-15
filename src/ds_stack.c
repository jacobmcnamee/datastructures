#include <datastructures/common.h>
#include <datastructures/ds_stack.h>
#include <datastructures/ds_array.h>

struct ds_stack_s {
  ds_array_t *array;
  size_t size;
};

ds_stack_t *ds_stack_create(size_t capacity)
{
  ds_stack_t *stack = (ds_stack_t *)malloc(sizeof(*stack));
  assert(stack != NULL);

  stack->array = ds_array_create(capacity);
  stack->size = 0;

  return stack;
}

void ds_stack_destroy(ds_stack_t **stack)
{
  assert(stack != NULL);
  assert(*stack != NULL);

  ds_array_destroy(&(*stack)->array);

  free(*stack);
  *stack = NULL;
}

void ds_stack_resize(ds_stack_t *stack, size_t capacity)
{
  assert(stack != NULL);
  assert(capacity >= stack->size);

  ds_array_resize(stack->array, capacity);
}

size_t ds_stack_capacity(ds_stack_t *stack)
{
  assert(stack != NULL);

  return ds_array_capacity(stack->array);
}

bool ds_stack_empty(ds_stack_t *stack)
{
  assert(stack != NULL);

  return (stack->size == 0);
}

size_t ds_stack_size(ds_stack_t *stack)
{
  assert(stack != NULL);

  return stack->size;
}

void ds_stack_push(ds_stack_t *stack, void *data)
{
  assert(stack != NULL);

  size_t capacity = ds_array_capacity(stack->array);
  if (stack->size == capacity) {
    ds_array_resize(stack->array, capacity > 0 ? 2 * capacity : 1);
  }

  ds_array_set(stack->array, stack->size++, data);
}

void *ds_stack_pop(ds_stack_t *stack)
{
  assert(stack != NULL);
  assert(stack->size > 0);

  return ds_array_get(stack->array, --stack->size);
}
