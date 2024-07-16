//Trabajo realizado por Javier Orbis Ramirez y Enrique Martin Rodriguez
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;
int mostrarMenu();//Muestra el menu y pide la opcion y la devuelve.
short int aleat();//Genera un numero aleatorio entre el 0 y el 6 inclusive.
string toStr(int n);//Pasa las variables int y short int a string.
string fichaToStr(short int izquierda, short int derecha);//Coge dos numeros generados aleatoriamente y crea una ficha tipo string .
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas);/*Muestra las fichas que hay en el tablero,
el numero de fichas colocadas y robadas y la ficha del jugador.*/
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);//Se ve si el numero a la izquierda del tablero es igual a algun numero de la ficha del jugador.
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);//Se ve si el numero a la derecha del tablero es igual a algun numero de la ficha del jugador.
string PonerFichaIzq(string tablero, short int fichaN1, short int fichaN2);//Se pone la ficha del jugador a la izquierda del tablero.
string PonerFichaDer(string tablero, short int fichaN1, short int fichaN2);//Se pone la ficha del jugador a la derecha del tablero.

int main() {
	srand(time(NULL));
	int op = -1, numColocadas = 0, numRobadas = 0;
	short int izquierda = 0, derecha = 0, fichaN1 = 0, fichaN2 = 0;
	string tablero, save;
	ifstream cargar;
	ofstream guardar;
	bool robar;
	izquierda = aleat();
	derecha = aleat();
	tablero = fichaToStr(izquierda, derecha);
	fichaN1 = aleat();
	fichaN2 = aleat();
	cout << "Desea cargar partida. (SI/NO)" << endl;
	cin >> save;
	if (save == "SI") {
		cargar.open("partida.txt");
		if (cargar.is_open()) {
			//Lee el tablero y el numero de fichas colocadas y robadas de un archivo .txt
			cargar >> tablero >> numColocadas >> numRobadas;
		}
		else {
			cout << "Error" << endl;
		}
		cargar.close();
	}
	while (op != 0) {
		mostrarTablero(fichaN1, fichaN2, tablero, numColocadas, numRobadas);
		op = mostrarMenu();
		system("cls");//Limpia el texto anterior.
		switch (op) {
		case 1: {
			robar = puedePonerIzq(tablero, fichaN1, fichaN2);
			if (robar) {
				tablero = PonerFichaIzq(tablero, fichaN1, fichaN2);
				numColocadas++;
				fichaN1 = aleat();
				fichaN2 = aleat();
			}
			else {
				cout << "No se puede." << endl;
			}

		}
				break;
		case 2: {

			robar = puedePonerDer(tablero, fichaN1, fichaN2);
			if (robar) {
				tablero = PonerFichaDer(tablero, fichaN1, fichaN2);
				numColocadas++;
				fichaN1 = aleat();
				fichaN2 = aleat();
			}
			else {
				cout << "No se puede." << endl;
			}

			}
				 break;
		case 3: {
			fichaN1 = aleat();
			fichaN2 = aleat();
			numRobadas++;
		}
				break;
		}
	}
	

	cout << "Desea guardar partida. (SI/NO)" << endl;
	cin >> save;
	if (save == "SI") {
		guardar.open("partida.txt");
		if (guardar.is_open()) {
			//Guarda el tablero y el numero de fichas colocadas y robadas en un archivo .txt
			guardar << tablero << " " << numColocadas << " " << numRobadas;
		}
		guardar.close();
	}
}
string toStr(int n) {
	string num;
	num = to_string(n);
	return num;
}
short int aleat() {
	int num, limi = 0, lims = 6;
	num = limi + rand() % (lims + 1 - limi);
	return num;
}
string fichaToStr(short int izquierda, short int derecha) {
	string ficha, nf1, nf2;
	nf1 = toStr(izquierda);
	nf2 = toStr(derecha);
	ficha = '|' + nf1 + '-' + nf2 + '|';
	return ficha;
}
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas) {
	cout << " -------------------------" << endl;
	cout << "|         TABLERO         |" << endl;
	cout << " -------------------------" << endl << endl;
	cout << tablero << endl;
	cout << "Fichas colocadas:" << numColocadas << "  " << "Fichas robadas:" << numRobadas << endl;
	cout << "Ficha jugador:" << "|" << fichaN1 << "-" << fichaN2 << "|" << endl << endl;
}
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2) {
	bool izq;
	int fichat = stoi(tablero.substr(1, 1));//Extrae el numero que esta a la izquierda del tablero.
	if ((fichat == fichaN1) || (fichat == fichaN2)) {
		izq = true;
	}
	else {
		izq = false;
	}
	return izq;
}
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2) {
	bool der;
	int fichat = stoi(tablero.substr(tablero.size() - 2, 1));//Extrae el numero que esta a la derecha del tablero.
	if ((fichat == fichaN1) || (fichat == fichaN2)) {
		der = true;
	}
	else {
		der = false;
	}
	return der;
}
string PonerFichaIzq(string tablero, short int fichaN1, short int fichaN2) {
	int fichat = stoi(tablero.substr(1, 1));//Extrae el numero que esta a la izquierda del tablero.
	if (fichat == fichaN2) {
		tablero = fichaToStr(fichaN1, fichaN2) + tablero;
	}
	else {
		tablero = fichaToStr(fichaN2, fichaN1) + tablero;
	}
	return tablero;
}
string PonerFichaDer(string tablero, short int fichaN1, short int fichaN2) {
	int fichat = stoi(tablero.substr(tablero.size() - 2, 1));//Extrae el numero que esta a la derecha del tablero.
	if (fichat == fichaN1) {
		tablero = tablero + fichaToStr(fichaN1, fichaN2);
	}
	else {
		tablero = tablero + fichaToStr(fichaN2, fichaN1);
	}
	return tablero;
}
int mostrarMenu() {
	int op;
	cout << " -------------------------" << endl;
	cout << "|      MENU OPCIONES      |" << endl;
	cout << " -------------------------" << endl << endl;
	cout << "1. Poner ficha por la izquierda" << endl;
	cout << "2. Poner ficha por la derecha" << endl;
	cout << "3. Robar ficha nueva" << endl;
	cout << "0. Salir" << endl;
	cout << "Elija opcion:";
	cin >> op;
	while ((op < 0) || (op > 3)) {
		cout << "Error" << endl << "Elija opcion:";
		cin >> op;
	}
	return op;
}