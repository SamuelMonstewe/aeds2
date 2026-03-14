import java.util.Scanner;

public class SomaDigitosRecursiva {
  public static int somaDigitosRec(int num) {
    if ((num / 10) == 0)
      return num;

    int resto = num % 10;
    int quociente = num / 10;
    return resto + somaDigitosRec(quociente);
  }

  public static int somaDigitos(int num) {
    return somaDigitosRec(num);
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);

    while (s.hasNextInt()) {
      int num = s.nextInt();
      System.out.println(somaDigitos(num));
    }

    s.close();
  }
}
