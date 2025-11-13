#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct tarea{
    string nombre;
    int tiempo;
};

vector<tarea> generarVector(int n, vector<string> tareas){
    vector<tarea> lista;
    int i;
    srand(time(0));
    for(i=0; i < n; i++){
        tarea t;
        t.nombre = tareas[rand() % 40];
        t.tiempo = rand() % 10 + 1;
        lista.push_back(t);
    }
    return lista;
}

void imprimeVector(int n, vector<tarea> lista){
    int i;
    for(i=0; i < n; i++){
        cout << i+1 << ".- " << lista[i].nombre << "\tTiempo: " << lista[i].tiempo << "\n" << endl;
    }
    cout << "\n";
}

vector<tarea> optimizarLista(int x, int n, vector<tarea> lista){
    vector<tarea> optimizado;
    int i=0, suma = 0;
    while(lista[i].tiempo + suma <= x || i >= n){
        optimizado.push_back(lista[i]);
        suma += lista[i].tiempo;
        i++;
    }
    return optimizado;
}

int main(){
    vector<string> tareas = {
    "Compilar",
    "Depurar",
    "Comitear",
    "Pushear",
    "Mergear",
    "Documentar",
    "Probar",
    "Diseñar",
    "Analizar",
    "Codificar",
    "Refactorizar",
    "Ejecutar",
    "Optimizar",
    "Comentar",
    "Importar",
    "Exportar",
    "Versionar",
    "Enlazar",
    "Testear",
    "Deployar",
    "Configurar",
    "Instalar",
    "Actualizar",
    "Planificar",
    "Integrar",
    "Simular",
    "Cifrar",
    "Desplegar",
    "CompilarDebug",
    "HacerBackup",
    "RevisarLogs",
    "LimpiarCache",
    "DiseñarClase",
    "CrearModulo",
    "LanzarBuild",
    "MedirRend",
    "ResolverBug",
    "ArmarScript",
    "LeerEntrada",
    "ValidarDatos"
    };
    int n, x;
    cout << "Introduzca el numero de tareas: ";
    cin >> n;
    cout << "Introduzca el tiempo disponible: ";
    cin >> x;

    vector<tarea> lista = generarVector(n, tareas);
    cout << "Lista de tareas: \n";

    sort(lista.begin(), lista.end(), [](const tarea& a, const tarea& b) {//Inicio, fin, criterio(lambda)
    return a.tiempo < b.tiempo;  // criterio de orden
    });

    imprimeVector(n, lista);

    vector<tarea> optimizado = optimizarLista(x, n, lista);
    cout << "Lista optimizada para " << x <<" horas: \n" << endl;
    imprimeVector(optimizado.size(), optimizado);

    return 0;
}
