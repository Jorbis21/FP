// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: El burro y las alforjas
// Comentario general sobre la solución: Datos de entrada limitados
#include <iostream>
#include <fstream>
using namespace std;
const int N = 100;
typedef int tLista[N];
typedef struct {
	int alforja1 = 0;
	int alforja2 = 0;
	int burro = 0;
}tBurro;
// función que resuelve el problema de ordenar los “total” elementos de la “lista”
void resolver(tLista lista, int total) {
	int tmp;
	for (int i = 0; i < total; i++) {
		for (int j = total - 1; j > i; j--) {
			if (lista[j] < lista[j - 1]) {
				tmp = lista[j];
				lista[j] = lista[j - 1];
				lista[j - 1] = tmp;
			}
		}
	}
	// Introducir el código que corresponda
}
// Resuelve un caso de prueba, leyendo de la entrada que es una secuencia de números que
// finaliza cuando se encuentra al centinela “0”
// Se escribe la secuencia de números separados por un espacio
void resuelveCaso(tBurro burro) {
	// leer la secuencia de números que finaliza con el centinela “0”
	// y se almacenan en un array llamado “lista”
	tLista lista;
	int num, i = 0, sacos = 0, burros = 0;
	burro.burro = 0;
	cin >> burros;
	cin >> sacos;
	while (i < sacos) {
		cin >> num;
		lista[i] = num;
		i++;
	}
	// Es necesario pasar el número de elementos que contiene la lista
	resolver(lista, i);
	// Escribo la secuencia de números ordenados, separados por un espacio en blanco
	for (int j = 0; j < i; j++) {
		burro.alforja1 = lista[j];
		burro.alforja2 = lista[j + 1];
		if (burro.burro == burros) {
			j = i;
		}
		else if (burro.alforja1 == burro.alforja2) {
			burro.burro++;
			j++;
		}
	}
	cout << burro.burro;
	cout << endl;
}
int main() {
	tBurro burro;
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
		resuelveCaso(burro);
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

