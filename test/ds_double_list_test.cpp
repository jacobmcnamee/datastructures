#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_double_list.h>
}

TEST(DoubleList, CreateDestroy)
{
  ds_double_list_t *s = ds_double_list_create();
  ASSERT_TRUE(s != NULL);
  ds_double_list_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(DoubleList, PushFrontPopFront)
{
  ds_double_list_t *s = ds_double_list_create();

  const size_t size = 123;
  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_double_list_push_front(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_double_list_pop_front(s), (void *)i);
  }

  ds_double_list_destroy(&s);
}

TEST(DoubleList, PushBackPopBack)
{
  ds_double_list_t *s = ds_double_list_create();

  const size_t size = 123;
  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_double_list_push_back(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_double_list_pop_back(s), (void *)i);
  }

  ds_double_list_destroy(&s);
}

TEST(DoubleList, PushFrontPopBack)
{
  ds_double_list_t *s = ds_double_list_create();

  const size_t size = 123;
  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_double_list_push_front(s, (void *)i);
  }
  for (size_t i = offset; i < offset + size; i++) {
    EXPECT_EQ(ds_double_list_pop_back(s), (void *)i);
  }

  ds_double_list_destroy(&s);
}

TEST(DoubleList, PushBackPopFront)
{
  ds_double_list_t *s = ds_double_list_create();

  const size_t size = 123;
  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_double_list_push_back(s, (void *)i);
  }
  for (size_t i = offset; i < offset + size; i++) {
    EXPECT_EQ(ds_double_list_pop_front(s), (void *)i);
  }

  ds_double_list_destroy(&s);
}

TEST(DoubleList, PushPopMix)
{
  ds_double_list_t *s = ds_double_list_create();
  ds_double_list_push_back(s, (void *)1);
  ds_double_list_push_back(s, (void *)2);
  ds_double_list_push_front(s, (void *)3);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)2);
  EXPECT_EQ(ds_double_list_pop_front(s), (void *)3);
  EXPECT_EQ(ds_double_list_pop_front(s), (void *)1);
  ds_double_list_push_front(s, (void *)4);
  ds_double_list_push_back(s, (void *)5);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)5);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)4);
  ds_double_list_destroy(&s);
}

TEST(DoubleList, Empty)
{
  ds_double_list_t *s = ds_double_list_create();
  EXPECT_TRUE(ds_double_list_empty(s));
  ds_double_list_push_back(s, (void *)1);
  EXPECT_FALSE(ds_double_list_empty(s));
  ds_double_list_push_back(s, (void *)1);
  EXPECT_FALSE(ds_double_list_empty(s));
  ds_double_list_pop_front(s);
  EXPECT_FALSE(ds_double_list_empty(s));
  ds_double_list_pop_front(s);
  EXPECT_TRUE(ds_double_list_empty(s));
  ds_double_list_destroy(&s);
}

TEST(DoubleList, Size)
{
  ds_double_list_t *s = ds_double_list_create();

  const size_t size = 17;
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_double_list_size(s), i);
    ds_double_list_push_back(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_double_list_size(s), size - i);
    ds_double_list_pop_front(s);
  }

  EXPECT_EQ(ds_double_list_size(s), 0);
  ds_double_list_destroy(&s);
}

TEST(DoubleList, Insert)
{
  ds_double_list_t *s = ds_double_list_create();

  ds_double_list_insert(s, 0, (void *)1);
  ds_double_list_insert(s, 0, (void *)2);
  ds_double_list_insert(s, 1, (void *)3);
  ds_double_list_insert(s, 3, (void *)4);
  ds_double_list_insert(s, 3, (void *)5);
  ds_double_list_insert(s, 5, (void *)6);

  EXPECT_EQ(ds_double_list_pop_front(s), (void *)2);
  EXPECT_EQ(ds_double_list_pop_front(s), (void *)3);
  EXPECT_EQ(ds_double_list_pop_front(s), (void *)1);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)6);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)4);
  EXPECT_EQ(ds_double_list_pop_back(s), (void *)5);

  ds_double_list_destroy(&s);
}

TEST(DoubleList, Remove)
{
  ds_double_list_t *s = ds_double_list_create();

  ds_double_list_push_front(s, (void *)5);
  ds_double_list_push_front(s, (void *)4);
  ds_double_list_push_front(s, (void *)3);
  ds_double_list_push_front(s, (void *)2);
  ds_double_list_push_front(s, (void *)1);

  EXPECT_EQ(ds_double_list_remove(s, 0), (void *)1);
  EXPECT_EQ(ds_double_list_remove(s, 0), (void *)2);
  EXPECT_EQ(ds_double_list_remove(s, 2), (void *)5);
  EXPECT_EQ(ds_double_list_remove(s, 1), (void *)4);
  EXPECT_EQ(ds_double_list_remove(s, 0), (void *)3);

  ds_double_list_destroy(&s);
}

TEST(DoubleList, Get)
{
  ds_double_list_t *s = ds_double_list_create();

  ds_double_list_push_front(s, (void *)5);
  ds_double_list_push_front(s, (void *)4);
  ds_double_list_push_front(s, (void *)3);
  ds_double_list_push_front(s, (void *)2);
  ds_double_list_push_front(s, (void *)1);

  EXPECT_EQ(ds_double_list_get(s, 2), (void *)3);
  EXPECT_EQ(ds_double_list_get(s, 1), (void *)2);
  EXPECT_EQ(ds_double_list_get(s, 4), (void *)5);
  EXPECT_EQ(ds_double_list_get(s, 3), (void *)4);
  EXPECT_EQ(ds_double_list_get(s, 0), (void *)1);

  ds_double_list_destroy(&s);
}

TEST(DoubleList, IterateForward)
{
  ds_double_list_t *s = ds_double_list_create();

  ds_double_list_push_front(s, (void *)3);
  ds_double_list_push_front(s, (void *)4);
  ds_double_list_push_front(s, (void *)1);
  ds_double_list_push_front(s, (void *)5);
  ds_double_list_push_front(s, (void *)2);

  ds_double_list_iterate_forward_begin(s);
  EXPECT_EQ(ds_double_list_iterate_forward_next(s), (void *)2);
  EXPECT_EQ(ds_double_list_iterate_forward_next(s), (void *)5);
  EXPECT_EQ(ds_double_list_iterate_forward_next(s), (void *)1);
  EXPECT_EQ(ds_double_list_iterate_forward_next(s), (void *)4);
  EXPECT_EQ(ds_double_list_iterate_forward_next(s), (void *)3);

  ds_double_list_destroy(&s);
}

TEST(DoubleList, IterateReverse)
{
  ds_double_list_t *s = ds_double_list_create();

  ds_double_list_push_front(s, (void *)3);
  ds_double_list_push_front(s, (void *)4);
  ds_double_list_push_front(s, (void *)1);
  ds_double_list_push_front(s, (void *)5);
  ds_double_list_push_front(s, (void *)2);

  ds_double_list_iterate_reverse_begin(s);
  EXPECT_EQ(ds_double_list_iterate_reverse_next(s), (void *)3);
  EXPECT_EQ(ds_double_list_iterate_reverse_next(s), (void *)4);
  EXPECT_EQ(ds_double_list_iterate_reverse_next(s), (void *)1);
  EXPECT_EQ(ds_double_list_iterate_reverse_next(s), (void *)5);
  EXPECT_EQ(ds_double_list_iterate_reverse_next(s), (void *)2);

  ds_double_list_destroy(&s);
}
