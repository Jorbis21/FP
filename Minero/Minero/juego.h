// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#ifndef juego_h
#define juego_h
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "mina.h"

typedef enum {
	IZDA, DCHA, ARRIBA, ABAJO, SALIR, TNT, NADA
}tTecla;

typedef enum {
	EXPLORANDO, EXITO, ABANDONO, FRACASO
}tEstado;

typedef struct{
	tMina mina;
	int ngemas = 0;
	int dinamitas = 0;
	int mov = 0;
	tEstado estado = EXPLORANDO;
	int tam = 0;
}tJuego;

tTecla cogerMov();//Lee el movimiento que se ha introducido por fichero.
istream& operator>>(istream& movimientos, tTecla& tecla);//Lee el movimiento que se ha introducido por teclado.
void lanzarTNT(tJuego& juego);//Lanza la dinamita hacia abajo.
void leerMovimiento(tJuego& juego, tTecla& tecla, std::istream& movimientos);//Decide en que estado esta el minero segunla tecla elegida o casilla en la que se encuentra.
void realizarMovimiento(tJuego& juego, tTecla mov);//Decide hacia donde ha de ir el minero.
void dibujar(tJuego const& juego);//Comprueba en que escala se dibuja y lo hace.
void jugar(tJuego& juego, std::istream& entrada, std::istream& movimientos);//jugar con movimientos por teclado.
void jugar2(tJuego& juego, std::istream& entrada, std::istream& movimientos);//Jugar con movimientos por fichero.
void caer(tJuego& juego);//Recorre la array de piedras y comprueba de abjao hasta arriba si se tienen que caer.
void moverPiedra(tJuego& juego, int i);//Permite al minero mover la piedra.
void mover(tJuego& juego, int i);//Permite mover al minero.
#endif