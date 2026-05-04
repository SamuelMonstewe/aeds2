#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MATRICULA 897962
int compSelecao = 0, movSelecao = 0;
double tempoSelecao = 0;

int compQuick = 0, movQuick = 0;
double tempoQuick = 0.0;

int compBinaria = 0;
double tempoBinaria = 0;

int compInsercao = 0, movInsercao = 0;
double tempoInsercao = 0.0;

int compHeap = 0, movHeap = 0;
double tempoHeap = 0.0;

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

typedef struct Celula {
  struct Celula *prox;
  Restaurante *elemento;
} Celula;

typedef struct Lista {
  Celula *primeiro;
  Celula *ultimo;
} Lista;

int tamanho(Lista *lista) {
  Celula *tmp = lista->primeiro->prox;
  int n = 0;

  while (tmp != NULL) {
    n++;
    tmp = tmp->prox;
  }
  return n;
}
void inserirInicio(Lista *lista, Restaurante *r) {
  lista->primeiro->elemento = r; // antigo cabeça recebe o restaurante
  Celula *novoCabeca = (Celula *)malloc(sizeof(Celula));
  novoCabeca->prox = lista->primeiro;
  lista->primeiro = novoCabeca;

  novoCabeca = NULL;
}

void inserirFim(Lista *lista, Restaurante *r) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->elemento = r;
  nova->prox = NULL;
  lista->ultimo->prox = nova;
  lista->ultimo = nova;
}
void inserir(Lista *lista, Restaurante *r, int posicao) {
  int tam = tamanho(lista);

  if (posicao < 0 || posicao > tam) {
    return;
  } else if (posicao == 0) {
    inserirInicio(lista, r);
  } else if (posicao == tam) {
    inserirFim(lista, r);
  } else {
    Celula *i = lista->primeiro;
    for (int j = 0; j < posicao; j++) {
      i = i->prox;
    }

    Celula *tmp = (Celula *)malloc(sizeof(Celula));
    tmp->elemento = r;
    tmp->prox = i->prox;
    i->prox = tmp;

    tmp = NULL;
  }
}

Restaurante *removerInicio(Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    return NULL;
  }

  // aqui eu faço uma exclusão lógica
  Celula *tmp = lista->primeiro;
  lista->primeiro = lista->primeiro->prox;
  free(tmp);
  tmp = NULL;

  return lista->primeiro->elemento;
}

Restaurante *removerFim(Lista *lista) {
  if (lista->primeiro == lista->ultimo) {
    return NULL;
  }

  Celula *tmp = lista->primeiro;

  while (tmp->prox != lista->ultimo) {
    tmp = tmp->prox;
  }

  lista->ultimo = tmp;
  Restaurante *r = tmp->prox->elemento;
  lista->ultimo->prox = NULL;
  free(tmp->prox);

  return r;
}

Restaurante *remover(Lista *lista, int posicao) {
  int tam = tamanho(lista);
  Restaurante *r;
  if (lista->primeiro == lista->ultimo || tam < 0 || posicao >= tam) {
    return NULL;
  } else if (posicao == 0) {
    r = removerInicio(lista);
  } else if (posicao == tam - 1) {
    r = removerFim(lista);
  } else {
    Celula *i = lista->primeiro;
    int j = 0;

    while (j < posicao) {
      i = i->prox;
      j++;
    }

    Celula *tmp = i->prox;
    r = tmp->elemento;

    i->prox = tmp->prox;
    free(tmp);
  }
  return r;
}

void mostrar(Lista *lista) {
  Celula *i = lista->primeiro->prox;
  char buffer[300];

  while (i != NULL) {
    formatar_restaurante(i->elemento, buffer);
    printf("%s\n", buffer);
    i = i->prox;
  }
}

int particiona(Restaurante **rs, int p, int r) {
  Restaurante *x = rs[r]; // restaurante pivo
  movQuick++;
  int i = p - 1;

  for (int j = p; j < r; j++) {
    compQuick++;
    if (x->avaliacao == rs[j]->avaliacao) { // precisa desempatar
      compQuick++;
      // se o nome for menor "alfabeticamente" que o nome do pivo
      if (strcmp(rs[j]->nome, x->nome) < 0) {
        i++;
        Restaurante *tmp = rs[i];
        rs[i] = rs[j];
        rs[j] = tmp;
        movQuick += 3;
      }
    } else if (rs[j]->avaliacao <= x->avaliacao) {
      i++;
      Restaurante *tmp = rs[i];
      rs[i] = rs[j];
      rs[j] = tmp;
      compQuick++;
      movQuick += 3;
    }
  }

  Restaurante *aux = rs[i + 1];
  // coloca o pivo uma casa a direita do ultimo elemento da partição de baixo
  rs[i + 1] = rs[r];
  rs[r] = aux;
  return i + 1; // retorna o novo pivo
}
void ordenacao_por_quicksort(Restaurante **rs, int p, int r) {
  if (p < r) {
    int q = particiona(rs, p, r);
    ordenacao_por_quicksort(rs, p, q - 1);
    ordenacao_por_quicksort(rs, q + 1, r);
  }
}
void liberar_memoria(Colecao_Restaurantes *c) {
  for (int i = 0; i < 500; i++) {
    free(c->restaurantes[i]);
  }

  free(c);
}

void retirar_quebra_de_linha(char *x) {
  for (int i = 0; x[i] != '\0'; i++) {
    if (x[i] == '\n' || x[i] == '\r') {
      x[i] = '\0';
      return;
    }
  }
}
void print_restaurantes(Restaurante *rs[], int end) {
  char buffer[300];
  while (end-- > 0) {
    formatar_restaurante(*rs++, buffer);
    printf("%s\n", buffer);
  }
}

int get_maior_capacidade(Restaurante *rs[], int end) {
  int maior = rs[0]->capacidade;
  int n = 0, atual;

  for (int i = 0; i < end; i++) {
    atual = rs[i]->capacidade;
    if (atual > maior) {
      maior = atual;
    }
  }

  return maior;
}

void ordenacao_por_insercao(Restaurante *rs[], int n, int k) {
  int j;
  clock_t inicio = clock();

  for (int i = 1; i < n; i++) {
    Restaurante *chave = rs[i];
    // se i > k, significa que já passamos dos nossos K-top. O j só vai
    // decrementar a partir de K - 1 agora

    j = (i < k) ? i - 1 : k - 1;

    compInsercao++;
    while (j >= 0 && strcmp(chave->nome, rs[j]->nome) < 0) {
      rs[j + 1] = rs[j];
      j--;
      movInsercao++;
    }

    rs[j + 1] = chave;
    movInsercao++;

    clock_t fim = clock();
    tempoInsercao += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  }
}

int esquerda(int i) { return (2 * i) + 1; }
int direita(int i) { return (2 * i) + 2; }
int tamanhoHeap = 0;
void maximiza_heap(Restaurante *rs[], int i) {
  int r = direita(i);
  int l = esquerda(i);
  int maior = i;

  if (l < tamanhoHeap) {
    int comp = compareTo(rs[l]->data_abertura, rs[maior]->data_abertura);
    compHeap += 2;
    if ((comp > 0) || (comp == 0 && strcmp(rs[l]->nome, rs[maior]->nome) > 0)) {
      maior = l;
    }
  }
  if (r < tamanhoHeap) {
    compHeap += 2;

    int comp = compareTo(rs[r]->data_abertura, rs[maior]->data_abertura);
    if ((comp > 0) || (comp == 0 && strcmp(rs[r]->nome, rs[maior]->nome) > 0)) {
      maior = r;
    }
  }

  if (maior != i) {
    movHeap += 3;
    Restaurante *tmp = rs[i];
    rs[i] = rs[maior];
    rs[maior] = tmp;

    maximiza_heap(rs, maior);
  }
}

void constroi_max_heap(Restaurante *rs[], int n) {
  tamanhoHeap = n;
  for (int i = (i / 2) - 1; i >= 0; i--) {
    maximiza_heap(rs, i);
  }
}

void heapsort(Restaurante *rs[], int n) {
  constroi_max_heap(rs, n);

  for (int i = n - 1; i > 0; i--) {
    Restaurante *tmp = rs[0];
    rs[0] = rs[i];
    rs[i] = tmp;
    tamanhoHeap--;
    movHeap += 3;
    maximiza_heap(rs, 0);
  }
}
int main() {
  Colecao_Restaurantes *c = ler_csv();
  char s[500], buffer[300];
  Restaurante *rs[500];

  // questão 2
  // int id = 0, end = 0;
  // fgets(s, sizeof(s), stdin);
  // sscanf(s, "%d", &id);

  // while (id != -1) {
  //   rs[end++] = pesquisa_sequencial_por_id(c, id);
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }
  // int k = 10;
  // ordenacao_por_insercao(rs, end, ++k);

  // FILE *logInsercao = fopen("897962_insercao.txt", "w");
  // if (logInsercao) {
  //   fprintf(logInsercao, "%d\t%d\t%lf\t%d\n", MATRICULA, compInsercao,
  //           tempoInsercao, movInsercao);
  //   fclose(logInsercao);
  // }
  // questão 4

  // int id = 0, end = 0, k = 10;
  // fgets(s, sizeof(s), stdin);
  // sscanf(s, "%d", &id);

  // while (id != -1) {
  //   rs[end++] = pesquisa_sequencial_por_id(c, id);
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }

  // heapsort(rs, end);
  // print_restaurantes(rs, end);

  // questão 5

  Lista *lista = (Lista *)malloc(sizeof(Lista));
  Celula *cabeca = (Celula *)malloc(sizeof(Celula));
  lista->primeiro = cabeca;
  lista->ultimo = cabeca;

  int id, end = 0;
  fgets(s, sizeof(s), stdin);
  sscanf(s, "%d", &id);

  while (id != -1) {
    inserirFim(lista, pesquisa_sequencial_por_id(c, id));
    end++;
    fgets(s, sizeof(s), stdin);
    sscanf(s, "%d", &id);
  }

  int n, pos, valor, size = 0;
  scanf("%d", &n);
  Restaurante *removidos[100];
  char comando[2];

  for (int i = 0; i < n; i++) {
    scanf("%s", comando);

    if (strcmp(comando, "II") == 0) {
      scanf("%d", &valor);
      inserirInicio(lista, pesquisa_sequencial_por_id(c, valor));
    } else if (strcmp(comando, "I*") == 0) {
      scanf("%d %d", &pos, &valor);
      inserir(lista, pesquisa_sequencial_por_id(c, valor), pos);
    } else if (strcmp(comando, "IF") == 0) {
      scanf("%d", &valor);
      inserirFim(lista, pesquisa_sequencial_por_id(c, valor));
    } else if (strcmp(comando, "RI") == 0) {
      Restaurante *r = removerInicio(lista);
      removidos[size++] = r;
    } else if (strcmp(comando, "R*") == 0) {
      scanf("%d", &pos);
      Restaurante *r = remover(lista, pos);
      removidos[size++] = r;
    } else if (strcmp(comando, "RF") == 0) {
      Restaurante *r = removerFim(lista);
      removidos[size++] = r;
    }
  }

  for (int i = 0; i < size; i++) {
    printf("(R)%s\n", removidos[i]->nome);
  }

  mostrar(lista);
  liberar_memoria(c);
}
