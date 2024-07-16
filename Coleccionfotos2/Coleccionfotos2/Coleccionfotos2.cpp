// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Coleccion de fotos por vectores y memoria dinamica 15

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const short int n = 50, N = 200;

typedef struct {
    string titulo;
    string tema;
    short int foto[n][n];
}tFoto;
typedef struct {
    int numfotos;
    tFoto * arrayfotos[N];
}tArrayfotos;

void ordenartitulo(tArrayfotos& titulo, int num) {
    bool inter = true;
    int i = 0;
    while ((i < num - 1) && inter) {
        inter = false;
        for (int j = num - 1; j > i; j--) {
            if (titulo.arrayfotos[j]->titulo < titulo.arrayfotos[j - 1]->titulo) {
                tArrayfotos tmp;
                tmp.arrayfotos[j] = titulo.arrayfotos[j];
                titulo.arrayfotos[j] = titulo.arrayfotos[j - 1];
                titulo.arrayfotos[j - 1] = tmp.arrayfotos[j];
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }
}
void ordenartema(tArrayfotos& tema, int num) {
    bool inter = true;
    int i = 0;
    while ((i < num - 1) && inter) {
        inter = false;
        for (int j = num - 1; j > i; j--) {
            if (tema.arrayfotos[j]->tema < tema.arrayfotos[j - 1]->tema) {
                tArrayfotos tmp;
                tmp.arrayfotos[j] = tema.arrayfotos[j];
                tema.arrayfotos[j] = tema.arrayfotos[j - 1];
                tema.arrayfotos[j - 1] = tmp.arrayfotos[j];
                inter = true;
            }
            else if (tema.arrayfotos[j]->tema == tema.arrayfotos[j - 1]->tema) {
                if (tema.arrayfotos[j]->titulo < tema.arrayfotos[j - 1]->titulo) {
                    tArrayfotos tmp;
                    tmp.arrayfotos[j] = tema.arrayfotos[j];
                    tema.arrayfotos[j] = tema.arrayfotos[j - 1];
                    tema.arrayfotos[j - 1] = tmp.arrayfotos[j];
                    inter = true;
                }
            }
        }
        if (inter) {
            i++;
        }
    }
}
void mostrar(tArrayfotos& tema, tArrayfotos& titulo, int num) {
    for (int i = 0; i < num; i++) {
        cout << titulo.arrayfotos[i]->titulo << endl;
    }
    cout << endl;
    for (int i = 0; i < num; i++) {
        cout << tema.arrayfotos[i]->tema << " - " << tema.arrayfotos[i]->titulo << endl;
    }
}
void cargar(tArrayfotos& titulo, tArrayfotos& tema) {
    cin.ignore();
    for (int i = 0; i < titulo.numfotos; i++) {
        titulo.arrayfotos[i] = new tFoto;
        getline(cin, titulo.arrayfotos[i]->titulo);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                titulo.arrayfotos[i]->foto[j][k] = 3;
            }
        }
    }
    for (int i = 0; i < tema.numfotos; i++) {
        tema.arrayfotos[i] = new tFoto;
        getline(cin, tema.arrayfotos[i]->tema);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                tema.arrayfotos[i]->foto[j][k] = 3;
            }
        }
    }
    for (int i = 0; i < tema.numfotos; i++) {
        tema.arrayfotos[i]->titulo = titulo.arrayfotos[i]->titulo;
    }

}
void eliminar(tArrayfotos& titulo, tArrayfotos& tema) {
    for (int i = 0; i < titulo.numfotos; i++) {
        delete titulo.arrayfotos[i];
        delete tema.arrayfotos[i];
    }
}
bool resuelveCaso() {
    tArrayfotos titulo, tema;
    
    cin >> titulo.numfotos;
    tema.numfotos = titulo.numfotos;
    if (titulo.numfotos == 0)
        return false;
    cargar(titulo, tema);
    int num = titulo.numfotos;
    
    ordenartitulo(titulo, num);
    ordenartema(tema, num);
    mostrar(tema, titulo, num);
    eliminar(titulo, tema);
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