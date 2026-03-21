import java.util.Random;

public class AlteracaoAleatoria {

  public static void main(String args[]) {
    MyIO.setCharset("ISO-8859-1");
    Random r = new Random();
    r.setSeed(4);
    String palavra = MyIO.readLine();
    String y = ""; // como não podemos utilizar nenhum auxilio da classe string, vamos criar uma
                   // variável auxiliar

    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {
      char c1 = (char) ('a' + (Math.abs(r.nextInt()) % 26));
      char c2 = (char) ('a' + (Math.abs(r.nextInt()) % 26));

      for (int i = 0; i < palavra.length(); i++) {
        if (palavra.charAt(i) == c1) { // caso identifique um caractere a ser substituido, concatenamos o caractere de
                                       // substituição a variável y
          y += c2;
        } else { // caso contrário, só prosseguimos com a string normal mesmo
          y += palavra.charAt(i);
        }
      }

      MyIO.println(y);
      palavra = MyIO.readLine();
      y = "";
    }

  }
}
