// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: 4 en raya
// Comentario general sobre la solución: Centinela

#include <iostream>
#include <fstream>

using namespace std;

typedef struct {
	int mat[6][7] = { 0 };
	int cont = 0;
	int numfichas = 0;
	int linea[4];
	bool lin[4];
	bool seg = false;
	int x = 0, y = 0;
}tRaya;

istream& operator>> (istream& in, tRaya& raya) {
	int num = 0, jug = 0, j = 5, h = 5, k = 5, l = 5, p = 5, m = 5, n = 5;
	for (int i = 0; i < raya.numfichas; i++) {
		cin >> num;
		int par = i % 2;
		if (par == 0) {
			jug = 1;
		}
		else {
			jug = 2;
		}
		switch (num) {
			case 0: {
				if (j >= 0) {
					raya.mat[j][0] = jug;// muy posiblemente habar que cambiarlo
					j--;
				}
			}
			break;
			case 1: {
				if (h >= 0) {
					raya.mat[h][1] = jug;// muy posiblemente habar que cambiarlo
					h--;
				}
			}
			break;
			case 2: {
				if (k >= 0) {
					raya.mat[k][2] = jug;// muy posiblemente habar que cambiarlo
					k--;
				}
			}
			break;
			case 3: {
				if (l >= 0) {
					raya.mat[l][3] = jug;// muy posiblemente habar que cambiarlo
					l--;
				}
			}
			break;
			case 4: {
				if (p >= 0) {
					raya.mat[p][4] = jug;// muy posiblemente habar que cambiarlo
					p--;
				}
			}
			break;
			case 5: {
				if (m >= 0) {
					raya.mat[m][5] = jug;// muy posiblemente habar que cambiarlo
					m--;
				}
			}
			break;
			case 6: {
				if (n >= 0) {
					raya.mat[n][6] = jug;// muy posiblemente habar que cambiarlo
					n--;
				}
			}
			break;
		}
	}
	return in;
}

void reinicio(tRaya& raya) {
	for (int i = 0; i < 4; i++) {
		if (raya.seg) {
			raya.linea[i] = 1;
		}
		else {
			raya.linea[i] = 2;
		}
		raya.lin[i] = false;
	}
}
bool filas(tRaya& raya, bool exito) {
	int i = 0;
	while (i < 6 && !exito) {
		int j = 0;
		while (j < 4 && !exito) { // 4 porque 7 - 3 = 4 you now
			int p = 0;
			while (raya.linea[p] == raya.mat[i][j + p] && p < 4) {
				raya.lin[p] = true;
				p++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			j++;
		}
		i++;
	}
	return exito;
}
bool columnas(tRaya& raya, bool exito) {
	int i = 0;
	while (i < 7 && !exito) {
		int j = 0;
		while (j < 3 && !exito) { 
			int p = 0;
			while (raya.linea[p] == raya.mat[j + p][i] && p < 4) {
				raya.lin[p] = true;
				p++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			j++;
		}
		i++;
	}
	return exito;
}
bool diagonales1(tRaya& raya, bool exito) {
	int i = 2, x = 4;
	while (i >= 0 && !exito){
		int j = 0;
		int k = i;
		while (j < x - 3 && !exito) {
			int n = 0;
			while (raya.linea[n] == raya.mat[k + n][j + n] && n < 4) {
				raya.lin[n] = true;
				n++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			j++;
			k++;
		}
		x++;
		i--;
	}
	x = x - 1;
	int j = 1;
	while (j < 4 && !exito) {
		int i = 0;
		int k = j;
		while (i < x - 3 && !exito) {
			int n = 0;
			while (raya.linea[n] == raya.mat[i + n][k + n] && n < 4) {
				raya.lin[n] = true;
				n++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			i++;
			k++;
		}
		x--;
		j++;
	}
	return exito;
}
bool diagonales2(tRaya& raya, bool& exito) {
	int j = 3,x = 4;
	while (j < 6 && !exito) {
		int i = 0;
		int k = j;
		while (i < x - 3 && !exito) {
			int n = 0;
			while (raya.linea[n] == raya.mat[i + n][k - n] && n < 4) {
				raya.lin[n] = true;
				n++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			i++;
		}
		x++;
		j++;
	}
	x = x - 1;
	int i = 0;
	while (i < 3 && !exito) {
		int j = 6;
		int k = i;
		while (j > x - 3 && !exito) {// revisar
			int n = 0;
			while (raya.linea[n] == raya.mat[k + n][j - n] && n < 4) {
				raya.lin[n] = true;
				n++;
			}
			for (int k = 0; k < 4; k++) {
				if (raya.lin[k]) {
					exito = true;
				}
				else {
					exito = false;
				}
			}
			reinicio(raya);
			j--;
		}
		i++;
		x--;
	}
	return exito;
}
bool resolver(tRaya& raya) {
	bool exito = false;
	if (!exito) {
		exito = filas(raya, exito);
	}
	if (!exito) {
		exito = columnas(raya, exito);
	}
	if (!exito) {
		exito = diagonales1(raya, exito);
	}
	if (!exito) {
		exito = diagonales2(raya, exito);
	}

	return exito;
}


bool resuelveCaso() {
	tRaya raya;
	bool sol = false;
	cin >> raya.numfichas;
	
	if (raya.numfichas == 0) {
		return false;
	}
		
	cin >> raya;
	int i = 0;
	while (!sol && i < 2) {
		if (i == 1) {
			raya.seg = true;
		}
		reinicio(raya);
		sol = resolver(raya);
		i++;
	}
	
	
	if (sol && i == 2) {
		cout << "Gana A" << endl;
	}
	else if (sol && i == 1) {
		cout << "Gana B" << endl;
	}
	else if (!sol) {
		cout << "Empate" << endl;
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
