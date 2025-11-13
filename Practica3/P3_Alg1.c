#include <stdio.h>

void Alg1(int n){
    if(n > 1){
        puts("hola");
        Alg1(n/2);
        Alg1(n/2);
    }
}

void Alg2(int n){
    if(n > 1){
        Alg2(n/2);
        Alg2(n/2);
        int i;
        for(i=0; i<n; i++)
            puts("Soy el algoritmo 2");
    }
}

void Alg3(int n){
    if(n > 1){
        Alg3(n/2);
        Alg3(n/2);
        int i, j;
        for(i=0; i<n; i++){
            for(j=0; j<n; j++)
                puts("Soy el algoritmo 3");
        }
    }
}

int main(){
    int n; //n es una potencia de 2
    puts("Introduce un numero entero que sea potencia de 2");
    scanf("%d", &n);

    Alg1(n);
    //Alg2(n);
    //Alg3(n);

    return 0;
}
