#include <bits/stdc++.h>
#include <string.h>
using namespace std;

vector<int> leerDenominacion(){
    vector<int> denom;
    char opc= 'y';
    int num;
    while(opc == 'y'){
        cout << "Ingresa una denominacion: \n";
        cin >> num;
        denom.push_back(num);
        cout << "Quiere ingresar otra denominacion? (y/n) \n";
        cin >> opc;
    }
    return denom;
}

void imprimeDenom(vector<int> denom){
    int n = denom.size();
    int i;
    cout << "Denominaciones:\n";
    for(i = 0; i < n; i++)
        cout << denom[i] << "\t";
    cout << "\n";
}

vector<pair<int,int>> minimo(vector<vector<pair<int,int>>> &opciones){
    int maximo = 10000000;
    vector<pair<int,int>> mejor;

    for(auto &camino: opciones){
        int totalMonedas = 0;

        for(auto &p: camino)
            totalMonedas += p.first;

        if(totalMonedas < maximo){
            maximo = totalMonedas;
            mejor = camino;
        }
    }
    return mejor;
}

vector<pair<int,int>> cambio(int n, vector<int> &denom){
    // Posibles caminos desde 0 hasta n
    vector<vector<vector<pair<int,int>>>> dp(n+1);

    // Si n = 0, no usar monedas
    dp[0].push_back({});

    for(int d : denom){
        //s=d, de forma que no puede ser menor que la denominacion
        for(int s = d; s <= n; s++){
            // Se agregan los posibles caminos si existe el elemento s-d
            if(!dp[s - d].empty()){
                for(auto camino : dp[s - d]){
                    //Agrega la opcion 1,d a los caminos almacenados
                    camino.push_back({1, d});
                    dp[s].push_back(camino);
                }
            }
        }
    }

    // Ahora dp[n] tiene todas las combinaciones con pares (1, denom)
    // Falta reducir a un solo elemento i,denom
    vector<vector<pair<int,int>>> resultado;

    for(auto &camino : dp[n]){
        map<int,int> contador;
        for(auto &p : camino){//Utiliza un diccionario para marcar cada opcion posible
            contador[p.second] += 1;
        }

        vector<pair<int,int>> compactado;
        for(auto &p : contador){//Arma el arreglo de opciones compactado
            compactado.push_back({p.second, p.first});
        }

        resultado.push_back(compactado);
    }

    vector<pair<int,int>> mejor = minimo(resultado);
    return mejor;
}

void imprimeRes(vector<pair<int,int>> &res){
    int cont = 0;
    for (auto &p: res){
        cout << p.second << ": " << p.first << "\n";
        cont += p.first;
    }
    cout << "Total de monedas: " << cont << "\n";
}

void probarEjemploCambio(vector<int> denom, int n) {
    cout << "\n======================INICIO=======================\n";
    imprimeDenom(denom);

    cout << "Cambio solicitado: $" << n << "\n\n";

    vector<pair<int,int>> res = cambio(n, denom);

    cout << "--- Resultado ---\n";
    imprimeRes(res);

    cout << "===========================FIN======================\n\n";
}

int main(){
    // ============================================
    // EJEMPLO 1: Sistema típico de monedas MX
    // ============================================
    probarEjemploCambio(
        {1, 2, 5, 10},   // denominaciones
        28               // cambio a dar
    );

    // ============================================
    // EJEMPLO 2: Denominaciones no estándar
    // ============================================
    probarEjemploCambio(
        {4, 3, 1},
        11
    );

    // ============================================
    // EJEMPLO 3: Denominaciones grandes
    // ============================================
    probarEjemploCambio(
        {50, 20, 10, 5},
        135
    );

    // ============================================
    // EJEMPLO 4: Cambio exacto no posible (requiere lógica del algoritmo)
    // ============================================
    probarEjemploCambio(
        {7, 5, 2},
        13
    );

    // ============================================
    // EJEMPLO 5: Solo una denominación
    // ============================================
    probarEjemploCambio(
        {3},
        18
    );
    // LECTURA DE DATOS
    /*
    vector<int> denom = leerDenominacion();
    imprimeDenom(denom);
    int n = 0;
    cout << "Ingrese el cambio a dar: ";
    cin >> n;
    cout << "Cambio a dar: $" << n << "\n";

    //PROCEDIMIENTO
    vector<pair<int,int>> res = cambio(n, denom);
    imprimeRes(res);

    */
    return 0;
}
