// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#include <iostream>
#include <fstream>
#include <string>
#include "puntuaciones.h"
using namespace std;

bool cargar_Marcador(tPuntuaciones& marcador) {
	std::ifstream in("Puntuaciones.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	marcador.capacidad = 2;
	inicializar_Marcador(marcador);
	bool leer = true; int IdMina = 0;
	string nombre;
	cin >> nombre;
	if (nombre == "") {
		leer = false;
		destruir(marcador);
	}
	while (nombre != "000" && leer) {
		marcador.array_clasificacion[marcador.num_jugadores].nombre = nombre;
		cin >> marcador.array_clasificacion[marcador.num_jugadores].punt_total >> marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas;
		for (int i = 0; i < marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas; i++) {
			cin >> IdMina;
			marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[IdMina - 1].IdMina = IdMina;
			cin >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[IdMina - 1].numMovimientos;
			cin >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[IdMina - 1].numGemas;
			cin >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[IdMina - 1].numDinamitas;
			cin >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[IdMina - 1].puntosMina;
		}
		marcador.num_jugadores++;
		cin >> nombre;
		if (marcador.num_jugadores == marcador.capacidad && nombre != "000")
			aumentar_Capacidad(marcador);	
		
	}
	std::cin.rdbuf(cinbuf);
	return leer;
}
bool guardar_Marcador(tPuntuaciones& marcador) {
	std::ofstream out("Puntuaciones.txt");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
	bool leer = true;
	int x = 0;
	if (marcador.array_clasificacion[x].nombre == "")
		leer = false;
	while (x < marcador.num_jugadores && leer) {
		cout << marcador.array_clasificacion[x].nombre << endl;
		cout << marcador.array_clasificacion[x].punt_total << endl;
		cout << marcador.array_clasificacion[x].minasRecorridas << endl;
		for (int i = 0; i < 5; i++) {
			if (marcador.array_clasificacion[x].vMinasRecorridas[i].IdMina != 0) {
				cout << marcador.array_clasificacion[x].vMinasRecorridas[i].IdMina << " ";
				cout << marcador.array_clasificacion[x].vMinasRecorridas[i].numMovimientos << " ";
				cout << marcador.array_clasificacion[x].vMinasRecorridas[i].numGemas << " ";
				cout << marcador.array_clasificacion[x].vMinasRecorridas[i].numDinamitas << " ";
				cout << marcador.array_clasificacion[x].vMinasRecorridas[i].puntosMina << endl;
			}
		}		
		x++;	
	}
	destruir(marcador);
	cout << "000" << endl;
	std::cout.rdbuf(coutbuf);
	return leer;
}
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont) {
	bool total = true;
	cout << marcador.array_clasificacion[cont].nombre << endl;
	if (marcador.array_clasificacion[cont].minasRecorridas == 0) {
		cout << "No se ha recorrido ninguna mina." << endl;
	}
	for (int i = 0; i < 5; i++) {
		if (marcador.array_clasificacion[cont].vMinasRecorridas[i].IdMina != 0) {
			cout << "Mina " << marcador.array_clasificacion[cont].vMinasRecorridas[i].IdMina << "  ";
			cout << "Movimientos:"<< marcador.array_clasificacion[cont].vMinasRecorridas[i].numMovimientos << "  ";
			cout << "Gemas:" << marcador.array_clasificacion[cont].vMinasRecorridas[i].numGemas << "  ";
			cout << "Dinamitas:"<< marcador.array_clasificacion[cont].vMinasRecorridas[i].numDinamitas << "  ";
			cout << "Puntos:" << marcador.array_clasificacion[cont].vMinasRecorridas[i].puntosMina << "  ";
			if (total) {
				cout << "Puntos en total:" << marcador.array_clasificacion[cont].punt_total << endl;
				total = false;
			}
			else {
				cout << endl;
			}
		}
		if (i == 4) {
			cout << endl;
		}
	}
}
void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	cout << "\t\t\t Mira las puntuaciones de los otros jugadores." << endl << endl;
	cout << "\t\t\t------------  LISTA DE JUGADORES  ------------" << endl << endl;
	for (int i = 0; i < marcador.num_jugadores; i++) 
		cout << "\t\t\t\t\t" << marcador.array_clasificacion[i].nombre << " " << marcador.array_clasificacion[i].punt_total << endl;	
}
void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	cout << "\t\t\t-----  JUGADORES ORDENADOS POR NOMBRE  -----" << endl;
	cout << "\t\t    Mira las minas que has recorrido ordenadas por nivel" << endl << endl;
	for (int i = 0; i < marcador.num_jugadores; i++)
		mostrar_Minas_Usuario(marcador, i);
}
void inicializar_Marcador(tPuntuaciones& marcador) {
	marcador.array_clasificacion = new tPuntuacionJugador[marcador.capacidad];
}
void aumentar_Capacidad(tPuntuaciones& marcador) {
	tPuntuacionJugador* auxilius = nullptr;
	auxilius = new tPuntuacionJugador[2 * marcador.capacidad];
	for (int i = 0; i < marcador.capacidad; i++)
		auxilius[i] = marcador.array_clasificacion[i];
	delete[] marcador.array_clasificacion;
	marcador.array_clasificacion = auxilius;
	marcador.capacidad *= 2;
	auxilius = nullptr;
}
void destruir(tPuntuaciones& marcador) {
	delete[]marcador.array_clasificacion;
}
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	int  ini = 0, fin = marcador.num_jugadores - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (nombre == marcador.array_clasificacion[mitad].nombre) 
			encontrado = true;
		else if (nombre < marcador.array_clasificacion[mitad].nombre) {
			fin = mitad - 1;
			pos = mitad;
		}	
		else {
			ini = mitad + 1;
			pos = ini;
		}		
	}
	if (encontrado) {
		pos = mitad;
	}
	return encontrado;
}
void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	tPuntuacionJugador medesmayus;
	marcador.num_jugadores++;
	if (marcador.num_jugadores > marcador.capacidad) 
		aumentar_Capacidad(marcador);	
	for (int i = marcador.num_jugadores - 1; i > pos; i--) 
		marcador.array_clasificacion[i] = marcador.array_clasificacion[i - 1];
	marcador.array_clasificacion[pos] = medesmayus;
	marcador.array_clasificacion[pos].nombre = nombre;
}