#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_treap.h>
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

TEST(Treap, CreateDestroy)
{
  ds_treap_t *s = ds_treap_create(compare_void);
  ASSERT_TRUE(s != NULL);
  ds_treap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Treap, InsertSearch)
{
  const int insert_data[] = { 3, 7, 4, 1, 2, 9, 6 };
  const size_t insert_data_size = sizeof(insert_data) / sizeof(insert_data[0]);
  const int other_data[] = { 8, 0, 10, 5 };
  const size_t other_data_size = sizeof(other_data) / sizeof(other_data[0]);

  ds_treap_t *s = ds_treap_create(compare_int_asc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < insert_data_size; i++) {
    ds_treap_insert(s, (void *)&insert_data[i]);
  }
  for (size_t i = 0; i < other_data_size; i++) {
    EXPECT_FALSE(ds_treap_search(s, (void *)&other_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_TRUE(ds_treap_search(s, (void *)&insert_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_TRUE(ds_treap_search(s, (void *)&insert_data[i]));
  }

  ds_treap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Treap, InsertRemove)
{
  const int insert_data[] = { 3, 7, 4, 1, 2, 9, 6 };
  const size_t insert_data_size = sizeof(insert_data) / sizeof(insert_data[0]);
  const int other_data[] = { 8, 0, 10, 5 };
  const size_t other_data_size = sizeof(other_data) / sizeof(other_data[0]);

  ds_treap_t *s = ds_treap_create(compare_int_asc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < insert_data_size; i++) {
    ds_treap_insert(s, (void *)&insert_data[i]);
  }
  for (size_t i = 0; i < other_data_size; i++) {
    EXPECT_FALSE(ds_treap_remove(s, (void *)&other_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_TRUE(ds_treap_remove(s, (void *)&insert_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_FALSE(ds_treap_remove(s, (void *)&insert_data[i]));
  }

  ds_treap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Treap, InsertRemoveDup)
{
  const int insert_data[] = { 3, 7, 4, 1, 2, 9, 6, 1, 1, 3, 9, 3 };
  const size_t insert_data_size = sizeof(insert_data) / sizeof(insert_data[0]);
  const int other_data[] = { 8, 0, 10, 5 };
  const size_t other_data_size = sizeof(other_data) / sizeof(other_data[0]);

  ds_treap_t *s = ds_treap_create(compare_int_asc);
  ASSERT_TRUE(s != NULL);

  for (size_t i = 0; i < insert_data_size; i++) {
    ds_treap_insert(s, (void *)&insert_data[i]);
  }
  for (size_t i = 0; i < other_data_size; i++) {
    EXPECT_FALSE(ds_treap_remove(s, (void *)&other_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_TRUE(ds_treap_remove(s, (void *)&insert_data[i]));
  }
  for (size_t i = 0; i < insert_data_size; i++) {
    EXPECT_FALSE(ds_treap_remove(s, (void *)&insert_data[i]));
  }

  ds_treap_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Treap, Empty)
{
  ds_treap_t *s = ds_treap_create(compare_void);
  EXPECT_TRUE(ds_treap_empty(s));
  ds_treap_insert(s, (void *)1);
  EXPECT_FALSE(ds_treap_empty(s));
  ds_treap_insert(s, (void *)1);
  EXPECT_FALSE(ds_treap_empty(s));
  ds_treap_remove(s, (void *)1);
  EXPECT_FALSE(ds_treap_empty(s));
  ds_treap_remove(s, (void *)1);
  EXPECT_TRUE(ds_treap_empty(s));
  ds_treap_destroy(&s);
}

TEST(Treap, Size)
{
  const size_t size = 17;
  ds_treap_t *s = ds_treap_create(compare_void);

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_treap_size(s), i);
    ds_treap_insert(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_treap_size(s), size - i);
    ds_treap_remove(s, (void *)1);
  }

  EXPECT_EQ(ds_treap_size(s), 0);
  ds_treap_destroy(&s);
}
