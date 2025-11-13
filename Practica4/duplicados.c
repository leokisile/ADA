#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void imprimeLista(int *A, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", A[i]);
    puts(" ");
}

int minimo(int *A, int n){
    int i, min = A[0];
    for(i = 0; i<n; i++){
        if(A[i] < min) min = A[i];
    }
    return min;
}

int maximo(int *A, int n){
    int i, max = A[0];
    for(i = 0; i<n; i++){
        if(A[i] > max) max= A[i];
    }
    return max;
}

int estaEnLista(int x, int *A, int n){
    int i, esta = 0;
    for(i = 0; i < n; i++){
        if(A[i] == x) esta = 1;
    }
    return esta;
}

int* duplicados(int *A, int n){
    printf("Entrando duplicados(n = %d)\n", n);

    if(n <= 1) return A;
    int min, max, i;

    //Calculamos el minimo y maximo
    min = minimo(A, n);
    max = maximo(A, n);

    //Caso base para el hashing
    if(min == max){
        int *res_final = (int*)calloc(2, sizeof(int));
        res_final[0] = 1; // Contador = 1
        res_final[1] = min; // El valor sin duplicar
        return res_final;
    }

    //Encontramos la potencia de 2 mas cercana a 2n
    int M = 1;
    while(M < 2*n){
        M = M<<1;
    }
    printf("n = %d, M = %d\n", n, M);

    //Creamos la matriz de sublistas
    int **B = (int**)malloc(sizeof(int*) * M);
    for(i=0; i < M; i++){
        B[i] = (int*)calloc(1, sizeof(int));
        B[i][0] = 0;
    }

    int indice;
    for(i = 0; i<n; i++){
        indice =(int)(M *((double)(A[i]-min)/(max - min +1)));
        if (!estaEnLista(A[i], B[indice], B[indice][0])) {
            B[indice][0]++; // incrementamos el contador
            B[indice] = realloc(B[indice], sizeof(int) * (B[indice][0] + 1));
            B[indice][B[indice][0]] = A[i]; // guardamos el nuevo elemento
        }
    }

    int *res = (int*)calloc(1, sizeof(int));
    res[0] = 0; //Inicializar lsita con un contador en la primera posicion

    for (i = 0; i < M; i++){
        if (B[i][0] > 1){
            int n_sublista = B[i][0];
            int *datos_puros = (int*)malloc(sizeof(int) * n_sublista);
            memcpy(datos_puros, B[i] + 1, sizeof(int) * n_sublista);
            int *resultado_recursivo = duplicados(datos_puros, n_sublista);
            free(datos_puros);
            free(B[i]);
            B[i] = resultado_recursivo;
        }

        res = realloc(res, sizeof(int) * (res[0] + B[i][0] + 1));// tam res + tam de la sublista
        memcpy(res + res[0] + 1, B[i] + 1, sizeof(int) * B[i][0]);
        res[0] += B[i][0];

        free(B[i]);
    }
    free(B);

    return res;
}

int main(){
    int A[14] = {1, 2,2,2, 3,3, 4, 10, 10, 10, 23, 23, 23, 25};
    int C[14] = {1, 1,2,2, 3,3, 4, 4, 5, 5, 6, 7, 7, 8};
    int D[14] = {1, 1,1,1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1};
    int E[14] = {1, 10,100, 20, 21, 20, 10, 100, 21, 22, 22, 500, 500, 1};
    int n = 14;

    imprimeLista(A, n);
    int *res = duplicados(A, 14);
    imprimeLista(res + 1, res[0]);
    free(res);
    return 0;
}
