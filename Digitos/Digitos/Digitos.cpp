// Autor/a: Javier Orbis Ramirez
// email: jorbis@ucm.es
// Compilador y S.O. Visual studio 2019 16.6.1 Windows 10
// Nombre del problema Numero digitos
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int digito(unsigned long long int n) {
    int sol = 0;
    if (n < 10)
        sol = 1;
    else 
        sol = 1 + digito(n / 10);
    return sol;
}
bool resuelveCaso() {
    long long int num;
    cin >> num;
    if (!std::cin)
        return false;
    cout << digito(num) << endl;   
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