// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Sudoku
// Comentario general sobre la solución: Datos de entrada limitados

#include <iostream>
#include <fstream>
using namespace std;
const int N = 9;
typedef int tMatriz[N][N];
typedef int tLinea[N];
typedef bool tBolinea[N];

typedef struct {
	tMatriz sudoku;
	tLinea linea;
	tBolinea bolinea;
	int cont = 0;
}tSudoku;
void iniciar(tSudoku& doku) {
	int n = 1;
	for (int i = 0; i < N; i++) {
		doku.linea[i] = n;
		doku.bolinea[i] = false;
		n++;
	}
}
bool cuadrantes(tSudoku& doku, bool exito) {
	bool fin = false;
	int h = 0;
	int g = 0;
	int f = 0;
	while (exito && f < N) {
		int i = 0;
		while (exito && (i + g) < (3 + g)) {
			int j = 0;
			while (exito && (j + h) < (3 + h)) {
				int n = 0;
				while (exito && n < N && !fin) {
					if (doku.linea[n] == doku.sudoku[i + g][j + h]) {
						doku.bolinea[n] = true;
						fin = true;
					}
					n++;
				}
				fin = false;
				j++;
			}
			i++;
		}
		for (int k = 0; k < N; k++) {
			if (!doku.bolinea[k]) {
				exito = false;
			}
		}
		iniciar(doku);		
		h = h + 3;
		if (h >= N) {
			h = 0;
			g = g + 3;
		}
		f++;
	}
	
	return exito;
}
bool filas(tSudoku& doku, bool exito) {
	int i = 0;
	while (exito && i < N) {
		int j = 0;
		int n = 0;
		while (exito && j < N && n != N) {
			if (doku.linea[n] == doku.sudoku[i][j]) {
				doku.bolinea[n] = true;
				n++;
				j = -1;
			}
			j++;
		}
		for (int k = 0; k < N; k++) {
			if (!doku.bolinea[k]) {
				exito = false;
			}
		}
		iniciar(doku);
		i++;
	}
	return exito;
}
bool columnas(tSudoku& doku, bool exito) {
	int j = 0;
	while (exito && j < N) {
		int i = 0;
		int n = 0;
		while (exito && i < N && n != N) {
			if (doku.linea[n] == doku.sudoku[i][j]) {
				doku.bolinea[n] = true;
				n++;
				i = -1;
			}
			i++;
		}
		for (int k = 0; k < N; k++) {
			if (!doku.bolinea[k]) {
				exito = false;
			}
		}
		iniciar(doku);
		j++;
	}
	return exito;
}
bool resolver(tSudoku& doku) {
	bool exito = true;
	if (exito) {
		exito = filas(doku, exito);
	}
	if (exito) {
		exito = columnas(doku, exito);
	}
	if (exito) {
		exito = cuadrantes(doku, exito);
	}
	
	return exito;
}


void resuelveCaso() {
	tSudoku doku;
	iniciar(doku);
	int num;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> num;
			doku.sudoku[i][j] = num;
			doku.cont++;
		}
	}

	if (resolver(doku)) {
		cout << "SI" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}