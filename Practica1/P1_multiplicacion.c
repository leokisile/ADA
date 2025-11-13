#include <stdio.h>
#include <time.h>

int multiplica(int a, int b){
	if(a<=0 || b<0) return -1;
	if(b == 0) return 0;
	int z = multiplica(a, b/2);
	if(b % 2 == 0) return 2*z;
	return a+2*z;
}

int main(){
    srand(time(NULL));
	int a= rand()%1000,b = rand()%1000;

	printf("La multiplicacion de %d * %d es %d", a, b, multiplica(a,b));
	return 0;
}
