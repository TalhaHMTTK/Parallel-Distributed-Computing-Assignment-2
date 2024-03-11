#include <omp.h>
#include <stdio.h>
static long num_steps = 100000;
double step;

int main() {
  double start_time, end_time;
  start_time = omp_get_wtime();
  int i;
  double y, res, sum = 0.0;
  step = 5.0 / (double)num_steps;

  for (i = 0; i < num_steps; i++) {
    y = 5.0 + (i + 0.5) * step;
    sum = sum + 1.0 / (1.0 + y + y * y + y * y * y * y);
  }

  res = step * sum;

  end_time = omp_get_wtime();
  printf("res = %f \n", res);
  printf("Elapsed time: %f seconds\n", end_time - start_time);
  return 0;
}