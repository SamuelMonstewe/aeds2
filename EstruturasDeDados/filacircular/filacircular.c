#include <stdio.h>
// 0 % 5 = 0
// 1 % 5 = 1
//...
// 5 % 5 = 0
int n = 5, inicio = 0, fim = 0, total = 0;
void enqueue(int *fila, int x) {
  if (total == n) {
    printf("fila cheia!");
    return;
  }
  fila[fim] = x;
  fim = (fim + 1) % n;
  total++;
}
void dequeue(int *fila) {
  if (fim == inicio) {
    printf("Fila vazia!");
    return;
  }
  total--;
  inicio = (inicio + 1) % n;
}
void imprimir(int *fila) {
  for (int i = 0; i < total; i++) {
    printf("%d ", fila[(inicio + i) % n]);
  }
  printf("\n");
}
int main() {
  int fila[n];

  enqueue(fila, 10);
  enqueue(fila, 20);
  enqueue(fila, 30);
  dequeue(fila);
  enqueue(fila, 40);
  enqueue(fila, 50);
  enqueue(fila, 60);

  imprimir(fila);
}
