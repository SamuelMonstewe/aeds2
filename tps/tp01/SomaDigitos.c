#include <stdio.h>

int somaDigitosRecursivo(int num) {
  if ((num / 10) == 0)
    return num;

  int resto = num % 10;
  int quociente = num / 10;
  return resto + somaDigitosRecursivo(quociente);
}
int somaDigitos(int num) { return somaDigitosRecursivo(num); }
int main() {

  int num;

  while (scanf("%d", &num)) {
    printf("%d\n", somaDigitos(num));
  }
}
