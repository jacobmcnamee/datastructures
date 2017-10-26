#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_stack.h>
}

static void BM_StackPush(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_stack_t *s = ds_stack_create(1);
    for (size_t i = 0; i < count; i++) {
      ds_stack_push(s, (void *)i);
    }
    ds_stack_destroy(&s);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_StackPush)->Range(8, 32<<10)->Complexity(benchmark::oN);
