#include <cstdlib>
#include <float.h>
#include <iostream>
#include <omp.h>

using namespace std;
#define N 100

int main() {
  long double start, end, elapsed = 0.0;

  double mats[N][100][100];

  for (int MAT = 0; MAT < N; MAT++) {
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        mats[MAT][i][j] = (double)rand() / (double)(RAND_MAX);
      }
    }
  }

  start = omp_get_wtime();

  double m = -DBL_MAX;
  for (int MAT = 0; MAT < N; MAT++)
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        m = max(m, mats[MAT][i][j]);
      }
    }

  end = omp_get_wtime();
  elapsed = end - start;
  cout << elapsed << endl;
  return 0;
}
