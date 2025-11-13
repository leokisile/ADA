#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct moneda{
    float denominacion;
    float cantidad;
};

void imprimeVector(int n, vector<moneda> lista){
    int i;
    for(i=0; i < n; i++){
        cout << i+1 << ".- $" << lista[i].denominacion << "\t Cantidad: " << lista[i].cantidad << " = " << lista[i].denominacion * lista[i].cantidad << "\n" << endl;
    }
    cout << "\n";
}

vector<moneda> optimizarMoneda(float x, int k, vector<float> denominaciones){
    vector<moneda> optimizado;
    int i; float suma = 0;
    for(i = 0; i < k; i++){
        cout << suma << " " << denominaciones[i] << " " << (float)((x - suma) / denominaciones[i]) << endl;
        moneda m;
        m.denominacion = denominaciones[i];
        int c = (x - suma) / denominaciones[i];
        if( c > 0.9 && c < 1)
            m.cantidad = c + 0.01;
        else
            m.cantidad = c;
        suma += m.cantidad * denominaciones[i];
        optimizado.push_back(m);
    }
    return optimizado;
}

int main(){
    vector<float> denominaciones = {
    10.0, 5.0, 2.0, 1.0, 0.5, 0.1};
    float x; int k = 6;
    cout << "Introduzca la cantidad de dinero: ";
    cin >> x;

    sort(denominaciones.begin(), denominaciones.end(), [](const float& a, const float& b) {//Inicio, fin, criterio(lambda)
    return a > b;  // criterio de orden
    });

    vector<moneda> optimizado = optimizarMoneda(x, k, denominaciones);
    cout << "Lista optimizada para $" << x <<": \n" << endl;
    imprimeVector(optimizado.size(), optimizado);

    return 0;
}
