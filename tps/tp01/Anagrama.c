#include <stdio.h>

int isComprimentoIgual(char *s1, char *s2) {

  int sizeS1 = 0, sizeS2 = 0;
  for (int i = 0; s1[i] != '\0' && s1[i] != '\n'; i++) {
    sizeS1++;
  }
  for (int j = 0; s2[j] != '\0' && s2[j] != '\n'; j++) {
    sizeS2++;
  }

  if (sizeS1 != sizeS2)
    return 0;

  return 1;
}
// o meu algoritmo (meio merda) para verificar anagrama é ver, primeiramente, se
// as duas strings possuem comprimento igual; Caso contrário eu faço uma
// contagem para ver se as ocorrencias de uma letra na string S1 vai ser a mesma
// quantidade da string S2
int isAnagrama(char *s1, char *s2) {

  if (!isComprimentoIgual(s1, s2)) {
    return 0;
  }

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
    // manipulei as entradas para pegar o inicio da segunda string e armazenar
    // no vetor S2
    for (k = 0, j = i + 1; entrada[j] != '\0'; j++, k++) {
      s2[k] = entrada[j];
    }
    s2[k] = '\0';

    (isAnagrama(s1, s2)) ? printf("SIM") : printf("NAO");
    printf("\n");
    fgets(entrada, sizeof(entrada), stdin);
  }
}
