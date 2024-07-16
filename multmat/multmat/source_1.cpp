// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Papá Noel
// Comentario general sobre la solución: Datos de entrada ilimitados
#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	int matriz[100][100];
	int filas, columnas;
}tMatriz;

istream& operator>> (istream& in, tMatriz& m) {
	cin >> m.filas >> m.columnas;
	for (int i = 0; i < m.filas; i++) {
		for (int j = 0; j < m.columnas; j++) {
			cin >> m.matriz[i][j];
		}
	}
	return in;
}

ostream& operator<< (ostream& out, tMatriz const& m) {

	for (int i = 0; i < m.filas; i++) {
		for (int j = 0; j < m.columnas; j++) {
			cout << m.matriz[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}
tMatriz operator* (tMatriz const& a, tMatriz const& b) {
	tMatriz c;
	c.filas = a.filas;
	c.columnas = b.columnas;                                         // Matriz A tiene k filas y m columnas, matriz b tiene m filas y n columnas y matriz c tiene k filas y n columnas 
	for (int i = 0; i < a.filas; i++) {   //filas
		for (int j = 0; j < b.columnas; j++) {//columnas
			c.matriz[i][j] = 0;
			for (int z = 0; z < a.columnas; z++) {//cuentas
				c.matriz[i][j] += a.matriz[i][z] * b.matriz[z][j]; // Generar matriz c


			}

		}
	}

	return c;
}




bool resuelveCaso(){
	tMatriz a,b,c;
    cin >> a >> b;

	if (cin.fail())
		return false;

	c = a * b;
	cout << c;

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