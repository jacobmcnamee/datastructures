#include <datastructures/common.h>
#include <datastructures/ds_bst.h>

typedef struct node_s {
  void *data;
  struct node_s *left;
  struct node_s *right;
  struct node_s *parent;
} node_t;

struct ds_bst_s {
  node_t *root;
  size_t size;
  int (*compare)(const void *a, const void *b);
};

static node_t *node_create(void)
{
  node_t *node = (node_t *)malloc(sizeof(*node));
  assert(node != NULL);

  node->data = NULL;
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

static node_t *search(ds_bst_t *bst, void *data)
{
  node_t *node = bst->root;
  while (node != NULL) {
    int compare_result = bst->compare(data, node->data);
    if (compare_result == 0) {
      return node;
    }
    node = (compare_result < 0) ? node->left : node->right;
  }

  return NULL;
}

static void splice(ds_bst_t *bst, node_t *node)
{
  node_t *child = (node->left != NULL) ? node->left : node->right;
  node_t *parent = node->parent;

  node_t **p_next;
  if (parent == NULL) {
    p_next = &bst->root;
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

ds_bst_t *ds_bst_create(int (*compare)(const void *a, const void *b))
{
  assert(compare != NULL);

  ds_bst_t *bst = (ds_bst_t *)malloc(sizeof(*bst));
  assert(bst != NULL);

  bst->root = NULL;
  bst->size = 0;
  bst->compare = compare;

  return bst;
}

void ds_bst_destroy(ds_bst_t **bst)
{
  assert(bst != NULL);
  assert(*bst != NULL);

  node_t *node = (*bst)->root;
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
  (*bst)->root = NULL;

  free(*bst);
  *bst = NULL;
}

bool ds_bst_empty(ds_bst_t *bst)
{
  assert(bst != NULL);

  return (bst->size == 0);
}

size_t ds_bst_size(ds_bst_t *bst)
{
  assert(bst != NULL);

  return bst->size;
}

void ds_bst_insert(ds_bst_t *bst, void *data)
{
  assert(bst != NULL);

  node_t **p_node = &bst->root;
  node_t *prev = NULL;
  while (*p_node != NULL) {
    prev = *p_node;
    if(bst->compare(data, (*p_node)->data) <= 0) {
      p_node = &(*p_node)->left;
    } else {
      p_node = &(*p_node)->right;
    }
  }

  node_t *node = node_create();
  node->data = data;
  node->parent = prev;
  *p_node = node;
  bst->size++;
}

bool ds_bst_search(ds_bst_t *bst, void *data)
{
  assert(bst != NULL);

  return search(bst, data) != NULL;
}

bool ds_bst_remove(ds_bst_t *bst, void *data)
{
  assert(bst != NULL);

  node_t *node = search(bst, data);
  if (node == NULL) {
    return false;
  }

  if ((node->left != NULL) && (node->right != NULL)) {
    node_t *next = node->right;
    while (next->left != NULL) {
      next = next->left;
    }
    node->data = next->data;
    splice(bst, next);
    node_destroy(&next);
  } else {
    splice(bst, node);
    node_destroy(&node);
  }

  bst->size--;
  return true;
}
