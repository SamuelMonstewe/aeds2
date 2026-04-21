class Celula {
  int elemento;
  Celula prox;
}

class Pilha {
  Celula topo;

  Pilha() {
    topo = null;
  }

  public void inserir(int x) {
    Celula tmp = new Celula();

    if (topo == null) {
      topo = tmp;
      topo.elemento = x;
    } else {
      tmp.prox = topo;
      topo = tmp;
      tmp.elemento = x;
    }
  }

  public int remover() {
    if (topo == null) {
      System.out.println("Vazia!");
      return -1;
    } else {
      Celula tmp = topo;
      int el = tmp.elemento;
      topo = topo.prox;
      tmp = tmp.prox = null;
      return el;
    }
  }

  public void mostrar() {
    if (topo == null) {
      System.out.println("Vazia!");
      return;
    }

    Celula tmp = topo;
    System.out.print("[");
    while (tmp != null) {
      System.out.print(tmp.elemento + " ");
      tmp = tmp.prox;
    }
    System.out.print("]");
  }
}

class PilhaFlexivel {
  public static void main(String[] args) {
    Pilha pilha = new Pilha();

    pilha.inserir(1);
    pilha.inserir(2);
    pilha.inserir(3);
    pilha.inserir(4);
    System.out.println(pilha.remover());
    System.out.println(pilha.remover());
    System.out.println(pilha.remover());
    System.out.println(pilha.remover());
    System.out.println(pilha.remover());
  }
}
