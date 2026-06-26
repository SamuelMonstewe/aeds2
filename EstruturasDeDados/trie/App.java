import java.util.*;

class Celula {
  Node filho;
  char letra;
  Celula prox;

  public Celula(Node f, char l) {
    filho = f;
    letra = l;
    prox = null;
  }
}

class Node {
  Celula primeiro;
  char letra;
  boolean fim;

  public Node(Celula p, char l) {
    primeiro = p;
    letra = l;
    fim = false;
  }

  Celula inserirInicio(char c) {
    Celula cel = new Celula(new Node(null, c), c);
    cel.prox = primeiro;
    primeiro = cel;

    return primeiro;
  }

  Celula inserirInicioAux(char c) {
    primeiro = inserirInicio(c);
    return primeiro;
  }

  Celula pesquisar(char c) {
    for (Celula i = primeiro; i != null; i = i.prox) {
      if (i.letra == c)
        return i;
    }

    return null;
  }
}

class Trie {
  Node root;

  public Trie() {
    root = new Node(null, ' ');
  }

  Node inserir(Node node, String palavra, int p) {
    if (p >= palavra.length()) {
      node.fim = true;
      return node;
    }

    Celula c = node.pesquisar(palavra.charAt(p));

    if (c == null) {
      c = node.inserirInicioAux(palavra.charAt(p));
    }

    inserir(c.filho, palavra, p + 1);

    return node;
  }

  void inserir(String palavra) {
    root = inserir(root, palavra, 0);
  }

  void mostrar() {
    mostrar(root, "");
  }

  void mostrar(Node node, String s) {
    if (node.fim) {
      System.out.println(s);
    }

    for (Celula i = node.primeiro; i != null; i = i.prox) {
      mostrar(i.filho, s + i.letra);
    }
  }

  Node buscarNo(Node node, String prefixo, int p) {
    if (p >= prefixo.length()) {
      return node;
    }

    Celula c = node.pesquisar(prefixo.charAt(p));

    if (c == null) {
      return null;
    }

    return buscarNo(c.filho, prefixo, p + 1);
  }

  void startsWith(String prefixo) {
    Node node = buscarNo(root, prefixo, 0);

    if (node == null)
      return;

    mostrar(node, prefixo);
  }

  int contarPalavras() {
    return contarPalavras(root);
  }

  int contarPalavras(Node node) {
    int total = (node.fim) ? 1 : 0;

    for (Celula i = node.primeiro; i != null; i = i.prox) {
      total += contarPalavras(i.filho);
    }

    return total;
  }

  void deletar(String palavra) {
    deletar(root, palavra, 0);
  }

  boolean deletar(Node node, String palavra, int p) {
    if (node.fim && p >= palavra.length()) {
      node.fim = false;
      return node.primeiro == null;
    }

    Celula c = node.pesquisar(palavra.charAt(p));

    if (c == null) {
      return false;
    }

    boolean possoDeletar = deletar(c.filho, palavra, p + 1);

    if (possoDeletar) {
      if (c == node.primeiro) {
        node.primeiro = null;
      } else {
        Celula i = node.primeiro;

        while (i.prox != c) {
          i = i.prox;
        }

        i.prox = c.prox;
      }

      c.filho = null;
      c = null;

    }

    if (node.fim == false && node.primeiro == null) {
      return true;
    }

    return false;
  }
}

class App {
  public static void main(String[] args) {
    Trie t = new Trie();

    t.inserir("mar");
    t.inserir("marujo");
    t.inserir("marta");
    t.inserir("marte");
    t.inserir("martelo");

    t.inserir("casaco");
    t.inserir("castelo");
    t.inserir("carro");

    t.inserir("sol");
    t.inserir("soldado");
    t.inserir("par");
    t.inserir("parede");

    t.inserir("a");
    t.inserir("b");

    t.deletar("martelo");
    t.mostrar();
  }
}
