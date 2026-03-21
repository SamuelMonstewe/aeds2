#include <locale.h>
#include <stdio.h>
void ciframentoRecursivo(char *s, int i) {
  if (s[i] == '\0' || s[i] == '\n' || s[i] == '\r') {
    s[i] = '\0';
    return;
  }

  s[i] = s[i] + 3;               // fazemos o deslocamento na tabela ascii
  ciframentoRecursivo(s, i + 1); // incrementamos o i para pegar o próximo
                                 // caractere na proxima chamada
}
void ciframento(char *s) { ciframentoRecursivo(s, 0); }
int main() {
  setlocale(LC_ALL, "pt_BR.iso88591");
  char s[1000];

  fgets(s, sizeof(s), stdin);

  while (!(s[0] == 'F' && s[1] == 'I' && s[2] == 'M')) {
    ciframento(s);

    printf("%s\n", s);
    fgets(s, sizeof(s), stdin);
  }
}
