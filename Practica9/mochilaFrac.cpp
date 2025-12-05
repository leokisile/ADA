#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> leerMochila(){
    vector<pair<int,int>> mochila; //peso, valor
    char opc= 'y';
    pair<int,int> obj;
    while(opc == 'y'){
        cout << "Ingresa un objeto (peso, valor): \n";
        cin >> obj.first >> obj.second;
        mochila.push_back(obj);
        cout << "Quiere ingresar otra denominacion? (y/n) \n";
        cin >> opc;
    }
    return mochila;
}

void imprimeMochila(vector<pair<int,int>> &mochila){
    cout << "Objetos (peso, valor) de la mochila: \n";
    int i = 1;
    for(auto &p: mochila){
        cout << i++ << ".- w: " << p.first << "\tv: " << p.second << "\tv/w: " << (double)p.second/p.first << "\n";
    }
}

vector<pair<double,double>> mochilaFrac(vector<pair<int,int>> &mochila, int peso){
    vector<pair<double,double>> res;
    int acumulado = 0;

    for(auto &p: mochila){
        if(p.first + acumulado <= peso){
            // Cabe completo
            res.push_back({(double)p.first, (double)p.second});
            acumulado += p.first;
        }
        else{
            // Solo cabe parte del objeto
            int restante = peso - acumulado;
            if(restante <= 0) break; // Mochila llena

            double frac = (double)p.second / p.first;

            double peso_frac = restante;
            double valor_frac = frac * restante;

            res.push_back({peso_frac, valor_frac});
            break; // ya no cabe nada más
        }
    }

    return res;
}

void imprimeRes(vector<pair<double,double>> &res){
    double value = 0, weight = 0;
    int i = 1;
    cout << "Objetos introducidos en la mochila: \n";
    for(auto &p: res){
        cout << i++ << ".- w: " << p.first << "\tv: " << p.second << "\n";
        value += p.second;
        weight += p.first;
    }
    cout  << "Peso total introducido: " << weight << "\n";
    cout << "Valor acumulado: " << value << "\n";
}


void probarEjemplo(int peso, vector<pair<int,int>> mochila) {
    cout << "\n========================INICIO=======================\n";
    cout << "Mochila con peso máximo = " << peso << "\n";

    // Ordenar por valor/peso descendente
    sort(mochila.begin(), mochila.end(),
         [](const pair<int,int> &a, const pair<int,int> &b){
            return (double)a.second / a.first > (double)b.second / b.first;
         });

    imprimeMochila(mochila);

    auto res = mochilaFrac(mochila, peso);

    cout << "\n--- Resultado mochila fraccionaria ---\n";
    imprimeRes(res);

    cout << "==========================FIN=====================\n\n";
}

int main(){
     // ================= EJEMPLO 1 =================
    probarEjemplo(
        50,
        {
            {10, 60},   // ratio 6
            {20, 100},  // ratio 5
            {30, 120}   // ratio 4
        }
    );
    // ================= EJEMPLO 2 =================
    probarEjemplo(
        15,
        {
            {10, 30},   // ratio 3
            {20, 100},  // ratio 5
            {5, 20}     // ratio 4
        }
    );
    // ================= EJEMPLO 3 =================
    probarEjemplo(
        100,
        {
            {10, 10},
            {15, 40},
            {5, 30},
            {20, 90}
        }
    );
    // ================= EJEMPLO 4 =================
    probarEjemplo(
        10,
        {
            {40, 200},  // ratio 5
            {20, 60},   // ratio 3
            {50, 500}   // ratio 10 (mejor)
        }
    );
    // ================= EJEMPLO 5 =================
    probarEjemplo(
        30,
        {
            {10, 20},   // ratio 2
            {20, 40},   // ratio 2
            {5, 10},    // ratio 2
            {15, 30}    // ratio 2
        }
    );
    /*
    int n=0;
    vector<pair<int,int>> mochila;
    vector<pair<double,double>> res;

    cout << "Ingrese el peso de la mochila: ";
    cin >> n;

    mochila = leerMochila();
    sort(mochila.begin(), mochila.end(), [](const pair<int,int> &a, const pair<int,int> &b) {
    return (double)a.second / a.first > (double)b.second / b.first;
    });

    cout << "Peso de la mochila: " << n << "\n";
    imprimeMochila(mochila);

    res = mochilaFrac(mochila, n);
    imprimeRes(res);
    */
    return 0;
}
