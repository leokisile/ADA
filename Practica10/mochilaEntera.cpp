#include <bits/stdc++.h>
using namespace std;

// ==================== LECTURA DE OBJETOS DESDE TXT ====================
vector<pair<int,int>> leeObjetosDesdeArchivo(const string &nombreArchivo, int &W, int &n) {
    ifstream archivo(nombreArchivo);
    vector<pair<int,int>> objetos;
    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << "\n";
        return objetos;
    }

    archivo >> W >> n;
    pair<int,int> objeto;
    for(int i = 0; i < n; i++) {
        archivo >> objeto.first >> objeto.second;
        objetos.push_back(objeto);
    }

    archivo.close();
    return objetos;
}

void imprimeObjetos(vector<pair<int,int>> &objetos){
    int i = 1;
    for(auto &obj: objetos){
        cout << i++ << ".- " << "v: " << obj.first << "\tw: " << obj.second << "\n";
    }
}

// ==================== GENERAR MATRIZ DE VALORES ====================
vector<vector<int>> matrizValor(int n, int W, vector<pair<int,int>> &objetos){
    vector<vector<int>> matriz(n + 1, vector<int>(W + 1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= W; j++){
            if (objetos[i-1].second > j)
                matriz[i][j] = matriz[i-1][j];
            else
                matriz[i][j] = max(matriz[i-1][j], matriz[i-1][j - objetos[i-1].second] + objetos[i-1].first);
        }
    }
    return matriz;
}

void imprimeMatriz(const vector<vector<int>> &matriz){
    for (const auto &fila : matriz){
        for (int valor : fila){
            cout << setw(4) << valor << " ";
        }
        cout << "\n";
    }
}

// ==================== GUARDAR MATRIZ EN TXT ====================
void guardaMatrizArchivo(const vector<vector<int>> &matriz, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo " << nombreArchivo << "\n";
        return;
    }

    for (const auto &fila : matriz){
        for (int valor : fila){
            archivo << valor << " ";
        }
        archivo << "\n";
    }

    archivo.close();
    cout << "Matriz guardada en " << nombreArchivo << "\n";
}

// ==================== RECUPERAR MATRIZ DESDE TXT ====================
vector<vector<int>> leeMatrizDesdeArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<vector<int>> matriz;
    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << "\n";
        return matriz;
    }

    string linea;
    while(getline(archivo, linea)){
        istringstream iss(linea);
        vector<int> fila;
        int valor;
        while(iss >> valor){
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }

    archivo.close();
    return matriz;
}

// ==================== OBTENER OBJETOS RESULTADO ====================
vector<pair<int,int>> listaRes(vector<vector<int>> &matriz, int n, int W, vector<pair<int,int>> &objetos) {
    vector<pair<int,int>> res;
    int i = n, j = W;

    while(i > 0 && j > 0){
        if(matriz[i][j] != matriz[i-1][j]){
            res.push_back(objetos[i-1]);
            j -= objetos[i-1].second;
        }
        i--;
    }

    return res;
}

// ==================== MAIN ====================
int main(){
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de objetos (txt): ";
    cin >> nombreArchivo;

    int W, n;
    vector<pair<int,int>> objetos = leeObjetosDesdeArchivo(nombreArchivo, W, n);

    if(objetos.empty()){
        cout << "No hay objetos o no se pudo leer el archivo.\n";
        return 1;
    }

    cout << "\nObjetos leídos:\n";
    imprimeObjetos(objetos);
    cout << "\nPeso maximo: " << W << "\n";

    vector<vector<int>> matriz = matrizValor(n, W, objetos);

    cout << "\nMatriz de valores:\n";
    imprimeMatriz(matriz);

    // Guardar matriz
    string nombreMatriz = "matriz_generada.txt";
    guardaMatrizArchivo(matriz, nombreMatriz);

    // Preguntar si usar matriz existente
    char opcion;
    cout << "¿Desea usar la matriz generada (" << nombreMatriz << ") o especificar otra matriz? (g/o): ";
    cin >> opcion;
    if(opcion == 'o'){
        cout << "Ingrese el nombre del archivo de la matriz: ";
        cin >> nombreMatriz;
        matriz = leeMatrizDesdeArchivo(nombreMatriz);
        if(matriz.empty()){
            cout << "No se pudo leer la matriz.\n";
            return 1;
        }
        cout << "\nMatriz leída desde archivo:\n";
        imprimeMatriz(matriz);
    }

    vector<pair<int,int>> res = listaRes(matriz, n, W, objetos);
    cout << "\nObjetos seleccionados:\n";
    imprimeObjetos(res);

    return 0;
}
