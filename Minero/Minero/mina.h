// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#ifndef mina_h
#define mina_h
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

typedef enum {
	TIERRA, PIEDRA, MURO, GEMA, SALIDA, LIBRE, MINERO, DINAMITA
}tElemento;

typedef struct {
	int x = 0, y = 0;
}tPiedras;

typedef struct {
	tPiedras piedra[100];//Array donde se guardan las posicions de todas las piedras
	int n = 0, m = 0;
	int tam = 0;
	int entrada = 0;
	int salida = 1;
	tElemento mina[100][100] = {MURO};
	int contp = 0;
	string fichero;
	int x = 0, y = 0;
}tMina;

tElemento char2elem(char c);//Transforma los caracteres del fichero en elementos.
ostream& operator<<(ostream& out, tElemento& e);//Transforma los elementos en caracteres que se mostraran por pantalla.
void cargarNiveles(istream& fichero, tMina& mina);//Elige que nivel tiene que cargar.
void colorFondo(int color);//Permite cambiar el color del fondo del programa.
void cargar_mina(istream& fichero, tMina& mina);//Carga la mina desde el fichero elegido en cargarNiveles();.
void dibujar1_1(tMina const& mina);//Dibuja la matriz en escala 1:1.
void dibujar3_1(tMina const& mina);//Dubuja la matriz en escala 3:1.
bool dentroPlano(tMina const& mina, int x, int y);//Comprueba si los elementos estan dentro del plano.
#endif