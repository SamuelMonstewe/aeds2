#include <stdio.h>
void ciframentoRecursivo(char *s, int i) {
  if (s[i] == '\0')
    return;

  s[i] = s[i] + 3;
  ciframentoRecursivo(s, i + 1);
}
void ciframento(char *s) { ciframentoRecursivo(s, 0); }
int main() {
  char s[100];

  fgets(s, sizeof(s), stdin);

  while (!(s[0] == 'F' && s[1] == 'I' && s[2] == 'M')) {
    ciframento(s);

    printf("%s\n", s);
    fgets(s, sizeof(s), stdin);
  }
}
