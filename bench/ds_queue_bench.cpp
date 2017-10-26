#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_queue.h>
}

static void BM_QueuePush(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_queue_t *s = ds_queue_create(1);
    for (size_t i = 0; i < count; i++) {
      ds_queue_push(s, (void *)i);
    }
    ds_queue_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_QueuePush)->Range(8, 32<<10)->Complexity(benchmark::oN);
