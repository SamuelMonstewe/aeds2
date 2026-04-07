import java.util.Scanner;

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
    return String.format("%d:%d", hora, minuto);
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
    Hora hora = Hora.parseHora("14:45");
    System.out.println(hora.formatar());
  }
}
