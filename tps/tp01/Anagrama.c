#include <stdio.h>

int isAnagrama(char *s1, char *s2) {

  int achou = 0;
  char stop = ' ';
  int teveOcorrencia = 1;
  int countOcorrenciasS1 = 0, countOcorrenciasS2 = 0;

  for (int i = 0; s1[i] != '\0' && teveOcorrencia; i++) {
    teveOcorrencia = 0;
    char caracter = s1[i];

    for (int j = 0; s1[j] != '\0'; j++) {
      if (s1[j] == caracter || s1[j] - 32 == caracter ||
          s1[j] == caracter - 32) {
        countOcorrenciasS1++;
      }
    }
    for (int k = 0; s2[k] != '\0'; k++) {
      if (s2[k] == caracter || s2[k] - 32 == caracter ||
          s2[k] == caracter - 32) {
        countOcorrenciasS2++;
      }
    }

    if (countOcorrenciasS1 == countOcorrenciasS2) {
      teveOcorrencia = 1;
    }

    countOcorrenciasS1 = countOcorrenciasS2 = 0;
  }

  return teveOcorrencia;
}
int main() {
  char entrada[1000];
  char s1[500];
  char s2[500];

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
