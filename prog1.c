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

#define SIZE 200
int main(int argc, char *argv[]) {
  long double a[SIZE][SIZE];
  long double b[SIZE][SIZE];
  long double c[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      a[i][j] = 10;

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      b[i][j] = 123;

  double start = omp_get_wtime();
#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        c[i][j] = a[i][j] + b[i][j];
  }
  double end = omp_get_wtime();
  printf("%lf\n", (end));
  printf("%lf\n", (start));
  /* printMat(c, SIZE); */
  printf("%lf", (end - start));
  return 0;
}
