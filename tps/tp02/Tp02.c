#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  sprintf(buffer, "%d/%d/%d", data->dia, data->mes, data->ano);
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

  sscanf(s, "%d,%[^,],%[^,],%d,%lf,%[^,],%[^,],%[^,],%[^,],%[^,]", &r->id,
         r->nome, r->cidade, &r->capacidade, &r->avaliacao, strTiposCozinha,
         strFaixaPreco, strHorario, strDataAbertura, strAberto);

  strHorario[5] = '\0';

  r->horario_abertura = parse_hora(strHorario);
  r->horario_fechamento = parse_hora(strHorario + 6);
  r->data_abertura = parse_data(strDataAbertura);
  r->aberto = strcmp("true", strAberto) ? 0 : 1;

  char t1[30];
  char t2[30];

  sscanf(strTiposCozinha, "%[^;];%[^\n]", t1, t2);

  int tam1 = 0;
  while (t1[tam1] != '\0') {
    tam1++;
  }

  int tam2 = 0;
  while (t2[tam2] != '\0') {
    tam2++;
  }

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
  // printf("%s %s %s %s %s %s %d %d", r->tipos_cozinha[0], r->tipos_cozinha[1],
  //        strFaixaPreco, strHorario, strDataAbertura, strAberto, r->aberto,
  //        r->faixa_preco);
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
          "[%d ## %s ## %s ## %d ## %.2lf ## [%s,%s] ## %s ## "
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
Colecao_Restaurantes *ler_csv() {}

int main() {
  Colecao_Restaurantes c;
  ler_csv_colecao(&c, "restaurantes.csv");
}
