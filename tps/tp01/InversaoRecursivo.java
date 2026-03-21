
public class InversaoRecursivo {
  public static void inversao(String s) {
    inversaoRecursivo(s, 0);
  }

  public static void inversaoRecursivo(String s, int i) {
    if (i == s.length())
      return;

    inversaoRecursivo(s, i + 1);
    MyIO.print(s.charAt(i));

  }

  public static void main(String[] args) {
    MyIO.setCharset("UTF-8");
    String palavra = MyIO.readLine();
    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {
      inversao(palavra);
      MyIO.println("");
      palavra = MyIO.readLine();
    }

  }
}
