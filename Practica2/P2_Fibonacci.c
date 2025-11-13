#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int fibonacciArr(int n, int *A){
    int i;
    A[0] = 0;
    A[1] = 1;
    if(n>1){
        for(i=2; i<=n; i++){
            A[i] = A[i-1] + A[i-2];
        }
    }
    return A[n];
}

int main(){
    int n;
    puts("Ingrese la posicion de fibonacci");
    scanf("%d", &n);
    int *A = (int*)malloc(sizeof(int) * n);
    printf("La posicion %d de la secuencia de fibonacci es %d\n", n, fibonacci(n));
    printf("La posicion %d de la secuencia de fibonacci es %d\n", n, fibonacciArr(n, A));

    return 0;
}
