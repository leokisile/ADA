#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> llenaObjetos (int n){
    vector<pair<int,int>> objetos;
    pair<int, int> objeto; //valor, peso

    for(int i=0; i<n; i++){
        cout << "Ingrese el (valor, peso) del objeto: ";
        cin >> objeto.first >> objeto.second;
        objetos.push_back(objeto);
    }
    return objetos;
}

void imprimeObjetos(vector<pair<int,int>> &objetos){
    int i = 1;
    for(auto &obj: objetos){
        cout << i++ << ".- " << "v: " << obj.first << "\tw: " << obj.second << "\n";
    }
}

vector<vector<int>> matrizValor(int n, int W, vector<pair<int,int>> &objetos){
    vector<vector<int>> matriz(n + 1, vector<int>(W + 1));

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= W; j++){

            if(i == 0 || j == 0)
                matriz[i][j] = 0;

            else if (objetos[i-1].second > j)
                matriz[i][j] = matriz[i-1][j];

            else {
                matriz[i][j] = max(
                    matriz[i-1][j],
                    matriz[i-1][j - objetos[i-1].second] + objetos[i-1].first
                );
            }
        }
    }

    return matriz;
}

void imprimeMatriz(const vector<vector<int>> &matriz) {
    for (const auto &fila : matriz) {
        for (int valor : fila) {
            cout << setw(4) << valor << " ";
        }
        cout << "\n";
    }
}
vector<pair<int,int>> listaRes(vector<vector<int>> &matriz, int n, int W, vector<pair<int,int>> &objetos) {
    vector<pair<int,int>> res;

    int i = n;      // última fila
    int j = W;      // última columna

    while (i > 0 && j > 0) {
        // Si el valor cambió, tomaste el objeto i-1
        if (matriz[i][j] != matriz[i-1][j]) {
            res.push_back(objetos[i-1]);
            cout << "\nSe agrego el objeto con v: " << objetos[i-1].first << "\tw: " << objetos[i-1].second << "\n";
            j -= objetos[i-1].second;  // reduces el peso
            i--;                       // subes una fila
        }
        else {
            i--; // no tomaste el objeto, solo subes
        }
    }

    return res; // devuelve los objetos seleccionados
}

int main(){
    vector<pair<int,int>> objetos;
    int W, n;

    cout << "Ingrese el peso de la mochila: ";
    cin >> W;

    cout << "Ingrese el numero de objetos a ingresar: ";
    cin >> n;

    objetos = llenaObjetos(n);
    imprimeObjetos(objetos);

    vector<vector<int>> matriz = matrizValor(n, W, objetos);

    cout << "\nMatriz de valores:\n";
    imprimeMatriz(matriz);

    vector<pair<int, int>> res = listaRes(matriz, n, W, objetos);
    cout << "\nObjetos introductidos:\n";
    imprimeObjetos(res);

    return 0;
}
