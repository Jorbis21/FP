// ************************1***************************

// Prueba de evaluación del día 22 de junio de 2020
// Alumno/a: Javier Orbis Ramirez
// email:  jorbis@ucm.es
// Grupo: B

// ****************************************************



#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NF = 6;
const int NC = 12;
typedef int tMatriz[NF][NC];

const int M = 30;

// Funcion que lee los datos de entrada y crea la matriz
void cargarMatriz(tMatriz m);

// Funcion que muestra los datos de una matriz
// Esta función se proporciona para ayudar a depurar el código
// No se debe mostrar la matriz en la solución enviada al juez
void mostrarMatriz(tMatriz m);

//AÑADE AQUÍ LOS PROTOTIPOS DE TUS FUNCIONES
bool atractivo(int aux);
int solucion(tMatriz m);



void resuelveCaso() {
    int nf, nc;
    std::cin >> nf >> nc;
    tMatriz m;
    cargarMatriz(m);
    // Muestra la matriz para ver si se ha cargardo bien
    // Después comenta mostrarMatriz para enviar al juez
    //mostrarMatriz(m);
    
    cout << solucion(m) << endl;
}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
    std::ofstream out("sample.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos; cin >> numCasos; cin.ignore();
    for (int i = 0; i < numCasos; ++i) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif

    return 0;
}




void cargarMatriz(tMatriz m) {
    for (int f = 0; f < NF; f++) {
        for (int c = 0; c < NC; c++) {
            cin >> m[f][c];
        }
    }
}

// Esta función se proporciona para ayudar a depurar el código
// No se debe mostrar la matriz en la solución enviada al juez
void mostrarMatriz(tMatriz m) {
    cout << "MATRIZ" << endl;
    for (int f = 0; f < NF; f++) {
        for (int c = 0; c < NC; c++) {
            cout << m[f][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
bool atractivo(int aux) {//comprueba si es atractivo o no
    if (aux < M) {
        return false;
    }
    else {
        return true;
    }
}

int solucion(tMatriz m){//recorre la matriz y al finalizar devuelve cuantos no son atractivos
    int aux = 0, cont = 0;
    int j = 0;
    while (j < NF) {
        int i = 0;
        aux = 0;
        while (i < NC){ 
            aux = aux + m[j][i];
            i++;
        }
        if (!atractivo(aux)) {
            cont++;
        }
        j++;
    }
    return cont;
}

//AÑADE AQUÍ LA IMPLEMENTACIÓN DE TUS FUNCIONES