#include <stdio.h>

int substringMaisLonga(char *s) {
  int size = 0, j, maior = 0, novaSub = 0;

  for (int i = 1; s[i] != '\0' && s[i] != '\n'; i++) {
    for (j = novaSub; j < i; j++) {
      if (s[j] == s[i]) {
        novaSub = j + 1;
        j = i;
      }
    }
    size = i - novaSub + 1;
    if (size > maior)
      maior = size;
  }

  return maior;
}
int main() {

  char s[100];

  fgets(s, sizeof(s), stdin);

  while (!(s[0] == 'F' && s[1] == 'I' && s[2] == 'M')) {
    printf("%d\n", substringMaisLonga(s));
    fgets(s, sizeof(s), stdin);
  }
}
