#include <stdio.h>
#include <stdlib.h>

struct No {
  struct No *dir;
  struct No *esq;
  struct No *pai;
  int elemento;
};

struct Arvore {
  struct No *root;
};

// h = altura da árvore
void percurso_em_ordem(struct No *x) { // Θ(n)
  if (x != NULL) {
    percurso_em_ordem(x->esq);
    printf("%d ", x->elemento);
    percurso_em_ordem(x->dir);
  }
}

struct No *busca_arvore(struct No *x, int k) { // O(h)
  while (x != NULL && x->elemento != k) {
    if (k < x->elemento) {
      x = x->esq;
    } else
      x = x->dir;
  }

  return x;
}

struct No *minimo(struct No *x) { // O(h)
  while (x->esq != NULL) {
    x = x->esq;
  }

  return x;
}

struct No *maximo(struct No *x) { // O(h)
  while (x->dir != NULL) {
    x = x->dir;
  }

  return x;
}

void inserir(struct Arvore *T, struct No *z) { // O(h)
  struct No *x = T->root;
  struct No *y = NULL;

  while (x != NULL) {
    y = x;
    if (z->elemento < x->elemento) {
      x = x->esq;
    } else
      x = x->dir;
  }

  z->pai = y;
  if (y == NULL) {
    T->root = z;
  } else if (z->elemento < y->elemento) {
    y->esq = z;
  } else {
    y->dir = z;
  }
}

struct No *inserirRecursivo(struct No *raiz, struct No *z) {
  struct No *x = raiz;

  // se x for null, encontramos uma posição para z
  if (x != NULL) {
    if (z->elemento < x->elemento) {
      x->esq = inserirRecursivo(x->esq, z);
      return x;
    } else {
      x->dir = inserirRecursivo(x->dir, z);
      return x;
    }
  }

  return z;
}

int main() {
  struct Arvore *T = (struct Arvore *)malloc(sizeof(struct Arvore));
  T->root = NULL;
  int A[] = {12, 18, 15, 17, 19, 5, 9, 2};
  int i = 0;
  while (i < 8) {
    struct No *no = (struct No *)malloc(sizeof(struct No));
    no->elemento = A[i];
    no->dir = NULL;
    no->esq = NULL;
    no->pai = NULL;
    T->root = inserirRecursivo(T->root, no);
    i++;
  }
  percurso_em_ordem(T->root);
}
