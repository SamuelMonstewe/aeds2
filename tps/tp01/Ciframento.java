import java.util.Scanner;

public class Ciframento {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    MyIO.setCharset("ISO-8859-1");
    String palavra = MyIO.readLine();
    String y = "";

    // iteramos equanto a string FIM não aparecer
    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {
      for (int i = 0; i < palavra.length(); i++) {
        y += (char) (palavra.charAt(i) + 3); // aqui nós incrementamos em 3 o valor do padrão de codificação usado
                                             // para fazer o deslocamento do caractere
      }
      MyIO.println(y);
      palavra = MyIO.readLine();
      y = ""; // limpamos a variável y para criar uma nova saída
    }

    s.close();
  }
}
