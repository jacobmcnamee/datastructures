#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_array.h>
}

TEST(Array, CreateDestroy)
{
  ds_array_t *a = ds_array_create(1000);
  ASSERT_TRUE(a != NULL);
  ds_array_destroy(&a);
  ASSERT_TRUE(a == NULL);
}

TEST(Array, Capacity)
{
  const size_t size = 1234;
  ds_array_t *a = ds_array_create(size);
  EXPECT_EQ(ds_array_capacity(a), size);
  ds_array_destroy(&a);
}

TEST(Array, Resize)
{
  size_t size = 1234;
  ds_array_t *a = ds_array_create(size);
  EXPECT_EQ(ds_array_capacity(a), size);

  size = 4567;
  ds_array_resize(a, size);
  EXPECT_EQ(ds_array_capacity(a), size);

  size = 333;
  ds_array_resize(a, size);
  EXPECT_EQ(ds_array_capacity(a), size);

  ds_array_destroy(&a);
}

TEST(Array, GetSet)
{
  const size_t size = 1000;
  ds_array_t *a = ds_array_create(size);
  for (size_t i = 0; i < size; i++) {
    ds_array_set(a, i, (void *)(1234 + i));
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_array_get(a, i), (void *)(1234 + i));
  }
  ds_array_destroy(&a);
}

TEST(Array, GetSetResize)
{
  const size_t size = 1000;
  ds_array_t *a = ds_array_create(size);
  for (size_t i = 0; i < size; i++) {
    ds_array_set(a, i, (void *)(1234 + i));
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_array_get(a, i), (void *)(1234 + i));
  }

  ds_array_resize(a, 3 * size);
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ds_array_get(a, i), (void *)(1234 + i));
  }
  ds_array_destroy(&a);
}
