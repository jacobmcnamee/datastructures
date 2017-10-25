#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_queue.h>
}

TEST(Queue, CreateDestroy)
{
  ds_queue_t *s = ds_queue_create(1000);
  ASSERT_TRUE(s != NULL);
  ds_queue_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Queue, PushPop)
{
  const size_t size = 123;
  ds_queue_t *s = ds_queue_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_queue_push(s, (void *)i);
  }
  for (size_t i = offset; i < offset + size; i++) {
    EXPECT_EQ(ds_queue_pop(s), (void *)i);
  }

  ds_queue_destroy(&s);
}

TEST(Queue, Empty)
{
  ds_queue_t *s = ds_queue_create(1000);
  EXPECT_TRUE(ds_queue_empty(s));
  ds_queue_push(s, (void *)1);
  EXPECT_FALSE(ds_queue_empty(s));
  ds_queue_push(s, (void *)1);
  EXPECT_FALSE(ds_queue_empty(s));
  ds_queue_pop(s);
  EXPECT_FALSE(ds_queue_empty(s));
  ds_queue_pop(s);
  EXPECT_TRUE(ds_queue_empty(s));
  ds_queue_destroy(&s);
}

TEST(Queue, Size)
{
  const size_t size = 17;
  ds_queue_t *s = ds_queue_create(size);

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_queue_size(s), i);
    ds_queue_push(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_queue_size(s), size - i);
    ds_queue_pop(s);
  }

  EXPECT_EQ(ds_queue_size(s), 0);
  ds_queue_destroy(&s);
}

TEST(Queue, PushPopResize)
{
  const size_t size = 123;
  ds_queue_t *s = ds_queue_create(size);

  const size_t offset = 1000;
  const size_t count = 3 * size;
  for (size_t i = offset; i < offset + count; i++) {
    ds_queue_push(s, (void *)i);
  }
  for (size_t i = offset; i < offset + count; i++) {
    EXPECT_EQ(ds_queue_pop(s), (void *)i);
  }

  EXPECT_GE(ds_queue_capacity(s), count);

  ds_queue_destroy(&s);
}
