#include <bits/stdc++.h>
#include "disjoint.h"
using namespace std;

struct Arista {
        int u, v, w;
};

vector<Arista> converListaAristas(const vector<vector<pair<int,int>>> &adj){
    vector<Arista> aristas;

    for (int u = 0; u < adj.size(); u++) {
        for (auto &par : adj[u]) {
            int v = par.first;
            int w = par.second;

            // Evitamos el duplicado usando u<v unicamente
            if (u < v)
                aristas.push_back({u, v, w});
        }
    }

    // Ordenar de forma ascendente
    sort(aristas.begin(), aristas.end(),
        [](const Arista &a, const Arista &b){
            return a.w < b.w;
        }
    );
    return aristas;
}

void imprimirAristasOrdenadas(vector<Arista> aristas, vector<char> letras) {

    // Impresion
    cout << "Aristas ordenadas por peso:\n";
    for (auto &a : aristas) {
        cout << "(" << letras[a.u] << " -- " << letras[a.v] << ") peso=" << a.w << "\n";
    }
}

void imprimirListaAdy(vector<vector<pair<int,int>>> adj, int n, vector<char> letras){
    for (int i = 0; i < n; i++) {
        cout << letras[i] << " -> ";
        // Recorremos cada par (vecino, peso)
        for (auto &par : adj[i]) {
            cout << "(" << letras[par.first] << ", peso=" << par.second << ") ";
        }

        cout << "\n";
    }
}

vector<Arista> kruskal(vector<Arista> aristas, int n, vector<char> letras){
    vector<Arista> res;
    //Generamos los disjoint sets necesarios
    DisjointSet ds(n);
    //Unimos
    for(auto &a : aristas){
        if(ds.find(a.u) != ds.find(a.v)){
            res.push_back(a);
            ds.unite(a.u, a.v);
            cout << "(" << letras[a.u] << " -- " << letras[a.v] << ") se agrego al resultado\n";
        }else{
            cout << "(" << letras[a.u] << " -- " << letras[a.v] << ") estan en el mismo set\n";
        }
    }
    return res;
}

int main() {
    vector<char> letras = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    cout << "===== EJEMPLO 1 =====" << "\n";
    vector<vector<pair<int,int>>> ej1(5);
    ej1[0] = {{1,2},{3,2}};
    ej1[1] = {{0,2},{2,4},{3,3}};
    ej1[2] = {{1,4},{3,4},{4,5}};
    ej1[3] = {{0,2},{1,3},{2,4},{4,5}};
    ej1[4] = {{2,5},{5,5}};
    //Imprime lista de adyacencia
    imprimirListaAdy(ej1, 5, letras);
    //Convierte e imprime a aristas de forma ascendente
    vector<Arista> a = converListaAristas(ej1);
    imprimirAristasOrdenadas(a, letras);
    //Devuelve el arbol de recubrimiento minimo
    cout << "----- Proceso -----" << "\n";
    vector<Arista> res = kruskal(a, 5, letras);
    cout << "----- Arbol de recubrimiento minimo -----" << "\n";
    imprimirAristasOrdenadas(res, letras);
    cout << "===== FIN DE EJEMPLO 1 =====" << "\n\n";

    cout << "===== EJEMPLO 2 =====" << "\n";
    vector<vector<pair<int,int>>> ej2(6);
    ej2[0] = {{1,3},{5,4}};          // A
    ej2[1] = {{0,3},{2,2},{4,6}};    // B
    ej2[2] = {{1,2},{3,5}};          // C
    ej2[3] = {{2,5},{4,1}};          // D
    ej2[4] = {{3,1},{5,2},{1,6}};    // E
    ej2[5] = {{4,2},{0,4}};          // F
    //Imprime lista de adyacencia
    imprimirListaAdy(ej2, 6, letras);
    //Convierte e imprime a aristas de forma ascendente
    a = converListaAristas(ej2);
    imprimirAristasOrdenadas(a, letras);
    //Devuelve el arbol de recubrimiento minimo
    cout << "----- Proceso -----" << "\n";
    res = kruskal(a, 6, letras);
    cout << "----- Arbol de recubrimiento minimo -----" << "\n";
    imprimirAristasOrdenadas(res, letras);
    cout << "===== FIN DE EJEMPLO 2 =====" << "\n\n";

    cout << "===== EJEMPLO 3 =====" << "\n";
    vector<vector<pair<int,int>>> ej3(7);
    ej3[0] = {{1,1},{2,4},{3,3},{4,2},{5,7},{6,6}};   // Centro A
    ej3[1] = {{0,1},{2,5}};                           // B
    ej3[2] = {{0,4},{1,5},{3,1}};                     // C
    ej3[3] = {{0,3},{2,1},{4,4}};                     // D
    ej3[4] = {{0,2},{3,4},{6,3}};                     // E
    ej3[5] = {{0,7},{6,2}};                           // F
    ej3[6] = {{0,6},{4,3},{5,2}};                     // G
    //Imprime lista de adyacencia
    imprimirListaAdy(ej3, 7, letras);
    //Convierte e imprime a aristas de forma ascendente
    a = converListaAristas(ej3);
    imprimirAristasOrdenadas(a, letras);
    //Devuelve el arbol de recubrimiento minimo
    cout << "----- Proceso -----" << "\n";
    res = kruskal(a, 7, letras);
    cout << "----- Arbol de recubrimiento minimo -----" << "\n";
    imprimirAristasOrdenadas(res, letras);
    cout << "===== FIN DE EJEMPLO 3 =====" << "\n\n";

    cout << "===== EJEMPLO 4 =====" << "\n";
    vector<vector<pair<int,int>>> ej4(8);
    ej4[0] = {{1,2},{4,3}};          // A
    ej4[1] = {{0,2},{2,1},{5,4}};    // B
    ej4[2] = {{1,1},{3,2},{6,3}};    // C
    ej4[3] = {{2,2},{7,5}};          // D
    ej4[4] = {{0,3},{5,2}};          // E
    ej4[5] = {{4,2},{1,4},{6,1}};    // F
    ej4[6] = {{5,1},{2,3},{7,2}};    // G
    ej4[7] = {{3,5},{6,2}};          // H
    //Imprime lista de adyacencia
    imprimirListaAdy(ej4, 8, letras);
    //Convierte e imprime a aristas de forma ascendente
    a = converListaAristas(ej4);
    imprimirAristasOrdenadas(a, letras);
    //Devuelve el arbol de recubrimiento minimo
    cout << "----- Proceso -----" << "\n";
    res = kruskal(a, 8, letras);
    cout << "----- Arbol de recubrimiento minimo -----" << "\n";
    imprimirAristasOrdenadas(res, letras);
    cout << "===== FIN DE EJEMPLO 4 =====" << "\n\n";

    cout << "===== EJEMPLO 5 =====" << "\n";
    vector<vector<pair<int,int>>> ej5(6);
    ej5[0] = {{1,3},{2,8},{3,5}};        // A
    ej5[1] = {{0,3},{2,2},{4,7}};        // B
    ej5[2] = {{0,8},{1,2},{5,4}};        // C
    ej5[3] = {{0,5},{4,1},{5,3}};        // D
    ej5[4] = {{1,7},{3,1},{5,6}};        // E
    ej5[5] = {{2,4},{3,3},{4,6}};        // F
    //Imprime lista de adyacencia
    imprimirListaAdy(ej5, 6, letras);
    //Convierte e imprime a aristas de forma ascendente
    a = converListaAristas(ej5);
    imprimirAristasOrdenadas(a, letras);
    //Devuelve el arbol de recubrimiento minimo
    cout << "----- Proceso -----" << "\n";
    res = kruskal(a, 6, letras);
    cout << "----- Arbol de recubrimiento minimo -----" << "\n";
    imprimirAristasOrdenadas(res, letras);
    cout << "===== FIN DE EJEMPLO 5 =====" << "\n\n";

    return 0;
}
