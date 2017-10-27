#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_single_list.h>
}

TEST(SingleList, CreateDestroy)
{
  ds_single_list_t *s = ds_single_list_create();
  ASSERT_TRUE(s != NULL);
  ds_single_list_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(SingleList, PushPop)
{
  ds_single_list_t *s = ds_single_list_create();

  const size_t size = 123;
  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_single_list_push_front(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_single_list_pop_front(s), (void *)i);
  }

  ds_single_list_destroy(&s);
}

TEST(SingleList, Empty)
{
  ds_single_list_t *s = ds_single_list_create();
  EXPECT_TRUE(ds_single_list_empty(s));
  ds_single_list_push_front(s, (void *)1);
  EXPECT_FALSE(ds_single_list_empty(s));
  ds_single_list_push_front(s, (void *)1);
  EXPECT_FALSE(ds_single_list_empty(s));
  ds_single_list_pop_front(s);
  EXPECT_FALSE(ds_single_list_empty(s));
  ds_single_list_pop_front(s);
  EXPECT_TRUE(ds_single_list_empty(s));
  ds_single_list_destroy(&s);
}

TEST(SingleList, Size)
{
  ds_single_list_t *s = ds_single_list_create();

  const size_t size = 17;
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_single_list_size(s), i);
    ds_single_list_push_front(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_single_list_size(s), size - i);
    ds_single_list_pop_front(s);
  }

  EXPECT_EQ(ds_single_list_size(s), 0);
  ds_single_list_destroy(&s);
}

TEST(SingleList, Insert)
{
  ds_single_list_t *s = ds_single_list_create();

  ds_single_list_insert(s, 0, (void *)1);
  ds_single_list_insert(s, 0, (void *)2);
  ds_single_list_insert(s, 1, (void *)3);
  ds_single_list_insert(s, 3, (void *)4);
  ds_single_list_insert(s, 3, (void *)5);

  EXPECT_EQ(ds_single_list_pop_front(s), (void *)2);
  EXPECT_EQ(ds_single_list_pop_front(s), (void *)3);
  EXPECT_EQ(ds_single_list_pop_front(s), (void *)1);
  EXPECT_EQ(ds_single_list_pop_front(s), (void *)5);
  EXPECT_EQ(ds_single_list_pop_front(s), (void *)4);

  ds_single_list_destroy(&s);
}

TEST(SingleList, Remove)
{
  ds_single_list_t *s = ds_single_list_create();

  ds_single_list_push_front(s, (void *)5);
  ds_single_list_push_front(s, (void *)4);
  ds_single_list_push_front(s, (void *)3);
  ds_single_list_push_front(s, (void *)2);
  ds_single_list_push_front(s, (void *)1);

  EXPECT_EQ(ds_single_list_remove(s, 0), (void *)1);
  EXPECT_EQ(ds_single_list_remove(s, 0), (void *)2);
  EXPECT_EQ(ds_single_list_remove(s, 2), (void *)5);
  EXPECT_EQ(ds_single_list_remove(s, 1), (void *)4);
  EXPECT_EQ(ds_single_list_remove(s, 0), (void *)3);

  ds_single_list_destroy(&s);
}

TEST(SingleList, Get)
{
  ds_single_list_t *s = ds_single_list_create();

  ds_single_list_push_front(s, (void *)5);
  ds_single_list_push_front(s, (void *)4);
  ds_single_list_push_front(s, (void *)3);
  ds_single_list_push_front(s, (void *)2);
  ds_single_list_push_front(s, (void *)1);

  EXPECT_EQ(ds_single_list_get(s, 2), (void *)3);
  EXPECT_EQ(ds_single_list_get(s, 1), (void *)2);
  EXPECT_EQ(ds_single_list_get(s, 4), (void *)5);
  EXPECT_EQ(ds_single_list_get(s, 3), (void *)4);
  EXPECT_EQ(ds_single_list_get(s, 0), (void *)1);

  ds_single_list_destroy(&s);
}

TEST(SingleList, Iterate)
{
  ds_single_list_t *s = ds_single_list_create();

  ds_single_list_push_front(s, (void *)3);
  ds_single_list_push_front(s, (void *)4);
  ds_single_list_push_front(s, (void *)1);
  ds_single_list_push_front(s, (void *)5);
  ds_single_list_push_front(s, (void *)2);

  ds_single_list_iterate_begin(s);
  EXPECT_EQ(ds_single_list_iterate_next(s), (void *)2);
  EXPECT_EQ(ds_single_list_iterate_next(s), (void *)5);
  EXPECT_EQ(ds_single_list_iterate_next(s), (void *)1);
  EXPECT_EQ(ds_single_list_iterate_next(s), (void *)4);
  EXPECT_EQ(ds_single_list_iterate_next(s), (void *)3);

  ds_single_list_destroy(&s);
}
