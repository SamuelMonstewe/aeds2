#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(a, b) ((a < b) ? b : a)
typedef struct {
  int hora;
  int minuto;
} Hora;

Hora parse_hora(char *s) {
  int horas, minutos;
  int lidos = sscanf(s, "%d:%d", &horas, &minutos);

  return (Hora){horas, minutos};
}
void formatar_hora(Hora *hora, char *buffer) {
  sprintf(buffer, "%d:%d", hora->hora, hora->minuto);
}

typedef struct {
  int ano;
  int mes;
  int dia;
} Data;

Data parse_data(char *s) {
  int ano, mes, dia;
  int lidos = sscanf(s, "%d-%d-%d", &ano, &mes, &dia);

  return (Data){ano, mes, dia};
}
void formatar_data(Data *data, char *buffer) {
  sprintf(buffer, "%02d/%02d/%02d", data->dia, data->mes, data->ano);
}
int compareTo(Data x, Data outra) {
  if (x.ano != outra.ano) {
    return x.ano - outra.ano;
  }
  if (x.mes != outra.mes) {
    return x.mes - outra.mes;
  }

  return x.dia - outra.dia;
}
typedef struct {
  int id;
  char nome[100];
  char cidade[100];
  int capacidade;
  double avaliacao;
  int n_tipos_cozinha;
  char *tipos_cozinha[2];
  int faixa_preco;
  Hora horario_abertura;
  Hora horario_fechamento;
  Data data_abertura;
  int aberto;
} Restaurante;

Restaurante *parse_restaurante(char *s) {
  Restaurante *r = (Restaurante *)malloc(sizeof(Restaurante));
  char strTiposCozinha[50];
  char strFaixaPreco[5];
  char strHorario[12];
  char strDataAbertura[11];
  char strAberto[6];

  sscanf(s, "%d,%[^,],%[^,],%d,%lf,%[^,],%[^,],%[^,],%[^,],%s", &r->id, r->nome,
         r->cidade, &r->capacidade, &r->avaliacao, strTiposCozinha,
         strFaixaPreco, strHorario, strDataAbertura, strAberto);

  strHorario[5] = '\0';

  r->horario_abertura = parse_hora(strHorario);
  r->horario_fechamento = parse_hora(strHorario + 6);
  r->data_abertura = parse_data(strDataAbertura);
  r->aberto = (strcmp("true", strAberto) == 0);
  char t1[30];
  char t2[30];

  sscanf(strTiposCozinha, "%[^;];%[^\n]", t1, t2);

  int tam1;
  for (tam1 = 0; t1[tam1]; tam1++)
    ;

  int tam2;

  for (tam2 = 0; t2[tam2]; tam2++)
    ;

  r->tipos_cozinha[0] = (char *)malloc(tam1 + 1 * sizeof(char));
  r->tipos_cozinha[1] = (char *)malloc(tam2 + 1 * sizeof(char));

  for (int i = 0; i < tam1; i++) {
    r->tipos_cozinha[0][i] = t1[i];
  }

  r->tipos_cozinha[0][tam1] = '\0';

  for (int i = 0; i < tam2; i++) {
    r->tipos_cozinha[1][i] = t2[i];
  }

  r->tipos_cozinha[1][tam2] = '\0';

  int faixaPreco = 0;

  while (strFaixaPreco[faixaPreco] != '\0') {
    faixaPreco++;
  }

  r->faixa_preco = faixaPreco;

  return r;
}
void formatar_restaurante(Restaurante *restaurante, char *buffer) {
  char dataBuff[11];
  char faixaPreco[5];

  int i = 0;
  for (; i < restaurante->faixa_preco; i++) {
    faixaPreco[i] = '$';
  }

  faixaPreco[i] = '\0';
  formatar_data(&restaurante->data_abertura, dataBuff);

  sprintf(buffer,
          "[%d ## %s ## %s ## %d ## %.1lf ## [%s,%s] ## %s ## "
          "%02d:%02d-%02d:%02d ## "
          "%s ## %s]",
          restaurante->id, restaurante->nome, restaurante->cidade,
          restaurante->capacidade, restaurante->avaliacao,
          restaurante->tipos_cozinha[0], restaurante->tipos_cozinha[1],
          faixaPreco, restaurante->horario_abertura.hora,
          restaurante->horario_abertura.minuto,
          restaurante->horario_fechamento.hora,
          restaurante->horario_fechamento.minuto, dataBuff,
          restaurante->aberto ? "true" : "false");
}

typedef struct {
  int tamanho;
  Restaurante *restaurantes[499];
} Colecao_Restaurantes;

void ler_csv_colecao(Colecao_Restaurantes *c, char *path) {
  FILE *fp = fopen(path, "r");
  if (!fp) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char linha[1024];
  fgets(linha, sizeof(linha), fp);
  int i = 0;
  char buff[300];

  while (fgets(linha, 1024, fp)) {
    Restaurante *r = parse_restaurante(linha);
    c->restaurantes[i] = r;
    i++;
  }

  fclose(fp);
}
Colecao_Restaurantes *ler_csv() {
  Colecao_Restaurantes *c =
      (Colecao_Restaurantes *)malloc(sizeof(Colecao_Restaurantes));
  ler_csv_colecao(c, "/tmp/restaurantes.csv");
  return c;
}

Restaurante *pesquisa_sequencial_por_id(Colecao_Restaurantes *c, int id) {
  Restaurante **r = c->restaurantes;

  for (int i = 0; i < 500; i++) {
    if (r[i]->id == id) {
      return r[i];
    }
  }

  return NULL;
}

int compArvore = 0;

#define RED 'R'
#define BLACK 'B'
typedef struct Node {
  char color;
  struct Node *left;
  struct Node *right;
  Restaurante *key;
} Node;

typedef struct RedBlackTree {
  Node *root;
  Node *nil;
} RedBlackTree;

Node *newNode(RedBlackTree *T, Restaurante *r) {
  Node *new = (Node *)malloc(sizeof(Node));
  new->key = r;
  new->color = RED;
  new->left = T->nil;
  new->right = T->nil;

  return new;
}

Node *rotate_for_left(Node *x) {
  Node *y = x->right;
  x->right = y->left;
  y->left = x;

  return y;
}

Node *rotate_for_right(Node *x) {
  Node *y = x->left;
  x->left = y->right;
  y->right = x;

  return y;
}
Node *RB_insert(RedBlackTree *T, Node *root, Restaurante *r) {
  compArvore++;
  if (root == T->nil) {
    Node *new = newNode(T, r);
    return new;
  }

  compArvore++;
  if (root->left->color == RED && root->right->color == RED) {
    root->color = RED;
    root->left->color = BLACK;
    root->right->color = BLACK;
  }
  int result = strcmp(r->nome, root->key->nome);
  compArvore++;
  if (result < 0) {
    root->left = RB_insert(T, root->left, r);
  } else if (result > 0) {
    compArvore++;
    root->right = RB_insert(T, root->right, r);
  }

  compArvore++;
  if (root->left->color == RED) {

    if (root->left->right->color == RED) {
      root->left = rotate_for_left(root->left);
    }

    if (root->left->left->color == RED) {
      root->color = RED;
      root->left->color = BLACK;
      root = rotate_for_right(root);
    }
  } else if (root->right->color == RED) {
    if (root->right->left->color == RED) {
      root->right = rotate_for_right(root->right);
    }

    if (root->right->right->color == RED) {
      root->color = RED;
      root->right->color = BLACK;
      root = rotate_for_left(root);
    }
  }

  return root;
}

Node *RB_insert_wrapper(RedBlackTree *T, Restaurante *r) {
  T->root = RB_insert(T, T->root, r);
  T->root->color = BLACK;
  return T->root;
}

void inorder_traversal(RedBlackTree *T, Node *root) {
  compArvore++;
  if (root == T->nil) {
    return;
  }

  char buff[300];
  inorder_traversal(T, root->left);
  formatar_restaurante(root->key, buff);
  printf("%s\n", buff);
  inorder_traversal(T, root->right);
}

void search(RedBlackTree *T, Node *root, char *r) {
  compArvore++;
  if (root == T->nil) {
    printf("NAO\n");
    return;
  }

  int result = strcmp(r, root->key->nome);

  compArvore++;
  if (result == 0) {
    printf("SIM\n");
    return;
  } else if (result < 0) {
    printf("esq ");
    compArvore++;
    search(T, root->left, r);
  } else if (result > 0) {
    printf("dir ");
    compArvore++;
    search(T, root->right, r);
  }
}
void retirar_quebra_de_linha(char *x) {
  for (int i = 0; x[i] != '\0'; i++) {
    if (x[i] == '\n' || x[i] == '\r') {
      x[i] = '\0';
      return;
    }
  }
}
int height(RedBlackTree *T, Node *root) {
  if (root == T->nil) {
    return -1;
  }

  if (root->left == T->nil && root->right == T->nil) {
    return 0;
  }
  int hl = 1 + height(T, root->left);
  int hr = 1 + height(T, root->right);

  return MAX(hl, hr);
}

typedef struct HashReserva {
  int m;
  int r;
  Restaurante *vet[50];
} HashReserva;

int compHashReserva = 0;
HashReserva *newHashReserva(int m, int r) {
  HashReserva *t = (HashReserva *)malloc(sizeof(HashReserva));
  t->m = m;
  t->r = r;

  for (int i = 0; i < 50; i++) {
    t->vet[i] = NULL;
  }

  return t;
}

int somaAsc(char *nome) {
  int s = 0;

  while (*nome) {
    s += *nome++;
  }

  return s;
}
int hashReserva(int m, char *nome) { return somaAsc(nome) % m; }

int isPosicaoVazia(HashReserva *t, int pos) {
  return (t->vet[pos] == NULL) ? 1 : 0;
}

int inserirHashReserva(HashReserva *t, Restaurante *r) {
  int pos = hashReserva(t->m, r->nome);

  compHashReserva++;
  if (t->vet[pos] == NULL) {
    t->vet[pos] = r;
    return 1;
  }

  int i = t->m;

  compHashReserva++;
  while (i < t->m + t->r && !isPosicaoVazia(t, i)) {
    compHashReserva++;
    i++;
  }

  compHashReserva++;
  if (i >= t->m + t->r) {
    return 0;
  }

  t->vet[i] = r;

  return 1;
}

// crio um pair para conseguir retornar informações sobre o hash no metodo
// pesquisar
typedef struct Pair {
  int key;
  Restaurante *value;
} Pair;

Pair pesquisar(HashReserva *t, char *nome) {
  int pos = hashReserva(t->m, nome);
  compHashReserva++;
  if (t->vet[pos] != NULL && strcmp(t->vet[pos]->nome, nome) == 0) {
    return (Pair){pos, t->vet[pos]};
  }

  int i = t->m;

  compHashReserva++;
  while (i < t->m + t->r) {
    compHashReserva += 2;
    if (strcmp(t->vet[i]->nome, nome) == 0) {
      return (Pair){i, t->vet[i]};
    }

    i++;
  }

  return (Pair){-1, NULL};
}

void mostrarTabela(HashReserva *t) {
  for (int i = 0; i < t->m + t->r; i++) {
    printf("%s\n", (t->vet[i] != NULL) ? t->vet[i]->nome : "null");
  }
}
// Celula que aceita qualquer tipo por conta de void *
typedef struct Celula {
  struct Celula *prox;
  void *elemento;
} Celula;

typedef struct Lista {
  struct Celula *primeiro;
  struct Celula *ultimo;
} Lista;

void inserirInicio(Lista *lista, void *x) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->elemento = x;
  nova->prox = NULL;

  if (lista->primeiro == lista->ultimo) {
    lista->ultimo->prox = nova;
    lista->ultimo = nova;
    return;
  }

  nova->prox = lista->primeiro->prox;
  lista->primeiro->prox = nova;
  nova = NULL;
}
void inserirInicioOrdenado(Lista *lista, Restaurante *x) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->elemento = x;
  nova->prox = NULL;

  if (lista->primeiro == lista->ultimo) {
    lista->ultimo->prox = nova;
    lista->ultimo = nova;
    return;
  }

  Celula *i = lista->primeiro;

  while (i->prox != NULL) {
    Restaurante *r = (Restaurante *)i->prox->elemento;
    // if (x->nome[0] == 'C') {
    //   printf("Celula atual: %s - Para inserir: %s\n", r->nome, x->nome);
    // }
    if (strcmp(x->nome, r->nome) < 0) {
      nova->prox = i->prox;
      i->prox = nova;
      return;
    }

    i = i->prox;
  }

  i->prox = nova;
  lista->ultimo = nova;
}
Restaurante *pesquisarLista(Lista *lista, char *nome) {
  if (lista->primeiro == lista->ultimo) {
    return NULL;
  }

  Celula *tmp = lista->primeiro->prox;

  while (tmp != NULL) {
    Restaurante *r = (Restaurante *)tmp->elemento;
    if (strcmp(r->nome, nome) == 0) {
      return (Restaurante *)tmp->elemento;
    }

    tmp = tmp->prox;
  }

  return NULL;
}
typedef struct HashEncadeado {
  Lista *vet[31];
} HashEncadeado;

Lista *newLista() {
  Lista *l = (Lista *)malloc(sizeof(Lista));
  l->primeiro = (Celula *)malloc(sizeof(Celula));
  l->ultimo = l->primeiro;
  l->ultimo->prox = NULL;
  return l;
}
HashEncadeado *newHashEncadeado() {
  HashEncadeado *t = (HashEncadeado *)malloc(sizeof(HashEncadeado));

  for (int i = 0; i < 31; i++) {
    t->vet[i] = newLista();
  }

  return t;
}

Celula *newCelula(void *x) {
  Celula *c = (Celula *)malloc(sizeof(Celula));
  c->elemento = x;
  c->prox = NULL;

  return c;
}

int hashEncadeado(int m, char *nome) { return somaAsc(nome) % m; }

void inserirHashEncadeado(HashEncadeado *t, Restaurante *r) {
  inserirInicio(t->vet[hashEncadeado(31, r->nome)], r);
}

void imprimirHashEncadeado(HashEncadeado *t) {
  for (int i = 0; i < 31; i++) {
    Lista *l = t->vet[i];

    if (l->primeiro == l->ultimo) {
      printf("null");
    } else {
      Celula *tmp = l->primeiro->prox;
      while (tmp != NULL) {
        Restaurante *r = (Restaurante *)tmp->elemento;
        printf("%s -> ", r->nome);
        tmp = tmp->prox;
      }
    }
    printf("\n");
  }
}

Pair pesquisarHashEncadeado(HashEncadeado *t, char *nome) {
  int pos = hashEncadeado(31, nome);
  Restaurante *r = pesquisarLista(t->vet[pos], nome);

  if (r == NULL) {
    return (Pair){-1, r};
  }

  return (Pair){pos, r};
}
#define MATRICULA 897962

typedef struct NodeBST {
  Lista *lista;
  struct NodeBST *left;
  struct NodeBST *right;
  char letter;
} NodeBST;

typedef struct ArvoreBinaria {
  NodeBST *root;
} ArvoreBinaria;

ArvoreBinaria *newArvoreBinaria() {
  ArvoreBinaria *t = (ArvoreBinaria *)malloc(sizeof(NodeBST));
  t->root = NULL;

  return t;
}
NodeBST *newNodeBST(Restaurante *r) {
  NodeBST *n = (NodeBST *)malloc(sizeof(NodeBST));
  n->left = NULL;
  n->right = NULL;
  n->letter = r->nome[0];
  n->lista = newLista();
  inserirInicioOrdenado(n->lista, r);

  return n;
}
NodeBST *insert(NodeBST *root, Restaurante *r) {
  if (root == NULL) {
    return newNodeBST(r);
  }

  // printf("%c %s\n", root->letter, r->nome);

  if (root->letter == r->nome[0]) {
    inserirInicioOrdenado(root->lista, r);
  } else if (r->nome[0] < root->letter) {
    root->left = insert(root->left, r);
  } else if (r->nome[0] > root->letter) {
    root->right = insert(root->right, r);
  }

  return root;
}

void print_list(Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    return;
  }

  Celula *i = lista->primeiro->prox;

  while (i != NULL) {
    Restaurante *r = (Restaurante *)i->elemento;
    printf("| %s |-> ", r->nome);

    i = i->prox;
  }
}

Restaurante *search_list(Lista *lista, char *x) {
  if (lista->primeiro == lista->ultimo) {
    return NULL;
  }

  Celula *i = lista->primeiro->prox;

  while (i != NULL) {
    Restaurante *r = (Restaurante *)i->elemento;

    if (strcmp(x, r->nome) == 0) {
      return r;
    }

    if (strcmp(x, r->nome) < 0) {
      return NULL;
    }

    printf("%s ", r->nome);

    i = i->prox;
  }

  return NULL;
}
void inorder_traversal_bst(NodeBST *root) {
  if (root != NULL) {
    print_list(root->lista);
    printf("\n");
    inorder_traversal_bst(root->left);

    // printf("%c ", root->letter);
    inorder_traversal_bst(root->right);
  }
}

Restaurante *search_bst(NodeBST *root, char *s) {
  if (root == NULL) {
    return NULL;
  }

  if (root->letter == s[0]) {
    return search_list(root->lista, s);
  }

  if (s[0] < root->letter) {
    printf("ESQ ");
    return search_bst(root->left, s);
  }

  printf("DIR ");
  return search_bst(root->right, s);
}
int main() {
  Colecao_Restaurantes *c = ler_csv();
  char s[500];
  Restaurante *rs[500];

  // questão 1
  //  RedBlackTree *T = (RedBlackTree *)malloc(sizeof(RedBlackTree));
  //  T->nil = (Node *)malloc(sizeof(Node));
  //  T->nil->color = BLACK;
  //  T->root = T->nil;

  // int id = 0;
  // fgets(s, sizeof(s), stdin);
  // sscanf(s, "%d", &id);

  // int inicio = clock();
  // while (id != -1) {
  //   Restaurante *r = pesquisa_sequencial_por_id(c, id);
  //   T->root = RB_insert_wrapper(T, r);
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }

  // while (fgets(s, sizeof(s), stdin) != NULL &&
  //        !(s[0] == 'F' && s[1] == 'I' && s[2] == 'M')) {
  //   retirar_quebra_de_linha(s);
  //   printf("raiz ");
  //   search(T, T->root, s);
  // }

  // inorder_traversal(T, T->root);

  // int fim = clock();
  // double tempoArvore = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  // FILE *logArvore = fopen("897962_arvore_bicolor.txt", "w");
  // if (logArvore) {
  //   fprintf(logArvore, "%d\t%d\t%lf\t", MATRICULA, compArvore,
  //   tempoArvore); fclose(logArvore);
  // }

  // questão 3

  // HashReserva *t = newHashReserva(31, 19);

  // int id;

  // scanf("%d", &id);

  // int inicio = clock();
  // while (id != -1) {
  //   Restaurante *r = pesquisa_sequencial_por_id(c, id);
  //   if (!inserirHashReserva(t, r)) {
  //     printf("%s\n", r->nome);
  //   }
  //   scanf("%d", &id);
  // }

  // char search[500];

  // scanf(" %[^\n]", search);
  // while (strcmp(search, "FIM") != 0) {
  //   Pair r = pesquisar(t, search);

  //   if (r.value != NULL) {
  //     char buff[500];
  //     formatar_restaurante(r.value, buff);
  //     printf("%d %s\n", r.key, buff);
  //   } else {
  //     printf("%d\n", -1);
  //   }

  //   scanf(" %[^\n]", search);
  // }

  // int fim = clock();

  // double tempoReserva = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  // FILE *logArvore = fopen("897962_hash_reserva.txt", "w");
  // if (logArvore) {
  //   fprintf(logArvore, "%d\t%d\t%lf\t", MATRICULA, compArvore, tempoReserva);
  //   fclose(logArvore);
  // }

  // questão 4

  // HashEncadeado *t = newHashEncadeado();

  // int id;

  // scanf("%d", &id);

  // while (id != -1) {
  //   inserirHashEncadeado(t, pesquisa_sequencial_por_id(c, id));

  //   scanf("%d", &id);
  // }

  // char search[500];

  // scanf(" %[^\n]", search);
  // while (strcmp(search, "FIM") != 0) {
  //   Pair r = pesquisarHashEncadeado(t, search);

  //   if (r.value != NULL) {
  //     char buff[500];
  //     formatar_restaurante(r.value, buff);
  //     printf("%d %s\n", r.key, buff);
  //   } else {
  //     printf("%d\n", -1);
  //   }

  //   scanf(" %[^\n]", search);
  // }

  // questão 7

  ArvoreBinaria *t = newArvoreBinaria();

  int id;

  scanf("%d", &id);

  while (id != -1) {
    t->root = insert(t->root, pesquisa_sequencial_por_id(c, id));

    scanf("%d", &id);
  }
  // printf("-------------------------------------------------------\n");
  // inorder_traversal_bst(t->root);

  char search[500];

  scanf(" %[^\n]", search);
  while (strcmp(search, "FIM") != 0) {
    printf("RAIZ ");
    Restaurante *resp = search_bst(t->root, search);
    if (resp != NULL) {
      char buff[400];
      formatar_restaurante(resp, buff);
      printf("SIM %s\n", buff);
    } else {
      printf("NAO\n");
    }
    scanf(" %[^\n]", search);
  }
}
