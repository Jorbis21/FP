// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Vectores Dinamicos 17
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef struct {
    string nombre;
    int cantidad;
}tObj;
typedef struct {
    tObj *vector;
    int cont;
    int cap;
}tVector;

bool buscar(tVector& vector, string& objeto, int& pos){
    bool encontrado = false;
    int i = 0;
    while (!encontrado && i <= vector.cont) {
        if (objeto == vector.vector[i].nombre) {
            encontrado = true;
        }
        i++;
    }
    if (encontrado) {
        pos = i - 1;
        return true;
    } 
    else
        return false;
}
void aumentarcap(tVector& vector) {
    tObj* aux = nullptr;
    aux = new tObj[2 * vector.cap];
    for (int i = 0; i < vector.cap; i++) 
        aux[i] = vector.vector[i];
    delete[] vector.vector;
    vector.vector = aux;
    vector.cap *= 2;
    aux = nullptr;
}
bool resuelveCaso() {
    tVector vector;
    string nombre;
    int cant = 0, pos = -1;
    vector.cap = 3;
    vector.vector = new tObj[vector.cap];
    char c;
    cin >> c;
    if (c == 'F' || !cin)
        return false;
    vector.cont = 0;
    while (c != 'F') {
        switch (c) {
        case 'A': {
            cin >> nombre >> cant;
            if (buscar(vector, nombre, pos)) {
                vector.vector[pos].cantidad = vector.vector[pos].cantidad + cant;
            }
            else {
                vector.vector[vector.cont].nombre = nombre;
                vector.vector[vector.cont].cantidad = cant;
                vector.cont++;
            }  
        }
                break;
        case 'R': {
            cin >> nombre >> cant;
            if (buscar(vector, nombre, pos)) {
                vector.vector[pos].cantidad = vector.vector[pos].cantidad - cant;
                if (vector.vector[pos].cantidad < 0) {
                    vector.vector[pos].cantidad = 0;
                }
            }
        }
                break;
        case 'L': {
            for (int i = 0; i < vector.cont; i++) {
                cout << vector.vector[i].nombre << " " << vector.vector[i].cantidad << endl;
            }
            cout << "---" << endl;
        }
                break;
        }
        if (vector.cont >= vector.cap) {
            aumentarcap(vector);
        }
        cin >> c;  
    }
    delete[] vector.vector;
    vector.vector = nullptr;
    return true;
}

int main() {
  
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}