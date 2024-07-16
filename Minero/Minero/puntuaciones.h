// Autor/a: Javier Orbis Ramirez, Enrique Martin Rodriguez
// email: jorbis@ucm.es enrima08@ucm.es
// Compilador y S.O. utilizado: VS profesional 2019 windows 10
// Nombre del problema: Minero v2

#ifndef puntuaciones_h
#define puntuaciones_h
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct {
	int IdMina = 0;
	int numMovimientos = 0;
	int numGemas = 0;
	int numDinamitas = 0;
	int puntosMina = 0;
} tDatosMina;

typedef struct {
	string nombre;
	int punt_total = 0;
	int minasRecorridas = 0;
	tDatosMina vMinasRecorridas[5];
} tPuntuacionJugador;

typedef struct {
	int capacidad = 2;
	int num_jugadores = 0;
	tPuntuacionJugador *array_clasificacion;
} tPuntuaciones;

bool cargar_Marcador(tPuntuaciones& marcador);//Carga el marcador desde el fichero.
bool guardar_Marcador(tPuntuaciones& marcador);//Guarda el marcador en el fichero.
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);//Muestra las minas que ha recorrido el usuario.
void mostrar_Alfabetico(const tPuntuaciones& marcador);//Muestra en orden los jugadores y sus puntaciones totales.
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);//Muestra todos los usuarios y sus minas.
void inicializar_Marcador(tPuntuaciones& marcador);//Inicia el puntero marcador.
void aumentar_Capacidad(tPuntuaciones& marcador);//Aumenta la capacidad de la arrray de los jugadores.
void destruir(tPuntuaciones& marcador);//Destruye el puntero marcador.
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);//Busca el jugador y devuelve la posicione en la que se encuentra.
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);//Inserta un nuevo jugador en la array.
#endif