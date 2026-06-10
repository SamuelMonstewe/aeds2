import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

class Restaurante implements Comparable<Restaurante> {
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

  public Restaurante() {
  }

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

  @Override
  public String toString() {
    return String.format("[%d ## %s ## %s ## %d ## %.1f ## [%s] ## %s ## %s-%s ## %s ## %b]", id, nome, cidade,
        capacidade, notaMedia, tiposCozinhaFormatado(), faixaPrecoFormatado(), horarioAbertura.formatar(),
        horarioFechamento.formatar(),
        dataAbertura.formatar(), aberto);

  }

  @Override
  public int compareTo(Restaurante outro) {
    return this.getNome().compareTo(outro.getNome());
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

class Node<T extends Comparable<T>> {
  int h;
  T key;
  Node<T> left;
  Node<T> right;

  public Node(T x) {
    this.left = null;
    this.right = null;
    this.key = x;
    this.h = 0;
  }

  int getHeight() {
    return getHeight(this);
  }

  int getHeight(Node<T> node) {
    if (node == null) {
      return -1;
    }

    int height_l = (node.left != null) ? node.left.h : -1;
    int height_r = (node.right != null) ? node.right.h : -1;

    return 1 + Math.max(height_l, height_r);
  }

  int getBalanceFactor() {
    return getBalanceFactor(this);
  }

  int getBalanceFactor(Node<T> node) {
    int h_r = getHeight(node.right);
    int h_l = getHeight(node.left);

    return h_l - h_r;
  }
}

class AVL<T extends Comparable<T>> {
  Node<T> root;
  static int compArvore = 0;

  void inorderTraversal() {
    inorderTraversal(root);
  }

  void inorderTraversal(Node<T> node) {
    if (node != null) {
      inorderTraversal(node.left);
      // O método padrão toString() substitui o método customizado formatar()
      System.out.println(node.key.toString());
      inorderTraversal(node.right);
    }
  }

  boolean search(T x) {
    System.out.print("raiz ");
    return search(root, x);
  }

  boolean search(Node<T> node, T x) {
    compArvore++;
    if (node == null) {
      return false;
    }

    int result = x.compareTo(node.key);
    compArvore++;

    if (result == 0) {
      return true;
    }
    compArvore++;

    if (result < 0) {
      System.out.print("esq ");
      return search(node.left, x);
    } else {
      System.out.print("dir ");
      return search(node.right, x);
    }
  }

  void insert(T x) {
    this.root = insert(this.root, x);
  }

  Node<T> insert(Node<T> node, T x) {
    compArvore++;
    if (node == null) {
      return new Node<>(x);
    }

    compArvore++;
    if (node.key.compareTo(x) > 0) {
      node.left = insert(node.left, x);
    } else {
      node.right = insert(node.right, x);
    }

    return balance(node);
  }

  Node<T> balance(Node<T> node) {
    int factorBalance = node.getBalanceFactor();

    compArvore++;
    if (factorBalance >= -1 && factorBalance <= 1) {
      node.h = node.getHeight();
      return node;
    } else if (factorBalance == 2) {
      compArvore++;
      int factorBalanceLeft = node.left.getBalanceFactor();

      if (factorBalanceLeft < 0) {
        node.left = rotateForLeft(node.left);
      }

      node = rotateForRight(node);
    } else {
      int factorBalanceRight = node.right.getBalanceFactor();

      compArvore++;
      if (factorBalanceRight > 0) {
        node.right = rotateForRight(node.right);
      }
      node = rotateForLeft(node);
    }

    return node;
  }

  Node<T> rotateForRight(Node<T> node) {
    Node<T> y = node.left;
    node.left = y.right;
    y.right = node;

    y.h = y.getHeight();
    node.h = node.getHeight();

    return y;
  }

  Node<T> rotateForLeft(Node<T> node) {
    Node<T> y = node.right;
    node.right = y.left;
    y.left = node;

    y.h = y.getHeight();
    node.h = node.getHeight();

    return y;
  }
}

class NodeBST {
  int capacity;
  AVL<String> rootAVL;
  NodeBST left;
  NodeBST right;

  public NodeBST() {

  }

  public NodeBST(int capacity, AVL<String> root, NodeBST left, NodeBST right) {
    this.capacity = capacity;
    this.rootAVL = root;
    this.left = left;
    this.right = right;
  }
}

class ArvoreBinaria {
  NodeBST root;

  public ArvoreBinaria() {
    this.root = null;
  }

  NodeBST insert(int capacity, String nome) {
    root = insert(root, capacity, nome);
    return root;

  }

  NodeBST insert(NodeBST node, int capacity, String nome) {
    if (node == null) {
      NodeBST newNode = new NodeBST(capacity, new AVL<String>(), null, null);
      newNode.rootAVL.insert(nome);
      return newNode;
    }

    if (node.capacity == capacity) {
      node.rootAVL.insert(nome);
    } else if (capacity < node.capacity) {
      node.left = insert(node.left, capacity, nome);
    } else if (capacity > node.capacity) {
      node.right = insert(node.right, capacity, nome);
    }

    return node;
  }

  boolean search(String nome) {
    System.out.print("RAIZ ");
    if (search(root, nome)) {
      System.out.print("SIM ");
      return true;
    }

    System.out.println("NAO");
    return false;
  }

  boolean search(NodeBST node, String nome) {
    if (node == null)
      return false;

    if (node.rootAVL.search(nome)) {
      return true;
    }

    System.out.print("ESQ ");
    if (search(node.left, nome)) {
      return true;
    }

    System.out.print("DIR ");
    if (search(node.right, nome)) {
      return true;
    }

    return false;
  }

  void inorderTraversal(NodeBST node) {
    if (node != null) {
      inorderTraversal(node.left);
      node.rootAVL.inorderTraversal();
      inorderTraversal(node.right);
    }
  }

  void inorderTraversal() {
    inorderTraversal(root);
  }

}

class Tp04 {
  public static Restaurante pesquisaSequencialPorNome(Restaurante[] rs, String nome, int end) {

    for (int i = 0; i < end; i++) {
      if (rs[i].getNome().compareTo(nome) == 0) {
        return rs[i];
      }
    }

    return null;
  }

  public static Restaurante pesquisaSequencialPorId(ColecaoRestaurantes c, int id) {
    Restaurante[] r = c.getRestaurantes();
    for (Restaurante restaurante : r) {
      if (restaurante != null && restaurante.getId() == id) {
        return restaurante;
      }
    }

    return null;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();

    Restaurante[] rs = new Restaurante[500];

    // questão 1
    // AVL<Restaurante> a = new AVL<>();
    // int id = 0;
    // id = s.nextInt();

    // long inicio = System.nanoTime();
    // double tempoArvore = 0.0;

    // while (id != -1) {
    // a.insert(pesquisaSequencialPorId(c, id));
    // id = s.nextInt();
    // }
    // s.nextLine();
    // String chave;

    // chave = s.nextLine();

    // while (!chave.equals("FIM")) {
    // System.out.print("raiz ");
    // Restaurante restauranteBusca = new Restaurante();
    // restauranteBusca.setNome(chave);

    // a.search(restauranteBusca);

    // chave = s.nextLine();
    // }

    // a.inorderTraversal();

    // long fim = System.nanoTime();
    // tempoArvore += (fim - inicio) / 1000000.0;

    // try (BufferedWriter bw = new BufferedWriter(new
    // FileWriter("897962_arvore_avl.txt"))) {
    // String conteudo = "897962\t" + AVL.compArvore + "\t" + tempoArvore
    // + "\t" + "\n";
    // bw.write(conteudo);
    // } catch (IOException e) {
    // System.out.println(e);
    // }

    // questão 6
    ArvoreBinaria a = new ArvoreBinaria();
    int id, end = 0;

    id = s.nextInt();

    while (id != -1) {
      Restaurante r = pesquisaSequencialPorId(c, id);
      rs[end++] = r;
      int x = r.getCapacidade() % 15;
      a.insert(x, r.getNome());
      id = s.nextInt();
    }

    String nome;
    s.nextLine();
    nome = s.nextLine();

    while (!(nome.equals("FIM"))) {
      if (a.search(nome)) {
        Restaurante r = pesquisaSequencialPorNome(rs, nome, end);

        System.out.println(r.formatar());
      }

      nome = s.nextLine();
    }
    s.close();
  }
}
