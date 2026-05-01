#include <stdio.h>
#include <stdlib.h>

struct Celula {
  struct Celula *prox;
  struct Celula *ant;
  int elemento;
};

struct Lista {
  struct Celula *primeiro;
  struct Celula *ultimo;
};

void inserirFim(struct Lista *lista, int x) {
  struct Celula *nova = (struct Celula *)malloc(sizeof(struct Celula));
  nova->elemento = x;
  lista->ultimo->prox = nova;
  nova->ant = lista->ultimo;
  nova->prox = NULL;
  lista->ultimo = nova;
  nova = NULL;
}

void inserirInicio(struct Lista *lista, int x) {
  struct Celula *nova = (struct Celula *)malloc(sizeof(struct Celula));
  nova->elemento = x;

  if (lista->primeiro == lista->ultimo) {
    lista->ultimo->prox = nova;
    nova->ant = lista->ultimo;
    lista->ultimo = nova;
    return;
  }

  nova->ant = lista->primeiro;
  nova->prox = lista->primeiro->prox;
  lista->primeiro->prox->ant = nova;
  lista->primeiro->prox = nova;
  nova = NULL;
}

int tamanho(struct Lista *lista) {
  int n = 0;
  struct Celula *tmp = lista->primeiro;

  while (tmp != NULL) {
    tmp = tmp->prox;
    n++;
  }

  return n;
}
void inserir(struct Lista *lista, int x, int pos) {
  int tam = tamanho(lista);

  if (pos < 0 || pos > tam) {
    printf("finalizando execução...");
    exit(1);
  } else if (pos == 0) {
    inserirInicio(lista, x);
  } else if (pos == tam) {
    inserirFim(lista, x);
  } else {
    struct Celula *nova = (struct Celula *)malloc(sizeof(struct Celula));
    nova->elemento = x;
    int j = 0;
    struct Celula *tmp = lista->primeiro;

    while (j <= pos) {
      tmp = tmp->prox;
      j++;
    }

    tmp->ant->prox = nova;
    nova->ant = tmp->ant;
    tmp->ant = nova;
    nova->prox = tmp;
    nova = NULL;
  }
}

void mostrar(struct Lista *lista) {
  struct Celula *tmp = lista->primeiro->prox;

  printf("[ ");
  while (tmp != NULL) {
    printf("%d ", tmp->elemento);
    tmp = tmp->prox;
  }
  printf("]");
}

void liberar_memoria(struct Lista *lista) {
  struct Celula *current = lista->primeiro;
  struct Celula *tmp = current->prox;

  while (tmp != NULL) {
    free(current);
    current = tmp;
    tmp = tmp->prox;
  }

  current = NULL;
}

int main() {
  struct Lista *lista = (struct Lista *)malloc(sizeof(struct Lista));
  lista->primeiro = (struct Celula *)malloc(sizeof(struct Celula));
  lista->ultimo = lista->primeiro;

  inserirFim(lista, 1);
  inserirFim(lista, 2);
  inserirFim(lista, 3);
  inserirFim(lista, 4);
  inserirFim(lista, 5);
  inserirInicio(lista, 0);
  inserir(lista, 7, 1);
  inserir(lista, 8, 10);
  mostrar(lista);
  liberar_memoria(lista);
}
