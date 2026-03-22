#include <stdlib.h>
#include <time.h>
void merge(int *A, int p, int q, int r) {
  int nl = q - p + 1;
  int nr = r - q, i, j;
  int L[nl], R[nr];

  for (i = 0; i < nr; i++) {
    L[i] = A[p + i];
  }

  for (j = 0; j < nl; j++) {
    R[j] = A[q + j + 1];
  }

  i = 0;
  j = 0;
  int k = p;

  while (i < nl && j < nr) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < nl) {
    A[k] = L[i];
    i++;
    k++;
  }
  while (j < nr) {
    A[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int *A, int p, int r) {
  if (p >= r)
    return;

  int q = (p + r) / 2;

  mergeSort(A, p, q);
  mergeSort(A, q + 1, r);

  merge(A, p, q, r);
}
int main() {
  srand(time(NULL));
  long n = 1000000; // o merge sort é guloso quanto memória, a partir de 10⁷
                    // (nesta máquina que estou executando), o programa retorna
                    // segmentation fault
  int A[n];

  for (int i = 0; i < n; i++) {
    A[i] = rand() % 100;
  }
  mergeSort(A, 0, 7);
}
