#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
  int elemento;
  struct Celula *prox;
} Celula;

typedef struct {
  Celula *topo;
} Pilha;

void inserir(Pilha *pilha, int x) {
  Celula *tmp = (Celula *)malloc(sizeof(Celula));
  if (pilha->topo == NULL) {
    pilha->topo = tmp;
    tmp->elemento = x;
    tmp->prox = NULL;
  } else {
    tmp->prox = pilha->topo;
    pilha->topo = tmp;
    tmp->elemento = x;
  }
}

int remover(Pilha *pilha) {
  if (pilha->topo == NULL) {
    printf("Vazia!");
    return -1;
  }
  int el;
  Celula *tmp = pilha->topo;
  pilha->topo = tmp->prox;
  el = tmp->elemento;
  free(tmp);
  return el;
}

void mostrar(Pilha *pilha) {
  Celula *tmp = pilha->topo;

  printf("[");
  while (tmp != NULL) {
    printf("%d ", tmp->elemento);
    tmp = tmp->prox;
  }
  printf("]");
}
int main() {
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->topo = NULL;
  inserir(pilha, 1);
  inserir(pilha, 2);
  inserir(pilha, 3);
  inserir(pilha, 4);
  mostrar(pilha);
}
