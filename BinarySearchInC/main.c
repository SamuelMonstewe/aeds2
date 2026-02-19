#include <stdio.h>

int x = 10;
int n = 6;

int binarySearch(int *A, int e, int d){
    if(e > d){
    return 0;
  }

  int pivot = (e + d) / 2;
  int diff = x - A[pivot]; 

  if(diff == 0){
    return 1;
  }
  else if(diff > 0){
    e = pivot + 1;
    return binarySearch(A, e, d);
  }
  else{
    d = pivot - 1;
    return binarySearch(A, e, d);
  }
}

void sort(int *A){
 
  int j;

  for(int i = 1; i < n; i++){
    int key = A[i];
    j = i - 1;

    while((j >= 0) && A[j] > key){
      A[j + 1] = A[j];
      j = j - 1;
    }

    A[j + 1] = key;    
  }
}

void printArray(int *A){
  for(int i = 0; i < n; i++){
    printf("%d ", A[i]);
  } 
}

int main(){
  int A[] = {5, 2, 3, 8, 1, 7};

  printArray(A);
  printf("\n");
  sort(A);
  printArray(A);
 
  printf("\n");

  if(binarySearch(A, 0, n-1)){
    printf("O elemento esta no array!");
  }else{
    printf("O elemento nao esta no array!");
  }

  return 0;
}
