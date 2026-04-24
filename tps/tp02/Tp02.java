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
  Celula prox;
  Restaurante elemento;
}

class Lista {
  Celula primeiro;
  Celula ultimo;

  public Lista() {
    Celula lista = new Celula();
    primeiro = lista;
    ultimo = lista;
  }

  public void inserirInicio(Restaurante restaurante) {
    primeiro.elemento = restaurante;
    Celula novoCabeca = new Celula();
    novoCabeca.prox = primeiro;
    primeiro = novoCabeca;
    novoCabeca.elemento = restaurante;
    novoCabeca = null;
  }

  public void inserir(Restaurante restaurante, int posicao) {
    int tam = tamanho();
    if (posicao < 0 || posicao > tam) {
      return;
    } else if (posicao == 0) {
      inserirInicio(restaurante);
    } else if (posicao == tam) {
      inserirFim(restaurante);
    } else {
      Celula i = primeiro;
      for (int j = 0; j < posicao; j++) {
        i = i.prox;
      }

      Celula tmp = new Celula();
      tmp.elemento = restaurante;
      tmp.prox = i.prox;
      i.prox = tmp;
    }
  }

  public void inserirFim(Restaurante restaurante) {
    Celula novo = new Celula();
    novo.elemento = restaurante;
    novo.prox = null;
    ultimo.prox = novo;
    ultimo = novo;
    novo = null;
  }

  public Restaurante removerInicio() {
    if (primeiro == ultimo) {
      return null;
    }

    Celula tmp = primeiro.prox;
    primeiro.prox = tmp.prox;
    Restaurante r = tmp.elemento;
    tmp.prox = null;
    tmp = null;
    return r;
  }

  public int tamanho() {
    Celula i = primeiro;
    int n = 0;

    while (i.prox != null) {
      n++;
      i = i.prox;
    }

    return n;
  }

  public Restaurante removerFim() {
    if (primeiro == ultimo) {
      return null;
    }

    Celula i = primeiro;

    while (i.prox != ultimo) {
      i = i.prox;
    }

    ultimo = i;
    Restaurante r = i.prox.elemento;
    ultimo.prox = null;
    i = null;
    return r;
  }

  public Restaurante remover(int posicao) {
    int tam = tamanho();
    Restaurante r;
    if (primeiro == ultimo || tam < 0 || posicao >= tam) {
      return null;
    } else if (posicao == 0) {
      r = removerInicio();
    } else if (posicao == tam - 1) {
      r = removerFim();
    } else {
      Celula i = primeiro;
      int j = 0;

      while (j < posicao) {
        i = i.prox;
        j++;
      }

      Celula tmp = i.prox;
      i.prox = tmp.prox;
      r = tmp.elemento;
      tmp.prox = null;
      tmp = null;
    }

    return r;
  }

  public void exibir() {
    Celula i = primeiro.prox;

    while (i != null) {
      System.out.println(i.elemento.formatar());
      i = i.prox;
    }
  }

}

class Tp02 {
  public static int compInsercao = 0;
  public static double tempoInsercao = 0.0;
  public static int movInsercao = 0;

  public static int compSequencial = 0;
  public static double tempoSequencial = 0.0;

  public static int compMerge = 0;
  public static double tempoMerge = 0.0;
  public static int movMerge = 0;

  public static int tamanhoHeap = 0;

  public static int compHeap = 0;
  public static double tempoHeap = 0.0;
  public static int movHeap = 0;

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
      compInsercao++;
      while ((j >= 0) && rs[j].getCidade().compareTo(chave.getCidade()) > 0) {
        rs[j + 1] = rs[j];
        movInsercao++;
        j--;
      }

      movInsercao++;
      rs[j + 1] = chave;
    }

    long tempoFinal = System.nanoTime();
    tempoInsercao += (tempoFinal - tempoInicial) / 1000000.0;
  }

  public static void merge(Restaurante[] rs, int p, int q, int r) {
    int nl = q - p + 1;
    int nr = r - q, i, j;
    Restaurante[] L = new Restaurante[nl];
    Restaurante[] R = new Restaurante[nr];

    for (i = 0; i < nl; i++) {
      L[i] = rs[p + i];
      movMerge++;
    }
    for (j = 0; j < nr; j++) {
      R[j] = rs[q + j + 1];
      movMerge++;
    }

    i = 0;
    j = 0;
    int k = p;

    while (i < nl && j < nr) {
      int diffCidade = L[i].getCidade().compareTo(R[j].getCidade());
      compMerge++;
      if (diffCidade == 0) { // se forem iguais, temos que desempatar
        if (L[i].getNome().compareTo(R[j].getNome()) <= 0) { // desempate pelo nome
          rs[k] = L[i];
          movMerge++;
          i++;
        } else {
          rs[k] = R[j];
          movMerge++;
          j++;
        }
      } else if (diffCidade < 0) {
        rs[k] = L[i];
        movMerge++;
        i++;
      } else {
        rs[k] = R[j];
        movMerge++;
        j++;
      }
      k++;
    }

    while (i < nl) {
      rs[k] = L[i];
      i++;
      k++;
      movMerge++;
    }
    while (j < nr) {
      rs[k] = R[j];
      j++;
      k++;
      movMerge++;
    }
  }

  public static void ordenacaoPorMerge(Restaurante[] rs, int p, int r) {
    if (p >= r) {
      return;
    }
    int q = (p + r) / 2;
    ordenacaoPorMerge(rs, p, q);
    ordenacaoPorMerge(rs, q + 1, r);
    merge(rs, p, q, r);
  }

  public static int pai(int i) {
    return (i - 1) / 2;
  }

  public static int esquerda(int i) {
    return (2 * i) + 1;
  }

  public static int direita(int i) {
    return (2 * i) + 2;
  }

  public static void maximizaHeap(Restaurante[] rs, int i) {
    int l = esquerda(i);
    int r = direita(i);
    int maior = i;

    if (l < tamanhoHeap) {
      int comp = rs[l].getDataAbertura().compareTo(rs[maior].getDataAbertura());
      compHeap += 2;
      if ((comp > 0) || (comp == 0 && rs[l].getNome().compareTo(rs[maior].getNome()) > 0)) {
        maior = l;
      }
    }

    if (r < tamanhoHeap) {
      int comp = rs[r].getDataAbertura().compareTo(rs[maior].getDataAbertura());
      compHeap += 2;
      if ((comp > 0) || (comp == 0 && rs[r].getNome().compareTo(rs[maior].getNome()) > 0)) {
        maior = r;
      }
    }

    if (maior != i) {
      Restaurante tmp = rs[i];
      rs[i] = rs[maior];
      rs[maior] = tmp;
      movHeap += 3;
      maximizaHeap(rs, maior);
    }
  }

  public static void constroiMaxHeap(Restaurante[] rs, int n) {
    tamanhoHeap = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
      maximizaHeap(rs, i);
    }
  }

  public static void ordenacaoPorHeap(Restaurante[] rs, int n) {
    constroiMaxHeap(rs, n);

    for (int i = n - 1; i > 0; i--) {
      Restaurante tmp = rs[0];
      rs[0] = rs[i];
      rs[i] = tmp;
      movHeap += 3;
      tamanhoHeap--;
      maximizaHeap(rs, 0);
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();

    Restaurante[] rs = new Restaurante[500];
    int end = 0;
    int id = s.nextInt();

    // questão 1

    // while (id != -1) {
    // rs[end] = pesquisaSequencialPorId(c, id);
    // end++;
    // id = s.nextInt();
    // }
    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // id = s.nextInt();
    // }
    // questão 4
    // while (id != -1) {
    // rs[end] = pesquisaSequencialPorId(c, id);
    // end++;

    // id = s.nextInt();
    // }

    // ordenacaoPorInsercao(rs, end);

    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_insercao.txt"))) {
    // String conteudo = "897962\t" + compInsercao + "\t" + movInsercao + "\t" +
    // tempoInsercao + "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    // questão 5

    // while (id != -1) {
    // Restaurante res = pesquisaSequencialPorId(c, id);
    // rs[end] = res;
    // end++;
    // id = s.nextInt();
    // }

    // String[] nomes = new String[500];
    // int endNomes = 0;
    // String nome = s.next();

    // nome = s.nextLine();
    // while (!(nome.charAt(0) == 'F' && nome.charAt(1) == 'I' && nome.charAt(2) ==
    // 'M')) {
    // nomes[endNomes] = nome;
    // endNomes++;
    // nome = s.nextLine();
    // }

    // for (int i = 0; i < endNomes; i++) {
    // pesquisaSequencialPorNome(rs, nomes[i], end);
    // }

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_sequencial.txt"))) {
    // String conteudo = "897962\t" + compSequencial + "\t" + tempoSequencial +
    // "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    // questão 7

    // while (id != -1) {
    // rs[end] = pesquisaSequencialPorId(c, id);
    // end++;
    // id = s.nextInt();
    // }

    // long tempoInicial = System.nanoTime();

    // ordenacaoPorMerge(rs, 0, end - 1);

    // long tempoFinal = System.nanoTime();
    // tempoMerge += (tempoFinal - tempoInicial) / 1000000.0;

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_mergesort.txt"))) {
    // String conteudo = "897962\t" + compMerge + "\t" + movMerge + "\t" +
    // tempoMerge + "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // questão 9

    // while (id != -1) {
    // rs[end] = pesquisaSequencialPorId(c, id);
    // end++;
    // id = s.nextInt();
    // }

    // long tempoInicial = System.nanoTime();
    // ordenacaoPorHeap(rs, end);
    // long tempoFinal = System.nanoTime();
    // tempoHeap += (tempoFinal - tempoInicial) / 1000000.0;

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_heapsort.txt"))) {
    // String conteudo = "897962\t" + compHeap + "\t" + movHeap + "\t" +
    // tempoHeap + "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    // for (int i = 0; i < end; i++) {
    // System.out.println(rs[i].formatar());
    // }

    // questão 11
    Lista lista = new Lista();

    while (id != -1) {
      lista.inserirFim(pesquisaSequencialPorId(c, id));
      end++;
      id = s.nextInt();
    }

    int n = s.nextInt(), pos, valor, size = 0;
    Restaurante[] removidos = new Restaurante[100];
    String comando;
    for (int i = 0; i < n; i++) {
      comando = s.next();

      if (comando.compareTo("II") == 0) {
        valor = s.nextInt();
        lista.inserirInicio(pesquisaSequencialPorId(c, valor));
      } else if (comando.compareTo("I*") == 0) {
        pos = s.nextInt();
        valor = s.nextInt();
        lista.inserir(pesquisaSequencialPorId(c, valor), pos);
      } else if (comando.compareTo("IF") == 0) {
        valor = s.nextInt();
        lista.inserirFim(pesquisaSequencialPorId(c, valor));
      } else if (comando.compareTo("RI") == 0) {
        Restaurante r = lista.removerInicio();
        removidos[size++] = r;
      } else if (comando.compareTo("R*") == 0) {
        pos = s.nextInt();
        Restaurante r = lista.remover(pos);
        removidos[size++] = r;
      } else if (comando.compareTo("RF") == 0) {
        Restaurante r = lista.removerFim();
        removidos[size++] = r;
      }
    }

    for (int i = 0; i < size; i++) {
      System.out.println("(R)" + removidos[i].getNome());
    }
    lista.exibir();

    s.close();
  }
}
