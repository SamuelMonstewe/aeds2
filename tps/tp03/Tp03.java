import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

class Restaurante {
  private int id;
  private String nome;
  private String cidade;
  private int capacidade;
  private double notaMedia;
  private String[] tiposCozinha;
  private int faixaPreco;
  private Hora horarioAbertura;
  private Hora horarioFechamento;
  private Data dataAbertura;
  private boolean aberto;

  public Restaurante(
      int id,
      String nome,
      String cidade,
      int capacidade,
      double notaMedia,
      String[] tiposCozinha,
      int faixaPreco,
      Hora horarioAbertura,
      Hora horarioFechamento,
      Data dataAbertura,
      boolean aberto) {

    this.id = id;
    this.nome = nome;
    this.cidade = cidade;
    this.capacidade = capacidade;
    this.notaMedia = notaMedia;
    this.tiposCozinha = tiposCozinha;
    this.faixaPreco = faixaPreco;
    this.horarioAbertura = horarioAbertura;
    this.horarioFechamento = horarioFechamento;
    this.dataAbertura = dataAbertura;
    this.aberto = aberto;
  }

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
  }

  public String getNome() {
    return nome;
  }

  public void setNome(String nome) {
    this.nome = nome;
  }

  public String getCidade() {
    return cidade;
  }

  public void setCidade(String cidade) {
    this.cidade = cidade;
  }

  public int getCapacidade() {
    return capacidade;
  }

  public void setCapacidade(int capacidade) {
    this.capacidade = capacidade;
  }

  public double getNotaMedia() {
    return notaMedia;
  }

  public void setNotaMedia(double notaMedia) {
    this.notaMedia = notaMedia;
  }

  public String[] getTipoCozinha() {
    return tiposCozinha;
  }

  public void setTipoCozinha(String[] tiposCozinha) {
    this.tiposCozinha = tiposCozinha;
  }

  public int getFaixaPreco() {
    return faixaPreco;
  }

  public void setFaixaPreco(int faixaPreco) {
    this.faixaPreco = faixaPreco;
  }

  public Hora getHorarioAbertura() {
    return horarioAbertura;
  }

  public void setHorarioAbertura(Hora horarioAbertura) {
    this.horarioAbertura = horarioAbertura;
  }

  public Hora getHorarioFechamento() {
    return horarioFechamento;
  }

  public void setHorarioFechamento(Hora horarioFechamento) {
    this.horarioFechamento = horarioFechamento;
  }

  public Data getDataAbertura() {
    return dataAbertura;
  }

  public void setDataAbertura(Data dataAbertura) {
    this.dataAbertura = dataAbertura;
  }

  public boolean isAberto() {
    return aberto;
  }

  public void setAberto(boolean aberto) {

    this.aberto = aberto;
  }

  private static String[] criarTipos(String tipos) {
    Scanner scTiposRaw = new Scanner(tipos).useDelimiter(";");
    int countTipos = 0;

    while (scTiposRaw.hasNext()) {
      scTiposRaw.next();
      countTipos++;
    }

    scTiposRaw.close();

    String[] tiposCozinha = new String[countTipos];

    Scanner scTipos = new Scanner(tipos).useDelimiter(";");
    for (int i = 0; scTipos.hasNext(); i++) {
      String tipo = scTipos.next();
      tiposCozinha[i] = tipo;
    }

    scTipos.close();

    return tiposCozinha;
  }

  public static Restaurante parseRestaurante(String s) {
    Scanner sc = new Scanner(s).useDelimiter(",");
    int id = sc.nextInt();
    String nome = sc.next();
    String cidade = sc.next();
    int capacidade = sc.nextInt();
    double notaMedia = sc.nextDouble();
    String tipos = sc.next();
    String[] tiposCozinha = criarTipos(tipos);
    int faixaPreco = sc.next().length();

    String horarios = sc.next();
    Scanner scHorarios = new Scanner(horarios).useDelimiter("-");

    Hora horarioAbertura = Hora.parseHora(scHorarios.next());
    Hora horarioFechamento = Hora.parseHora(scHorarios.next());

    scHorarios.close();

    Data dataAbertura = Data.parseData(sc.next());
    boolean aberto = Boolean.parseBoolean(sc.next());

    sc.close();

    return new Restaurante(id, nome, cidade, capacidade, notaMedia, tiposCozinha, faixaPreco, horarioAbertura,
        horarioFechamento, dataAbertura, aberto);

  }

  private String tiposCozinhaFormatado() {
    String tiposCozinha = "";

    for (int i = 0; i < this.tiposCozinha.length; i++) {
      tiposCozinha += this.tiposCozinha[i];
      if (i < this.tiposCozinha.length - 1) {
        tiposCozinha += ",";
      }
    }

    return tiposCozinha;
  }

  private String faixaPrecoFormatado() {
    String faixaPreco = "";

    for (int i = 0; i < this.faixaPreco; i++) {
      faixaPreco += "$";
    }

    return faixaPreco;
  }

  public String formatar() {
    return String.format("[%d ## %s ## %s ## %d ## %.1f ## [%s] ## %s ## %s-%s ## %s ## %b]", id, nome, cidade,
        capacidade, notaMedia, tiposCozinhaFormatado(), faixaPrecoFormatado(), horarioAbertura.formatar(),
        horarioFechamento.formatar(),
        dataAbertura.formatar(), aberto);
  }
}

class ColecaoRestaurantes {
  private int tamanho;
  private Restaurante[] restaurantes;

  public void setTamanho(int tamanho) {
    this.tamanho = tamanho;
  }

  public void setRestaurantes(Restaurante[] restaurantes) {
    this.restaurantes = restaurantes;
  }

  public int getTamanho() {
    return this.tamanho;
  }

  public Restaurante[] getRestaurantes() {
    return this.restaurantes;
  }

  public void lerCsv(String path) {
    String arquivoCSV = path;
    try (BufferedReader br = new BufferedReader(new FileReader(arquivoCSV))) {
      long totalLinhas = Files.lines(Paths.get(arquivoCSV)).count() - 1;
      this.tamanho = (int) totalLinhas;
      String linha = br.readLine();
      int i = 0;
      this.restaurantes = new Restaurante[(int) totalLinhas];
      while ((linha = br.readLine()) != null) {
        Restaurante restaurante = Restaurante.parseRestaurante(linha);
        this.restaurantes[i] = restaurante;
        i++;
      }

    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public static ColecaoRestaurantes lerCsv() {
    ColecaoRestaurantes c = new ColecaoRestaurantes();
    c.lerCsv("/tmp/restaurantes.csv");
    return c;
  }

}

class Hora {
  private int hora;
  private int minuto;

  public Hora(int hora, int minuto) {
    this.hora = hora;
    this.minuto = minuto;
  }

  public void setHora(int hora) {
    this.hora = hora;
  }

  public void setMinuto(int minuto) {
    this.minuto = minuto;
  }

  public static Hora parseHora(String s) {
    Scanner sc = new Scanner(s).useDelimiter(":");
    int hora = sc.nextInt();
    int minuto = sc.nextInt();
    sc.close();

    return new Hora(hora, minuto);
  }

  public String formatar() {
    return String.format("%02d:%02d", hora, minuto);
  }
}

class Data {
  private int ano;
  private int mes;
  private int dia;

  public Data(int ano, int mes, int dia) {
    this.ano = ano;
    this.mes = mes;
    this.dia = dia;
  }

  public void setAno(int ano) {
    this.ano = ano;
  }

  public void setMes(int mes) {
    this.mes = mes;
  }

  public void setDia(int dia) {
    this.dia = dia;
  }

  public int getAno() {
    return this.ano;
  }

  public int getMes() {
    return this.mes;
  }

  public int getDia() {
    return this.dia;
  }

  public static Data parseData(String s) {
    Scanner sc = new Scanner(s).useDelimiter("-");
    int ano = sc.nextInt();
    int mes = sc.nextInt();
    int dia = sc.nextInt();
    sc.close();

    return new Data(ano, mes, dia);
  }

  public String formatar() {
    return String.format("%02d/%02d/%02d", dia, mes, ano);
  }

  public int compareTo(Data outra) {
    if (this.ano != outra.ano) {
      return this.ano - outra.ano;
    }
    if (this.mes != outra.mes) {
      return this.mes - outra.mes;
    }
    return this.dia - outra.dia;
  }
}

class Celula {
  Restaurante elemento;
  Celula prox;
}

class Pilha {
  Celula topo;

  public Pilha() {
    topo = null;
  }

  public void push(Restaurante r) {
    Celula nova = new Celula();
    nova.elemento = r;

    nova.prox = topo;
    topo = nova;
  }

  public Restaurante pop() {
    if (topo == null) {
      return null;
    }

    Celula tmp = topo;
    topo = tmp.prox;
    return tmp.elemento;
  }

  public void mostrar() {
    Celula i = topo;

    while (i != null) {
      System.out.println(i.elemento.formatar());
      i = i.prox;
    }
  }
}

class Tp03 {

  public static int compSequencial = 0;
  public static double tempoSequencial = 0.0;

  public static int compSelecao = 0;
  public static double tempoSelecao = 0.0;
  public static int movSelecao = 0;

  public static Restaurante pesquisaSequencialPorId(ColecaoRestaurantes c, int id) {
    Restaurante[] r = c.getRestaurantes();
    for (Restaurante restaurante : r) {
      if (restaurante != null && restaurante.getId() == id) {
        return restaurante;
      }
    }

    return null;
  }

  public static void pesquisaSequencialPorNome(Restaurante[] rs, String nome, int end) {
    long inicio = System.nanoTime();

    for (int i = 0; i < end; i++) {
      compSequencial++;
      if (rs[i].getNome().compareTo(nome) == 0) {
        System.out.println("SIM");
        long fim = System.nanoTime();
        tempoSequencial += (fim - inicio) / 1000000.0;
        return;
      }
    }
    System.out.println("NAO");

    long fim = System.nanoTime();
    tempoSequencial += (fim - inicio) / 1000000.0;
  }

  public static void ordenacaoPorSelecao(Restaurante[] rs, int k, int n) {
    long tempoInicial = System.nanoTime();

    for (int i = 0; i < k - 1; i++) {
      int menor = i;
      for (int j = i + 1; j < n; j++) {
        compSelecao++;
        if (rs[j].getNome().compareTo(rs[menor].getNome()) < 0) {
          menor = j;
        }
      }

      Restaurante tmp = rs[i];
      rs[i] = rs[menor];
      rs[menor] = tmp;
      movSelecao += 3;
    }
    long tempoFinal = System.nanoTime();
    tempoSelecao += (tempoFinal - tempoInicial) / 1000000.0;

  }

  public static int particiona(Restaurante[] rs, int p, int r) {
    Restaurante x = rs[r]; // pivo

    int i = p - 1;

    for (int j = p; j < r; j++) {
      if (x.getNotaMedia() == rs[j].getNotaMedia()) {
        if (rs[j].getNome().compareTo(x.getNome()) < 0) {
          i++;
          Restaurante tmp = rs[i];
          rs[i] = rs[j];
          rs[j] = tmp;
        }
      } else if (rs[j].getNotaMedia() <= x.getNotaMedia()) {
        i++;
        Restaurante tmp = rs[i];
        rs[i] = rs[j];
        rs[j] = tmp;
      }
    }
    Restaurante aux = rs[i + 1];
    rs[i + 1] = rs[r];
    rs[r] = aux;
    return i + 1;
  }

  public static void quicksort(Restaurante[] rs, int p, int r, int k) {
    if (p < r) {
      int q = particiona(rs, p, r);
      // Basta abandonar a partição à direita toda vez que a partição à esquerda
      // contiver k ou mais itens (UFMG)
      if (q >= k) {
        quicksort(rs, p, q - 1, k);
      } else {
        quicksort(rs, p, q - 1, k);
        quicksort(rs, q + 1, r, k);

      }
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();

    Restaurante[] rs = new Restaurante[500];

    // questão 1
    // int end = 0;
    // int id = s.nextInt();

    // while (id != -1) {
    // rs[end++] = pesquisaSequencialPorId(c, id);
    // id = s.nextInt();
    // }

    // int k = 10;
    // ordenacaoPorSelecao(rs, ++k, end);

    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // int end = 0;
    // int id = s.nextInt();

    // while (id != -1) {
    // rs[end++] = pesquisaSequencialPorId(c, id);
    // id = s.nextInt();
    // }

    // int k = 10;
    // quicksort(rs, 0, end - 1, k);

    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    Pilha pilha = new Pilha();
    int id = s.nextInt();

    while (id != -1) {
      pilha.push(pesquisaSequencialPorId(c, id));
      id = s.nextInt();
    }

    int n = s.nextInt(), valor, size = 0;
    Restaurante removidos[] = new Restaurante[100];
    String comando;

    for (int i = 0; i < n; i++) {
      comando = s.next();

      if (comando.compareTo("I") == 0) {
        valor = s.nextInt();
        pilha.push(pesquisaSequencialPorId(c, valor));
      } else if (comando.compareTo("R") == 0) {
        removidos[size++] = pilha.pop();
      }
    }

    for (int j = 0; j < size; j++) {
      System.out.println("(R)" + removidos[j].getNome());
    }
    pilha.mostrar();
    s.close();
  }
}
