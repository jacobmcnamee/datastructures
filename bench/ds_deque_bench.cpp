#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_deque.h>
}

static void BM_DequePushBack(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_deque_t *s = ds_deque_create(1);
    for (size_t i = 0; i < count; i++) {
      ds_deque_push_back(s, (void *)i);
    }
    ds_deque_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_DequePushBack)->Range(8, 32<<10)->Complexity(benchmark::oN);

static void BM_DequePushFront(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_deque_t *s = ds_deque_create(1);
    for (size_t i = 0; i < count; i++) {
      ds_deque_push_front(s, (void *)i);
    }
    ds_deque_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_DequePushFront)->Range(8, 32<<10)->Complexity(benchmark::oN);
