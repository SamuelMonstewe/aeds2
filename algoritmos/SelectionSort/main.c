#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 10;
void selecao(int *A) {
  int menor, tmp;

  for (int i = 0; i < n - 1; i++) {
    menor = i;
    for (int j = (i + 1); j < n; j++) {
      if (A[j] < A[menor]) {
        menor = j;
      }
    }
    tmp = A[i];
    A[i] = A[menor];
    A[menor] = tmp;
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
  selecao(A);
  print(A);
}
