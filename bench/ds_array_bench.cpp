#include <benchmark/benchmark.h>

extern "C" {
#include <datastructures/ds_array.h>
}

static void BM_ArraySet(benchmark::State &state) {
  size_t count = state.range(0);
  while (state.KeepRunning()) {
    ds_array_t *a = ds_array_create(count);
    for (size_t i = 0; i < count; i++) {
      ds_array_set(a, i, (void *)i);
    }
    ds_array_destroy(&a);
  }
  state.SetComplexityN(count);
}
BENCHMARK(BM_ArraySet)->Range(8, 32<<10)->Complexity(benchmark::oN);
