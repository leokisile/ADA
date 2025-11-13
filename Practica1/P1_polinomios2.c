#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void leerNums(int* A, int n, int Max, int Min){
    int i, x;
    for(i=0;i<n;i++){
        A[i] = rand() % (Max-Min+1) + Min;
    }
}

void imprimeNums(int* A, int n){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", A[i]);
	}
	putchar('\n');
}

int exponente(int x, int exp){
    if(exp == 0) return 1;
    int i, res = 1;
    for(i=0; i<exp; i++)
        res = res*x;
    return res;
}

int main(){
	srand(time(NULL));
	int n, x = rand() % 10 + 1, i;
	puts("Introduzca el numero de coeficientes a utilizar");
	scanf("%d", &n);

    int *A = (int*)malloc(sizeof(int) * n);
    leerNums(A, n, 99, 0);
    puts("Coeficientes escritos de mayor a menor grado");
	imprimeNums(A,n);

	int poli = 0;
    for(i = 0; i<n; i++){
        poli = poli + A[i]*exponente(x, n-i-1);
    }

    printf("P(%d) = %d", x, poli);

    return 0;
}
