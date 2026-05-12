#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  struct No *sup, *inf;
  struct No *esq, *dir;
  int elemento;
} No;
typedef struct Matriz {
  struct No *inicio;
  int linha, coluna;
} Matriz;

Matriz *newMatriz(int l, int c) {
  Matriz *m = (Matriz *)malloc(sizeof(Matriz));
  m->inicio = NULL;
  m->linha = l;
  m->coluna = c;

  return m;
}

No *newNo() {
  No *nova = (No *)malloc(sizeof(No));
  nova->elemento = 0;
  nova->sup = nova->inf = nova->esq = nova->dir = NULL;

  return nova;
}

void montarMatriz(Matriz *matriz) {
  matriz->inicio = newNo();
  No *linha = matriz->inicio;
  No *coluna = matriz->inicio;

  // cria o "cabeçalho" da matriz primeiro
  for (int i = 1; i < matriz->coluna; i++) {
    No *novo = newNo();
    novo->elemento = 0;
    novo->esq = coluna;
    coluna->dir = novo;
    coluna = novo;
  }

  coluna = linha;

  int quantidadeDeNoRestante = matriz->linha * matriz->coluna - matriz->coluna;

  for (int j = 0; j < quantidadeDeNoRestante; j++) {
    coluna->inf = newNo();
    coluna->inf->elemento = 0;
    coluna->inf->sup = coluna;
    coluna->inf->esq = NULL;
    coluna->inf->inf = NULL;

    // tem nó a esquerda para conectar ao novo?
    if (coluna->esq != NULL) {
      coluna->inf->esq = coluna->esq->inf;
      coluna->esq->inf->dir = coluna->inf;
    }

    // se o proximo nó (direito no caso) for nulo, terminamos a linha atual e
    // vamos para a de baixo
    if (coluna->dir != NULL) {
      coluna = coluna->dir;
    } else {
      linha = linha->inf;
      coluna = linha;
    }
  }
}

void mostrar(Matriz *matriz) {
  for (No *i = matriz->inicio; i != NULL; i = i->inf) {
    for (No *j = i; j != NULL; j = j->dir) {
      printf("%d ", j->elemento);
    }
    printf("\n");
  }
}
int main() {
  Matriz *matriz = newMatriz(2, 10);
  montarMatriz(matriz);
  mostrar(matriz);
}
