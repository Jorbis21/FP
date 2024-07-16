// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Interseccion de conjuntos
// Comentario general sobre la solución: Datos de entrada limitados
#include <iostream>
#include <fstream>
using namespace std;
typedef struct {
	int cto[500];
	int cont = 0;
}tCto;
typedef tCto tconj[3];
// función que resuelve el problema de ordenar los “total” elementos de la “lista”
void resolver(tconj cto, int total, int k) {
	int tmp;	
	for (int i = 0; i < total; i++) {
		for (int j = total - 1; j > i; j--) {
			if (cto[k].cto[j] < cto[k].cto[j - 1]) {
				tmp = cto[k].cto[j];
				cto[k].cto[j] = cto[k].cto[j - 1];
				cto[k].cto[j - 1] = tmp;
			}
		}
	}
}
void resuelveCaso(tconj cto) {
	int num;
	for (int j = 0; j < 2; j++) {
		int i = 0;
		cin >> num;
		while (num != 0) {
			cto[j].cto[i] = num;
			cin >> num;
			i++;
		}
		resolver(cto, i, j);
	}
	
	// Es necesario pasar el número de elementos que contiene la lista
	// Escribo la secuencia de números ordenados, separados por un espacio en blanco
	

	cout << endl;
}
int main() {
	tconj cto;
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
	// caso de pruebas limitados (4 casos).
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso(cto);
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}