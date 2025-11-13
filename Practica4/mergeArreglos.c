#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* merge(int *A, int *B) {
    int nA = A[0]; // Tam de A
    int nB = B[0]; // Tam de B
    int nTotal = nA + nB;

    int *C = (int*)malloc(sizeof(int) * (nTotal + 1));
    if (C == NULL) return NULL;

    C[0] = nTotal;
    int i = 1; // Índice para A
    int j = 1; // Índice para B
    int k = 1; // Índice para C

    //Merge para dos arreglos mediante dos indices
    while (i <= nA && j <= nB) {
        if (A[i] <= B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
    }

    // Copiar elementos restantes de A
    while (i <= nA) {
        C[k++] = A[i++];
    }

    // Copiar elementos restantes de B
    while (j <= nB) {
        C[k++] = B[j++];
    }

    free(A);
    free(B);

    return C;
}


int* mergeArrays(int **M, int izq, int der) {
    // Caso base
    if (izq == der) {
        //Como izq == der es solo un arreglo
        int n = M[izq][0];
        int *A = (int*)malloc(sizeof(int) * (n + 1));
        if (A == NULL) return NULL;

        memcpy(A, M[izq], sizeof(int) * (n + 1));
        return A;
    }

    // Divide
    int medio = izq + (der - izq) / 2;

    //Llamadas recursivas
    int *mergeIzq = mergeArrays(M, izq, medio);
    int *mergeDer = mergeArrays(M, medio + 1, der);

    // Combina
    return merge(mergeIzq, mergeDer);
}


void imprimeLista(int *A) {
    if (A == NULL) {
        printf("Lista vacía\n");
        return;
    }
    int n = A[0];
    printf("Tamaño: %d | Datos: ", n);
    for (int i = 1; i <= n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    // Formato: [tamaño, d1, d2, ...]
    int arr0[] = {3, 1, 5, 8};
    int arr1[] = {2, 2, 7};
    int arr2[] = {4, 3, 6, 9, 11};
    int arr3[] = {1, 10};
    int arr4[] = {1, 20};
    int arr5[] = {4, 8, 9, 11, 13};
    int arr6[] = {2, 15, 21};
    int arr7[] = {3, 3, 5, 8};

    int *M[] = {arr0, arr1, arr2, arr3};
    int k = sizeof(M) / sizeof(M[0]); // k = 4 arreglos

    printf("Arreglos de entrada:\n");
    for(int i = 0; i < k; i++) {
        imprimeLista(M[i]);
    }

    int *resultado = mergeArrays(M, 0, k - 1);

    printf("\nResultado Final Ordenado:\n");
    imprimeLista(resultado);

    if (resultado != NULL) {
        free(resultado);
    }

    int *M2[] = {arr4, arr5, arr6, arr7};
    int k2 = sizeof(M2) / sizeof(M2[0]); // k = 4 arreglos

    printf("\nArreglos de entrada:\n");
    for(int i = 0; i < k2; i++) {
        imprimeLista(M2[i]);
    }

    int *resultado2 = mergeArrays(M2, 0, k2 - 1);

    printf("\nResultado Final Ordenado:\n");
    imprimeLista(resultado2);

    if (resultado2 != NULL) {
        free(resultado2);
    }
    return 0;
}
