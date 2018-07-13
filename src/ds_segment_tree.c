#include <datastructures/common.h>
#include <datastructures/ds_segment_tree.h>
#include <datastructures/ds_array.h>

struct ds_segment_tree_s {
  void *array;
  size_t data_length;
  size_t data_element_size;
  void (*operate)(const void *a, const void *b, void *result);
};

static void* array_index(ds_segment_tree_t *segment_tree, size_t index)
{
  void *data = (void *)((char *)segment_tree->array +
                                segment_tree->data_element_size * index);
  return data;
}

static void build(ds_segment_tree_t *segment_tree, const void *data)
{
  void *dst = array_index(segment_tree, segment_tree->data_length);
  memcpy(dst, data, segment_tree->data_length *
                    segment_tree->data_element_size);

  for (size_t i = segment_tree->data_length - 1; i > 0; i--) {
    void *a = array_index(segment_tree, 2 * i);
    void *b = array_index(segment_tree, 2 * i + 1);
    void *result = array_index(segment_tree, i);
    segment_tree->operate(a, b, result);
  }
}

ds_segment_tree_t *
ds_segment_tree_create(const void *data, size_t data_length,
                       size_t data_element_size,
                       void (*operate)(const void *a, const void *b,
                                       void *result))
{
  assert(data != NULL);
  assert(data_length > 0);
  assert(data_element_size > 0);
  assert(operate != NULL);

  ds_segment_tree_t *segment_tree =
      (ds_segment_tree_t *)malloc(sizeof(*segment_tree));
  assert(segment_tree != NULL);

  size_t array_capacity = 2 * data_length;
  segment_tree->array = calloc(array_capacity, data_element_size);
  assert(segment_tree->array != NULL);

  segment_tree->data_length = data_length;
  segment_tree->data_element_size = data_element_size;
  segment_tree->operate = operate;

  build(segment_tree, data);

  return segment_tree;
}

void ds_segment_tree_destroy(ds_segment_tree_t **segment_tree)
{
  assert(segment_tree != NULL);
  assert(*segment_tree != NULL);

  free((*segment_tree)->array);
  (*segment_tree)->array = NULL;

  free(*segment_tree);
  *segment_tree = NULL;
}

void ds_segment_tree_query(ds_segment_tree_t *segment_tree, size_t left,
                           size_t right, void *result)
{
  assert(segment_tree != NULL);
  assert(left <= right);
  assert(right < segment_tree->data_length);
  assert(result != NULL);

  size_t l = left + segment_tree->data_length;
  size_t r = right + segment_tree->data_length;

  bool result_initialized = false;
  do {
    size_t op_indexes[2];
    size_t op_indexes_count = 0;

    if ((l % 2) == 1) {
      op_indexes[op_indexes_count++] = l;
      l++;
    }

    if ((r % 2) == 0) {
      op_indexes[op_indexes_count++] = r;
      r--;
    }

    for (size_t i = 0; i < op_indexes_count; i++) {
      void *src = array_index(segment_tree, op_indexes[i]);
      if (!result_initialized) {
        memcpy(result, src, segment_tree->data_element_size);
        result_initialized = true;
      } else {
        segment_tree->operate(src, result, result);
      }
    }

    l = l / 2;
    r = r / 2;
  } while (l <= r);
}

void ds_segment_tree_modify(ds_segment_tree_t *segment_tree, size_t index,
                            const void *data)
{
  assert(segment_tree != NULL);
  assert(index < segment_tree->data_length);
  assert(data != NULL);

  size_t i = index + segment_tree->data_length;

  void *dst = array_index(segment_tree, i);
  memcpy(dst, data, segment_tree->data_element_size);

  for (i = i / 2; i > 0; i /= 2) {
    void *a = array_index(segment_tree, 2 * i);
    void *b = array_index(segment_tree, 2 * i + 1);
    void *result = array_index(segment_tree, i);
    segment_tree->operate(a, b, result);
  }
}
