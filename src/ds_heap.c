#include <datastructures/common.h>
#include <datastructures/ds_heap.h>
#include <datastructures/ds_array.h>

struct ds_heap_s {
  ds_array_t *array;
  size_t size;
  int (*compare)(const void *a, const void *b);
};

static void bubble_up(ds_heap_t *heap, size_t index)
{
  size_t ci = index;
  void *cd = ds_array_get(heap->array, ci);
  while (ci != 0) {
    size_t pi = (ci - 1) / 2;
    void *pd = ds_array_get(heap->array, pi);

    if (heap->compare(cd, pd) >= 0) {
      break;
    }

    ds_array_set(heap->array, pi, cd);
    ds_array_set(heap->array, ci, pd);
    ci = pi;
  }
}

static void trickle_down(ds_heap_t *heap, size_t index)
{
  size_t pi = index;
  void *pd = ds_array_get(heap->array, pi);
  while (1) {
    size_t lci = 2 * pi + 1;
    size_t rci = lci + 1;

    size_t ci;
    void *cd;
    if (rci < heap->size) {
      void *lcd = ds_array_get(heap->array, lci);
      void *rcd = ds_array_get(heap->array, rci);
      if (heap->compare(lcd, rcd) < 0) {
        ci = lci;
        cd = lcd;
      } else {
        ci = rci;
        cd = rcd;
      }
    } else if (lci < heap->size) {
      ci = lci;
      cd = ds_array_get(heap->array, lci);
    } else {
      break;
    }

    if (heap->compare(cd, pd) >= 0) {
      break;
    }

    ds_array_set(heap->array, pi, cd);
    ds_array_set(heap->array, ci, pd);
    pi = ci;
  }
}

ds_heap_t *ds_heap_create(size_t capacity,
                          int (*compare)(const void *a, const void *b))
{
  assert(compare != NULL);

  ds_heap_t *heap = (ds_heap_t *)malloc(sizeof(*heap));
  assert(heap != NULL);

  heap->array = ds_array_create(capacity);
  heap->size = 0;
  heap->compare = compare;

  return heap;
}

void ds_heap_destroy(ds_heap_t **heap)
{
  assert(heap != NULL);
  assert(*heap != NULL);

  ds_array_destroy(&(*heap)->array);

  free(*heap);
  *heap = NULL;
}

void ds_heap_resize(ds_heap_t *heap, size_t capacity)
{
  assert(heap != NULL);
  assert(capacity >= heap->size);

  ds_array_resize(heap->array, capacity);
}

size_t ds_heap_capacity(ds_heap_t *heap)
{
  assert(heap != NULL);

  return ds_array_capacity(heap->array);
}

bool ds_heap_empty(ds_heap_t *heap)
{
  assert(heap != NULL);

  return (heap->size == 0);
}

size_t ds_heap_size(ds_heap_t *heap)
{
  assert(heap != NULL);

  return heap->size;
}

void ds_heap_insert(ds_heap_t *heap, void *data)
{
  assert(heap != NULL);

  size_t capacity = ds_array_capacity(heap->array);
  if (heap->size == capacity) {
    ds_array_resize(heap->array, capacity > 0 ? 2 * capacity : 1);
  }

  ds_array_set(heap->array, heap->size++, data);
  bubble_up(heap, heap->size - 1);
}

void *ds_heap_pop(ds_heap_t *heap)
{
  assert(heap != NULL);
  assert(heap->size > 0);

  void *data = ds_array_get(heap->array, 0);
  ds_array_set(heap->array, 0, ds_array_get(heap->array, --heap->size));
  trickle_down(heap, 0);

  return data;
}
