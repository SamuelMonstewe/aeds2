import java.util.Random;
import java.util.Scanner;

public class AlteracaoAleatoria {

  public static void main(String args[]) {
    Random r = new Random();
    Scanner s = new Scanner(System.in);
    r.setSeed(4);
    char c1 = (char) ('a' + (Math.abs(r.nextInt()) % 26));
    char c2 = (char) ('a' + (Math.abs(r.nextInt()) % 26));
    String palavra = s.nextLine();
    String y = ""; // como não podemos utilizar nenhum auxilio da classe string, vamos criar uma
                   // variável auxiliar

    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {

      for (int i = 0; i < palavra.length(); i++) {
        if (palavra.charAt(i) == c1) { // caso identifique um caractere a ser substituido, concatenamos o caractere de
                                       // substituição a variável y
          y += c2;
        } else { // caso contrário, só prosseguimos com a string normal mesmo
          y += palavra.charAt(i);
        }
      }

      System.out.println(y);
      palavra = s.nextLine();
      y = "";
    }

    s.close();
  }
}
