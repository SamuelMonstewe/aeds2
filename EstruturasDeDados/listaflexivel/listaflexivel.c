#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int elemento;
  struct No *prox;
} No;

typedef struct Lista {
  No *primeiro;
  No *ultimo;
} Lista;

void inserirFim(Lista *lista, int x) {
  No *novo = (No *)malloc(sizeof(No));

  novo->elemento = x;
  novo->prox = NULL;
  lista->ultimo->prox = novo;
  lista->ultimo = novo;
}

void inserirInicio(Lista *lista, int x) {
  lista->primeiro->elemento = x;
  No *novoCabeca = (No *)malloc(sizeof(No));
  novoCabeca->prox = lista->primeiro;
  lista->primeiro = novoCabeca;
  novoCabeca = NULL;
}

int tamanho(Lista *lista) {
  No *i = lista->primeiro;
  int n = 0;

  while (i->prox != NULL) {
    n++;
    i = i->prox;
  }

  return n;
}
void inserir(Lista *lista, int x, int pos) {
  int tam = tamanho(lista);

  if (pos < 0) {
    exit(1);
  } else if (pos == 0) {
    inserirInicio(lista, x);
  } else if (pos == tam) {
    inserirFim(lista, x);
  } else {
    No *i = lista->primeiro;
    int j = 0;

    while (j < pos) {
      i = i->prox;
      j++;
    }

    No *tmp = (No *)malloc(sizeof(No));
    tmp->elemento = x;
    tmp->prox = i->prox;
    i->prox = tmp;
    i = NULL;
    tmp = NULL;
  }
}
int removerFim(Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    exit(1);
  }

  No *i = lista->primeiro;

  while (i->prox != lista->ultimo) {
    i = i->prox;
  }

  lista->ultimo = i;
  int el = i->elemento;
  free(i->prox);
  lista->ultimo->prox = NULL;
  i = NULL;
  return el;
}

int removerInicio(Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    exit(1);
  }

  No *tmp = lista->primeiro->prox;
  lista->primeiro->prox = tmp->prox;
  int el = tmp->elemento;
  tmp->prox = NULL;
  free(tmp);
  return el;
}

int remover(Lista *lista, int pos) {
  int tam = tamanho(lista);
  int el;
  if (lista->primeiro == lista->ultimo || pos >= tam || pos < 0) {
    exit(1);
  } else if (pos == 0) {
    el = removerInicio(lista);
  } else if (pos == tam - 1) {
    el = removerFim(lista);
  } else {
    No *i = lista->primeiro;
    int j = 0;

    while (j < pos) {
      i = i->prox;
      j++;
    }

    No *tmp = i->prox;
    i->prox = tmp->prox;
    el = tmp->elemento;
    tmp->prox = NULL;
    free(tmp);
  }

  return el;
}

void mostrar(Lista *lista) {
  No *tmp = lista->primeiro->prox;

  printf("[ ");

  while (tmp != NULL) {
    printf("%d ", tmp->elemento);
    tmp = tmp->prox;
  }

  printf("]");
}

int main() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  No *cabeca = (No *)malloc(sizeof(No));

  lista->primeiro = cabeca;
  lista->ultimo = cabeca;

  inserirFim(lista, 3);
  inserirFim(lista, 5);
  inserirFim(lista, 7);
  inserirInicio(lista, 4);
  inserir(lista, 8, 1);
  remover(lista, 1);
  remover(lista, 1);
  mostrar(lista);
}
