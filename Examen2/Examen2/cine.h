// ****************************************************

// Prueba de evaluación del día 12 de junio de 2020
// Alumno/a: Javier Orbis Ramirez
// email:  jorbis@ucm.es
// Grupo: B

// ****************************************************

#ifndef cine_h
#define cine_h

#include <string>
using namespace std;

const int MAX_Pelis = 50;

typedef struct {
	string titulo;
	int precio;
	int annyo;
	int num_disponibles;
}tPeli;

// Lista de pelis disponibles en la cartelera
typedef struct {
	tPeli* arrayPelis[MAX_Pelis];
	int numPelis;
}tListaPelis;

typedef struct {
	string titulo;
	int num_solicitadas;
}tEntradas;

// Lista de entradas pendientes de confirmar 
typedef struct {
	tEntradas* arrayEntradas;
	int numEntradasPendientes, capacidad;
}tListaPeticiones;

// Prototipos
void inicializarListaEntradas(tListaPeticiones& listaEntradas);
void inicializarListaPelis(tListaPelis& listaPelis);
void ampliar(tListaPeticiones& lista);
bool cargar(tListaPelis& listaPelis, tListaPeticiones& listaEntradas);
void visualizarPelis(const tListaPelis& listaPelis);
void visualizarPeticiones(const tListaPeticiones& listaEntradas);
int procesarEntradas(tListaPelis& pelis, tListaPeticiones& peti);
void eliminar(tListaPelis& pelis, tListaPeticiones& peti);

#endif // !cine_h
