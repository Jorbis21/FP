// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

typedef struct {
    string titulo;
    string tema;
    int foto[50][50];
}tFoto;

typedef struct {
    int numfotos;
    tFoto arrayfotos[200];
}tArrayfotos;

void resolver() {

}

void cargar(tFoto& foto, int num) {
   
    for (int i = 0; i < num; i++) {
        cin >> foto.titulo;
    }
}
bool resuelveCaso() {
    tFoto foto;
    int num = 0;
    cin >> num;
    
    if (num == 0)
        return false;
    
    cargar(foto, num);



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