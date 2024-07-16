// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Puntos de silla
// Comentario general sobre la solución: Centinela

#include <iostream>
#include <fstream>
using namespace std;
typedef struct {
	int matriz[100][100];
	int filas = 0, columnas = 0;
	int cont = 0;
}tMatriz;
istream& operator>> (istream& in, tMatriz& m) {
	cin >> m.filas >> m.columnas;
	for (int i = 0; i < m.filas; i++) {
		for (int j = 0; j < m.columnas; j++) {
			cin >> m.matriz[i][j];
			m.cont++;
		}
	}
	return in;
}

bool menorfila(tMatriz& silla, int& i, int& j) {
	int n = 0;
	bool si = true;
	while (n < silla.columnas && si) {
		if (silla.matriz[i][j] > silla.matriz[i][n]) {
			si = false;
		}
		n++;
	}
	return si;
}
bool mayorfila(tMatriz& silla, int& i, int& j) {
	int n = 0;
	bool si = true;
	while (n < silla.columnas && si) {
		if (silla.matriz[i][j] < silla.matriz[i][n]) {
			si = false;
		}	
		n++;
	}
	return si;
}
bool menorcolumna(tMatriz& silla, int& i, int& j) {
	int n = 0;
	bool si = true;
	while (n < silla.filas && si) {
		if (silla.matriz[i][j] > silla.matriz[n][j]) {
			si = false;
		}
		n++;
	}
	return si;
}
bool mayorcolumna(tMatriz& silla, int& i, int& j) {
	int n = 0;
	bool si = true;
	while (n < silla.filas && si) {
		if (silla.matriz[i][j] < silla.matriz[n][j]) {
			si = false;
		}
		n++;
	}
	return si;
}
bool resolver(tMatriz& silla) {
	bool si = false;
	int i = 0;
	while (i < silla.filas) {
		int j = 0;
		while(j < silla.columnas) {
			if (menorfila(silla, i, j) && mayorcolumna(silla, i, j) || mayorfila(silla, i, j) && menorcolumna(silla, i, j)) {
				si = true;
			}
			j++;
		}
		i++;
	}
	return si;
}


bool resuelveCaso() {
	tMatriz M;
	bool fin = true;
	bool silla = false;
	cin >> M;
	if (M.filas == 0 && M.columnas == 0) {
		fin = false;
	}
	else {
		silla = resolver(M);
		if (silla) {
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	

	return fin;
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
