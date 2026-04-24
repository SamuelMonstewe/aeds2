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
void ordenacao_por_selecao(Restaurante **r, int n) {
  clock_t inicio = clock();
  for (int i = 0; i < n - 1; i++) {
    int menor = i;
    for (int j = i + 1; j < n; j++) {
      compSelecao++;
      if (strcmp(r[j]->nome, r[menor]->nome) < 0) {
        menor = j;
      }
    }

    Restaurante *tmp = r[i];
    r[i] = r[menor];
    r[menor] = tmp;
    movSelecao += 3;
  }
  clock_t fim = clock();
  tempoSelecao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
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
  }
}
void pesquisa_binaria_por_nome(Restaurante **rs, char *x, int end) {
  clock_t inicio = clock();
  int esq = 0, dir = end - 1, resp = 0;

  while (esq <= dir) {
    int meio = (esq + dir) / 2;
    int diff = strcmp(x, rs[meio]->nome);
    if (diff == 0) {
      resp = 1;
      esq = dir + 1;
      compBinaria++;
    } else if (diff < 0) {
      dir = meio - 1;
      compBinaria++;
    } else {
      esq = meio + 1;
      compBinaria++;
    }
  }

  (resp) ? printf("SIM\n") : printf("NAO\n");

  clock_t fim = clock();

  tempoBinaria += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

typedef struct Celula {
  Restaurante *elemento;
  struct Celula *prox;
} Celula;

typedef struct Pilha {
  Celula *topo;
} Pilha;

void inserir(Pilha *pilha, Restaurante *x) {
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

Restaurante *remover(Pilha *pilha) {
  if (pilha->topo == NULL) {
    printf("Vazia!");
    return NULL;
  }
  Restaurante *el;
  Celula *tmp = pilha->topo;
  pilha->topo = tmp->prox;
  el = tmp->elemento;
  free(tmp);
  return el;
}
void mostrar(Pilha *pilha) {
  Celula *tmp = pilha->topo;
  char buffer[300];

  while (tmp != NULL) {
    formatar_restaurante(tmp->elemento, buffer);
    printf("%s\n", buffer);
    tmp = tmp->prox;
  }
}
int main() {
  Colecao_Restaurantes *c = ler_csv();
  char s[500], buffer[300];
  Restaurante *rs[500];

  fgets(s, sizeof(s), stdin);
  int id;
  sscanf(s, "%d", &id);

  // questão 2
  // while (id != -1) {
  //   Restaurante *r = pesquisa_sequencial_por_id(c, id);
  //   formatar_restaurante(r, buffer);
  //   printf("%s\n", buffer);
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }
  // printf("\n");

  // questão 3

  // int end = 0;

  // while (id != -1) {
  //   rs[end] = pesquisa_sequencial_por_id(c, id);
  //   end++;
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }
  // ordenacao_por_selecao(rs, end);

  // print_restaurantes(rs, end)

  // FILE *logS = fopen("897962_selecao.txt", "w");
  // if (logS) {
  //   fprintf(logS, "%d\t%d\t%d\t%lf\n", MATRICULA, compSelecao, movSelecao,
  //           tempoSelecao);
  //   fclose(logS);
  // }

  // questão 6
  // int end = 0;

  // while (id != -1) {
  //   rs[end] = pesquisa_sequencial_por_id(c, id);
  //   end++;
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }

  // ordenacao_por_selecao(rs, end);

  // char nome[300];

  // if (fgets(nome, sizeof(nome), stdin) != NULL) {
  //   retirar_quebra_de_linha(nome);
  // }

  // while (strcmp(nome, "FIM") != 0) {
  //   pesquisa_binaria_por_nome(rs, nome, end);

  //   fgets(nome, sizeof(nome), stdin);

  //   retirar_quebra_de_linha(nome);
  // }

  // FILE *logB = fopen("897962_binaria.txt", "w");
  // if (logB) {
  //   fprintf(logB, "%d\t%d\t%lf\n", MATRICULA, compBinaria, tempoBinaria);
  //   fclose(logB);
  // }

  // questão 8

  // int end = 0;
  // while (id != -1) {
  //   rs[end] = pesquisa_sequencial_por_id(c, id);
  //   end++;
  //   fgets(s, sizeof(s), stdin);
  //   sscanf(s, "%d", &id);
  // }
  // clock_t inicio = clock();
  // ordenacao_por_quicksort(rs, 0, end - 1);
  // clock_t fim = clock();
  // for (int i = 0; i < end; i++) {
  //   formatar_restaurante(rs[i], buffer);
  //   printf("%s\n", buffer);
  // }
  // print_restaurantes(rs, end);
  // tempoQuick += ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  // FILE *logC = fopen("897962_quicksort.txt", "w");
  // if (logC) {
  //   fprintf(logC, "%d\t%d\t%d\t%lf\n", MATRICULA, compQuick, movQuick,
  //           tempoQuick);
  //   fclose(logC);
  // }

  // questão 12
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->topo = NULL;
  int n, valor, size = 0;
  char comando;
  while (id != -1) {
    inserir(pilha, pesquisa_sequencial_por_id(c, id));
    fgets(s, sizeof(s), stdin);
    sscanf(s, "%d", &id);
  }
  scanf("%d", &n);
  Restaurante *removidos[n];
  for (int i = 0; i < n; i++) {
    scanf(" %c", &comando);

    if (comando == 'I') {
      scanf("%d", &valor);
      inserir(pilha, pesquisa_sequencial_por_id(c, valor));
    } else if (comando == 'R') {
      removidos[size++] = remover(pilha);
    }
  }

  for (int j = 0; j < size; j++) {
    printf("(R)%s\n", removidos[j]->nome);
  }
  mostrar(pilha);
  liberar_memoria(c);
  free(pilha);
}
