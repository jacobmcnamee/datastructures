#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_heap.h>
}

static int compare_void(const void *a, const void *b)
{
  (void)a;
  (void)b;
  return 0;
}

static int compare_int_asc(const void *a, const void *b)
{
  int m = *(const int *)a;
  int n = *(const int *)b;
  if (m < n) {
    return -1;
  } else if (m > n) {
    return 1;
  } else {
    return 0;
  }
}

static int compare_int_desc(const void *a, const void *b)
{
  int m = *(const int *)a;
  int n = *(const int *)b;
  if (m > n) {
    return -1;
  } else if (m < n) {
    return 1;
  } else {
    return 0;
  }
}

TEST(Heap, CreateDestroy)
{
  ds_heap_t *s = ds_heap_create(1000, compare_void);
  ASSERT_TRUE(s != NULL);
  ds_heap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Heap, InsertPopAsc)
{
  const int data_unsorted[] = { 3, 7, 4, 1, 2, 9, 6 };
  const int data_sorted[] = { 1, 2, 3, 4, 6, 7, 9 };
  const size_t size = sizeof(data_unsorted) / sizeof(data_unsorted[0]);

  ds_heap_t *s = ds_heap_create(1000, compare_int_asc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < size; i++) {
    ds_heap_insert(s, (void *)&data_unsorted[i]);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(*(const int *)ds_heap_pop(s), data_sorted[i]);
  }

  ds_heap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Heap, InsertPopDesc)
{
  const int data_unsorted[] = { 3, 7, 4, 1, 2, 9, 6 };
  const int data_sorted[] = { 9, 7, 6, 4, 3, 2, 1 };
  const size_t size = sizeof(data_unsorted) / sizeof(data_unsorted[0]);

  ds_heap_t *s = ds_heap_create(1000, compare_int_desc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < size; i++) {
    ds_heap_insert(s, (void *)&data_unsorted[i]);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(*(const int *)ds_heap_pop(s), data_sorted[i]);
  }

  ds_heap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Heap, Empty)
{
  ds_heap_t *s = ds_heap_create(1000, compare_void);
  EXPECT_TRUE(ds_heap_empty(s));
  ds_heap_insert(s, (void *)1);
  EXPECT_FALSE(ds_heap_empty(s));
  ds_heap_insert(s, (void *)1);
  EXPECT_FALSE(ds_heap_empty(s));
  ds_heap_pop(s);
  EXPECT_FALSE(ds_heap_empty(s));
  ds_heap_pop(s);
  EXPECT_TRUE(ds_heap_empty(s));
  ds_heap_destroy(&s);
}

TEST(Heap, Size)
{
  const size_t size = 17;
  ds_heap_t *s = ds_heap_create(size, compare_void);

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_heap_size(s), i);
    ds_heap_insert(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_heap_size(s), size - i);
    ds_heap_pop(s);
  }

  EXPECT_EQ(ds_heap_size(s), 0);
  ds_heap_destroy(&s);
}

TEST(Heap, InsertPopResize)
{
  const int data_unsorted[] = { 3, 7, 4, 1, 2, 9, 6 };
  const int data_sorted[] = { 1, 2, 3, 4, 6, 7, 9 };
  const size_t size = sizeof(data_unsorted) / sizeof(data_unsorted[0]);

  ds_heap_t *s = ds_heap_create(size / 3, compare_int_asc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < size; i++) {
    ds_heap_insert(s, (void *)&data_unsorted[i]);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(*(const int *)ds_heap_pop(s), data_sorted[i]);
  }

  ds_heap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}
