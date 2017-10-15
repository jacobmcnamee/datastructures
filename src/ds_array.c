#include <datastructures/common.h>
#include <datastructures/ds_array.h>

struct ds_array_s {
  size_t capacity;
  void **data;
};

ds_array_t *ds_array_create(size_t capacity)
{
  ds_array_t *array = (ds_array_t *)malloc(sizeof(*array));
  assert(array != NULL);

  array->data = (void *)malloc(capacity * sizeof(*array->data));
  assert(array->data != NULL);

  array->capacity = capacity;
  return array;
}

void ds_array_destroy(ds_array_t **array)
{
  assert(array != NULL);
  assert(*array != NULL);
  assert((*array)->data != NULL);

  free((*array)->data);
  (*array)->data = NULL;
  free(*array);
  *array = NULL;
}

void ds_array_resize(ds_array_t *array, size_t capacity)
{
  assert(array != NULL);
  assert(array->data != NULL);

  array->data = (void *)realloc(array->data, capacity * sizeof(*array->data));
  assert(array->data != NULL);

  array->capacity = capacity;
}

size_t ds_array_capacity(ds_array_t *array)
{
  assert(array != NULL);

  return array->capacity;
}

void ds_array_set(ds_array_t *array, size_t index, void *data)
{
  assert(array != NULL);
  assert(array->data != NULL);
  assert(index < array->capacity);

  array->data[index] = data;
}

void *ds_array_get(ds_array_t *array, size_t index)
{
  assert(array != NULL);
  assert(array->data != NULL);
  assert(index < array->capacity);

  return array->data[index];
}
