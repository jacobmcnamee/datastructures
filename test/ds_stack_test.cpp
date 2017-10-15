#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_stack.h>
}

TEST(Stack, CreateDestroy)
{
  ds_stack_t *s = ds_stack_create(1000);
  ASSERT_TRUE(s != NULL);
  ds_stack_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(Stack, PushPop)
{
  const size_t size = 123;
  ds_stack_t *s = ds_stack_create(size);

  const size_t offset = 1000;
  for (size_t i = offset; i < offset + size; i++) {
    ds_stack_push(s, (void *)i);
  }
  for (size_t i = offset + size - 1; i >= offset; i--) {
    EXPECT_EQ(ds_stack_pop(s), (void *)i);
  }

  ds_stack_destroy(&s);
}

TEST(Stack, Empty)
{
  ds_stack_t *s = ds_stack_create(1000);
  EXPECT_TRUE(ds_stack_empty(s));
  ds_stack_push(s, (void *)1);
  EXPECT_FALSE(ds_stack_empty(s));
  ds_stack_push(s, (void *)1);
  EXPECT_FALSE(ds_stack_empty(s));
  ds_stack_pop(s);
  EXPECT_FALSE(ds_stack_empty(s));
  ds_stack_pop(s);
  EXPECT_TRUE(ds_stack_empty(s));
  ds_stack_destroy(&s);
}

TEST(Stack, Size)
{
  const size_t size = 17;
  ds_stack_t *s = ds_stack_create(size);

  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_stack_size(s), i);
    ds_stack_push(s, (void *)1);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_stack_size(s), size - i);
    ds_stack_pop(s);
  }

  EXPECT_EQ(ds_stack_size(s), 0);
  ds_stack_destroy(&s);
}

TEST(Stack, PushPopResize)
{
  const size_t size = 123;
  ds_stack_t *s = ds_stack_create(size);

  const size_t offset = 1000;
  const size_t count = 3 * size;
  for (size_t i = offset; i < offset + count; i++) {
    ds_stack_push(s, (void *)i);
  }
  for (size_t i = offset + count - 1; i >= offset; i--) {
    EXPECT_EQ(ds_stack_pop(s), (void *)i);
  }

  EXPECT_GE(ds_stack_capacity(s), count);

  ds_stack_destroy(&s);
}
