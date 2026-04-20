#include <stdio.h>
/*
  *
Para vetores que começam de 1:
  esquerda = 2i
  direita = 2i+1
  pai = i/2
  último nó que possui ao menos 1 filho = (n/2)
Para vetores que começam de 0:
  esquerda = 2i+1
  direita = 2i+2
  pai = (i/2)-1
 último nó que possui ao menos 1 filho = (n/2)-1

  */
int tamanhoHeap = 0;

int pai(int i) { return (i - 1) / 2; }
int esquerda(int i) { return (2 * i) + 1; }
int direita(int i) { return (2 * i) + 2; }
void maximiza_heap(int *A, int i) {
  int l = esquerda(i);
  int r = direita(i);
  int maior;
  if (l < tamanhoHeap && A[l] > A[i]) {
    maior = l;
  } else
    maior = i;

  if (r < tamanhoHeap && A[r] > A[maior]) {
    maior = r;
  }

  if (maior != i) {
    int tmp = A[i];
    A[i] = A[maior];
    A[maior] = tmp;
    maximiza_heap(A, maior);
  }
}
void constroi_max_heap(int *A, int n) {
  tamanhoHeap = n;

  for (int i = (n / 2) - 1; i >= 0; i--) {
    maximiza_heap(A, i);
  }
}
void print(int *A, int n) {
  for (int i = 0; i < n; i++) {
    printf(" %d", A[i]);
  }
}
void heapsort(int *A, int n) {
  constroi_max_heap(A, n);

  for (int i = n - 1; i > 0; i--) {
    int tmp = A[0];
    A[0] = A[i];
    A[i] = tmp;
    tamanhoHeap--;
    maximiza_heap(A, 0);
  }
}
int main() {
  int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  heapsort(A, 10);
  print(A, 10);
}
