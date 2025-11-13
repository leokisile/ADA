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

int main(){
	srand(time(NULL));
	int n, x = rand() % 10 + 1, i;
	puts("Introduzca el numero de coeficientes a utilizar");
	scanf("%d", &n);

    int *A = (int*)malloc(sizeof(int) * n);
    leerNums(A, n, 99, 0);
    puts("Coeficientes escritos de mayor a menor grado");
	imprimeNums(A,n);

	int poli = A[i];
    for(i=0; i<n-1; i++){
        poli = poli*x + A[i+1];
        printf("%d %d %d\n", i, i+1, poli);
    }

    printf("P(%d) = %d", x, poli);

    return 0;
}
