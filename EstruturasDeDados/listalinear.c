#include <stdio.h>
#define SIZE 6

typedef struct Lista {
  int itens[SIZE];
  int n;
} Lista;

void inserirInicio(Lista *lista, int value) {
  if (lista->n >= SIZE) {
    printf("Lista cheia!");
    return;
  }

  for (int i = lista->n; i > 0; i--) {
    lista->itens[i] = lista->itens[i - 1];
  }

  lista->itens[0] = value;
  lista->n++;
}
void inserirFim(Lista *lista, int value) {
  if (lista->n >= SIZE) {
    printf("Lista cheia!");
    return;
  }

  lista->itens[lista->n] = value;
  lista->n++;
}
void inserir(Lista *lista, int index, int value) {
  if (lista->n >= SIZE) { // suponha que o usuário sempre insira valores no
                          // intervalo do array
    printf("Lista cheia!");
    return;
  }

  for (int i = lista->n; i > index; i--) {
    lista->itens[i] = lista->itens[i - 1];
  }

  lista->itens[index] = value;
  lista->n++;
}
int removerInicio(Lista *lista) {
  if (lista->n == 0) {
    printf("Lista vazia!");
    return 0;
  }

  int value = lista->itens[0];
  lista->n--;

  for (int i = 0; i < lista->n; i++) {
    lista->itens[i] = lista->itens[i + 1];
  }

  return value;
}
int removerFim(Lista *lista) {
  if (lista->n == 0) {
    printf("Lista vazia!");
    return 0;
  }

  lista->n--;
  return lista->itens[lista->n];
}
int remover(Lista *lista, int index) {
  if (lista->n == 0) {
    printf("Lista vazia!");
    return 0;
  }

  int old = lista->itens[index];
  lista->n--;

  for (int i = index; i < lista->n; i++) {
    lista->itens[i] = lista->itens[i + 1];
  }

  return old;
}
void printLista(Lista *lista) {
  printf("[");
  for (int i = 0; i < lista->n; i++) {
    printf("%d, ", lista->itens[i]);
  }
  printf("]");
}
int main() {
  Lista lista;
  lista.n = 0;
  inserirFim(&lista, 1);
  inserirFim(&lista, 2);
  inserirFim(&lista, 3);
  inserirFim(&lista, 4);
  inserirFim(&lista, 5);
  inserirFim(&lista, 6);
  int e = remover(&lista, 1);
  inserir(&lista, 3, 7);
  printf("%d\n", e);
  printLista(&lista);
}
