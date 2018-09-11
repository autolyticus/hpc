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
        mats[MAT][i][j] = (double)rand() / (double)(RAND_MAX);
      }
    }
  }

  int threadArray[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32};

  for (int J = 0; J < 12; J++) {
    double m = -DBL_MAX;
    start = omp_get_wtime();

#pragma omp parallel shared(m) num_threads(threadArray[J])
    {
      double m_pri = m;
#pragma for
      for (int MAT = 0; MAT < N; MAT++)
#pragma for
        for (int i = 0; i < 100; i++) {
#pragma for
          for (int j = 0; j < 100; j++) {
            if (mats[MAT][i][j] > m_pri)
              m_pri = mats[MAT][i][j];
          }
#pragma omp flush(max)
          if (m_pri > m)
#pragma omp critical
            if (m_pri > m)
              m = m_pri;
        }
    }

    end = omp_get_wtime();
    elapsed = end - start;
    cout << threadArray[J] << "\t" << elapsed << endl;
  }
  return 0;
}
