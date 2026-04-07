import java.util.Scanner;

class Restaurante {
  private int id;
  private String nome;
  private String cidade;
  private int capacidade;
  private double notaMedia;
  private String[] tipoCozinha;
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
      String[] tipoCozinha,
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
    this.tipoCozinha = tipoCozinha;
    this.faixaPreco = faixaPreco;
    this.horarioAbertura = horarioAbertura;
    this.horarioFechamento = horarioFechamento;
    this.dataAbertura = dataAbertura;
    this.aberto = aberto;
  }

  public int getId() {
    return id;
  }

  public void setId(final int id) {
    this.id = id;
  }

  public String getNome() {
    return nome;
  }

  public void setNome(final String nome) {
    this.nome = nome;
  }

  public String getCidade() {
    return cidade;
  }

  public void setCidade(final String cidade) {
    this.cidade = cidade;
  }

  public int getCapacidade() {
    return capacidade;
  }

  public void setCapacidade(final int capacidade) {
    this.capacidade = capacidade;
  }

  public double getNotaMedia() {
    return notaMedia;
  }

  public void setNotaMedia(final double notaMedia) {
    this.notaMedia = notaMedia;
  }

  public String[] getTipoCozinha() {
    return tipoCozinha;
  }

  public void setTipoCozinha(final String[] tipoCozinha) {
    this.tipoCozinha = tipoCozinha;
  }

  public int getFaixaPreco() {
    return faixaPreco;
  }

  public void setFaixaPreco(final int faixaPreco) {
    this.faixaPreco = faixaPreco;
  }

  public Hora getHorarioAbertura() {
    return horarioAbertura;
  }

  public void setHorarioAbertura(final Hora horarioAbertura) {
    this.horarioAbertura = horarioAbertura;
  }

  public Hora getHorarioFechamento() {
    return horarioFechamento;
  }

  public void setHorarioFechamento(final Hora horarioFechamento) {
    this.horarioFechamento = horarioFechamento;
  }

  public Data getDataAbertura() {
    return dataAbertura;
  }

  public void setDataAbertura(final Data dataAbertura) {
    this.dataAbertura = dataAbertura;
  }

  public boolean isAberto() {
    return aberto;
  }

  public void setAberto(final boolean aberto) {

    this.aberto = aberto;
  }

  public static Restaurante parseRestaurante(final String s) {
    return new Restaurante(s);
  }
}

class Hora {
  private int hora;
  private int minuto;

  public Hora(final int hora, final int minuto) {
    this.hora = hora;
    this.minuto = minuto;
  }

  public void setHora(final int hora) {
    this.hora = hora;
  }

  public void setMinuto(final int minuto) {
    this.minuto = minuto;
  }

  public static Hora parseHora(final String s) {
    final Scanner sc = new Scanner(s).useDelimiter(":");
    final int hora = sc.nextInt();
    final int minuto = sc.nextInt();
    sc.close();

    return new Hora(hora, minuto);
  }

  public String formatar() {
    return String.format("%d:%d", hora, minuto);
  }
}

class Data {
  private int ano;
  private int mes;
  private int dia;

  public Data(final int ano, final int mes, final int dia) {
    this.ano = ano;
    this.mes = mes;
    this.dia = dia;
  }

  public void setAno(final int ano) {
    this.ano = ano;
  }

  public void setMes(final int mes) {
    this.mes = mes;
  }

  public void setDia(final int dia) {
    this.dia = dia;
  }

  public static Data parseData(final String s) {
    final Scanner sc = new Scanner(s).useDelimiter("-");
    final int ano = sc.nextInt();
    final int mes = sc.nextInt();
    final int dia = sc.nextInt();
    sc.close();

    return new Data(ano, mes, dia);
  }

  public String formatar() {
    return String.format("%d/%d/%d", dia, mes, ano);
  }
}

class Tp02 {
  public static void main(final String[] args) {
    final Hora hora = Hora.parseHora("14:45");
    System.out.println(hora.formatar());
  }
}
