#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exibir(int *vet, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", vet[i]);
  }
}
void bubbleSort(int *vet, int n) {
  int houveTroca = 1;
  for (int rep = 0; rep < n - 1 && houveTroca; rep++) {
    houveTroca = 0;

    // esse for vai ser para fazer a bolha subir até o seu lugar
    for (int b = 0; b < n - (rep + 1); b++) {
      if (vet[b] > vet[b + 1]) {
        int temp = vet[b];
        vet[b] = vet[b + 1];
        vet[b + 1] = temp;
        houveTroca = 1;
      }
    }
  }
}
int main() {
  srand(time(NULL));
  int n = 100000;
  int vet[n];

  for (int i = 0; i < n; i++) {
    vet[i] = rand() % 100;
  }

  bubbleSort(vet, n);
}
