#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_heap.h>
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

static void BM_HeapInsertRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_heap_t *s = ds_heap_create(1, compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_heap_insert(s, (void *)&data[i]);
    }
    ds_heap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_HeapInsertRandom)->Range(8, 32<<10)->Complexity(benchmark::oN);

static void BM_HeapInsertReverse(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = count - i;
  }

  while (state.KeepRunning()) {
    ds_heap_t *s = ds_heap_create(1, compare_int_asc);
    for (size_t i = 0; i < count; i++) {
      ds_heap_insert(s, (void *)&data[i]);
    }
    ds_heap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_HeapInsertReverse)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNLogN);

static void BM_HeapPopRandom(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = rand();
  }

  while (state.KeepRunning()) {
    ds_heap_t *s = ds_heap_create(1, compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_heap_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_heap_pop(s);
    }
    ds_heap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_HeapPopRandom)->Range(8, 32<<10)->Complexity(benchmark::oNLogN);

static void BM_HeapPopReverse(benchmark::State &state) {
  size_t count = state.range(0);

  int *data = (int *)malloc(count * sizeof(int));
  assert(data != NULL);
  for (size_t i = 0; i < count; i++) {
    data[i] = count - i;
  }

  while (state.KeepRunning()) {
    ds_heap_t *s = ds_heap_create(1, compare_int_asc);
    state.PauseTiming();
    for (size_t i = 0; i < count; i++) {
      ds_heap_insert(s, (void *)&data[i]);
    }
    state.ResumeTiming();
    for (size_t i = 0; i < count; i++) {
      ds_heap_pop(s);
    }
    ds_heap_destroy(&s);
  }

  free(data);
  state.SetComplexityN(count);
}
BENCHMARK(BM_HeapPopReverse)->Range(8, 32<<10)->Complexity(benchmark::oNLogN);
