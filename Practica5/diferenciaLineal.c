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
    int n;
	srand(time(NULL));
	puts("Introduzca el numero de elementos a registrar");
	scanf("%d", &n);
	int *A = (int*)malloc(sizeof(int) * n);
	leerNums(A, n, 99, 0);
	imprimeNums(A,n);

    int i, min=A[0], max=A[0];
    for(i = 1; i<n; i++){
        if(max < A[i]) max = A[i];
        if(min > A[i]) min = A[i];
    }
    printf("Diferencia maxima: %d\nN1: %d\nN2: %d\n", max-min, max, min);

    return 0;
}
