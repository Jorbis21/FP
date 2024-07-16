// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "mina.h"
#include <string>
using namespace std;

tElemento char2elem(char c) {
	tElemento p = LIBRE;
	switch(c) {
		case 'G':{
			p = GEMA;
		}
		break;
		case 'T': {
			p = TIERRA;
		}
		break;
		case 'P': {
			p = PIEDRA;	
		}
		break;
		case 'M': {
			p = MURO;
		}
		break;
		case 'S': {
			p = SALIDA;
		}
		break;
		case ' ': {
			p = LIBRE;
		}
		break;
		case 'J': {
			p = MINERO;
		}
		break;
		case 'D': {
			p = DINAMITA;
		}	
	}
	return p;
}
ostream& operator<<(ostream& out, tElemento const& e) {
	switch (e) {
		case GEMA: {
			out << 'G';
		}
		break;
		case TIERRA: {
			out << '.';
		}
		break;
		case PIEDRA: {
			out << '@';
		}
		break;
		case MURO: {
			out << 'X';
		}
		break;
		case SALIDA: {
			out << 'S';
		}
		break;
		case LIBRE: {
			out << '-';
		}
		break;
		case MINERO: {
			out << 'M';
		}
		break;
		case DINAMITA: {
			out << 'D';
		}
	}
	return out;
}
void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}
void cargarNiveles(istream& fichero, tMina& mina){
	string archivo;
	archivo = to_string(mina.salida) + ".txt";
	std::ifstream in(archivo);
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	cargar_mina(fichero, mina);
	std::cin.rdbuf(cinbuf);
}
void cargar_mina(istream& fichero, tMina& mina) {
	char c;
	int k = 0;
	cin >> mina.n >> mina.m;
	cin.ignore(1);
	for (int i = 0; i < mina.n; i++) {
		for (int j = 0; j < mina.m; j++) {
			fichero.get(c);
			if (c == 'J') {
				mina.x = i;
				mina.y = j;
			}
			if (c == 'P' || c == 'G') {
				mina.piedra[k].x = i;
				mina.piedra[k].y = j;
				mina.contp++;
				k++;
			}
			mina.mina[i][j] = char2elem(c);
		}
		cin.ignore(1);
	}	
}
void dibujar1_1(tMina const& mina) {
	for (int i = 0; i < mina.n; i++) {
		for (int j = 0; j < mina.m; j++) { 
			if (j == (mina.m - 1)){
				switch (mina.mina[i][j]) {
				case MINERO: {
					colorFondo(7);
				}
						   break;
				case SALIDA: {
					colorFondo(1);
				}
						   break;
				case GEMA: {
					colorFondo(2);
				}
						 break;
				case DINAMITA: {
					colorFondo(12);
				}
							 break;
				default: {
					colorFondo(4);
				}
					   break;
				
				}
				cout << mina.mina[i][j] << endl;
				colorFondo(0);
			}
			else {
				switch (mina.mina[i][j]) {
					case MINERO: {
						colorFondo(7);
					}
					break;
					case SALIDA: {
						colorFondo(1);
					}
					break;
					case GEMA: {
						colorFondo(2);
					}
					break;
					case DINAMITA: {
						colorFondo(12);
					}
								 break;
					default: {
						colorFondo(4);
					}
					break;
				}
				cout << mina.mina[i][j];
			}
		}
	}
}
void dibujar3_1(tMina const& mina) {
	for (int i = 0; i < mina.n; i++) {
		for (int k = 0; k < 3; k++) {
			for (int j = 0; j < mina.m; j++) {
				for (int h = 0; h < 3; h++) {
					if (j == (mina.m - 1) && h == 2) {
						switch (mina.mina[i][j]) {
						case MINERO: {
							colorFondo(7);
						}
								   break;
						case SALIDA: {
							colorFondo(1);
						}
								   break;
						case GEMA: {
							colorFondo(2);
						}
								 break;
						case DINAMITA: {
							colorFondo(12);
						}
									 break;
						default: {
							colorFondo(4);
						}
							   break;
						}
						cout << setw(1) << mina.mina[i][j] << endl;
						colorFondo(0);
					}
					else {
						switch (mina.mina[i][j]) {
						case MINERO: {
							colorFondo(7);
						}
								   break;
						case SALIDA: {
							colorFondo(1);
						}
								   break;
						case GEMA: {
							colorFondo(2);
						}
								 break;
						case DINAMITA: {
							colorFondo(12);
						}
									 break;
						default: {
							colorFondo(4);
						}
							   break;
						}
						cout << setw(1) << mina.mina[i][j];
					}
					
				}				
			}
		}
		
	}
}
bool dentroPlano(tMina const& mina, int x, int y){
	if (x < mina.n && y < mina.m && x >= 0 && y >= 0) {
		return true;
	}
	else {
		return false;
	}
}