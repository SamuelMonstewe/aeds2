#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n = 10;
void insercao(int *A) {

  int j;

  for (int i = 1; i < n; i++) {
    int key = A[i];
    j = i - 1;

    while ((j >= 0) && A[j] > key) {
      A[j + 1] = A[j];
      j = j - 1;
    }

    A[j + 1] = key;
  }
}
void print(int *A) {
  for (int i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
}
int main() {
  srand(time(NULL));

  int A[n];

  for (int i = 0; i < n; i++) {
    A[i] = rand() % 100;
  }

  print(A);
  insercao(A);
  print(A);
}
