#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
const int MAX_PEDIDOS = 4;
typedef struct {
	string pedido;
	string nombre;
	string direccion;
	string codigo;
	bool entregado = false;
}tPedido[MAX_PEDIDOS];

bool cargarPedidos(tPedido& pedido);


int main() {
	tPedido pedido;
	cargarPedidos(pedido);
	for (int i = 0; i < MAX_PEDIDOS; i++) {
		cout << pedido[i].pedido << endl;
		cout << pedido[i].nombre << endl;
		cout << pedido[i].direccion << endl;
		cout << pedido[i].codigo << endl;
	}


}

bool cargarPedidos(tPedido& pedido) {
	ifstream archivo;
	bool leer = false;
	int i = 0;
	archivo.open("pedidos.txt");
	if (archivo.is_open()) {
		getline(archivo, pedido[i].pedido);
		while (pedido[i].pedido != "0") {
			getline(archivo, pedido[i].nombre);
			getline(archivo, pedido[i].direccion);
			getline(archivo, pedido[i].codigo);
			i++;
			getline(archivo, pedido[i].pedido);
		}
		leer = true;
	}
	else {
		cout << "No se puede abrir el archivo" << endl;
		leer = false;
	}
	archivo.close();
	return leer;
}