#include <cstdlib>
#include <float.h>
#include <iostream>
#include <omp.h>

using namespace std;
#define N 100

int main() {
  long double start, end, elapsed = 0.0;

  double mats[N][100][100];

#pragma omp parallel for
  for (int MAT = 0; MAT < N; MAT++) {
#pragma omp parallel for
    for (int i = 0; i < 100; i++) {
#pragma omp parallel for
      for (int j = 0; j < 100; j++) {
        mats[MAT][i][j] = (double)rand() / (double)RAND_MAX;
      }
    }
  }

  int threadArray[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32};

  for (int J = 0; J < 12; J++) {
    double m = -DBL_MAX;

    start = omp_get_wtime();
    // Finds max of all 100 matrices parallely then combines
#pragma omp parallel for reduction(max : m) num_threads(threadArray[J])
    for (int MAT = 0; MAT < N; MAT++)
      for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
          m = max(m, mats[MAT][i][j]);
        }
      }

    end = omp_get_wtime();
    elapsed = end - start;
    cout << threadArray[J] << "\t" << elapsed << endl;
    // cout << m << endl;
  }
  return 0;
}
