#include <datastructures/common.h>
#include <datastructures/ds_double_list.h>

typedef struct node_s {
  void *data;
  struct node_s *next;
  struct node_s *prev;
} node_t;

struct ds_double_list_s {
  node_t *root;
  size_t size;
  node_t *iter_fw;
  node_t *iter_rev;
};

static node_t *node_create(void)
{
  node_t *node = (node_t *)malloc(sizeof(*node));
  assert(node != NULL);

  node->data = NULL;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

static void node_destroy(node_t **node)
{
  free(*node);
  *node = NULL;
}

static void insert_after(ds_double_list_t *double_list, node_t *left,
                         void *data)
{
  node_t *node = node_create();
  node_t *right = left->next;
  node->data = data;
  node->next = right;
  node->prev = left;
  left->next = node;
  right->prev = node;
  double_list->size++;
}

static void *remove(ds_double_list_t *double_list, node_t *node)
{
  node_t *left = node->prev;
  node_t *right = node->next;
  void *data = node->data;
  left->next = right;
  right->prev = left;
  node_destroy(&node);
  double_list->size--;

  return data;
}

static node_t *lookup(ds_double_list_t *double_list, size_t index)
{
  node_t *node = double_list->root;
  if (index < double_list->size / 2) {
    for (size_t i = 0; i <= index; i++) {
      node = node->next;
    }
  } else {
    for (size_t i = 0; i < double_list->size - index; i++) {
      node = node->prev;
    }
  }

  return node;
}

ds_double_list_t *ds_double_list_create(void)
{
  ds_double_list_t *double_list =
      (ds_double_list_t *)malloc(sizeof(*double_list));
  assert(double_list != NULL);

  node_t *root = node_create();
  root->next = root;
  root->prev = root;

  double_list->root = root;
  double_list->size = 0;
  double_list->iter_fw = root;
  double_list->iter_rev = root;

  return double_list;
}

void ds_double_list_destroy(ds_double_list_t **double_list)
{
  assert(double_list != NULL);
  assert(*double_list != NULL);

  node_t *node = (*double_list)->root;
  for (size_t i = 0; i <= (*double_list)->size; i++) {
    node_t *next = node->next;
    node_destroy(&node);
    node = next;
  }
  node = NULL;

  free(*double_list);
  *double_list = NULL;
}

bool ds_double_list_empty(ds_double_list_t *double_list)
{
  assert(double_list != NULL);

  return (double_list->size == 0);
}

size_t ds_double_list_size(ds_double_list_t *double_list)
{
  assert(double_list != NULL);

  return double_list->size;
}

void ds_double_list_push_front(ds_double_list_t *double_list, void *data)
{
  assert(double_list != NULL);

  insert_after(double_list, double_list->root, data);
}

void *ds_double_list_pop_front(ds_double_list_t *double_list)
{
  assert(double_list != NULL);
  assert(double_list->size > 0);

  return remove(double_list, double_list->root->next);
}

void ds_double_list_push_back(ds_double_list_t *double_list, void *data)
{
  assert(double_list != NULL);

  insert_after(double_list, double_list->root->prev, data);
}

void *ds_double_list_pop_back(ds_double_list_t *double_list)
{
  assert(double_list != NULL);
  assert(double_list->size > 0);

  return remove(double_list, double_list->root->prev);
}

void ds_double_list_insert(ds_double_list_t *double_list, size_t index,
                           void *data)
{
  assert(double_list != NULL);
  assert(index <= double_list->size);

  node_t *left = (index == 0) ? double_list->root :
                                lookup(double_list, index - 1);
  insert_after(double_list, left, data);
}

void *ds_double_list_remove(ds_double_list_t *double_list, size_t index)
{
  assert(double_list != NULL);
  assert(index < double_list->size);

  node_t *node = lookup(double_list, index);

  return remove(double_list, node);
}
void *ds_double_list_get(ds_double_list_t *double_list, size_t index)
{
  assert(double_list != NULL);
  assert(index < double_list->size);

  node_t *node = lookup(double_list, index);

  return node->data;
}

void ds_double_list_iterate_forward_begin(ds_double_list_t *double_list)
{
  assert(double_list != NULL);

  double_list->iter_fw = double_list->root->next;
}

void *ds_double_list_iterate_forward_next(ds_double_list_t *double_list)
{
  assert(double_list != NULL);
  assert(double_list->iter_fw != double_list->root);

  void *data = double_list->iter_fw->data;
  double_list->iter_fw = double_list->iter_fw->next;

  return data;
}

void ds_double_list_iterate_reverse_begin(ds_double_list_t *double_list)
{
  assert(double_list != NULL);

  double_list->iter_rev = double_list->root->prev;
}

void *ds_double_list_iterate_reverse_next(ds_double_list_t *double_list)
{
  assert(double_list != NULL);
  assert(double_list->iter_rev != double_list->root);

  void *data = double_list->iter_rev->data;
  double_list->iter_rev = double_list->iter_rev->prev;

  return data;
}
