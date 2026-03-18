import java.util.Scanner;

public class Validacao {
  // código super intuitivo, dispensa comentários
  public static boolean isEspecial(char c) {
    if ((c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c > 122)) {
      return true;
    }

    return false;
  }

  public static boolean isMaiuscula(char c) {
    if (c >= 65 && c <= 87) {
      return true;
    }

    return false;
  }

  public static boolean isMinuscula(char c) {
    if (c >= 97 && c <= 122) {
      return true;
    }

    return false;
  }

  public static boolean isNumber(char c) {
    if (c >= 48 && c <= 57) {
      return true;
    }

    return false;
  }

  public static boolean isSenhaForte(String s) {
    int contEspecial = 0, contMaiuscula = 0, contMinuscula = 0, contNumber = 0;

    for (int i = 0; i < s.length(); i++) {
      if (isMaiuscula(s.charAt(i))) {
        contMaiuscula++;
      }
      if (isMinuscula(s.charAt(i))) {
        contMinuscula++;
      }
      if (isEspecial(s.charAt(i))) {
        contEspecial++;
      }
      if (isNumber(s.charAt(i))) {
        contNumber++;
      }
    }

    if (s.length() >= 8 && contMaiuscula >= 1 && contMinuscula >= 1 && contEspecial >= 1 && contNumber >= 1)
      return true;

    return false;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String palavra = s.nextLine();

    while (!(palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')) {

      if (isSenhaForte(palavra)) {
        System.out.println("SIM");
      } else {
        System.out.println("NAO");
      }
      palavra = s.nextLine();
    }

    s.close();
  }
}
