#include <stdio.h>

void f(char *c, int v){
  if(c[0] == '\0' || c[0] == '\n'){
    printf("%d\n", v);
    return;
  }
  if(c[0]>=65 && c[0]<=90){
    f(&c[1], v+1);
  }
  else{
    f(&c[1], v);
  }
}
int main(){
  char palavra[100];
  int i;

  fgets(palavra, 100, stdin);

  while(!(palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M')){
      f(palavra, 0);
      fgets(palavra, 100, stdin);
  }

}
