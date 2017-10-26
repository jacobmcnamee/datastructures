#include <datastructures/common.h>
#include <datastructures/ds_deque.h>
#include <datastructures/ds_array.h>

struct ds_deque_s {
  ds_array_t *array;
  size_t start;
  size_t size;
};

static inline size_t index_mask(ds_deque_t *deque, size_t index)
{
  return index % ds_array_capacity(deque->array);
}

static void resize(ds_deque_t *deque, size_t capacity)
{
  ds_array_t *array_new = ds_array_create(capacity);

  size_t offset = deque->start;
  for (size_t i = 0; i < deque->size; i++) {
    ds_array_set(array_new, i, ds_array_get(deque->array, offset));
    offset = index_mask(deque, offset + 1);
  }

  ds_array_destroy(&deque->array);
  deque->array = array_new;
  deque->start = 0;
}

ds_deque_t *ds_deque_create(size_t capacity)
{
  ds_deque_t *deque = (ds_deque_t *)malloc(sizeof(*deque));
  assert(deque != NULL);

  deque->array = ds_array_create(capacity);
  deque->start = 0;
  deque->size = 0;

  return deque;
}

void ds_deque_destroy(ds_deque_t **deque)
{
  assert(deque != NULL);
  assert(*deque != NULL);

  ds_array_destroy(&(*deque)->array);

  free(*deque);
  *deque = NULL;
}

void ds_deque_resize(ds_deque_t *deque, size_t capacity)
{
  assert(deque != NULL);
  assert(capacity >= deque->size);

  resize(deque, capacity);
}

size_t ds_deque_capacity(ds_deque_t *deque)
{
  assert(deque != NULL);

  return ds_array_capacity(deque->array);
}

bool ds_deque_empty(ds_deque_t *deque)
{
  assert(deque != NULL);

  return (deque->size == 0);
}

size_t ds_deque_size(ds_deque_t *deque)
{
  assert(deque != NULL);

  return deque->size;
}

void ds_deque_push_front(ds_deque_t *deque, void *data)
{
  assert(deque != NULL);

  size_t capacity = ds_array_capacity(deque->array);
  if (deque->size == capacity) {
    resize(deque, capacity > 0 ? 2 * capacity : 1);
  }

  size_t index = index_mask(deque, deque->start + capacity - 1);
  ds_array_set(deque->array, index, data);
  deque->start = index;
  deque->size++;
}

void ds_deque_push_back(ds_deque_t *deque, void *data)
{
  assert(deque != NULL);

  size_t capacity = ds_array_capacity(deque->array);
  if (deque->size == capacity) {
    resize(deque, capacity > 0 ? 2 * capacity : 1);
  }

  size_t index = index_mask(deque, deque->start + deque->size);
  ds_array_set(deque->array, index, data);
  deque->size++;
}

void *ds_deque_pop_front(ds_deque_t *deque)
{
  assert(deque != NULL);
  assert(deque->size > 0);

  void *data = ds_array_get(deque->array, deque->start);
  deque->start = index_mask(deque, deque->start + 1);
  deque->size--;
  return data;
}

void *ds_deque_pop_back(ds_deque_t *deque)
{
  assert(deque != NULL);
  assert(deque->size > 0);

  size_t index = index_mask(deque, deque->start + deque->size - 1);
  void *data = ds_array_get(deque->array, index);
  deque->size--;
  return data;
}
