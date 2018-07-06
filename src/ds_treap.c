#include <datastructures/common.h>
#include <datastructures/ds_treap.h>

typedef struct node_s {
  void *data;
  int priority;
  struct node_s *left;
  struct node_s *right;
  struct node_s *parent;
} node_t;

struct ds_treap_s {
  node_t *root;
  size_t size;
  int (*compare)(const void *a, const void *b);
};

static node_t *node_create(void)
{
  node_t *node = (node_t *)malloc(sizeof(*node));
  assert(node != NULL);

  node->data = NULL;
  node->priority = rand();
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;

  return node;
}

static void node_destroy(node_t **node)
{
  free(*node);
  *node = NULL;
}

static node_t *search(ds_treap_t *treap, void *data)
{
  node_t *node = treap->root;
  while (node != NULL) {
    int compare_result = treap->compare(data, node->data);
    if (compare_result == 0) {
      return node;
    }
    node = (compare_result < 0) ? node->left : node->right;
  }

  return NULL;
}

static void splice(ds_treap_t *treap, node_t *node)
{
  node_t *child = (node->left != NULL) ? node->left : node->right;
  node_t *parent = node->parent;

  node_t **p_next;
  if (parent == NULL) {
    p_next = &treap->root;
  } else {
    p_next = (parent->left == node) ? &parent->left : &parent->right;
  }
  *p_next = child;

  if (child != NULL) {
    child->parent = parent;
  }

  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
}

static void rotate_left(ds_treap_t *treap, node_t *node)
{
  node_t *pivot = node->right;
  node_t *parent = node->parent;

  pivot->parent = parent;
  node_t **p_next;
  if (parent == NULL) {
    p_next = &treap->root;
  } else {
    p_next = (parent->left == node) ? &parent->left : &parent->right;
  }
  *p_next = pivot;

  node->right = pivot->left;
  if (node->right != NULL) {
    node->right->parent = node;
  }

  node->parent = pivot;
  pivot->left = node;
}

static void rotate_right(ds_treap_t *treap, node_t *node)
{
  node_t *pivot = node->left;
  node_t *parent = node->parent;

  pivot->parent = parent;
  node_t **p_next;
  if (parent == NULL) {
    p_next = &treap->root;
  } else {
    p_next = (parent->left == node) ? &parent->left : &parent->right;
  }
  *p_next = pivot;

  node->left = pivot->right;
  if (node->left != NULL) {
    node->left->parent = node;
  }

  node->parent = pivot;
  pivot->right = node;
}

static void bubble_up(ds_treap_t *treap, node_t *node)
{
  while ((node->parent != NULL) && (node->parent->priority < node->priority)) {
    if (node->parent->left == node) {
      rotate_right(treap, node->parent);
    } else {
      rotate_left(treap, node->parent);
    }
  }
}

static void trickle_down(ds_treap_t *treap, node_t *node)
{
  while ((node->left != NULL) || (node->right != NULL)) {
    if (node->left == NULL) {
      rotate_left(treap, node);
    } else if (node->right == NULL) {
      rotate_right(treap, node);
    } else if (node->left->priority > node->right->priority) {
      rotate_right(treap, node);
    } else {
      rotate_left(treap, node);
    }
  }
}

ds_treap_t *ds_treap_create(int (*compare)(const void *a, const void *b))
{
  assert(compare != NULL);

  ds_treap_t *treap = (ds_treap_t *)malloc(sizeof(*treap));
  assert(treap != NULL);

  treap->root = NULL;
  treap->size = 0;
  treap->compare = compare;

  return treap;
}

void ds_treap_destroy(ds_treap_t **treap)
{
  assert(treap != NULL);
  assert(*treap != NULL);

  node_t *node = (*treap)->root;
  node_t *prev = NULL;
  while (node != NULL) {
    node_t *next = NULL;
    if ((prev == node->parent) && (node->left != NULL)) {
      next = node->left;
    } else if (((prev == node->parent) || (prev == node->left)) &&
               (node->right != NULL)) {
      next = node->right;
    } else {
      next = node->parent;
    }

    prev = node;
    if (next == node->parent) {
      node_destroy(&node);
    }
    node = next;
  }
  (*treap)->root = NULL;

  free(*treap);
  *treap = NULL;
}

bool ds_treap_empty(ds_treap_t *treap)
{
  assert(treap != NULL);

  return (treap->size == 0);
}

size_t ds_treap_size(ds_treap_t *treap)
{
  assert(treap != NULL);

  return treap->size;
}

void ds_treap_insert(ds_treap_t *treap, void *data)
{
  assert(treap != NULL);

  node_t **p_node = &treap->root;
  node_t *prev = NULL;
  while (*p_node != NULL) {
    prev = *p_node;
    if(treap->compare(data, (*p_node)->data) <= 0) {
      p_node = &(*p_node)->left;
    } else {
      p_node = &(*p_node)->right;
    }
  }

  node_t *node = node_create();
  node->data = data;
  node->parent = prev;
  *p_node = node;
  treap->size++;
  bubble_up(treap, node);
}

bool ds_treap_search(ds_treap_t *treap, void *data)
{
  assert(treap != NULL);

  return search(treap, data) != NULL;
}

bool ds_treap_remove(ds_treap_t *treap, void *data)
{
  assert(treap != NULL);

  node_t *node = search(treap, data);
  if (node == NULL) {
    return false;
  }

  trickle_down(treap, node);
  splice(treap, node);
  node_destroy(&node);
  treap->size--;
  return true;
}
