#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_double_list.h>
}

static void BM_DoubleListPushFront(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_double_list_t *s = ds_double_list_create();
    for (size_t i = 0; i < count; i++) {
      ds_double_list_push_front(s, (void *)i);
    }
    ds_double_list_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_DoubleListPushFront)->Range(8, 32<<10)->Complexity(benchmark::oN);

static void BM_DoubleListInsertRandom(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_double_list_t *s = ds_double_list_create();
    for (size_t i = 0; i < count; i++) {
      size_t index = rand() % (i + 1);
      ds_double_list_insert(s, index, (void *)i);
    }
    ds_double_list_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_DoubleListInsertRandom)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNSquared);
