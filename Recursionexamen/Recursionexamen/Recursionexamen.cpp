// Prueba de evaluación del día 12 de junio de 2020
// Alumno/a: Javier Orbis Ramirez
// email:  jorbis@ucm.es
// Grupo: B

// Fíjate que hay 3 sitios donde aparece el comentario  "INTRODUCIR CODIGO"
// Debes cambiar los nombres de los ficheros para las distintas pruebas

#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	int cont;// he tenido que modificar esta parte por la version de visual studio que estoy usando 
	int array[100];
}tLista;

// Traduce (0/1) booleano a (FALSE/TRUE) del tipo string
string bool2string(bool x);
bool recursion(tLista l);//funcion recursiva que comprueba si todos los valores son el valor anterior más 2.

bool resuelveCaso(){
	tLista l;
	l.cont = 0;
	int num = 0;
	cin >> num;
	if (!std::cin)
		return false;
	while (num != -1){
		l.array[l.cont] = num;
		l.cont++;
		cin >> num;
	}
	bool acierto = true;// booleano que coge el valor de la recursion
	if ((l.cont != 1 && l.cont != 0) || num != -1)
		acierto = recursion(l);
	cout << bool2string(acierto) << endl;
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.1.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.1.1.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

bool recursion(tLista l) {
	if (l.array[l.cont - 1] == l.array[l.cont - 2] + 2) {// aqui comprueba el ultimo numero del array y su anterior +2 si son iguales continua la recursion
		l.cont--;
		return recursion(l);
	}
	else if (l.cont == 1) {// aqui si se ha llegado al final de la recurion sin ningun caso distinto devuelve true
		return true;
	}
	else if (l.array[l.cont - 1] != l.array[l.cont - 2] + 2) {// comprueba si son distintos si asi es  devuelve false
		return false;
	}
}
// Traduce (0/1) booleano a (FALSE/TRUE) del tipo string
string bool2string(bool x) {
	if (x)
		return "TRUE";
	else
		return "FALSE";
}