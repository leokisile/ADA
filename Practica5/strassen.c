#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **crearMatriz(int n) {
    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        M[i] = (int *)calloc(n, sizeof(int));
    }
    return M;
}

void liberarMatriz(int **M, int n) {
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

int **sumar(int **A, int **B, int n) {
    int **C = crearMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

int **restar(int **A, int **B, int n) {
    int **C = crearMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Copia un subbloque de matriz
void copiarSubmatriz(int **src, int **dest, int filaInicio, int colInicio, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i + filaInicio][j + colInicio];
}

// Inserta un bloque en una matriz destino
void insertarSubmatriz(int **dest, int **src, int filaInicio, int colInicio, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i + filaInicio][j + colInicio] = src[i][j];
}

int **multiplicarClasico(int **A, int **B, int n) {
    int **C = crearMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int siguientePotencia2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

int **strassen(int **A, int **B, int n) {
    if (n <= 2) {
        return multiplicarClasico(A, B, n);
    }

    int k = n / 2;

    // Dividir matrices A y B en subbloques
    int **A11 = crearMatriz(k);
    int **A12 = crearMatriz(k);
    int **A21 = crearMatriz(k);
    int **A22 = crearMatriz(k);
    int **B11 = crearMatriz(k);
    int **B12 = crearMatriz(k);
    int **B21 = crearMatriz(k);
    int **B22 = crearMatriz(k);

    //Origen, destino, fil inicio, col inicio, cantidad
    copiarSubmatriz(A, A11, 0, 0, k);
    copiarSubmatriz(A, A12, 0, k, k);
    copiarSubmatriz(A, A21, k, 0, k);
    copiarSubmatriz(A, A22, k, k, k);

    copiarSubmatriz(B, B11, 0, 0, k);
    copiarSubmatriz(B, B12, 0, k, k);
    copiarSubmatriz(B, B21, k, 0, k);
    copiarSubmatriz(B, B22, k, k, k);

    // P1 = (A11 + A22) * (B11 + B22)
    int **Atemp1 = sumar(A11, A22, k);
    int **Btemp1 = sumar(B11, B22, k);
    int **P1 = strassen(Atemp1, Btemp1, k);

    // P2 = (A21 + A22) * B11
    int **Atemp2 = sumar(A21, A22, k);
    int **P2 = strassen(Atemp2, B11, k);

    // P3 = A11 * (B12 - B22)
    int **Btemp3 = restar(B12, B22, k);
    int **P3 = strassen(A11, Btemp3, k);

    // P4 = A22 * (B21 - B11)
    int **Btemp4 = restar(B21, B11, k);
    int **P4 = strassen(A22, Btemp4, k);

    // P5 = (A11 + A12) * B22
    int **Atemp5 = sumar(A11, A12, k);
    int **P5 = strassen(Atemp5, B22, k);

    // P6 = (A21 - A11) * (B11 + B12)
    int **Atemp6 = restar(A21, A11, k);
    int **Btemp6 = sumar(B11, B12, k);
    int **P6 = strassen(Atemp6, Btemp6, k);

    // P7 = (A12 - A22) * (B21 + B22)
    int **Atemp7 = restar(A12, A22, k);
    int **Btemp7 = sumar(B21, B22, k);
    int **P7 = strassen(Atemp7, Btemp7, k);

    // C11 = P1 + P4 - P5 + P7
    int **temp1 = sumar(P1, P4, k);
    int **temp2 = restar(temp1, P5, k);
    int **C11 = sumar(temp2, P7, k);

    // C12 = P3 + P5
    int **C12 = sumar(P3, P5, k);

    // C21 = P2 + P4
    int **C21 = sumar(P2, P4, k);

    // C22 = P1 - P2 + P3 + P6
    temp1 = restar(P1, P2, k);
    temp2 = sumar(temp1, P3, k);
    int **C22 = sumar(temp2, P6, k);

    // Unir subbloques
    // destino, origen, fil inicio, col inicio, cantidad
    int **C = crearMatriz(n);
    insertarSubmatriz(C, C11, 0, 0, k);
    insertarSubmatriz(C, C12, 0, k, k);
    insertarSubmatriz(C, C21, k, 0, k);
    insertarSubmatriz(C, C22, k, k, k);

    return C;
}



int main() {
    int n;
    printf("Ingrese el tamaño de la matriz n: ");
    scanf("%d", &n);

    int m = siguientePotencia2(n);

    int **A = crearMatriz(m);
    int **B = crearMatriz(m);

    printf("Ingrese la matriz A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Ingrese la matriz B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    int **C = strassen(A, B, m);

    printf("\nResultado A × B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    liberarMatriz(A, m);
    liberarMatriz(B, m);
    liberarMatriz(C, m);
    return 0;
}

