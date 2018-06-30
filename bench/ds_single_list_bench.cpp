#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_single_list.h>
}

static void BM_SingleListPushFront(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_single_list_t *s = ds_single_list_create();
    for (size_t i = 0; i < count; i++) {
      ds_single_list_push_front(s, (void *)i);
    }
    ds_single_list_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_SingleListPushFront)->Range(8, 32<<10)->Complexity(benchmark::oN);

static void BM_SingleListInsertRandom(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_single_list_t *s = ds_single_list_create();
    for (size_t i = 0; i < count; i++) {
      size_t index = rand() % (i + 1);
      ds_single_list_insert(s, index, (void *)i);
    }
    ds_single_list_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_SingleListInsertRandom)->Range(8, 32<<10)-> \
          Complexity(benchmark::oNSquared);
