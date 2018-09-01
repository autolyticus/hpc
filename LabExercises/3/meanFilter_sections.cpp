#include <fstream>
#include <iostream>
#include <omp.h>

using namespace std;

#define WIDTH 384
#define HEIGHT 512

#define readImage(imageFile, image)                                            \
  for (int i = 0; i < WIDTH; ++i)                                              \
    for (int j = 0; j < HEIGHT; ++j)                                           \
      imageFile >> image[i][j];

#define resetImage(image)                                                      \
  for (int i = 0; i < WIDTH; ++i)                                              \
    for (int j = 0; j < HEIGHT; ++j)                                           \
      image[i][j] = 0;

double rImage[WIDTH][HEIGHT], gImage[WIDTH][HEIGHT], bImage[WIDTH][HEIGHT];
double newRImage[WIDTH][HEIGHT] = {{0}}, newGImage[WIDTH][HEIGHT] = {{0}},
       newBImage[WIDTH][HEIGHT] = {{0}};

int main() {
  ifstream rFile("red.txt");
  ifstream gFile("green.txt");
  ifstream bFile("blue.txt");
  readImage(rFile, rImage);
  readImage(gFile, gImage);
  readImage(bFile, bImage);

  int threadArray[11] = {1, 2, 4, 6, 8, 12, 16, 20, 24, 28, 32};

  long double start, end, elapsed;

  for (int J = 0; J < 11; ++J) {
    resetImage(newRImage);
    resetImage(newGImage);
    resetImage(newBImage);
    start = omp_get_wtime();

#pragma omp parallel sections num_threads(threadArray[J])
    {

#pragma omp section
      {
        for (int i = 1; i < WIDTH - 1; ++i)
          for (int j = 1; j < HEIGHT - 1; ++j)
            for (int ii = -1; ii < 2; ++ii)
              for (int jj = -1; jj < 2; ++jj)
                newRImage[i][j] += rImage[i + ii][j + jj] / 9.0;
      }

#pragma omp section
      {
        for (int i = 1; i < WIDTH - 1; ++i)
          for (int j = 1; j < HEIGHT - 1; ++j)
            for (int ii = -1; ii < 2; ++ii)
              for (int jj = -1; jj < 2; ++jj)
                newGImage[i][j] += gImage[i + ii][j + jj] / 9.0;
      }

#pragma omp section
      {
        for (int i = 1; i < WIDTH - 1; ++i)
          for (int j = 1; j < HEIGHT - 1; ++j)
            for (int ii = -1; ii < 2; ++ii)
              for (int jj = -1; jj < 2; ++jj)
                newBImage[i][j] += bImage[i + ii][j + jj] / 9.0;
      }
    }

    end = omp_get_wtime();
    elapsed = end - start;
    cout << threadArray[J] << '\t' << elapsed << endl;
  }
  ofstream rOutput("redOutput.txt");
  for (int i = 0; i < WIDTH; ++i)
    for (int j = 0; j < HEIGHT; ++j)
      rOutput << newRImage[i][j] << endl;
  ofstream gOutput("greenOutput.txt");
  for (int i = 0; i < WIDTH; ++i)
    for (int j = 0; j < HEIGHT; ++j)
      gOutput << newGImage[i][j] << endl;
  ofstream bOutput("blueOutput.txt");
  for (int i = 0; i < WIDTH; ++i)
    for (int j = 0; j < HEIGHT; ++j)
      bOutput << newBImage[i][j] << endl;
  return 0;
}
