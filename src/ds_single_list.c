#include <datastructures/common.h>
#include <datastructures/ds_single_list.h>

typedef struct node_s {
  void *data;
  struct node_s *next;
} node_t;

struct ds_single_list_s {
  node_t *root;
  size_t size;
  node_t *iter;
};

static node_t *node_create(void)
{
  node_t *node = (node_t *)malloc(sizeof(*node));
  assert(node != NULL);

  node->data = NULL;
  node->next = NULL;

  return node;
}

static void node_destroy(node_t **node)
{
  free(*node);
  *node = NULL;
}

static void insert(ds_single_list_t *single_list, node_t **p_next, void *data)
{
  node_t *node = node_create();
  node->data = data;
  node->next = *p_next;
  *p_next = node;
  single_list->size++;
}

static void *remove(ds_single_list_t *single_list, node_t **p_next)
{
  node_t *node = *p_next;
  void *data = node->data;
  *p_next = node->next;
  node_destroy(&node);
  single_list->size--;

  return data;
}

static node_t **lookup(ds_single_list_t *single_list, size_t index)
{
  node_t **p_next = &single_list->root;
  for (size_t i = 0; i < index; i++) {
    p_next = &(*p_next)->next;
  }

  return p_next;
}

ds_single_list_t *ds_single_list_create(void)
{
  ds_single_list_t *single_list =
      (ds_single_list_t *)malloc(sizeof(*single_list));
  assert(single_list != NULL);

  single_list->root = NULL;
  single_list->size = 0;
  single_list->iter = NULL;

  return single_list;
}

void ds_single_list_destroy(ds_single_list_t **single_list)
{
  assert(single_list != NULL);
  assert(*single_list != NULL);

  node_t *node = (*single_list)->root;
  while (node != NULL) {
    node_t *next = node->next;
    node_destroy(&node);
    node = next;
  }

  free(*single_list);
  *single_list = NULL;
}

bool ds_single_list_empty(ds_single_list_t *single_list)
{
  assert(single_list != NULL);

  return (single_list->size == 0);
}

size_t ds_single_list_size(ds_single_list_t *single_list)
{
  assert(single_list != NULL);

  return single_list->size;
}

void ds_single_list_push_front(ds_single_list_t *single_list, void *data)
{
  assert(single_list != NULL);

  insert(single_list, &single_list->root, data);
}

void *ds_single_list_pop_front(ds_single_list_t *single_list)
{
  assert(single_list != NULL);
  assert(single_list->size > 0);

  return remove(single_list, &single_list->root);
}

void ds_single_list_insert(ds_single_list_t *single_list, size_t index,
                           void *data)
{
  assert(single_list != NULL);
  assert(index <= single_list->size);

  node_t **p_next = lookup(single_list, index);
  insert(single_list, p_next, data);
}

void *ds_single_list_remove(ds_single_list_t *single_list, size_t index)
{
  assert(single_list != NULL);
  assert(index < single_list->size);

  node_t **p_next = lookup(single_list, index);

  return remove(single_list, p_next);
}

void *ds_single_list_get(ds_single_list_t *single_list, size_t index)
{
  assert(single_list != NULL);
  assert(index < single_list->size);

  node_t **p_next = lookup(single_list, index);

  return (*p_next)->data;
}

void ds_single_list_iterate_begin(ds_single_list_t *single_list)
{
  assert(single_list != NULL);

  single_list->iter = single_list->root;
}

void *ds_single_list_iterate_next(ds_single_list_t *single_list)
{
  assert(single_list != NULL);
  assert(single_list->iter != NULL);

  void *data = single_list->iter->data;
  single_list->iter = single_list->iter->next;

  return data;
}
