#include <stdio.h>
#include <time.h>

int powLineal(int x, int pow){
    if(pow == 0) return 1;
    int i, res = 1;
    for(i = 0; i<pow; i++)
        res = x * res;
    return res;
}

int powLog(int x, int pow){
    if(pow == 0) return 1;
    int res = 1;
    while(pow > 0){
        if(pow%2 == 1)
            res = res * x;
        x = x*x;
        pow = pow/2;
    }
    return res;
}

int main(){
    srand(time(NULL));
    int x = rand()%50 + 1, pow = rand()%10 + 1, n = rand()%10 + 1;
    printf("%d^%d mod %d = %d\n", x, pow, n, powLineal(x, pow) % n);
    printf("%d^%d mod %d = %d\n", x, pow, n, powLog(x, pow) % n);

    return 0;
}
