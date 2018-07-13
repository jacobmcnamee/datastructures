#include <gtest/gtest.h>

extern "C" {
#include <datastructures/ds_segment_tree.h>
}

static void operate_void(const void *a, const void *b, void *result)
{
  (void)a;
  (void)b;
  (void)result;
}

static void operate_int_sum(const void *a, const void *b, void *result)
{
  int m = *(const int *)a;
  int n = *(const int *)b;
  *(int *)result = m + n;
}

static void operate_int_max(const void *a, const void *b, void *result)
{
  int m = *(const int *)a;
  int n = *(const int *)b;
  *(int *)result = m > n ? m : n;
}

TEST(SegmentTree, CreateDestroy)
{
  const int data[] = { 1, 3, 5, 7, 9 };
  const size_t data_length = sizeof(data) / sizeof(data[0]);
  const size_t data_element_size = sizeof(data[0]);
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, data_length,
                                                data_element_size,
                                                operate_void);
  ASSERT_TRUE(s != NULL);
  ds_segment_tree_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(SegmentTree, QuerySum)
{
  const int data[] = { -1, 3, 12, 7, 0, 4, 2 };
  const size_t data_length = sizeof(data) / sizeof(data[0]);
  const size_t data_element_size = sizeof(data[0]);
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, data_length,
                                                data_element_size,
                                                operate_int_sum);
  ASSERT_TRUE(s != NULL);

  for (size_t left = 0; left < data_length; left++) {
    for (size_t right = left; right < data_length; right++) {

      int sum = 0;
      for (size_t i = left; i <= right; i++) {
        sum += data[i];
      }

      int result;
      ds_segment_tree_query(s, left, right, (void *)&result);
      EXPECT_EQ(result, sum);
    }
  }

  ds_segment_tree_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(SegmentTree, QueryMax)
{
  const int data[] = { 1, -3, 5, 6, 10, 9 };
  const size_t data_length = sizeof(data) / sizeof(data[0]);
  const size_t data_element_size = sizeof(data[0]);
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, data_length,
                                                data_element_size,
                                                operate_int_max);
  ASSERT_TRUE(s != NULL);

  for (size_t left = 0; left < data_length; left++) {
    for (size_t right = left; right < data_length; right++) {

      int max = INT_MIN;
      for (size_t i = left; i <= right; i++) {
        if (data[i] > max) {
          max = data[i];
        }
      }

      int result;
      ds_segment_tree_query(s, left, right, (void *)&result);
      EXPECT_EQ(result, max);
    }
  }

  ds_segment_tree_destroy(&s);
  ASSERT_TRUE(s == NULL);
}

TEST(SegmentTree, ModifySum)
{
  int data[] = { -1, 3, 12, 7, 0, 4, 2 };
  const size_t data_length = sizeof(data) / sizeof(data[0]);
  const size_t data_element_size = sizeof(data[0]);
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, data_length,
                                                data_element_size,
                                                operate_int_sum);
  ASSERT_TRUE(s != NULL);

  for (size_t left = 0; left < data_length; left++) {
    for (size_t right = left; right < data_length; right++) {

      size_t k = left + (right - left) / 2;
      data[k]++;
      ds_segment_tree_modify(s, k, (void *)&data[k]);

      int sum = 0;
      for (size_t i = left; i <= right; i++) {
        sum += data[i];
      }

      int result;
      ds_segment_tree_query(s, left, right, (void *)&result);
      EXPECT_EQ(result, sum);
    }
  }

  ds_segment_tree_destroy(&s);
  ASSERT_TRUE(s == NULL);
}
