#include <stdio.h>

int main() {

  int x, y, i, j = 0;

  while (scanf("%d %d", &x, &y) != EOF) {

    int vet[y];
    for (i = x, j = 0; i <= y; i++, j++) {
      printf("%d", i);
      vet[j] = i;
    }
    for (int k = j - 1; k >= 0; k--) {
      while (vet[k] != 0) {
        int resto = vet[k] % 10;
        printf("%d", resto);
        int aux = vet[k] / 10;
        vet[k] = aux;
      }
    }
    printf("\n");
  }
}
