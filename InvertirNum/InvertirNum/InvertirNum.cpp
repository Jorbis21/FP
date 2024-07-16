// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Numero invertido
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct sol {
    long long int numero = 0;
    int pot = 0;
};

sol invertir(sol sol, string& num) {
    if (sol.numero < 10) {
        num = num + to_string(sol.numero % 10);
        sol.numero = stoi(num);
        return sol;
    }        
    else {
        num = num + to_string(sol.numero % 10);
        sol.numero = sol.numero / 10;
        sol.pot++;
        return invertir(sol, num);
    }
}

bool resuelveCaso() {
    sol sol;
    string num;
    cin >> sol.numero;
    if (!std::cin)
        return false;
    sol = invertir(sol, num);
    cout << sol.numero << endl;
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