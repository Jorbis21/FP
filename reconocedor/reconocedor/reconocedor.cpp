// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Reconocedor de patron
// Comentario general sobre la solución: Datos de entrada ilimitados

#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	int matriz[40][40];
	int filas = 0, columnas = 0;
	int cont = 0;
	int x = 0, y = 0;
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

bool resolver(tMatriz& mat0, tMatriz& mat1) {
	bool encontrado = false;
	int g = 0, w = 0;
	int i = 0, j = 0, k = 0, h = 0;
	while (!encontrado && i < mat0.filas - (mat1.filas - 1)) {
		j = 0;
		while (!encontrado && j < mat0.columnas - (mat1.columnas - 1)) {
			g = 0;
			while (mat1.matriz[k + w][h + g] == mat0.matriz[i + w][j + g] && !encontrado) {				
				mat0.x = i;
				mat0.y = j;
				if (g == (mat1.columnas - 1) && w == (mat1.filas - 1)) {
					encontrado = true;
				}
				else if (g == (mat1.columnas - 1) && !encontrado) {	
					w++;
					g = -1;
				}
				
				g++;				
			}	
			w = 0;
			g = 0;
			j++;
		}
		i++;
	}
	return encontrado;
}
bool resuelveCaso() {
	tMatriz mat0, mat1;
	bool exito;
	cin >> mat0 >> mat1;
	if (!std::cin)  // fin de la entrada
		return false;
	exito = resolver(mat0, mat1);
	if (exito) {
		cout << mat0.x << " " << mat0.y << endl;
	}
	else {
		cout << "NO" << endl;
	}
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