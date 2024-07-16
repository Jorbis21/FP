// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

/*A lo largo del codigo hago uso del los codigos:

	std::ifstream in("archivo");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
		
	std::cin.rdbuf(cinbuf);
y
	std::ofstream out("archivo");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
	
	std::cout.rdbuf(coutbuf);

en vez de declarar en cada caso una variable tipo istream/ostream y abrir cada archivo.*/

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "juego.h"
#include "mina.h"
#include "puntuaciones.h"
using namespace std;

const int A = 10, B = 2;

int menu(tJuego& juego, int& op);//Muestra el menú que permite elegir escala.
int menu2(tJuego& juego, int& op, string nombre);//Muestra el menú que permite elegir que mina explorar.
int menu1(tJuego& juego, int& op);//Muestra el menú que permite elegir la forma de introducir movimientos.
void almacenar(tJuego& juego, tPuntuaciones& marcador, int& pos, int& puntuacion, bool& a, bool& b, bool& c, bool& d, bool& e);//Guarda los datos del jugador que estaban en juego a marcador.
void recorrerminas(tPuntuaciones& marcador, int& pos, bool& a, bool& b, bool& c, bool& d, bool& e);//Comprueba si el jugador ya ha recorrido una mina.

int main() {
	setlocale(LC_ALL, "spanish");
	tJuego *juego = new tJuego;
	tPuntuaciones *marcador = new tPuntuaciones;
	string nombre;
	int op = -1; int pos = -1;
	bool a = false, b = false, c = false, d = false, e = false;
	if (!cargar_Marcador(*marcador)) {
		cout << "No se ha podido acceder al archivo Puntuaciones.txt compruebe la carpeta del programa." << endl;
		inicializar_Marcador(*marcador);
		pos = 0;
		system("PAUSE");
		system("cls");
	}
	cout << "Introduce tu nombre de jugador/a:";
	cin >> nombre;
	cout << endl;
	if (buscar(nombre, *marcador, pos)) {
		cout << "Ya estas registrado/a." << endl << endl;
		cout << "\t\tMira las minas que has recorrido ordenadas por nivel" << endl << endl;
		mostrar_Minas_Usuario(*marcador, pos);
	}
	else {
		cout << "Eres nuevo/a:" << nombre << endl << endl;
		insertar(*marcador, nombre, pos);
		mostrar_Alfabetico(*marcador);
	}
	recorrerminas(*marcador, pos, a, b, c, d, e);
	system("PAUSE");
	op = menu2(*juego, op, nombre);
	while (op != 0 && juego->mina.salida <= 5) {
		int puntuacion = 0;
		op = menu(*juego, op);
		if (op == 1 || op == 2) {
			op = menu1(*juego, op);
		}
		if (juego->mina.entrada == 1) {
			jugar(*juego, cin, cin);		
		}
		else if (juego->mina.entrada == 2) {
			jugar2(*juego, cin, cin);
		}
		if (op == 1 || op == 2) {
			system("cls");
			almacenar(*juego, *marcador, pos, puntuacion, a, b, c, d, e);
			mostrar_Datos_Usuario(*marcador);
			op = menu2(*juego, op, nombre);	
		}
	}
	mostrar_Datos_Usuario(*marcador);
	if (!guardar_Marcador(*marcador)) {
		cout << "No se ha podido acceder al archivo Puntuaciones.txt compruebe la carpeta del programa." << endl;
	}
	delete juego;
	delete marcador;
	return 0;
}

int menu(tJuego& juego, int& op) {
	op = -1;
	while (op != 0 && op != 1 && op != 2) {		
		system("cls");
		cout << "1. Jugar partida a escala 1:1." << endl;
		cout << "2. Jugar partida a escala 3:1." << endl;
		cout << "0. Salir." << endl;
		cout << "Introduzca una opción: ";
		cin >> op;
		if (op == 1) {
			juego.mina.tam = 1;
		}
		else if (op == 2) {
			juego.mina.tam = 2;
		}
	}
	return op;
}
int menu2(tJuego& juego, int& op, string nombre) {
	op = -1;
	while (op != 0 && op != 1) {
		cout << nombre << ", ¿Qué mina quieres explorar?" << endl;
		cout << "Introduce un número entre 1 y 5 para explorar una mina o 0 para salir:";
		cin >> juego.mina.salida;
		if (juego.mina.salida == 0)
			op = 0;
		else if (juego.mina.salida <= 5 || juego.mina.salida >= 1)
			op = 1;
		system("cls");
	}
	return op;
}
int menu1(tJuego& juego, int& op) {
	op = -1;
	while (op != 0 && op != 1 && op != 2) {		
		system("cls");
		cout << "1. Introducir movimientos por teclado." << endl;
		cout << "2. Introducir movimientos por fichero." << endl;
		cout << "0. Salir." << endl;
		cout << "Introduzca una opción: ";
		cin >> op;
		if (op == 1) {
			juego.mina.entrada = 1;
		}
		else if (op == 2) {
			juego.mina.entrada = 2;
			cout << "¿En que fichero tiene los movimientos?" << endl << "(Ponga la extensión del archivo porfavor)" << endl;
			cout << "Nombre del archivo:";
			cin >> juego.mina.fichero;
		}
		system("cls");
	}
	return op;
}
void almacenar(tJuego& juego, tPuntuaciones& marcador, int& pos, int& puntuacion, bool& a, bool& b, bool& c, bool& d, bool& e) {
	puntuacion = (juego.mina.m * juego.mina.n) + (A * juego.ngemas) - juego.mov - (B * juego.dinamitas);
	if (juego.estado == EXITO && puntuacion > marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].puntosMina) {
		marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].puntosMina = puntuacion;
		marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].numDinamitas = juego.dinamitas;
		marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].numGemas = juego.ngemas;
		marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].numMovimientos = juego.mov;
		marcador.array_clasificacion[pos].vMinasRecorridas[juego.mina.salida - 1].IdMina = juego.mina.salida;
		juego.dinamitas = 0;
		juego.ngemas = 0;
		juego.mov = 0;
		for (int i = 0; i < 5; i++) {
			switch (marcador.array_clasificacion[pos].vMinasRecorridas[i].IdMina) {
			case 1: {
				if (!a) {
					marcador.array_clasificacion[pos].minasRecorridas++;
					a = true;
				}
			}
				  break;
			case 2: {
				if (!b) {
					marcador.array_clasificacion[pos].minasRecorridas++;
					b = true;
				}
			}
				  break;
			case 3: {
				if (!c) {
					marcador.array_clasificacion[pos].minasRecorridas++;
					c = true;
				}
			}
				  break;
			case 4: {
				if (!d) {
					marcador.array_clasificacion[pos].minasRecorridas++;
					d = true;
				}
			}
				  break;
			case 5: {
				if (!e) {
					marcador.array_clasificacion[pos].minasRecorridas++;
					e = true;
				}
			}
				  break;
			}
		}
		marcador.array_clasificacion[pos].punt_total = 0;
		for (int i = 0; i < 5; i++)
			marcador.array_clasificacion[pos].punt_total = marcador.array_clasificacion[pos].punt_total + marcador.array_clasificacion[pos].vMinasRecorridas[i].puntosMina;
	}
}
void recorrerminas(tPuntuaciones& marcador, int& pos, bool& a, bool& b, bool& c, bool& d, bool& e) {
	for (int i = 0; i < 5; i++) {
		switch (marcador.array_clasificacion[pos].vMinasRecorridas[i].IdMina) {
		case 1: {
			if (!a) {
				a = true;
			}
		}
			  break;
		case 2: {
			if (!b) {
				b = true;
			}
		}
			  break;
		case 3: {
			if (!c) {
				c = true;
			}
		}
			  break;
		case 4: {
			if (!d) {
				d = true;
			}
		}
			  break;
		case 5: {
			if (!e) {
				e = true;
			}
		}
			  break;
		}
	}
}