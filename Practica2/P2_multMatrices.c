#include <stdio.h>
#include <stdlib.h>

 void mult2x2(int A[2][2], int B[2][2], int C[2][2]){
    C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
 }

void expon2x2(int A[2][2], int res[2][2], int n) {
    int i;
    int temp[2][2];
    //identidad
    res[0][0] = 1; res[0][1] = 0;
    res[1][0] = 0; res[1][1] = 1;

    for (i = 0; i < n; i++) {
        mult2x2(res, A, temp);
        res[0][0] = temp[0][0];
        res[0][1] = temp[0][1];
        res[1][0] = temp[1][0];
        res[1][1] = temp[1][1];
    }
}

int fiboNorm(int A[2][2], int B[2][2], int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    expon2x2(A, B, n);
    return B[0][1];
}

void expon2x2log(int A[2][2], int res[2][2], int n) {
    if (n == 0) { // Identidad
        res[0][0] = 1; res[0][1] = 0;
        res[1][0] = 0; res[1][1] = 1;
        return;
    }

    if (n == 1) {
        res[0][0] = A[0][0]; res[0][1] = A[0][1];
        res[1][0] = A[1][0]; res[1][1] = A[1][1];
        return;
    }

    int mitad[2][2], temp[2][2];
    expon2x2log(A, mitad, n / 2); // Calcula A^(n/2)
    mult2x2(mitad, mitad, temp);  // Cuadrado -> A^(n/2 * 2) (saca el exponente par)

    if (n % 2 == 0) {
        res[0][0] = temp[0][0];
        res[0][1] = temp[0][1];
        res[1][0] = temp[1][0];
        res[1][1] = temp[1][1];
    } else {
        mult2x2(temp, A, res);    //Si es impar multiplicamos 1 vez mas
    }
}

int fiboLog(int A[2][2], int B[2][2], int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    expon2x2log(A, B, n);
    return B[0][1];
}

int main(){
    int A[2][2] = {{0,1},{1,1}}, n, B[2][2];
    puts("Introduzca el termino de la serie de fibonacci a calcular");
    scanf("%d", &n);
    printf("El %d termino de la serie de fibonacci es: %d\n", n, fiboNorm(A, B, n));
    printf("El %d termino de la serie de fibonacci es: %d\n", n, fiboLog(A, B, n));

    return 0;
}
