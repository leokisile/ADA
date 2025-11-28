#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//Estructura nodo
struct Nodo {
    char simbolo;
    float freq;
    Nodo* left;
    Nodo* right;

    Nodo(char s, float f) : simbolo(s), freq(f), left(nullptr), right(nullptr) {}
};

//Comparador para min heap
struct Comparar {
    bool operator()(Nodo* a, Nodo* b) const {
        return a->freq > b->freq;  // Menor frecuencia tiene mayor prioridad
    }
};

void imprimirArbolASCII(Nodo* root, string prefijo = "", bool esIzq = true) {
    if (!root)
        return;

    cout << prefijo;

    if (esIzq)
        cout << "|--";
    else
        cout << "|__";

    if (root->simbolo != '\0') {
        if (root->simbolo == ' ')
            cout << "' '" << "(" << root->freq << ")\n";
        else
            cout << root->simbolo << "(" << root->freq << ")\n";
    } else {
        cout << "(" << root->freq << ")\n";
    }

    string nuevoPrefijo = prefijo + (esIzq ? "|   " : "    ");
    imprimirArbolASCII(root->left, nuevoPrefijo, true);
    imprimirArbolASCII(root->right, nuevoPrefijo, false);
}


Nodo* construirHuffman(priority_queue<Nodo*, vector<Nodo*>, Comparar>& pq) {
    while (pq.size() > 1) {
        Nodo* izq = pq.top(); pq.pop();
        Nodo* der = pq.top(); pq.pop();

        Nodo* nuevo = new Nodo('\0', izq->freq + der->freq);
        nuevo->left = izq;
        nuevo->right = der;

        pq.push(nuevo);
    }
    return pq.top();
}

void generarCodigos(Nodo* root, string codigo, unordered_map<char,string>& tabla) {
    if (!root) return;

    if (root->simbolo != '\0') {
        tabla[root->simbolo] = codigo;
        return;
    }

    generarCodigos(root->left, codigo + "0", tabla);
    generarCodigos(root->right, codigo + "1", tabla);
}

int main() {
    priority_queue<Nodo*, vector<Nodo*>, Comparar> pq;

    //Leer archivo
    ifstream entrada("abecedario.txt");
    if (!entrada) {
        cout << "ERROR: No se pudo abrir el archivo entrada.txt\n";
        return 1;
    }

    cout << "Leyendo datos desde entrada.txt...\n";

    string s;
    float f;

    while (entrada >> s >> f) {
        char simbolo;

        if (s == "espacio")
            simbolo = ' ';
        else
            simbolo = s[0];

        pq.push(new Nodo(simbolo, f));
    }

    entrada.close();

    if (pq.empty()) {
        cout << "El archivo no contenía datos válidos.\n";
        return 1;
    }

    //Raíz del árbol de huffman
    Nodo* raiz = construirHuffman(pq);

    //Imprimir arbol
    cout << "\nÁrbol de Huffman generado:\n";
    imprimirArbolASCII(raiz);


    unordered_map<char,string> tabla;
    generarCodigos(raiz, "", tabla);

    ofstream salida("codificacion.txt");
    salida << "Letra - Codificacion Huffman\n";
    salida << "=============================\n\n";

    cout << "\nCódigos generados:\n";
    for (auto& p : tabla) {
        char c = p.first;
        string code = p.second;

        if (c == ' ') {
            cout << "' '" << " : " << code << endl;
            salida << "' '" << " : " << code << endl;
        } else {
            cout << c << " : " << code << endl;
            salida << c << " : " << code << endl;
        }
    }

    salida.close();
    cout << "\nArchivo 'codificacion.txt' escrito correctamente.\n";

    return 0;
}
