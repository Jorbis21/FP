//Trabajo realizado por Javier Orbis Ramirez y Enrique Martin Rodriguez
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;
const int NumFichas = 55, MinJugadores = 2, MaxJugadores = 4, MinDigito = 6, MaxDigito = 9;
const bool oculto = false;
typedef short int tArray[NumFichas];
typedef struct {
	short int izquierda;
	short int derecha;
}tFicha;
typedef tFicha tArray1[NumFichas];
typedef struct {
	tArray1 fichas;
}tArrayFichas;
typedef struct {
	tArrayFichas Arrayfichas;
	int Contador = 7;
	int NumRobadasM = 0;
}tListaFichas;
typedef tListaFichas tArray2[NumFichas];
typedef struct {
	tArray2 Jug;
}tJugadores;
typedef struct {
	tArray PuntosJug1;
	tArray PuntosJug2;
	tArray PuntosJug3;
	tArray PuntosJug4;
}tPuntosJugadores;
typedef struct {
	int numColocadas = 0;
	int numRobadas = 0;
	int cont = 0;
	int CantidadFichas = 0;
	int NumJugadores = 0;
	int MaxValorFichas = 0;
	int Jugador = -1;
	int Puntuacion = 0;
	int ini;
	int FichaEle;
	int suma = 0;
	int op = -1;
	short int fichasCont = 7;
	short int fichaN1 = 0;
	short int fichaN2 = 0;
	bool colocar = false;
	bool robar = false;
	bool mostrar = true;
	bool estra1 = false;
	string tablero;
	ifstream entrada;
	ofstream salida;
	tArray pozo1, pozo2;
	tFicha ficha;
	tArrayFichas Arrayfichas[NumFichas];
	tListaFichas listaFichas;
	tJugadores jugadores;
	tPuntosJugadores puntos;
}tJuego;
tJuego juego;

void generaPozo(tJuego& juego);//Genera las partes izquierda y derecha en pozo1 y pozo2 desde 0 hasta su valor maximo de todas las fichas.
void desordenaPozo(tJuego& juego);// Desordena el pozo.
void robaFicha(tJuego& juego);//Toma la ultima ficha que halla en el pozo y la coloca en fichaN1 y fichaN2.
void mostrarTablero(tJuego& juego);//Muestra las fichas que hay en el tablero, el numero de fichas colocadas y robadas y la ficha del jugador.
void eliminaFicha(tJuego& juego);//Elimina la ficha colocada y desplaza las demas a la izquierda para rellenar el vacio.
void guardarPartida(tJuego& juego);//Guarda la partida en un archivo.txt.
void estrategia2(tJuego& juego);//La maquina 1 coloca su ficha de mayor valor.
void estrategia1(tJuego& juego);//La maquina coloca la primera ficha que pueda.
void TurnoJugador(tJuego& juego);//Muestra las acciones que toma el jugador.

int mostrarMenu();//Muestra el menu y pide la opcion y la devuelve.
int quienEmpieza(tJuego& juego);//Indica que jugador empieza poniendo la ficha de mayor valor.
int fichaEmpieza(tJuego& juego);//Indica el numero de la ficha en el array.
short int aleat();//Genera un numero aleatorio entre el 0 y el 6 inclusive.
short int sumaPuntos(tJuego& juego);//Se encarga de sumar los puntos de las fichas que tiene el jugador.

bool puedePonerIzq(tJuego& juego);//Se ve si el numero a la izquierda del tablero es igual a algun numero de la ficha del jugador.
bool puedePonerDer(tJuego& juego);//Se ve si el numero a la derecha del tablero es igual a algun numero de la ficha del jugador.
bool puedeColocarFicha(tJuego& juego);//Se ve si el jugador puede colocar alguna de sus fichas en el tablero o no.
bool cargarPartida(tJuego& juego);//Carga la partida desde un fichero e indica si lo ha hecho o no.

string toStr(int n);//Pasa las variables int y short int a string.
string fichaToStr(short int izquierda, short int derecha);//Coge dos numeros generados aleatoriamente y crea una ficha tipo string .
string PonerFichaIzq(tJuego& juego);//Se pone la ficha del jugador a la izquierda del tablero.
string PonerFichaDer(tJuego& juego);//Se pone la ficha del jugador a la derecha del tablero.



int main() {
	srand(time(NULL));
	bool carga = false;
	carga = cargarPartida(juego);
	if (!carga) {
		while (juego.MaxValorFichas > 9 || juego.MaxValorFichas < 6) {
			cout << "Elija el numero maximo de las fichas (6-7-8-9):";
			cin >> juego.MaxValorFichas;
		}
		while (juego.NumJugadores < 2 || juego.NumJugadores > 4) {
			cout << "Contra cuantos jugadores quieres enfrentarte? (2-3-4): ";
			cin >> juego.NumJugadores;
		}
		system("cls");
		generaPozo(juego);
		if (juego.MaxValorFichas == 6) {
			juego.CantidadFichas = 28;
		}
		else if (juego.MaxValorFichas == 7) {
			juego.CantidadFichas = 36;
		}
		else if (juego.MaxValorFichas == 8) {
			juego.CantidadFichas = 45;
		}
		else if (juego.MaxValorFichas == 9) {
			juego.CantidadFichas = 55;
		}
		desordenaPozo(juego);

		int n = 0;
		int h = juego.cont;
		if (juego.NumJugadores == 2) {

			for (int i = juego.cont; i < juego.jugadores.Jug[0].Contador + 1; i++) {
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[1].Contador + h; i++) {
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
		}
		else if (juego.NumJugadores == 3) {
			for (int i = juego.cont; i < juego.jugadores.Jug[0].Contador + 1; i++) {
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[1].Contador + h; i++) {
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			h = juego.cont;
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[2].Contador + h; i++) {
				juego.jugadores.Jug[2].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[2].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
		}
		else if (juego.NumJugadores == 4) {
			for (int i = juego.cont; i < juego.jugadores.Jug[0].Contador + 1; i++) {
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[0].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			h = juego.cont;
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[1].Contador + h; i++) {
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[1].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			h = juego.cont;
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[2].Contador + h; i++) {
				juego.jugadores.Jug[2].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[2].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			h = juego.cont;
			n = 0;
			for (int i = juego.cont; i < juego.jugadores.Jug[3].Contador + h; i++) {
				juego.jugadores.Jug[3].Arrayfichas.fichas[n].izquierda = juego.pozo1[i];
				juego.jugadores.Jug[3].Arrayfichas.fichas[n].derecha = juego.pozo2[i];
				n++;
				juego.cont++;
			}
			juego.tablero = fichaToStr(juego.jugadores.Jug[quienEmpieza(juego)].Arrayfichas.fichas[fichaEmpieza(juego)].izquierda, juego.jugadores.Jug[quienEmpieza(juego)].Arrayfichas.fichas[fichaEmpieza(juego)].derecha);
			juego.fichaN1 = juego.jugadores.Jug[quienEmpieza(juego)].Arrayfichas.fichas[fichaEmpieza(juego)].izquierda;
			juego.fichaN2 = juego.jugadores.Jug[quienEmpieza(juego)].Arrayfichas.fichas[fichaEmpieza(juego)].derecha;
			juego.Jugador = quienEmpieza(juego);
			juego.FichaEle = fichaEmpieza(juego);
			eliminaFicha(juego);
		}
	}
	while (juego.op != 0) {
		if (juego.Jugador == 2) {
			if (quienEmpieza(juego) == 0) {
				estrategia2(juego);
				TurnoJugador(juego);
			}
			else {
				TurnoJugador(juego);
				estrategia2(juego);
			}
		}
		else {
			if (quienEmpieza(juego) == 0) {
				estrategia2(juego);
				estrategia1(juego);
				TurnoJugador(juego);
			}
			else if (quienEmpieza(juego) == 1) {
				estrategia1(juego);
				TurnoJugador(juego);
				estrategia2(juego);
			}
			else if (quienEmpieza(juego) == 2) {
				estrategia1(juego);
				TurnoJugador(juego);
				estrategia2(juego);
			}
			else {
				TurnoJugador(juego);
				estrategia2(juego);
				estrategia1(juego);
			}
		}
	}
	/*if (quienEmpieza(juego) == 0) {
		while (juego.op != 0) {
			mostrarTablero(juego);
			juego.op = mostrarMenu();
			system("cls");//Limpia el texto anterior.
			estrategia2(juego);
			estrategia1(juego);
			TurnoJugador(juego);
		}
	}
	else if(quienEmpieza(juego) == 1) {
		while (juego.op != 0) {
			mostrarTablero(juego);
			juego.op = mostrarMenu();
			system("cls");//Limpia el texto anterior.
			estrategia1(juego);
			TurnoJugador(juego);
			estrategia2(juego);
		}
	}
	else if (quienEmpieza(juego) == 2) {
		while (juego.op != 0) {
			mostrarTablero(juego);
			juego.op = mostrarMenu();
			system("cls");//Limpia el texto anterior.
			estrategia1(juego);
			TurnoJugador(juego);
			estrategia2(juego);
		}
	}
	else if (quienEmpieza(juego) == 3) {
		while (juego.op != 0) {
			mostrarTablero(juego);
			juego.op = mostrarMenu();
			system("cls");//Limpia el texto anterior.
			TurnoJugador(juego);
			estrategia2(juego);
			estrategia1(juego);
		}
	}*/
	guardarPartida(juego);
}



void generaPozo(tJuego& juego) {
	int n = 0;
	for (int i = 0; i < juego.MaxValorFichas + 1; i++) {
		for (int j = i; j < juego.MaxValorFichas + 1; j++) {
			juego.pozo1[n] = i;
			juego.pozo2[n] = j;
			n++;
		}
	}
}
void desordenaPozo(tJuego& juego) {
	int idx, i;
	short int tmp1, tmp2;
	for (int i = juego.CantidadFichas - 1; i >= 0; i--) {
		idx = rand() % (i + 1);
		if (i != idx) {
			tmp1 = juego.pozo1[i];
			tmp2 = juego.pozo2[i];
			juego.pozo1[i] = juego.pozo1[idx];
			juego.pozo2[i] = juego.pozo2[idx];
			juego.pozo1[idx] = tmp1;
			juego.pozo2[idx] = tmp2;

		}

	}
}
void robaFicha(tJuego& juego) {
	juego.fichaN1 = juego.pozo1[juego.cont];
	juego.fichaN2 = juego.pozo2[juego.cont];
	juego.cont++;
}
void mostrarTablero(tJuego& juego) {
	cout << " -------------------------" << endl;
	cout << "|        DOMINO V3        |" << endl;
	cout << " -------------------------" << endl << endl;
	cout << " -------------------------" << endl;
	cout << "|         TABLERO         |" << endl;
	cout << " -------------------------" << endl << endl;
	cout << juego.tablero << endl << endl;
	cout << "Maquina 1: ";
	for (int i = 0; i < juego.jugadores.Jug[1].Contador; i++) {
		cout << i + 1 << ":" << "|" << juego.jugadores.Jug[1].Arrayfichas.fichas[i].izquierda << "-" << juego.jugadores.Jug[1].Arrayfichas.fichas[i].derecha << "| ";
	}
	cout << endl << endl;
	if (juego.NumJugadores == 3) {
		cout << "Maquina 2: ";
		for (int i = 0; i < juego.jugadores.Jug[2].Contador; i++) {
			cout << i + 1 << ":" << "|" << juego.jugadores.Jug[2].Arrayfichas.fichas[i].izquierda << "-" << juego.jugadores.Jug[2].Arrayfichas.fichas[i].derecha << "| ";
		}
		cout << endl << endl;
	}
	if (juego.NumJugadores == 4) {
		cout << "Maquina 2: ";
		for (int i = 0; i < juego.jugadores.Jug[2].Contador; i++) {
			cout << i + 1 << ":" << "|" << juego.jugadores.Jug[2].Arrayfichas.fichas[i].izquierda << "-" << juego.jugadores.Jug[2].Arrayfichas.fichas[i].derecha << "| ";
		}
		cout << endl << endl;
		cout << "Maquina 3: ";
		for (int i = 0; i < juego.jugadores.Jug[3].Contador; i++) {
			cout << i + 1 << ":" << "|" << juego.jugadores.Jug[3].Arrayfichas.fichas[i].izquierda << "-" << juego.jugadores.Jug[3].Arrayfichas.fichas[i].derecha << "| ";
		}
		cout << endl << endl;
	}

	cout << "Jugador 1: ";
	for (int i = 0; i < juego.jugadores.Jug[0].Contador; i++) {// mira lo de fichasCont
		cout << i + 1 << ":" << "|" << juego.jugadores.Jug[0].Arrayfichas.fichas[i].izquierda << "-" << juego.jugadores.Jug[0].Arrayfichas.fichas[i].derecha << "| ";
	}
	cout << endl << endl;
	cout << "Fichas colocadas:" << juego.numColocadas << "  " << "Fichas robadas:" << juego.jugadores.Jug[0].NumRobadasM << endl;
	cout << "Contador de fichas:" << juego.fichasCont << endl;
}
void eliminaFicha(tJuego& juego) {

	if (juego.FichaEle < 0 || juego.FichaEle > juego.jugadores.Jug[juego.Jugador].Contador) {
		cout << "No se puede." << endl;
	}
	else {
		for (int i = juego.FichaEle; i < juego.jugadores.Jug[juego.Jugador].Contador - 1; i++) {

			juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].izquierda = juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i + 1].izquierda;
			juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].derecha = juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i + 1].derecha;

		}
		juego.jugadores.Jug[juego.Jugador].Contador--;
	}

}
void guardarPartida(tJuego& juego) {
	string save, nombre;
	cout << "Desea guardar partida. (y/n):";
	cin >> save;
	cout << "Inserte el nobmbre del fichero con la terminacion .txt:";
	cin >> nombre;
	if (save == "y") {
		juego.salida.open("partida.txt");
		if (juego.salida.is_open()) {
			juego.salida << juego.NumJugadores << " " << juego.MaxValorFichas << endl;
			juego.salida << juego.tablero << endl;
			juego.salida << juego.CantidadFichas << endl;
			for (int i = 0; i < juego.CantidadFichas; i++) {
				juego.salida << juego.pozo1[i] << " " << juego.pozo2[i] << " ";
			}
			juego.salida << endl;
			for (int i = 0; i < juego.NumJugadores + 2; i++) {
				juego.salida << juego.jugadores.Jug[i].Contador << endl;
				for (int j = 0; j < juego.jugadores.Jug[i].Contador; j++) {
					juego.salida << juego.jugadores.Jug[i].Arrayfichas.fichas[j].izquierda << " " << juego.jugadores.Jug[i].Arrayfichas.fichas[j].derecha << " ";
				}
				juego.salida << endl;
				juego.salida << juego.jugadores.Jug[i].NumRobadasM << endl;
			}
		}
		else {
			cout << "Error" << endl;
		}
		juego.salida.close();
	}
}
void estrategia1(tJuego& juego) {
	if (quienEmpieza(juego) == 2) {
		for (int i = 3; i < juego.NumJugadores; i++) {
			for (int j = 0; j < juego.jugadores.Jug[i].Contador; j++) {
				juego.Jugador = i;
				juego.FichaEle = j;
				if (puedeColocarFicha(juego) == true) {
					bool der = false, izq = false;
					juego.fichaN1 = juego.jugadores.Jug[i].Arrayfichas.fichas[j].izquierda;
					juego.fichaN2 = juego.jugadores.Jug[i].Arrayfichas.fichas[j].derecha;
					izq = puedePonerIzq(juego);
					der = puedePonerDer(juego);
					if (izq) {
						juego.tablero = PonerFichaIzq(juego);
						eliminaFicha(juego);
						j = juego.jugadores.Jug[i].Contador;
					}
					else if (der) {
						juego.tablero = PonerFichaDer(juego);
						eliminaFicha(juego);
						j = juego.jugadores.Jug[i].Contador;
					}
				}
				else {
					robaFicha(juego);
					juego.jugadores.Jug[i].Arrayfichas.fichas[juego.jugadores.Jug[i].Contador].izquierda = juego.fichaN1;
					juego.jugadores.Jug[i].Arrayfichas.fichas[juego.jugadores.Jug[i].Contador].derecha = juego.fichaN2;
					juego.jugadores.Jug[i].NumRobadasM++;
					juego.jugadores.Jug[i].Contador++;
				}
			}
		}
	}
	else {
		for (int i = 2; i < juego.NumJugadores; i++) {
			for (int j = 0; j < juego.jugadores.Jug[i].Contador; j++) {
				juego.Jugador = i;
				juego.FichaEle = j;
				if (puedeColocarFicha(juego) == true) {
					bool der = false, izq = false;
					juego.fichaN1 = juego.jugadores.Jug[i].Arrayfichas.fichas[j].izquierda;
					juego.fichaN2 = juego.jugadores.Jug[i].Arrayfichas.fichas[j].derecha;
					izq = puedePonerIzq(juego);
					der = puedePonerDer(juego);
					if (izq) {
						juego.tablero = PonerFichaIzq(juego);
						eliminaFicha(juego);
						j = juego.jugadores.Jug[i].Contador;
					}
					else if (der) {
						juego.tablero = PonerFichaDer(juego);
						eliminaFicha(juego);
						j = juego.jugadores.Jug[i].Contador;
					}
				}
				else {
					robaFicha(juego);
					juego.jugadores.Jug[i].Arrayfichas.fichas[juego.jugadores.Jug[i].Contador].izquierda = juego.fichaN1;
					juego.jugadores.Jug[i].Arrayfichas.fichas[juego.jugadores.Jug[i].Contador].derecha = juego.fichaN2;
					juego.jugadores.Jug[i].NumRobadasM++;
					juego.jugadores.Jug[i].Contador++;
				}
			}
		}
	}
}
void estrategia2(tJuego& juego) {
	int j = 0, k = 100, c = 1, jug = 1;
	while (c == 1) {
		for (int i = 0; i < juego.jugadores.Jug[1].Contador; i++) {
			if (puedePonerIzq(juego) || puedePonerDer(juego)) {
				if ((juego.jugadores.Jug[1].Arrayfichas.fichas[i].derecha + juego.jugadores.Jug[1].Arrayfichas.fichas[i].izquierda) > j) {
					k = i;
					j = juego.jugadores.Jug[1].Arrayfichas.fichas[i].izquierda + juego.jugadores.Jug[1].Arrayfichas.fichas[i].derecha;
				}
			}
		}
		juego.fichaN1 = juego.jugadores.Jug[1].Arrayfichas.fichas[k].izquierda;
		juego.fichaN2 = juego.jugadores.Jug[1].Arrayfichas.fichas[k].derecha;
		juego.FichaEle = k;
		if (puedePonerIzq(juego)) {
			juego.tablero = PonerFichaIzq(juego);
			juego.Jugador = 1;
			eliminaFicha(juego);
			c = 0;
			cout << "La maquina 1 ha puesto una ficha a la izquierda." << endl;
		}
		else if (puedePonerDer(juego)) {
			juego.tablero = PonerFichaDer(juego);
			juego.Jugador = 1;
			eliminaFicha(juego);
			c = 0;
			cout << "La maquina 1 ha puesto una ficha a la derecha." << endl;
		}
		else if (k == 100) {
			robaFicha(juego);
			juego.jugadores.Jug[1].Arrayfichas.fichas[juego.jugadores.Jug[1].Contador].izquierda = juego.fichaN1;
			juego.jugadores.Jug[1].Arrayfichas.fichas[juego.jugadores.Jug[1].Contador].derecha = juego.fichaN2;
			juego.jugadores.Jug[1].NumRobadasM++;
			juego.jugadores.Jug[1].Contador++;
		}

	}


}
void TurnoJugador(tJuego& juego) {
	mostrarTablero(juego);
	juego.op = mostrarMenu();
	juego.colocar = puedeColocarFicha(juego);

	system("cls");//Limpia el texto anterior.
	switch (juego.op) {

		if (juego.colocar) {
	case 1: {


		cout << "Que ficha desea colocar:";
		cin >> juego.FichaEle;
		juego.fichaN1 = juego.jugadores.Jug[0].Arrayfichas.fichas[juego.FichaEle - 1].izquierda;
		juego.fichaN2 = juego.jugadores.Jug[0].Arrayfichas.fichas[juego.FichaEle - 1].derecha;
		juego.robar = puedePonerIzq(juego);
		if (juego.robar) {
			juego.tablero = PonerFichaIzq(juego);
			juego.numColocadas++;
			juego.Jugador = 0;
			eliminaFicha(juego);
		}
		else {
			cout << "No se puede." << endl;
		}

	}
		  break;
	case 2: {
		cout << "Que ficha desea colocar:";
		cin >> juego.FichaEle;
		juego.fichaN1 = juego.jugadores.Jug[0].Arrayfichas.fichas[juego.FichaEle - 1].izquierda;
		juego.fichaN2 = juego.jugadores.Jug[0].Arrayfichas.fichas[juego.FichaEle - 1].derecha;

		juego.robar = puedePonerDer(juego);
		if (juego.robar) {
			juego.tablero = PonerFichaDer(juego);
			juego.numColocadas++;
			juego.Jugador = 0;
			eliminaFicha(juego);
		}
		else {
			cout << "No se puede." << endl;
		}

	}
		  break;
		}

	case 3: {
		if (juego.cont == juego.CantidadFichas) {
			cout << "No se puede robar mas." << endl;
		}
		else {
			if (puedeColocarFicha(juego)) {
				cout << "No puedes robar." << endl;
			}
			else {
				robaFicha(juego);
				juego.jugadores.Jug[0].Arrayfichas.fichas[juego.jugadores.Jug[0].Contador].izquierda = juego.fichaN1;
				juego.jugadores.Jug[0].Arrayfichas.fichas[juego.jugadores.Jug[0].Contador].derecha = juego.fichaN2;
				juego.jugadores.Jug[0].NumRobadasM++;
				juego.jugadores.Jug[0].Contador++;
			}
		}

	}
		  break;
	}
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
int quienEmpieza(tJuego& juego) {
	int A = 0, B = 0;
	for (int j = 0; j < juego.NumJugadores; j++) {
		for (int k = 0; k < juego.jugadores.Jug[j].Contador; k++) {
			if (juego.jugadores.Jug[j].Arrayfichas.fichas[k].izquierda == juego.jugadores.Jug[j].Arrayfichas.fichas[k].derecha) {
				if (juego.jugadores.Jug[j].Arrayfichas.fichas[k].izquierda > A) {
					A = juego.jugadores.Jug[j].Arrayfichas.fichas[k].izquierda;
					B = j;
				}
			}
		}
	}
	return B;
}
int fichaEmpieza(tJuego& juego) {
	int ficha = 0, n = quienEmpieza(juego);
	for (int i = 0; i < juego.jugadores.Jug[n].Contador; i++) {
		if (juego.jugadores.Jug[n].Arrayfichas.fichas[i].izquierda == juego.jugadores.Jug[n].Arrayfichas.fichas[i].derecha) {
			if (i > ficha) {
				ficha = i;
			}
		}
	}
	return ficha;
}
short int aleat() {
	int num, limi = 0, lims = juego.CantidadFichas;
	num = limi + rand() % (lims + 1 - limi);
	return num;
}
short int sumaPuntos(tJuego& juego) {
	int suma = 0, sumaf = 0;
	for (int i = 0; i < juego.jugadores.Jug[juego.Jugador].Contador; i++) {
		suma = juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].izquierda + juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].derecha;
		sumaf = suma + sumaf;
	}
	return sumaf;
}

bool puedePonerIzq(tJuego& juego) {
	bool izq;
	int fichat = stoi(juego.tablero.substr(1, 1));//Extrae el numero que esta a la izquierda del tablero.
	if ((fichat == juego.fichaN1) || (fichat == juego.fichaN2)) {
		izq = true;
	}
	else {
		izq = false;
	}
	return izq;
}
bool puedePonerDer(tJuego& juego) {
	bool der;
	int fichat = stoi(juego.tablero.substr(juego.tablero.size() - 2, 1));//Extrae el numero que esta a la derecha del tablero.
	if ((fichat == juego.fichaN1) || (fichat == juego.fichaN2)) {
		der = true;
	}
	else {
		der = false;
	}
	return der;
}
bool puedeColocarFicha(tJuego& juego) {
	bool col = false;
	int fichat1 = stoi(juego.tablero.substr(1, 1));
	int fichat2 = stoi(juego.tablero.substr(juego.tablero.size() - 2, 1));
	for (int i = 0; i < juego.jugadores.Jug[juego.Jugador].Contador; i++) {
		if (fichat1 == juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].izquierda || fichat2 == juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].izquierda || fichat1 == juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].derecha || fichat2 == juego.jugadores.Jug[juego.Jugador].Arrayfichas.fichas[i].derecha) {
			col = true;
			i = juego.jugadores.Jug[juego.Jugador].Contador;
		}
	}
	return col;
}
bool cargarPartida(tJuego& juego) {
	string save, nombre;
	bool carga;
	cout << "Desea cargar partida. (y/n):";
	cin >> save;
	if (save == "y") {
		cout << "Inserte el nombre del fichero:";
		cin >> nombre;
		carga = true;
		juego.entrada.open(nombre);
		if (juego.entrada.is_open()) {
			juego.entrada >> juego.NumJugadores >> juego.MaxValorFichas >> juego.tablero >> juego.CantidadFichas;
			for (int i = 0; i < juego.CantidadFichas; i++) {
				juego.entrada >> juego.pozo1[i] >> juego.pozo2[i];
			}
			for (int i = 0; i < juego.NumJugadores + 2; i++) {
				juego.entrada >> juego.jugadores.Jug[i].Contador;
				for (int j = 0; j < juego.jugadores.Jug[i].Contador; j++) {
					juego.entrada >> juego.jugadores.Jug[i].Arrayfichas.fichas[j].izquierda >> juego.jugadores.Jug[i].Arrayfichas.fichas[j].derecha;
				}
				juego.entrada >> juego.jugadores.Jug[i].NumRobadasM;
			}

		}
		else {
			cout << "Error" << endl;
		}
		juego.entrada.close();
	}
	else {
		carga = false;
	}
	return carga;
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
string PonerFichaIzq(tJuego& juego) {
	int fichat = stoi(juego.tablero.substr(1, 1));//Extrae el numero que esta a la izquierda del tablero.
	if (fichat == juego.fichaN2) {
		juego.tablero = fichaToStr(juego.fichaN1, juego.fichaN2) + juego.tablero;
	}
	else {
		juego.tablero = fichaToStr(juego.fichaN2, juego.fichaN1) + juego.tablero;
	}
	return juego.tablero;
}
string PonerFichaDer(tJuego& juego) {
	int fichat = stoi(juego.tablero.substr(juego.tablero.size() - 2, 1));//Extrae el numero que esta a la derecha del tablero.
	if (fichat == juego.fichaN1) {
		juego.tablero = juego.tablero + fichaToStr(juego.fichaN1, juego.fichaN2);
	}
	else {
		juego.tablero = juego.tablero + fichaToStr(juego.fichaN2, juego.fichaN1);
	}
	return juego.tablero;
}