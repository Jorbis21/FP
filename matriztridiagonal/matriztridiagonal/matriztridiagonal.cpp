// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Matriz Tridiagonal
// Comentario general sobre la solución: Datos de entrada ilimitados

#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	long int matriz[50][50];
	int filas = 0, columnas = 0;
	int cont = 0;
	long int max = 0;
	int x = 0;
}tMatriz;
const int NUM_DIRECCIONES = 4;
const std :: pair <int , int > dirs4 [ NUM_DIRECCIONES ] = {{ -1 ,0} ,{1 ,0} ,{0 ,1} ,{0 , -1}};
istream& operator>> (istream& in, tMatriz& m) {
	for (int i = 0; i < m.columnas; i++) {
		cin >> m.matriz[i][i];
	}
	for (int i = 0; i < m.columnas - 1; i++) {
		cin >> m.matriz[i][i + 1];
	}
	for (int i = 0; i < m.columnas - 1; i++) {
		cin >> m.matriz[i + 1][i];
	}
	return in;
}

void resolver(tMatriz& mat) {
	long int num = 0;
	if (mat.columnas == 1) {
		mat.max = mat.matriz[0][0];
		mat.x = 0;
	}
	else {
		for (int i = 0; i < mat.columnas; i++) {
			if (i == 0) {//primer caso
				mat.max = mat.matriz[i][i] + mat.matriz[i + dirs4[1].first][i + dirs4[1].second] + mat.matriz[i + dirs4[2].first][i + dirs4[2].second];
				mat.x = i;
			}
			else if (i == (mat.columnas - 1)) {// ultimo caso
				num = mat.matriz[i][i] + mat.matriz[i + dirs4[0].first][i + dirs4[0].second] + mat.matriz[i + dirs4[3].first][i + dirs4[3].second];
				if (num > mat.max) {
					mat.max = num;
					num = 0;
					mat.x = i;
				}
			}
			else {//para el resto de casos
				num = mat.matriz[i][i] + mat.matriz[i + dirs4[0].first][i + dirs4[0].second] + mat.matriz[i + dirs4[1].first][i + dirs4[1].second] + mat.matriz[i + dirs4[2].first][i + dirs4[2].second] + mat.matriz[i + dirs4[3].first][i + dirs4[3].second];
				if (num > mat.max) {
					mat.max = num;
					num = 0;
					mat.x = i;
				}
			}
			
		}
	}
	
}
bool resuelveCaso() {
	tMatriz mat;

	cin >> mat.columnas;
	if (!std::cin) { // fin de la entrada
		return false;
	}
	cin >> mat;
	resolver(mat);
	cout << mat.x << " " << mat.max << endl;
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