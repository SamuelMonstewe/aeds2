import java.util.*;

class Celula {
  Celula prox;
  Celula ant;
  int elemento;
}

class Lista {
  Celula primeiro;
  Celula ultimo;

  public Lista() {
    Celula cabeca = new Celula();
    primeiro = cabeca;
    ultimo = cabeca;
  }

  public void inserirInicio(int x) {
    Celula nova = new Celula();
    nova.elemento = x;

    if (primeiro == ultimo) {
      ultimo.prox = nova;
      nova.ant = ultimo;
      ultimo = nova;
      return;
    }

    nova.prox = primeiro.prox;
    nova.ant = primeiro;

    primeiro.prox.ant = nova;
    primeiro.prox = nova;
    nova = null;
  }

  public void inserirFim(int x) {
    Celula nova = new Celula();
    nova.elemento = x;

    ultimo.prox = nova;
    nova.ant = ultimo;
    ultimo = nova;

    nova.prox = null;
    nova = null;
  }

  public void inserir(int x, int pos) {
    int tam = tamanho();

    if (pos < 0 || pos > tam) {
      return;
    } else if (pos == 0) {
      inserirInicio(x);
    } else if (pos == tam) {
      inserirFim(x);
    } else {
      Celula nova = new Celula();
      nova.elemento = x;

      Celula tmp = primeiro;
      int j = 0;

      while (j <= pos) {
        tmp = tmp.prox;
        j++;
      }

      tmp.ant.prox = nova;
      nova.ant = tmp.ant;
      tmp.ant = nova;
      nova.prox = tmp;
      nova = null;
    }

  }

  public int removerFim() {
    if (primeiro == ultimo) {
      System.exit(1);
    }
    int el = ultimo.elemento;
    ultimo = ultimo.ant;
    ultimo.prox = null;

    return el;
  }

  public int removerInicio() {
    int el = primeiro.prox.elemento;

    if (primeiro == ultimo) {
      System.exit(1);
    }

    primeiro = primeiro.prox;
    primeiro.ant = null;

    return el;
  }

  public int remover(int pos) {
    int tam = tamanho();
    int el = 0;
    if (primeiro == ultimo || pos >= tam || pos < 0) {
      System.exit(1);
    } else if (pos == 0) {
      el = removerInicio();
    } else if (pos == tam - 1) {
      el = removerFim();
    } else {
      Celula tmp = primeiro;
      int j = 0;

      while (j <= pos) {
        tmp = tmp.prox;
        j++;
      }

      el = tmp.elemento;
      tmp.ant.prox = tmp.prox;
      tmp.prox = tmp.ant;
      tmp.ant = null;
      tmp.prox = null;
    }

    return el;
  }

  public int tamanho() {
    Celula tmp = primeiro;
    int n = 0;

    while (tmp != null) {
      tmp = tmp.prox;
      n++;
    }

    return n;
  }

  public void mostrar() {
    System.out.print("[ ");
    Celula tmp = primeiro.prox;

    while (tmp != null) {
      System.out.print(tmp.elemento + " ");
      tmp = tmp.prox;
    }

    System.out.print("]");
  }
}

class ListaDupla {
  public static void main(String[] args) {
    Lista lista = new Lista();
    lista.inserirFim(1);
    lista.inserirFim(2);
    lista.inserirFim(3);
    lista.inserirFim(4);
    lista.inserirFim(5);
    lista.remover(2);
    lista.mostrar();
  }
}
