//Trabajo realizado por Javier Orbis Ramirez y Enrique Martin Rodriguez
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;
const int NumFichas = 28, maxValor = 7;
typedef short int tArray[NumFichas];


void generaPozo(tArray pozo1, tArray pozo2, int maxValor);//Genera las partes izquierda y derecha en pozo1 y pozo2 desde 0 hasta su valor maximo de todas las fichas.
void desordenaPozo(tArray pozo1, tArray pozo2);// Desordena el pozo.
void robaFicha(tArray pozo1, tArray pozo2, int& cont, short int& fichaN1, short int& fichaN2);//Toma la ultima ficha que halla en el pozo y la coloca en fichaN1 y fichaN2.
void mostrarTablero(tArray& fichas1, tArray& fichas2, string& tablero, int& numColocadas, int& numRobadas, short int& fichasCont);//Muestra las fichas que hay en el tablero, el numero de fichas colocadas y robadas y la ficha del jugador.
void eliminaFicha(tArray& fichas1, tArray& fichas2, short int& fichasCont, short int& fichaNum); //Elimina la ficha colocada del jugador y desplaza las demas a la izquierda para rellenar el vacio.

int mostrarMenu();//Muestra el menu y pide la opcion y la devuelve.
short int aleat();//Genera un numero aleatorio entre el 0 y el 6 inclusive.
short int sumaPuntos(tArray fichas1, tArray fichas2, short int fichasCont);//Se encarga de sumar los puntos de las fichas que tiene el jugador.

bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);//Se ve si el numero a la izquierda del tablero es igual a algun numero de la ficha del jugador.
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);//Se ve si el numero a la derecha del tablero es igual a algun numero de la ficha del jugador.
bool puedeColocarFicha(tArray fichas1, tArray fichas2, short int fichasCont, string tablero);//Se ve si el jugador puede colocar alguna de sus fichas en el tablero o no.

string toStr(int n);//Pasa las variables int y short int a string.
string fichaToStr(short int izquierda, short int derecha);//Coge dos numeros generados aleatoriamente y crea una ficha tipo string .
string PonerFichaIzq(string tablero, short int fichaN1, short int fichaN2);//Se pone la ficha del jugador a la izquierda del tablero.
string PonerFichaDer(string tablero, short int fichaN1, short int fichaN2);//Se pone la ficha del jugador a la derecha del tablero.

int main() {
	srand(time(NULL));
	int op = -1, numColocadas = 0, numRobadas = 0, cont = 0, n = 0, suma = 0;
	short int izquierda = 0, derecha = 0, fichaN1 = 0, fichaN2 = 0, fichasCont = 7, fichaNum = 0;
	tArray pozo1, pozo2, fichas1, fichas2;
	string tablero, save;
	ifstream cargar;
	ofstream guardar;
	bool robar, colocar = false;
	generaPozo(pozo1, pozo2, maxValor);
	desordenaPozo(pozo1, pozo2);
	tablero = fichaToStr(pozo1[0], pozo2[0]);
	cont++;
	for (int i = 1; i < 8; i++) {
		fichas1[n] = pozo1[i];
		fichas2[n] = pozo2[i];
		n++;
		cont++;
	}


	cout << "Desea cargar partida. (y/n)" << endl;
	cin >> save;
	if (save == "y") {
		cargar.open("partida.txt");
		if (cargar.is_open()) {
			//Lee el tablero y el numero de fichas colocadas y robadas de un archivo .txt
			cargar >> tablero >> numColocadas >> numRobadas >> fichasCont >> cont;
			for (int i = 0; i < fichasCont; i++) {
				cargar >> fichas1[i] >> fichas2[i];
			}
			for (int i = 0; i < 28; i++) {
				cargar >> pozo1[i] >> pozo2[i];
			}
		}
		else {
			cout << "Error" << endl;
		}
		cargar.close();
	}
	while (op != 0) {
		mostrarTablero(fichas1, fichas2, tablero, numColocadas, numRobadas, fichasCont);
		op = mostrarMenu();
		colocar = puedeColocarFicha(fichas1, fichas2, fichasCont, tablero);
		system("cls");//Limpia el texto anterior.
		if ((cont == 27 && !colocar) || (fichasCont == 0)) {
			suma = sumaPuntos(fichas1, fichas2, fichasCont);
			cout << "Tu puntuacion final es:" << suma << endl;
			op = 0;
		}
		switch (op) {

			if (colocar) {
		case 1: {


			cout << "Que ficha desea colocar:";
			cin >> fichaNum;
			fichaN1 = fichas1[fichaNum - 1];
			fichaN2 = fichas2[fichaNum - 1];
			robar = puedePonerIzq(tablero, fichaN1, fichaN2);
			if (robar) {
				tablero = PonerFichaIzq(tablero, fichaN1, fichaN2);
				numColocadas++;
				eliminaFicha(fichas1, fichas2, fichasCont, fichaNum);
			}
			else {
				cout << "No se puede." << endl;
			}

		}
			  break;
		case 2: {
			cout << "Que ficha desea colocar:";
			cin >> fichaNum;
			fichaN1 = fichas1[fichaNum - 1];
			fichaN2 = fichas2[fichaNum - 1];
			robar = puedePonerDer(tablero, fichaN1, fichaN2);
			if (robar) {
				tablero = PonerFichaDer(tablero, fichaN1, fichaN2);
				numColocadas++;
				eliminaFicha(fichas1, fichas2, fichasCont, fichaNum);
			}
			else {
				cout << "No se puede." << endl;
			}

		}
			  break;
			}

		case 3: {
			if (cont == 28) {
				cout << "No se puede robar mas." << endl;
			}
			else {
				if (fichasCont < 7) {
					robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
					fichas1[fichasCont] = fichaN1;
					fichas2[fichasCont] = fichaN2;
					numRobadas++;
					fichasCont++;

				}
				else {
					cout << "No se pueden robar mas de 7 fichas." << endl;
				}
			}

		}
			  break;
		}
	}


	cout << "Desea guardar partida. (y/n)" << endl;
	cin >> save;
	if (save == "y") {
		guardar.open("partida.txt");
		if (guardar.is_open()) {
			//Guarda el tablero y el numero de fichas colocadas y robadas en un archivo .txt
			guardar << tablero << " " << numColocadas << " " << numRobadas << " " << fichasCont << " " << cont << endl;
			for (int i = 0; i < fichasCont; i++) {
				guardar << fichas1[i] << " " << fichas2[i] << " ";
			}
			guardar << endl;
			for (int i = 0; i < 28; i++) {
				guardar << pozo1[i] << " " << pozo2[i] << " ";
			}
		}
		guardar.close();
	}
}


void mostrarTablero(tArray& fichas1, tArray& fichas2, string& tablero, int& numColocadas, int& numRobadas, short int& fichasCont) {


	cout << " -------------------------" << endl;
	cout << "|         TABLERO         |" << endl;
	cout << " -------------------------" << endl << endl;
	cout << tablero << endl;
	cout << "Fichas colocadas:" << numColocadas << "  " << "Fichas robadas:" << numRobadas << endl;
	cout << "Fichas del jugador:";
	for (int i = 0; i < fichasCont; i++) {
		cout << i + 1 << ":" << "|" << fichas1[i] << "-" << fichas2[i] << "| ";
	}
	cout << endl;
	cout << "Contador de fichas:" << fichasCont << endl;
}
void eliminaFicha(tArray& fichas1, tArray& fichas2, short int& fichasCont, short int& fichaNum) {

	if (fichaNum < 0 || fichaNum > fichasCont) {
		cout << "No se puede." << endl;
	}
	else {
		for (int i = fichaNum - 1; i < fichasCont - 1; i++) {

			fichas1[i] = fichas1[i + 1];
			fichas2[i] = fichas2[i + 1];

		}
		fichasCont--;
	}

}
void generaPozo(tArray pozo1, tArray pozo2, int maxValor) {
	int n = 0;
	for (int i = 0; i < maxValor; i++) {
		for (int j = i; j < maxValor; j++) {
			pozo1[n] = i;
			pozo2[n] = j;
			n++;
		}
	}
}
void desordenaPozo(tArray pozo1, tArray pozo2) {
	int idx, i;
	short int tmp1, tmp2;
	for (int i = NumFichas - 1; i >= 0; i--) {
		idx = rand() % (i + 1);
		if (i != idx) {
			tmp1 = pozo1[i];
			tmp2 = pozo2[i];
			pozo1[i] = pozo1[idx];
			pozo2[i] = pozo2[idx];
			pozo1[idx] = tmp1;
			pozo2[idx] = tmp2;

		}

	}
}
void robaFicha(tArray pozo1, tArray pozo2, int& cont, short int& fichaN1, short int& fichaN2) {
	fichaN1 = pozo1[cont];
	fichaN2 = pozo2[cont];
	cont++;
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
short int aleat() {
	int num, limi = 0, lims = 6;
	num = limi + rand() % (lims + 1 - limi);
	return num;
}
short int sumaPuntos(tArray fichas1, tArray fichas2, short int fichasCont) {
	int suma = 0, sumaf = 0;
	for (int i = 0; i < fichasCont; i++) {
		suma = fichas1[i] + fichas2[i];
		sumaf = suma + sumaf;
	}
	return sumaf;
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
bool puedeColocarFicha(tArray fichas1, tArray fichas2, short int fichasCont, string tablero) {// hay que cambiar esto
	bool col = false;
	int fichat1 = stoi(tablero.substr(1, 1));
	int fichat2 = stoi(tablero.substr(tablero.size() - 2, 1));
	for (int i = 0; i < fichasCont; i++) {
		if (fichat1 == fichas1[i] || fichat2 == fichas1[i] || fichat1 == fichas2[i] || fichat2 == fichas2[i]) {
			col = true;
		}
	}
	return col;
}

string toStr(int n) {
	string num;
	num = to_string(n);
	return num;
}
string fichaToStr(short int izquierda, short int derecha) {
	string ficha, nf1, nf2;
	nf1 = toStr(izquierda);
	nf2 = toStr(derecha);
	ficha = '|' + nf1 + '-' + nf2 + '|';
	return ficha;
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
