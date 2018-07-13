#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_segment_tree.h>
}

static void operate_int_sum(const void *a, const void *b, void *result)
{
  int m = *(const int *)a;
  int n = *(const int *)b;
  *(int *)result = m + n;
}

static void BM_SegmentTreeCreate(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_segment_tree_t *s = ds_segment_tree_create((void *)data, count,
                                                  sizeof(int),
                                                  operate_int_sum);
    ds_segment_tree_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_SegmentTreeCreate)->Range(8, 32<<10)->Complexity(benchmark::oN);

static void BM_SegmentTreeQuery(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, count,
                                                sizeof(int),
                                                operate_int_sum);

  while (state.KeepRunning()) {
    size_t a = rand() % count;
    size_t b = rand() % count;
    size_t left = a < b ? a : b;
    size_t right = a < b ? b : a;

    int result;
    ds_segment_tree_query(s, left, right, (void *)&result);
  }

  ds_segment_tree_destroy(&s);
  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_SegmentTreeQuery)->Range(4<<10, 8<<20)-> \
          Complexity(benchmark::oLogN);

static void BM_SegmentTreeModify(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }
  ds_segment_tree_t *s = ds_segment_tree_create((void *)data, count,
                                                sizeof(int),
                                                operate_int_sum);

  while (state.KeepRunning()) {
    size_t i = rand() % count;
    data[i] = rand();

    ds_segment_tree_modify(s, i, (void *)&data[i]);
  }

  ds_segment_tree_destroy(&s);
  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_SegmentTreeModify)->Range(4<<10, 8<<20)-> \
          Complexity(benchmark::oLogN);
