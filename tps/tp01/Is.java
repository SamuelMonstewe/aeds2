import java.util.Scanner;

public class Is {
  public static boolean isSomenteVogais(String s) {
    char[] v = { 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };

    for (int i = 0; i < s.length(); i++) {
      int dir = v.length - 1, esq = 0, meio;
      boolean resp = false;

      // aqui eu aplico a busca binária para ver se o caractere atual consta no array
      // de vogais (as vogais estão ordenadas conforme o padrão ascii)
      while (esq <= dir) {
        meio = (dir + esq) / 2;
        int diff = (int) s.charAt(i) - (int) v[meio];

        if (diff == 0) {
          resp = true;
          esq = v.length;
        } else if (diff > 0) {
          esq = meio + 1;
        } else {
          dir = meio - 1;
        }
      }

      if (!resp) // se depois da pesquisa binaria eu nao ter identificado uma vogal, nem
                 // precisa seguir com o procedimento
        return false;

    }

    return true;
  }

  public static boolean isSomenteConsoantes(String s) {
    char[] c = {
        'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z', 'b',
        'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',

    };

    for (int i = 0; i < s.length(); i++) {
      int dir = c.length - 1, esq = 0, meio;
      boolean resp = false;
      // aqui eu aplico a busca binária para ver se o caractere atual consta no array
      // de consoantes (as consoantes estão ordenadas conforme o padrão ascii)
      while (esq <= dir) {
        meio = (dir + esq) / 2;

        int diff = (int) s.charAt(i) - (int) c[meio];

        if (diff == 0) {
          resp = true;
          esq = c.length;
        } else if (diff > 0) {
          esq = meio + 1;
        } else {
          dir = meio - 1;
        }
      }

      if (!resp) // se depois da pesquisa binaria eu nao ter identificado uma consoante, nem
                 // precisa seguir com o procedimento
        return false;

    }

    return true;
  }

  public static boolean isNumeroInteiro(String s) {
    for (int i = 0; i < s.length(); i++) {
      char c = s.charAt(i);
      if (!(c >= '0' && c <= '9')) // '0' é 48 e '9' é 57
        return false;
    }
    return true;
  }

  public static boolean isNumeroReal(String s) {
    int pontoOuVirgula = 0;
    for (int i = 0; i < s.length(); i++) {
      char c = s.charAt(i);

      if (c == '.' || c == ',')
        pontoOuVirgula++;
      else if (!(c >= '0' && c <= '9'))
        return false;

      if (pontoOuVirgula > 1)
        return false;
    }

    return true;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);

    String input = s.nextLine();
    while (!(input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M')) {
      System.out.print(isSomenteVogais(input) ? "SIM " : "NAO ");
      System.out.print(isSomenteConsoantes(input) ? "SIM " : "NAO ");
      System.out.print(isNumeroInteiro(input) ? "SIM " : "NAO ");
      System.out.print(isNumeroReal(input) ? "SIM " : "NAO ");
      System.out.println();
      input = s.nextLine();
    }
    s.close();
  }

}
