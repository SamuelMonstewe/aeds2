import java.util.Scanner;

public class InversaoRecursivo {
  public static void inversao(String s) {
    inversaoRecursivo(s, 0);
  }

  public static void inversaoRecursivo(String s, int i) {
    if (i == s.length())
      return;

    inversaoRecursivo(s, i + 1);
    System.out.print(s.charAt(i));

  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String palavra = s.nextLine();
    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {
      inversao(palavra);
      System.out.println();
      palavra = s.nextLine();
    }

    s.close();
  }
}
