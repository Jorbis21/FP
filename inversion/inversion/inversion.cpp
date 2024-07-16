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

int digito(unsigned long long int n) {
    int sol = 0;
    if (n < 10)
        sol = 1;
    else
        sol = 1 + digito(n / 10);
    return sol;
}

sol invertir(int n) {
    sol sol;int x = 1;
    sol.pot = digito(n);
    if (n < 10) {
        sol.numero = n;
    }
    else {
        for (int i = sol.pot - 1; i > 0; i--) {
            x *= 10;
        }
        sol.numero = (n % 10) * x + invertir(n / 10).numero;
    }
    return sol;
}

bool resuelveCaso() {
    sol sol; int num;
    cin >> num;
    if (!std::cin)
        return false;
    sol = invertir(num);
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
