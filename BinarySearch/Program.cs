namespace BinarySearch;

class Program
{
    const int n = 20;
    public static int comp = 0;

    static bool binarySearch(int[] A, int d, int e, int x){

      if(e > d){
        return false;
      }

      int meio = (e + d) / 2; 
      int diff = (x - A[meio]);

      comp++;

      if(diff == 0){
        return true;
      } 
      else if(diff > 0){
        e = meio + 1;
        return binarySearch(A, d, e, x);
      }
      else{
        d = meio - 1;
        return binarySearch(A, d, e, x);
      }

      
    }

    public static void preencherVetor(int[] arr){
      Random rand = new Random();

      for (int i = 0; i < n; i++){
         arr[i] = rand.Next(200); 
      }
    }

    public static void printVetor(int[] arr){
      foreach(int i in arr){
        Console.Write(i + " ");
      }
    }
    static void Main(string[] args)
    { 
      int[] A = new int[n];
      int d = n - 1;
      int e = 0;

      preencherVetor(A);
      A.Sort();
      // printVetor(A);

      if(binarySearch(A, d, e, 78)){
        Console.WriteLine("O elemento consta no vetor");
      }

      Console.WriteLine(comp);

    }
}
