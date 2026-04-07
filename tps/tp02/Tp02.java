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
    return String.format("%d/%d/%d", dia, mes, ano);
  }
}

class Tp02 {
  public static void main(String[] args) {
    String rest = "1,Classic Palace Works,Zurich,168,3.9,churrasco;internacional,$$,11:00-20:00,2018-03-31,false";
    Restaurante restaurante = Restaurante.parseRestaurante(rest);
    System.out.println(restaurante.formatar());
  }
}
