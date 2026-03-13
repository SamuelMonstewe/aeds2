import java.util.Scanner;

public class Ciframento {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);

    String palavra = s.nextLine();
    String y = "";

    // iteramos equanto a string FIM não aparecer
    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {
      for (int i = 0; i < palavra.length(); i++) {
        y = y + (char) (palavra.charAt(i) + 3); // aqui nós incrementamos em 3 o valor do padrão de codificação usado
                                                // para fazer o deslocamento do caractere
      }
      System.out.println(y);
      palavra = s.nextLine();
      y = ""; // limpamos a variável y para criar uma nova saída
    }

    s.close();
  }
}
