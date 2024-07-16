// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Consultas

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int N = 200;
typedef struct {
    int codigo;
    string especialidad;
}tEspecialidades;
typedef struct {
    int capacidad;
    int cont;
    tEspecialidades* especial;
}tArrayDinEsp;
typedef struct {
    int codigo;
    string fecha;
    int numCon;
}tConsultas;
typedef struct {
    int cont;
    tConsultas* array[N];
}tArrayConsultas;

void aumentar(tArrayDinEsp& esp) {
    tEspecialidades* aux = nullptr;
    aux = new tEspecialidades[2 * esp.capacidad];
    for (int i = 0; i < esp.capacidad; i++)
        aux[i] = esp.especial[i];
    delete[] esp.especial;
    esp.especial = aux;
    esp.capacidad *= 2;
    aux = nullptr;
}
void cargar(tArrayDinEsp& esp, tArrayConsultas& consul, int codigo) {
    consul.cont = 0;
    while (codigo != -1) {
        consul.array[consul.cont] = new tConsultas;
        consul.array[consul.cont]->codigo = codigo;
        cin >> consul.array[consul.cont]->fecha >> consul.array[consul.cont]->numCon;
        consul.cont++;
        cin >> codigo;
    }
    esp.cont = 0;
    cin >> codigo;
    while (codigo != -1) {
        esp.especial[esp.cont].codigo = codigo;
        getline(cin, esp.especial[esp.cont].especialidad);
        esp.cont++;
        if (esp.cont == esp.capacidad) {
            aumentar(esp);
        }
        cin >> codigo;
    }
}
void ordenar(tArrayConsultas& consul) {
    bool inter = true;
    int i = 0;
    while ((i < consul.cont - 1) && inter) {
        inter = false;
        for (int j = consul.cont - 1; j > i; j--) {
            if (consul.array[j]->fecha < consul.array[j - 1]->fecha) {
                tArrayConsultas tmp;
                tmp.array[j] = consul.array[j];
                consul.array[j] = consul.array[j - 1];
                consul.array[j - 1] = tmp.array[j];
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }
}
void mostrar(tArrayDinEsp& esp, tArrayConsultas& consul) {
    for (int i = 0; i < consul.cont; i++) {//a lo mejor hay que cambiar consul cont
        cout << consul.array[i]->fecha;
        int j = 0;
        bool encontrado = false;
        while (j <= esp.cont && !encontrado) {//rt
            if (consul.array[i]->codigo == esp.especial[j].codigo) {
                cout << esp.especial[j].especialidad << " " << consul.array[i]->numCon << endl;
                encontrado = true;
            }     
            j++;
        }
        if (!encontrado) {
            cout << " Especialidad inexistente" << endl;
        }
    }
}
bool resuelveCaso() {
    tArrayDinEsp esp;
    tArrayConsultas consul;
    int codigo = -1;
    esp.capacidad = 2;
    esp.especial = new tEspecialidades[esp.capacidad];
    cin >> codigo;
    if (codigo == -1)
        return false;
    cargar(esp, consul, codigo);
    ordenar(consul);
    mostrar(esp, consul);
    delete[] esp.especial;
    esp.especial = nullptr;
    for (int i = 0; i < consul.cont; i++) 
        delete consul.array[i];
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
