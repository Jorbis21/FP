// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez Grupo: 1º B
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Sopa de letras
// Comentario general sobre la solución: Numero de casos

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
const int incF[8] = { 1,1,0,-1,-1,-1,0,1 };
const int incC[8] = { 0,1,1,1,0,-1,-1,-1 };
typedef struct {
	string palabra[20];
	int cont = 0;
	int numPal = 0;
	bool Bpalabra[20] = { false };
	
}tPalabra;
typedef struct {
	char sopa[50][50];// matriz para la sopa
	char sopasol[50][50];
	int f = 0, c = 0; // filas y columnas
	int cont = 0;// posiblemente no sea util
	tPalabra palabra;
}tSopa;
istream& operator>> (istream& in, tSopa& sopa) {
	char c;
	cin >> sopa.f >> sopa.c;
	for (int i = 0; i < sopa.f; i++) {
		for (int j = 0; j < sopa.c; j++) {
			cin >> c;
			sopa.sopa[i][j] = c;
			sopa.cont++;
		}
	}
	string palabra;
	cin >> sopa.palabra.numPal;
	for (int i = 0; i < sopa.palabra.numPal; i++) {
		cin >> palabra;
		sopa.palabra.palabra[i] = palabra;
	}
	return in;
}
ostream& operator<< (ostream& out, tSopa& sopa) {
	for (int i = 0; i < sopa.c; i++) {
		if (i == (sopa.c - 1)) {
			cout << " -" << endl;
		}
		else {
			cout << " -";
		}
	}
	for (int i = 0; i < sopa.f; i++) {
		for (int j = 0; j < sopa.c; j++) {
			if (j == (sopa.c - 1)) {
				cout << " " << sopa.sopasol[i][j] << endl;
			}
			else {
				cout << " " << sopa.sopasol[i][j];
			}
		}
	}
	for (int i = 0; i < sopa.c; i++) {
		if (i == (sopa.c - 1)) {
			cout << " -" << endl;
		}
		else {
			cout << " -";
		}
	}
	cout << endl;
	return out;
}
void reinicio(tSopa& sopa, int x) {// hay que cambiarlo
	for (int i = 0; i < sopa.palabra.palabra[x].size(); i++) {
		sopa.palabra.Bpalabra[i] = false;
	}
}
void resolver(tSopa& sopa, int x) {
	bool encontrado = false;
	int i = 0;
	while (i < sopa.f && !encontrado) {
		int j = 0;
		while (j < sopa.c && !encontrado) {
			int y = 0;
			if (sopa.sopa[i][j] == sopa.palabra.palabra[x][y] && !encontrado) {
				sopa.palabra.Bpalabra[y] = true;
				int k = 0;
				y++;
				while (k < 8 && !encontrado) {
					if (sopa.sopa[i + incF[k]][j + incC[k]] == sopa.palabra.palabra[x][y] && !encontrado) {
						sopa.palabra.Bpalabra[y] = true;
						int ii = i + incF[k], jj = j + incC[k];
						while (y < sopa.palabra.palabra[x].size() && sopa.sopa[ii][jj] == sopa.palabra.palabra[x][y]) {
							sopa.palabra.Bpalabra[y] = true;
							ii += incF[k];
							jj += incC[k];
							y++;
						}
						for (int g = 0; g < sopa.palabra.palabra[x].size(); g++) {
							if (sopa.palabra.Bpalabra[g]) {
								encontrado = true;
							}
							else {
								encontrado = false;
							}
						}
						if (encontrado) {
							int z = i, q = j;
							for (int p = 0; p < sopa.palabra.palabra[x].size(); p++) {
								sopa.sopasol[z][q] = sopa.palabra.palabra[x][p];
								z += incF[k];
								q += incC[k];
							}
						}
						else {
							while(y > 1) {
								sopa.palabra.Bpalabra[y] = false;
								y--;
							}
						}
						
					}
					k++;
				}
				reinicio(sopa, x);
			}			
			j++;
		}
		i++;
	}
}


void resuelveCaso() {
	tSopa sopa;
	cin >> sopa;
	for (int i = 0; i < sopa.f; i++) {
		for (int j = 0; j < sopa.c; j++) {
			sopa.sopasol[i][j] = ' ';
		}
	}
	
	for (int x = 0; x < sopa.palabra.numPal; x++) {
		resolver(sopa, x);
	}
	
	cout << sopa;
	
	
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
