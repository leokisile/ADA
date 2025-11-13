#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int min;
    int max;
} Rango;

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
Rango min_max(int *A, int inicio, int fin){
    Rango res, izq, der;

    if(inicio == fin){
        res.min = A[inicio];
        res.max = A[inicio];
        return res;
    }

    if(fin == inicio + 1){
        if(A[fin] < A[inicio]){
            res.min = A[fin];
            res.max = A[inicio];
        }else{
            res.max = A[fin];
            res.min = A[inicio];
        }
        return res;
    }

    int medio = (fin + inicio)/2;
    izq = min_max(A, inicio, medio);
    der = min_max(A, medio + 1, fin);

    res.min = (izq.min < der.min) ? izq.min: der.min;
    res.max = (izq.max > der.max) ? izq.max: der.max;

    return res;
}

int main(){
    int n;
	srand(time(NULL));
	puts("Introduzca el numero de elementos a registrar");
	scanf("%d", &n);
	int *A = (int*)malloc(sizeof(int) * n);
	leerNums(A, n, 99, 0);
	imprimeNums(A,n);

    Rango res = min_max(A, 0, n-1);
    printf("Diferencia maxima: %d\nN1: %d\nN2: %d\n", res.max - res.min, res.max, res.min);

    return 0;
}
