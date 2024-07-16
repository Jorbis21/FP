// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Mapa Topográfico
// Comentario general sobre la solución: Datos de entrada ilimitados
#include <iostream>
#include <fstream>
using namespace std;
typedef int tMatriz[100][100];
typedef struct {
	int x = 0;
	int y = 0;
	int mayor = 0;
}tCoord;
void resolver(tMatriz &matriz, tCoord &sol, int N1, int N2) {
	sol.mayor = matriz[0][0];
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			if (sol.mayor < matriz[i][j]) {
				sol.mayor = matriz[i][j];
				sol.x = i;
				sol.y = j;
			}
		
		}
	}
}

bool resuelveCaso() {
	tMatriz matriz;
	tCoord sol;
	int N1, N2, num;
	cin >> N1 >> N2;
	
	if (!std::cin)  // fin de la entrada
		return false;

	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			cin >> num;
			matriz[i][j] = num;
		}
	}

	resolver(matriz, sol, N1, N2);

	cout << sol.mayor << " " << sol.x << " " << sol.y;
	cout << endl;
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}