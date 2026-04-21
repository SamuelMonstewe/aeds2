import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
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
}

class Tp02 {
  public static int compInsercao = 0;
  public static double tempoInsercao = 0.0;

  public static int compSequencial = 0;
  public static double tempoSequencial = 0.0;

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

  public static void ordenacaoPorInsercao(Restaurante[] rs, int end) {
    long tempoInicial = System.nanoTime();
    int j;

    for (int i = 1; i < end; i++) {
      Restaurante chave = rs[i];
      j = i - 1;
      compInsercao++; // Acumula globalmente baseado na sua lógica original
      while ((j >= 0) && rs[j].getCidade().compareTo(chave.getCidade()) > 0) {
        rs[j + 1] = rs[j];
        j--;
      }

      rs[j + 1] = chave;
    }

    long tempoFinal = System.nanoTime();
    tempoInsercao += (tempoFinal - tempoInicial) / 1000000.0;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();

    // questão 4
    Restaurante[] rs = new Restaurante[100];
    int end = 0;

    int id = s.nextInt();

    // while (id != -1) {
    // rs[end] = pesquisaSequencialPorId(c, id);
    // end++;

    // id = s.nextInt();
    // }

    // ordenacaoPorInsercao(rs, end);
    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // questão 5

    while (id != -1) {
      Restaurante res = pesquisaSequencialPorId(c, id);
      rs[end] = res;
      end++;
      id = s.nextInt();
    }

    String[] nomes = new String[100];
    int endNomes = 0;
    String nome = s.next();

    nome = s.nextLine();
    while (!(nome.charAt(0) == 'F' && nome.charAt(1) == 'I' && nome.charAt(2) == 'M')) {
      nomes[endNomes] = nome;
      endNomes++;
      nome = s.nextLine();
    }

    for (int i = 0; i < endNomes; i++) {
      pesquisaSequencialPorNome(rs, nomes[i], end);
    }

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_insercao.txt"))) {
    // String conteudo = "897962\t" + compInsercao + "\t" + tempoInsercao + "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    try (BufferedWriter bw = new BufferedWriter(new FileWriter("897962_sequencial.txt"))) {
      String conteudo = "897962\t" + compSequencial + "\t" + tempoSequencial + "\n";
      bw.write(conteudo);
    } catch (IOException e) {
      System.out.println(e);
    }

    s.close();
  }
}
