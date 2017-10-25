#include <datastructures/common.h>
#include <datastructures/ds_queue.h>
#include <datastructures/ds_array.h>

struct ds_queue_s {
  ds_array_t *array;
  size_t start;
  size_t size;
};

static inline size_t index_mask(ds_queue_t *queue, size_t index)
{
  return index % ds_array_capacity(queue->array);
}

static void resize(ds_queue_t *queue, size_t capacity)
{
  ds_array_t *array_new = ds_array_create(capacity);

  size_t offset = queue->start;
  for (size_t i = 0; i < queue->size; i++) {
    ds_array_set(array_new, i, ds_array_get(queue->array, offset));
    offset = index_mask(queue, offset + 1);
  }

  ds_array_destroy(&queue->array);
  queue->array = array_new;
  queue->start = 0;
}

ds_queue_t *ds_queue_create(size_t capacity)
{
  ds_queue_t *queue = (ds_queue_t *)malloc(sizeof(*queue));
  assert(queue != NULL);

  queue->array = ds_array_create(capacity);
  queue->start = 0;
  queue->size = 0;

  return queue;
}

void ds_queue_destroy(ds_queue_t **queue)
{
  assert(queue != NULL);
  assert(*queue != NULL);

  ds_array_destroy(&(*queue)->array);

  free(*queue);
  *queue = NULL;
}

void ds_queue_resize(ds_queue_t *queue, size_t capacity)
{
  assert(queue != NULL);
  assert(capacity >= queue->size);

  resize(queue, capacity);
}

size_t ds_queue_capacity(ds_queue_t *queue)
{
  assert(queue != NULL);

  return ds_array_capacity(queue->array);
}

bool ds_queue_empty(ds_queue_t *queue)
{
  assert(queue != NULL);

  return (queue->size == 0);
}

size_t ds_queue_size(ds_queue_t *queue)
{
  assert(queue != NULL);

  return queue->size;
}

void ds_queue_push(ds_queue_t *queue, void *data)
{
  assert(queue != NULL);

  size_t capacity = ds_array_capacity(queue->array);
  if (queue->size == capacity) {
    resize(queue, capacity > 0 ? 2 * capacity : 1);
  }

  size_t index = index_mask(queue, queue->start + queue->size);
  ds_array_set(queue->array, index, data);
  queue->size++;
}

void *ds_queue_pop(ds_queue_t *queue)
{
  assert(queue != NULL);
  assert(queue->size > 0);

  void *data = ds_array_get(queue->array, queue->start);
  queue->start = index_mask(queue, queue->start + 1);
  queue->size--;
  return data;
}
