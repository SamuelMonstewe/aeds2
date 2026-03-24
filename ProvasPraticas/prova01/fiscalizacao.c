#include <stdio.h>

int isTamanhoCorreto(char *p){
	int tam = 0;
	for(int i = 0; p[i] != '\0'; i++){
		tam++;
	}

	if(tam == 7) return 1;

	return 0;
}
int main(){
	char p[10];
	int n = 0;

	scanf("%d", &n);

	for(int i = 0; i < n; i++){
		scanf("%s", p);
		
		if(!isTamanhoCorreto(p)){
			printf("I");	
		}
		else if(
		(p[0] <= 'Z' && p[0] >= 'A') &&  
		(p[1] <= 'Z' && p[1] >= 'A')  && 
		(p[2] <= 'Z' && p[2] >= 'A') &&
		(p[3] >= '0' && p[3] <= '9') &&	
		(p[4] >= '0' && p[4] <= '9') && 
		(p[5] >= '0' && p[5] <= '9') &&
		(p[6] >= '0' && p[6] <= '9') 
		){
			printf("A");
		}
		else if(	
		(p[0] <= 'Z' && p[0] >= 'A') &&  
		(p[1] <= 'Z' && p[1] >= 'A')  && 
		(p[2] <= 'Z' && p[2] >= 'A') &&
		(p[3] >= '0' && p[3] <= '9') &&	
		(p[4] <= 'Z' && p[4] >= 'A') && 
		(p[5] >= '0' && p[5] <= '9') &&
		(p[6] >= '0' && p[6] <= '9') 
		){
			printf("M");
		}
		else {
			printf("I");
		}
		printf("\n");
		
	}
}
