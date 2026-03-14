#include <stdio.h>

int isAnagrama(char *s1, char *s2) {

  int achou = 0;
  char stop = ' ';
  int i;
  for (i = 0; s1[i] != '\0'; i++, stop = ' ') {
    for (int j = 0; s2[j] != '\0' && stop != '\0'; j++) {
      // na tabela ascii, as letras maiusculas possuem uma certa simetria com as
      // minusculas, se você somar 32 a uma maiuscula, chega na sua
      // correspondente minuscula e vice-versa
      if (s1[i] == s2[j] || s1[i] - 32 == s2[j] || s1[i] == s2[j] - 32) {
        achou++;
        stop = '\0';
      }
    }
  }

  if (achou == i)
    return 1;

  return 0;
}
int main() {
  char entrada[100];
  char s1[50];
  char s2[50];

  fgets(entrada, sizeof(entrada), stdin);

  while (!(entrada[0] == 'F' && entrada[1] == 'I' && entrada[2] == 'M')) {
    int i;
    int j;
    int k;

    for (i = 0; entrada[i] != ' '; i++) {
      s1[i] = entrada[i];
    }
    s1[i] = '\0';
    // como as entradas vão ser separadas por - e espaço em branco, manipulei
    // a variável j para cair direto no início da segunda string
    for (k = 0, j = i + 3; entrada[j] != '\0'; j++, k++) {
      s2[k] = entrada[j];
    }
    s2[k] = '\0';

    (isAnagrama(s1, s2)) ? printf("SIM") : printf("NÃO");
    printf("\n");
    fgets(entrada, sizeof(entrada), stdin);
  }
}
