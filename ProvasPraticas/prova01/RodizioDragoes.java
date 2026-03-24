import java.util.*;

class RodizioDragoes{
	static int tamFila = 0, inicio = 0, fim = 0;	
	static Scanner s = new Scanner(System.in);

	public static void imprimir(String[] fila){
		for(int i = 0; i < tamFila; i++){
			System.out.print(fila[i] + " ");
		}	
		System.out.println();
	}

	public static void inserir(String[] fila, String dragonName){
		if(fim ==  fila.length)
			return;

		fila[fim] = dragonName;
		fim++;
		tamFila++;	

	}
	public static void remover(String[] fila){
		if(tamFila == 0){
			System.out.println("vazia");
			return;
		}

		tamFila--;
		fim--;
		for(int i = 0; i < tamFila; i++){
			fila[i] = fila[i+1];
		}

	}
	public static void main(String[] args){
		int n,m;
		String dragonName;
		String evt;

		n = s.nextInt();
		m = s.nextInt();		
		String[] fila = new String[n];

		for(int i = 0; i < m; i++){
			evt = s.next();
			if(evt.charAt(0) == 'E'){
				dragonName = s.next();
				inserir(fila, dragonName);
			}
			else if(evt.charAt(0) == 'V'){
				remover(fila);
			}
			else if(evt.charAt(0) == 'B'){
				imprimir(fila);
			}
		}

		imprimir(fila);
	}
}
