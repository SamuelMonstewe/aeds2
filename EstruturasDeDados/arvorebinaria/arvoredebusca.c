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
struct No *newNo(int x) {
  struct No *no = (struct No *)malloc(sizeof(struct No));
  no->elemento = x;
  no->dir = NULL;
  no->esq = NULL;
  no->pai = NULL;

  return no;
}
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

struct No *sucessor(struct No *x) {
  struct No *y = NULL;
  if (x->dir != NULL) {
    return minimo(x->dir);
  } else {
    y = x->pai;

    while (y != NULL && x == y->dir) {
      x = y;
      y = y->pai;
    }
  }

  return y;
}

struct No *inserirRecursivo(struct No *raiz, int x) {

  if (raiz == NULL) {
    return newNo(x);
  } else {
    if (x < raiz->elemento) {
      raiz->esq = inserirRecursivo(raiz->esq, x);
      raiz->esq->pai = raiz;
    } else {
      raiz->dir = inserirRecursivo(raiz->dir, x);
      raiz->dir->pai = raiz;
    }
  }

  return raiz;
}
int heigth(struct No *root) {
  if (root == NULL || (root->dir == NULL && root->esq == NULL)) {
    return 0;
  }

  int hl = 1 + heigth(root->esq);
  int hr = 1 + heigth(root->dir);

  return (hl < hr) ? hr : hl;
}

int main() {
  struct Arvore *T = (struct Arvore *)malloc(sizeof(struct Arvore));
  T->root = NULL;
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int i = 0;
  while (i < 8) {
    T->root = inserirRecursivo(T->root, A[i]);
    i++;
  }

  printf("%d", sucessor(T->root)->elemento);
}
