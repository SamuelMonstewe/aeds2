#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long n = 1000000;
int particiona(int *A, int p, int r) {
  int x = A[r];
  int i = p - 1;

  for (int j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }

  int aux = A[i + 1];
  A[i + 1] = A[r];
  A[r] = aux;
  return i + 1;
}

void quickSort(int *A, int p, int r) {
  if (p < r) {
    int q = particiona(A, p, r);
    quickSort(A, p, q - 1);
    quickSort(A, q + 1, r);
  }
}

void imprimir(int *A) {
  for (int i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
}
int main() {
  srand(time(NULL));

  int A[n];

  for (int i = 0; i < n; i++) {
    A[i] = (rand() << 15) | rand();
  }
  // imprimir(A);
  // printf("\n");
  quickSort(A, 0, n - 1);

  // imprimir(A);
}
