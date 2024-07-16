// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Coleccion de fotos por vectores 14

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
    tFoto arrayfotos[N];
}tArrayfotos;
typedef tFoto *tPuntfotos;
typedef struct{
    tPuntfotos array[N];
    int cont;
}tArraypunteros;

void ordenartitulo(tArraypunteros& titulo, int num) {
    bool inter = true;
    int i = 0;
    while ((i < num - 1) && inter) {
        inter = false;
        for (int j = num - 1; j > i; j--) {
            if (titulo.array[j]->titulo < titulo.array[j - 1]->titulo) {
                tArraypunteros tmp;
                tmp.array[j] = titulo.array[j];
                titulo.array[j] = titulo.array[j - 1];
                titulo.array[j - 1] = tmp.array[j];
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }
}
void ordenartema(tArraypunteros& tema, int num) {
    bool inter = true;
    int i = 0;
    while ((i < num - 1) && inter) {
        inter = false;
        for (int j = num - 1; j > i; j--) {
            if (tema.array[j]->tema < tema.array[j - 1]->tema) {
                tArraypunteros tmp;
                tmp.array[j] = tema.array[j];
                tema.array[j] = tema.array[j - 1];
                tema.array[j - 1] = tmp.array[j];
                inter = true;
            }
            else if (tema.array[j]->tema == tema.array[j - 1]->tema) {
                if (tema.array[j]->titulo < tema.array[j - 1]->titulo) {
                    tArraypunteros tmp;
                    tmp.array[j] = tema.array[j];
                    tema.array[j] = tema.array[j - 1];
                    tema.array[j - 1] = tmp.array[j];
                    inter = true;
                }
            }
        }
        if (inter) {
            i++;
        }
    }
}
void mostrartitulos(tArraypunteros& titulo, int num) {
    for (int i = 0; i < num; i++) {
        cout << titulo.array[i]->titulo << endl;
    }
    cout << endl;
}
void mostrartema(tArraypunteros& tema, int num) {
    for (int i = 0; i < num; i++) {
        cout << tema.array[i]->tema << " - " << tema.array[i]->titulo << endl;
    }
}
void cargar(tArrayfotos& foto) {
    cin.ignore();
    for (int i = 0; i < foto.numfotos; i++) {
        getline(cin, foto.arrayfotos[i].titulo);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                foto.arrayfotos[i].foto[j][k] = 3;
            }
        }
    }
    for (int i = 0; i < foto.numfotos; i++) {
        getline(cin, foto.arrayfotos[i].tema);

    }
}
bool resuelveCaso() {
    tArrayfotos foto;
    foto.numfotos = 0;
    cin >> foto.numfotos;
    if (foto.numfotos == 0)
        return false;
    cargar(foto);
    int num = foto.numfotos;
    tArraypunteros titulo, tema;
    for (int i = 0; i < num; i++) {
        titulo.array[i] = &foto.arrayfotos[i];
        tema.array[i] = &foto.arrayfotos[i];
    }
    ordenartitulo(titulo, num);
    ordenartema(tema, num);
    mostrartitulos(titulo, num);
    mostrartema(tema, num);
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