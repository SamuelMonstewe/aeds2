class Lista {
  int[] array;
  int n = 0; // n marca a qtd de elementos, sendo esses localizados nas posições de 0 a n-1

  public Lista() {
    array = new int[6];
    n = 0;
  }

  public Lista(int tamanho) {
    array = new int[tamanho];
    n = 0;
  }

  void inserirInicio(int value) {
    if (n >= array.length) {
      System.out.println("lista cheia!");
      return;
    }

    for (int i = n; i > 0; i--) {
      array[i] = array[i - 1];
    }

    array[0] = value;
    n++;
  }

  void inserirFim(int value) {
    if (n >= array.length) {
      System.out.println("lista cheia!");
      return;
    }

    array[n] = value;
    n++;
  }

  void inserir(int index, int value) {
    if (n >= array.length) {
      System.out.println("lista cheia!");
      return;
    }

    for (int i = n; i > index; i--) {
      array[i] = array[i - 1];
    }

    array[index] = value;
    n++;
  }

  int removerInicio() {
    if (n == 0) {
      System.out.println("lista vazia!");
      return 0;
    }

    int resp = array[0];
    n--;

    for (int i = 0; i < n; i++) {
      array[i] = array[i + 1];
    }

    return resp;
  }

  int removerFim() {
    if (n == 0) {
      System.out.println("lista vazia!");
      return 0;
    }

    return array[--n];
  }

  int remover(int index) {
    if (n == 0) {
      System.out.println("lista vazia!");
      return 0;
    }

    int resp = array[index];
    n--;

    for (int i = index; i < n; i++) {
      array[i] = array[i + 1];
    }

    return resp;
  }

  void printLista() {
    System.out.print("[");
    for (int i = 0; i < n; i++) {
      System.out.print(array[i] + ", ");
    }

    System.out.print("]");
  }
}

public class ListaLinear {
  public static void main(String[] args) {
    Lista lista = new Lista();
    lista.inserirFim(1);
    lista.inserirFim(2);
    lista.inserirFim(3);
    lista.inserirFim(5);

    lista.inserirInicio(6);
    lista.inserirInicio(7);
    lista.printLista();
  }
}
