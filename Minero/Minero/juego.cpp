// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "juego.h"
#include "mina.h"
using namespace std;

const std::pair <int, int> dirs4[4] = { {-1 , 0}, {1 , 0}, {0 , 1}, {0 , -1} };
const std::pair <int, int> dirs8[8] = { {-1 , -1}, {-1 , 0}, {-1 , 1}, {0 , -1}, {0 , 1} , {1, -1}, {1 , 0}, {1, 1} };

tTecla cogerMov() {
	char c;
	cin >> c;
	switch (c) {
	case 'S': {
		return SALIR;
	}
			break;
	case 'D': {
		return TNT;
	}
			break;
	case 'A': {
		return ARRIBA;
	}
			break;
	case 'Z': {
		return ABAJO;
	}
			break;
	case 'N': {
		return IZDA;
	}
			break;
	case 'M': {
		return DCHA;
	}
			break;
	}	
}
istream& operator>>(istream& movimientos, tTecla& tecla) {
	cin.sync();
	int dir = _getch(); // dir: tipo int
	if (dir == 0xe0) {
		dir = _getch();
		switch (dir) {
		
		case 72: {
			tecla = ARRIBA;
		}
			   break;
		case 80: {
			tecla = ABAJO;
   	    }
			   break;
		case 77: {
			tecla = DCHA;
		}
			break;
		case 75: {
			tecla = IZDA;
		}
			break;
		}
	}
	switch (dir) {
	case 27: case 83: case 115: {
		tecla = SALIR;
	}
		   break;
	case 100: case 68: {//Dinamita
		tecla = TNT;
	}
			break;
	case 65:  case 97: {
		tecla = ARRIBA;
	}
		   break;
	case 90: case 122:{
		tecla = ABAJO;
	}
		   break;
	case 78: case 110:{
		tecla = IZDA;
	}
		   break;
	case 77: case 109:{
		tecla = DCHA;
	}
		   break;
	}		
	return movimientos;	
}
void lanzarTNT(tJuego& juego) {
	int x = 0, y = 0;
	if (juego.mina.mina[juego.mina.x + dirs4[1].first][juego.mina.y] != LIBRE) {
		juego.mina.mina[juego.mina.x][juego.mina.y] = DINAMITA;
		juego.estado = FRACASO;
		x = juego.mina.x;
	}
	else {
		juego.mina.mina[juego.mina.x + dirs4[1].first][juego.mina.y] = DINAMITA;
		x = juego.mina.x + dirs4[1].first;
	}
	y = juego.mina.y;
	while (juego.mina.mina[x + dirs4[1].first][y] == LIBRE) {
		juego.mina.mina[x + dirs4[1].first][y] = DINAMITA;
		juego.mina.mina[x][y] = LIBRE;
		system("cls");
		dibujar(juego);		
		x++;
	}
	juego.mina.mina[x][y] = LIBRE;
	for (int i = 0; i < 8; i++) {
		if (juego.mina.mina[x + dirs8[i].first][y + dirs8[i].second] == MINERO) {
			juego.estado = FRACASO;
		}
		if (dentroPlano(juego.mina, x + dirs8[i].first, y + dirs8[i].second)) {
			juego.mina.mina[x + dirs8[i].first][y + dirs8[i].second] = LIBRE;			
		}
	}
	juego.dinamitas++;
	juego.mov++;
}
void caer(tJuego& juego) {
	for (int i = juego.mina.contp; i >= 0; i--) {
		while (juego.mina.mina[juego.mina.piedra[i].x + dirs4[1].first][juego.mina.piedra[i].y] == LIBRE && (juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] == GEMA || juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] == PIEDRA)) {
			if (juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] == GEMA){
				juego.mina.mina[juego.mina.piedra[i].x + dirs4[1].first][juego.mina.piedra[i].y] = GEMA;
				juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] = LIBRE;
				juego.mina.piedra[i].x += dirs4[1].first;				
			}
			if (juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] == PIEDRA) {
				juego.mina.mina[juego.mina.piedra[i].x + dirs4[1].first][juego.mina.piedra[i].y] = PIEDRA;
				juego.mina.mina[juego.mina.piedra[i].x][juego.mina.piedra[i].y] = LIBRE;
				juego.mina.piedra[i].x += dirs4[1].first;
			}
		}
	}
}
void moverPiedra(tJuego& juego, int i) {
	bool piedra = false;
	if (juego.mina.mina[juego.mina.x][juego.mina.y + dirs4[i].second] == PIEDRA && juego.mina.mina[juego.mina.x][juego.mina.y + 2 * dirs4[i].second] == LIBRE && dentroPlano(juego.mina,juego.mina.x + 2 * dirs4[i].first, juego.mina.y + 2 * dirs4[i].second)) {
		juego.mina.mina[juego.mina.x][juego.mina.y + 2 * dirs4[i].second] = PIEDRA;
		juego.mina.mina[juego.mina.x][juego.mina.y + dirs4[i].second] = MINERO;
		juego.mina.mina[juego.mina.x][juego.mina.y] = LIBRE;
		juego.mina.y += dirs4[i].second;
		int j = 0;
		while (j <= juego.mina.contp && !piedra) {
			if (juego.mina.mina[juego.mina.piedra[j].x][juego.mina.piedra[j].y] == MINERO) {
					juego.mina.piedra[j].y += dirs4[i].second;
					piedra = true;
			}
			j++;
		}		
	}
}
void mover(tJuego& juego, int i) {
	if (dentroPlano(juego.mina, juego.mina.x + dirs4[i].first, juego.mina.y + dirs4[i].second) && juego.mina.mina[juego.mina.x + dirs4[i].first][juego.mina.y + dirs4[i].second] != PIEDRA && juego.mina.mina[juego.mina.x + dirs4[i].first][juego.mina.y + dirs4[i].second] != MURO) {
		if (juego.mina.mina[juego.mina.x + dirs4[i].first][juego.mina.y + dirs4[i].second] == GEMA) {
			juego.ngemas++;
		}
		if (juego.mina.mina[juego.mina.x + dirs4[i].first][juego.mina.y + dirs4[i].second] == SALIDA) {
			juego.estado = EXITO;
		}
		juego.mina.mina[juego.mina.x + dirs4[i].first][juego.mina.y + dirs4[i].second] = MINERO;
		juego.mina.mina[juego.mina.x][juego.mina.y] = LIBRE;
		juego.mina.x += dirs4[i].first;
		juego.mina.y += dirs4[i].second;
	}
}
void leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimientos) {
	switch (tecla) {
	case ARRIBA: {
		juego.estado = EXPLORANDO;
	}
			   break;
	case ABAJO: {
		juego.estado = EXPLORANDO;
	}
			  break;
	case DCHA: {
		juego.estado = EXPLORANDO;
	}
			 break;
	case IZDA: {
		juego.estado = EXPLORANDO;
	}
			 break;
	case SALIR: {
		juego.estado = ABANDONO;
	}
			  break;
	case TNT: {
		juego.estado = EXPLORANDO;
	}
	}
}
void realizarMovimiento(tJuego& juego, tTecla mov) {
	int i = -1;
	switch (mov) {
		case ARRIBA: {
			i = 0;
			mover(juego, i);
			juego.mov++;
		}
		break;
		case ABAJO: {
			i = 1;
			mover(juego, i);
			juego.mov++;
		}
		break;
		case IZDA: {
			i = 3;			
			if (juego.mina.mina[juego.mina.x][juego.mina.y + dirs4[i].second] == PIEDRA) {
				moverPiedra(juego, i);
			}
			else {
				mover(juego, i);
			}
			juego.mov++;
		}
		break;
		case DCHA: {			
			i = 2;			
			if (juego.mina.mina[juego.mina.x][juego.mina.y + dirs4[i].second] == PIEDRA) {
				moverPiedra(juego, i);
			}
			else {
				mover(juego, i);
			}
			juego.mov++;
		}
		break;
		case TNT: {
			lanzarTNT(juego);
		}
		break;
		case SALIR: {
			juego.estado = ABANDONO;
		}
	}
}
void dibujar(tJuego const& juego) {	
	if (juego.mina.tam == 1) {
		dibujar1_1(juego.mina);
	}
	else if (juego.mina.tam == 2) {
		dibujar3_1(juego.mina);
	}
	colorFondo(0);
	cout << "Movimientos: " << juego.mov << endl;
	cout << "Gemas: " << juego.ngemas << endl;
	cout << "Dinamitas: " << juego.dinamitas << endl;
	if (juego.estado == ABANDONO) {
		cout << "Pide rescate" << endl;
	}
	else if (juego.estado == EXITO) {
		cout << "Mina recorrida" << endl;
	}
	else if (juego.estado == FRACASO) {
		cout << "Le alcanzo la dinamita" << endl;
	}
}
void jugar(tJuego& juego, istream& entrada, istream& movimientos) {
	tTecla tecla;
	bool fin = false;
	cargarNiveles(cin, juego.mina);
	while (!fin) {
		dibujar(juego);
		tecla = NADA;
		cin >> tecla;
		leerMovimiento(juego, tecla, cin);
		realizarMovimiento(juego, tecla);
		caer(juego);		
		system("cls");
		if (juego.estado == ABANDONO || juego.estado == EXITO || juego.estado == FRACASO) {
			fin = true;
			dibujar(juego);
			system("PAUSE");
		}
	}	
}
void jugar2(tJuego& juego, istream& entrada, istream& movimientos) {
	std::ifstream in(juego.mina.fichero);
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	tTecla tecla;
	bool fin = false;
	cargarNiveles(cin, juego.mina);
	while (!fin) {
		dibujar(juego);
		tecla = cogerMov();
		leerMovimiento(juego, tecla, cin);
		realizarMovimiento(juego, tecla);
		caer(juego);
		system("cls");
		if (juego.estado == ABANDONO || juego.estado == EXITO || juego.estado == FRACASO) {			
			fin = true;
			dibujar(juego);
			system("PAUSE");			
		}
	}
	std::cin.rdbuf(cinbuf);
}