#include <stdio.h>

typedef struct {
  int hora;
  int minuto;
} Hora;

Hora parse_hora(char *s) {}
void formatar_hora(Hora *hora, char *buffer) {}

typedef struct {
  int ano;
  int mes;
  int dia;
} Data;

Data parse_data(Data *data, char *buffer) {}
void formatar_data(Data *data, char *buffer) {}

typedef struct {
  int id;
  char *nome;
  char *cidade;
  int capacidade;
  double avaliacao;
  int n_tipos_cozinha;
  char **tipos_cozinha;
  int faixa_preco;
  Hora horario_abertura;
  Hora horario_fechamento;
  Data data_abertura;
  int aberto;
} Restaurante;

Restaurante *parse_restaurante(char *s) {}
void formatar_restaurante(Restaurante *restaurante, char *buffer) {}

typedef struct {
  int tamanho;
  Restaurante **restaurantes;
} Colecao_Restaurantes;

void ler_csv_colecao(Colecao_Restaurantes *c, char *path) {}
Colecao_Restaurantes *ler_csv() {}

int main() {}
