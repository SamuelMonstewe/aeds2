#include <stdio.h>

// < pub.in > saida.txt
// diff saida.txt pub.out

int main() {
  int n = 500;
  char primeira[500];
  char segunda[500];
  char destino[500] = {'\0'};

  // minha segunda solução para o problema
  while (scanf(" %s %s", primeira, segunda) != EOF) {
    int i = 0;
    int k = 0;

    while (primeira[i] != '\0' && segunda[i] != '\0') {
      destino[k] = primeira[i];
      k++;
      destino[k] = segunda[i];
      k++;
      i++;
    }

    while (primeira[i] != '\0') {
      destino[k] = primeira[i];
      i++;
      k++;
      destino[k] = '\0';
    }
    while (segunda[i] != '\0') {
      destino[k] = primeira[i];
      i++;
      k++;
    }
    printf("%s\n", destino);
    destino[k] = '\0';
  }

  return 0;
}
// minha primeira solução para o problema
//  while (i < n) {
//    if (primeira[i] != '\0' && segunda[i] != '\0') {
//      destino[k] = primeira[i];
//      k++;
//      destino[k] = segunda[i];
//      k++;
//      i++;
//    } else if (primeira[i] == '\0') {
//      l = i;
//      int j = k;
//      for (; segunda[l] != '\0'; j++, l++) {
//        destino[j] = segunda[l];
//      }
//      destino[j] = '\0';
//      i = n;
//    } else if (segunda[i] == '\0') {
//      l = i;
//      int j = k;
//      for (; primeira[l] != '\0'; j++, l++) {
//        destino[j] = primeira[l];
//      }

//     destino[j] = '\0';
//     i = n;
//   }
// }
