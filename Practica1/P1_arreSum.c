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

void imprimeMatriz(int **B, int n){
	int i,j;
	for(i=0; i<n; i++){
    	for(j=0; j<n; j++){
    		printf("%d ", B[i][j]);
		}
		putchar('\n');
	}
}

int main(){
	int n, i, j,k, suma;
	srand(time(NULL));
	puts("Introduzca el numero de elementos a registrar");
	scanf("%d", &n);
	int *A = (int*)malloc(sizeof(int) * n);
	leerNums(A, n, 99, 0);
	imprimeNums(A,n);

	int **B = (int**)malloc(sizeof(int*) * n);
	for(i=0; i<n; i++){
        B[i] = (int*)calloc(n, sizeof(int));
    }
    imprimeMatriz(B,n);

    for(i=0; i<n; i++){
        suma = A[i];
        k = i;
    	for(j=0; j<n; j++){
    	    if(i<j && k<j){
                suma = suma + A[++k];
    			B[i][j] = suma;
			}
		}
	}

	imprimeMatriz(B,n);

	return 0;
}
