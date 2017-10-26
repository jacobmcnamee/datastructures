#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_deque.h>
}

TEST(Deque, CreateDestroy)
{
  ds_deque_t *s = ds_deque_create(1000);
  ASSERT_TRUE(s != NULL);
  ds_deque_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Deque, PushBackPopFront)
{
  const size_t size = 123;
  ds_deque_t *s = ds_deque_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_deque_push_back(s, (void *)i);
  }
  for (size_t i = offset; i < offset + size; i++) {
    EXPECT_EQ(ds_deque_pop_front(s), (void *)i);
  }

  ds_deque_destroy(&s);
}

TEST(Deque, PushFrontPopBack)
{
  const size_t size = 123;
  ds_deque_t *s = ds_deque_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_deque_push_front(s, (void *)i);
  }
  for (size_t i = offset; i < offset + size; i++) {
    EXPECT_EQ(ds_deque_pop_back(s), (void *)i);
  }

  ds_deque_destroy(&s);
}

TEST(Deque, PushFrontPopFront)
{
  const size_t size = 123;
  ds_deque_t *s = ds_deque_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_deque_push_front(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_deque_pop_front(s), (void *)i);
  }

  ds_deque_destroy(&s);
}

TEST(Deque, PushBackPopBack)
{
  const size_t size = 123;
  ds_deque_t *s = ds_deque_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_deque_push_back(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_deque_pop_back(s), (void *)i);
  }

  ds_deque_destroy(&s);
}

TEST(Deque, PushPopMix)
{
  ds_deque_t *s = ds_deque_create(1000);
  ds_deque_push_back(s, (void *)1);
  ds_deque_push_back(s, (void *)2);
  ds_deque_push_front(s, (void *)3);
  EXPECT_EQ(ds_deque_pop_back(s), (void *)2);
  EXPECT_EQ(ds_deque_pop_front(s), (void *)3);
  EXPECT_EQ(ds_deque_pop_front(s), (void *)1);
  ds_deque_push_front(s, (void *)4);
  ds_deque_push_back(s, (void *)5);
  EXPECT_EQ(ds_deque_pop_back(s), (void *)5);
  EXPECT_EQ(ds_deque_pop_back(s), (void *)4);
  ds_deque_destroy(&s);
}

TEST(Deque, Empty)
{
  ds_deque_t *s = ds_deque_create(1000);
  EXPECT_TRUE(ds_deque_empty(s));
  ds_deque_push_back(s, (void *)1);
  EXPECT_FALSE(ds_deque_empty(s));
  ds_deque_push_back(s, (void *)1);
  EXPECT_FALSE(ds_deque_empty(s));
  ds_deque_pop_front(s);
  EXPECT_FALSE(ds_deque_empty(s));
  ds_deque_pop_front(s);
  EXPECT_TRUE(ds_deque_empty(s));
  ds_deque_destroy(&s);
}

TEST(Deque, Size)
{
  const size_t size = 17;
  ds_deque_t *s = ds_deque_create(size);

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_deque_size(s), i);
    ds_deque_push_back(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_deque_size(s), size - i);
    ds_deque_pop_front(s);
  }

  EXPECT_EQ(ds_deque_size(s), 0);
  ds_deque_destroy(&s);
}

TEST(Deque, PushPopResize)
{
  const size_t size = 123;
  ds_deque_t *s = ds_deque_create(size);

  const size_t offset = 1000;
  const size_t count = 3 * size;
  for (size_t i = offset; i < offset + count; i++) {
    ds_deque_push_back(s, (void *)i);
  }
  for (size_t i = offset; i < offset + count; i++) {
    EXPECT_EQ(ds_deque_pop_front(s), (void *)i);
  }

  EXPECT_GE(ds_deque_capacity(s), count);

  ds_deque_destroy(&s);
}
