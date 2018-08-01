/*
 * prog1.c
 * Copyright (C) 2018 g <g@levi-al>
 *
 * Distributed under terms of the MIT license.
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define printMat(a, n)                                                         \
  for (int i = 0; i < n; i++) {                                                \
    for (int j = 0; j < n; j++) {                                              \
      printf("%Lf ", a[i][j]);                                                 \
    }                                                                          \
    printf("\n");                                                              \
  }

#define SIZE 100000
int main(int argc, char *argv[]) {
  long double a[SIZE];
  long double b[SIZE];

  double start = omp_get_wtime();
#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < SIZE; i++) {
      a[i] = (i + 1) * 3.0;
      b[i] = (i + 1) * 2.0;
    }
  }
  double end = omp_get_wtime();
  /* printMat(c, SIZE); */
  printf("%lf\n", (end - start));
  return 0;
}
