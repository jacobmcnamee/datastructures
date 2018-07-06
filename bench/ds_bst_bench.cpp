#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_bst.h>
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

static void BM_BSTInsertRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_bst_t *s = ds_bst_create(compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_bst_insert(s, (void *)&data[i]);
    }
    ds_bst_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_BSTInsertRandom)->Range(8, 32<<10)->Complexity(benchmark::oNLogN);

static void BM_BSTInsertOrdered(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = i;
  }

  while (state.KeepRunning()) {
    ds_bst_t *s = ds_bst_create(compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_bst_insert(s, (void *)&data[i]);
    }
    ds_bst_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_BSTInsertOrdered)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNSquared);

static void BM_BSTRemoveRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_bst_t *s = ds_bst_create(compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_bst_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_bst_remove(s, (void *)&data[count - 1 - i]);
    }
    ds_bst_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_BSTRemoveRandom)->Range(8, 32<<10)->Complexity(benchmark::oNLogN);

static void BM_BSTRemoveOrdered(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = i;
  }

  while (state.KeepRunning()) {
    ds_bst_t *s = ds_bst_create(compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_bst_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_bst_remove(s, (void *)&data[count - 1 - i]);
    }
    ds_bst_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_BSTRemoveOrdered)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNSquared);
