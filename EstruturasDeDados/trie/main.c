#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
  struct Node *filho;
  struct Celula *prox;
  char letra;
} Celula;

typedef struct Node {
  char letra;
  Celula *primeiro;
  bool fim;
} Node;

Node *newNode(char letra) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->letra = letra;
  node->primeiro = NULL;
  node->fim = false;
  return node;
}
Celula *newCelula(char letra) {
  Celula *c = (Celula *)malloc(sizeof(Celula));
  c->filho = newNode(letra);
  c->letra = letra;
  c->prox = NULL;
  return c;
}

Celula *inserirInicio(Celula *primeiro, char letra) {
  Celula *c = newCelula(letra);

  c->prox = primeiro;
  primeiro = c;

  return primeiro;
}

typedef struct Trie {
  Node *root;
} Trie;

Celula *pesquisar(Celula *primeiro, char letra) {
  for (Celula *i = primeiro; i != NULL; i = i->prox) {
    if (i->letra == letra)
      return i;
  }

  return NULL;
}
void inserir(Node *node, char *palavra) {
  if (palavra[0] == '\0') {
    node->fim = true;
    return;
  }

  Celula *filho = pesquisar(node->primeiro, palavra[0]);

  if (filho == NULL) {
    filho = inserirInicio(node->primeiro, palavra[0]);
    node->primeiro = filho;
  }

  inserir(filho->filho, palavra + 1);
}

void mostrar(Node *node, char *s) {
  if (node->fim) {
    printf("%s\n", s);
  }

  for (Celula *i = node->primeiro; i != NULL; i = i->prox) {
    char concat[300];
    sprintf(concat, "%s%c", s, i->letra);

    mostrar(i->filho, concat);
  }
}

Trie *newTrie() {
  Trie *t = (Trie *)malloc(sizeof(Trie));
  t->root = newNode('\0');

  return t;
}

Node *buscarNo(Node *node, char *sufixo) {
  if (sufixo[0] == '\0')
    return node;

  Celula *filho = pesquisar(node->primeiro, sufixo[0]);

  return buscarNo(filho->filho, sufixo + 1);
}
void startsWith(Node *node, char *sufixo) {
  Node *no = buscarNo(node, sufixo);

  mostrar(no, sufixo);
}

int contarPalavras(Node *node) {
  if (node == NULL) {
    return 0;
  }

  int total = (node->fim) ? 1 : 0;

  for (Celula *i = node->primeiro; i != NULL; i = i->prox) {
    total += contarPalavras(i->filho);
  }

  return total;
}

bool buscarPalavra(Node *node, char *palavra) {

  if (palavra[0] == '\0') {
    return node->fim;
  }

  Celula *filho = pesquisar(node->primeiro, palavra[0]);

  if (filho == NULL) {
    return false;
  }

  return buscarPalavra(filho->filho, palavra + 1);
}

/*
caminhar até o nó e setar fim palavra como false
se esse nó não tiver filho, deletar
ao voltar da recursao, deletar um nó se, e somente se, ele não tiver filhos e
não for fim de outra palavra

*/

void destroy(Node *node, Celula *c) {
  Celula *i = node->primeiro;

  if (c == node->primeiro) {
    node->primeiro = node->primeiro->prox;
  } else {
    while (i->prox != c)
      i = i->prox;

    i->prox = c->prox;
  }

  if (c->filho != NULL) {
    free(c->filho);
  }
  free(c);
}

bool deletar(Node *node, char *palavra) {
  if (node->fim && palavra[0] == '\0') {
    node->fim = false;
    return node->primeiro == NULL;
  }

  Celula *c = pesquisar(node->primeiro, palavra[0]);

  if (c == NULL) {
    return false;
  }

  bool possoDeletar = deletar(c->filho, palavra + 1);

  if (possoDeletar) {
    destroy(node, c);
    c = NULL;
  }

  if (node->fim == false && node->primeiro == NULL) {
    return true;
  }

  return false;
}

int main() {
  Trie *t = newTrie();

  // Palavras com o prefixo "mar" e variações
  inserir(t->root, "mar");
  inserir(t->root, "marujo");
  inserir(t->root, "marta");
  inserir(t->root, "marte");
  inserir(t->root, "martelo");

  // Palavras com outros prefixos comuns
  inserir(t->root, "casaco");
  inserir(t->root, "castelo");
  inserir(t->root, "carro");

  // Palavras curtas e inserções que são subpalavras de outras
  inserir(t->root, "sol");
  inserir(t->root, "soldado");
  inserir(t->root, "par");
  inserir(t->root, "parede");

  // Teste de borda: palavra de uma única letra
  inserir(t->root, "a");
  inserir(t->root, "b");

  mostrar(t->root, "");
}
