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

int removerFim(struct Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    exit(1);
  }

  lista->ultimo = lista->ultimo->ant;
  int el = lista->ultimo->prox->elemento;
  free(lista->ultimo->prox);
  lista->ultimo->prox = NULL;

  return el;
}

int removerInicio(struct Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    exit(1);
  }

  int el = lista->primeiro->prox->elemento;
  lista->primeiro->prox = lista->primeiro->prox->prox;
  free(lista->primeiro->prox->ant);
  lista->primeiro->prox->ant = lista->primeiro;

  return el;
}

int remover(struct Lista *lista, int pos) {
  int tam = tamanho(lista);
  int el;
  if (lista->primeiro == lista->ultimo || pos >= tam || pos < 0) {
    exit(1);
  } else if (pos == 0) {
    el = removerInicio(lista);
  } else if (pos == tam - 1) {
    el = removerFim(lista);
  } else {
    struct Celula *tmp = lista->primeiro;
    int j = 0;

    while (j <= pos) {
      tmp = tmp->prox;
      j++;
    }

    el = tmp->elemento;
    tmp->ant->prox = tmp->prox;
    tmp->prox->ant = tmp->ant;
    tmp->ant = NULL;
    tmp->prox = NULL;
    free(tmp);
  }
  return el;
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
  printf("%d\n", remover(lista, 1));
  mostrar(lista);
  liberar_memoria(lista);
}
