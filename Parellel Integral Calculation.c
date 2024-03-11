#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;

#define NUM_THREADS 2

int main() {
  double start_time, end_time;
  start_time = omp_get_wtime();
  int i, nthreads;

  double res, sum[NUM_THREADS];
  step = 5.0 / (double)num_steps;
  omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
  {
    int i, id, nthrds;
    double x, local_sum = 0.0;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if (id == 0)
      nthreads = nthrds;

    for (i = id; i < num_steps; i = i + nthrds) {
      x = 5 + (i + 0.5) * step;
      local_sum += 1.0 / (1.0 + x + x * x + x * x * x * x);
    }

#pragma omp critical
    { sum[id] += local_sum; }
  }

  for (i = 0, res = 0.0; i < nthreads; i++)
    res += sum[i] * step;

  end_time = omp_get_wtime();
  printf("res = %f\n", res);
  printf("Elapsed time: %f seconds\n", end_time - start_time);

  return 0;
}
