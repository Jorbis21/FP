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
tFoto *cargar(tArrayfotos& titulo, tArrayfotos& tema) {
    tFoto* ArrayDin = new tFoto[titulo.numfotos];
    cin.ignore();
    for (int i = 0; i < titulo.numfotos; i++) {
        getline(cin, ArrayDin[i].titulo);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ArrayDin[i].foto[j][k] = 3;
            }
        }
        titulo.arrayfotos[i] = &ArrayDin[i];
        tema.arrayfotos[i] = &ArrayDin[i];
    }
    for (int i = 0; i < tema.numfotos; i++) {
        getline(cin, ArrayDin[i].tema);
        tema.arrayfotos[i] = &ArrayDin[i];
        titulo.arrayfotos[i] = &ArrayDin[i];
    }
    return ArrayDin;
}
bool resuelveCaso() {
    tArrayfotos titulo, tema;
    cin >> titulo.numfotos;
    tema.numfotos = titulo.numfotos;
    if (titulo.numfotos == 0)
        return false;
    tFoto *foto = cargar(titulo, tema);
    int num = titulo.numfotos;
    ordenartitulo(titulo, num);
    ordenartema(tema, num);
    mostrar(tema, titulo, num);
    delete[] foto;
    foto = NULL;
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