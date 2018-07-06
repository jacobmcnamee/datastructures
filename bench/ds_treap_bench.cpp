#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_treap.h>
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

static void BM_TreapInsertRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_treap_t *s = ds_treap_create(compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_treap_insert(s, (void *)&data[i]);
    }
    ds_treap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_TreapInsertRandom)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNLogN);

static void BM_TreapInsertOrdered(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = i;
  }

  while (state.KeepRunning()) {
    ds_treap_t *s = ds_treap_create(compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_treap_insert(s, (void *)&data[i]);
    }
    ds_treap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_TreapInsertOrdered)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNLogN);

static void BM_TreapRemoveRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_treap_t *s = ds_treap_create(compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_treap_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_treap_remove(s, (void *)&data[count - 1 - i]);
    }
    ds_treap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_TreapRemoveRandom)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNLogN);

static void BM_TreapRemoveOrdered(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = i;
  }

  while (state.KeepRunning()) {
    ds_treap_t *s = ds_treap_create(compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_treap_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_treap_remove(s, (void *)&data[count - 1 - i]);
    }
    ds_treap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_TreapRemoveOrdered)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNLogN);
