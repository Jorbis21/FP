#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
const int MAX_PEDIDOS = 5;
typedef struct {
	int numPed;
	string nombre;
	string direccion;
	string codRepartidor;
	bool entregado;
}tPedido;
typedef struct {
	tPedido pedidos[MAX_PEDIDOS];
	int cont;
}tListaPedidos;

bool cargarPedidos(tListaPedidos &lista);
bool actualizarPedido(tListaPedidos& lista, int numPed);
int posicionRepartidor(tListaPedidos lista, string codRep);
void mostrarPedidosRepartidor(tListaPedidos lista, string codRep, int pos);
void mostrarPedidos(tListaPedidos lista);
bool guardarPedidos(tListaPedidos lista);

int main(){
	tListaPedidos lista;
	if (!cargarPedidos(lista)) {
		cout << "No se ha podido cargar los pedidos." << endl;
	}
	else {
		cout << "Pedidos cargados con exito." << endl;
	}
	system("PAUSE");
	system("cls");
	int op = -1;
	while (op != 0 && op <= 3){
		cout << "1.- Mostrar todos los pedidos pendientes de un repartidor" << endl;
		cout << "2.- Mostrar todos los pedidos" << endl;
		cout << "3.- Registro de pedido entregado" << endl;
		cout << "0.- Salir" << endl;
		cout << "Opcion:";
		cin >> op;
		switch (op) {
		case 1: {
			cout << "Indique codigo del repartidor" << endl;
			string cod;
			cin >> cod;
			cout << "Pedidos pendientes del repartidor " << cod << endl << endl;
			int x = posicionRepartidor(lista, cod);
			mostrarPedidosRepartidor(lista, cod, x);
		}
			  break;
		case 2: {
			mostrarPedidos(lista);
		}
			  break;
		case 3: {
			cout << "Indique el numero del pedido" << endl;
			int a;
			cin >> a;
			if (!actualizarPedido(lista, a)) {
				cout << "No se ha podido actualizar el pedido" << endl;
			}
			else {
				cout << "Pedido actualizado" << endl;
			}
		}
			  break;
		}
		system("PAUSE");
		system("cls");
	}
	guardarPedidos(lista);
	return 0;
	
}

bool cargarPedidos(tListaPedidos &lista) {
	ifstream archivo;
	lista.cont = 0;
	char c;
	archivo.open("pedidos.txt");
	if (archivo.is_open()) {
		archivo >> lista.pedidos[lista.cont].numPed;
		while (lista.pedidos[lista.cont].numPed != 0) {
			archivo.get(c);
			getline(archivo, lista.pedidos[lista.cont].nombre);
			getline(archivo, lista.pedidos[lista.cont].direccion);
			getline(archivo, lista.pedidos[lista.cont].codRepartidor);
			lista.pedidos[lista.cont].entregado = false;
			lista.cont++;
			if (lista.cont == MAX_PEDIDOS) {
				archivo.close();
				return true;
			}
			else {
				archivo >> lista.pedidos[lista.cont].numPed;
			}
			
		}
		archivo.close();
		return true;
	}
	else {
		archivo.close();
		return false;
	}
}

bool actualizarPedido(tListaPedidos &lista, int numPed){
	for (int i = 0; i < lista.cont; i++) {
		if (lista.pedidos[i].numPed == numPed){
			lista.pedidos[i].entregado = true;
			return true;
		}
	}
	return false;
}
int posicionRepartidor(tListaPedidos lista, string codRep) {
	for (int i = 0; i < lista.cont; i++) {
		if (lista.pedidos[i].codRepartidor == codRep) {
			return i;
		}
	}
	return lista.cont;
}
void mostrarPedidosRepartidor(tListaPedidos lista, string codRep, int pos) {
	for (int i = pos; i < lista.cont; i++) {
		if (lista.pedidos[i].codRepartidor == codRep && lista.pedidos[i].entregado == false) {
			cout << "Numero Pedido:" << lista.pedidos[i].numPed << endl;
			cout << "Cliente:" << lista.pedidos[i].nombre<< endl;
			cout << "Direccion:" << lista.pedidos[i].direccion << endl << endl;
		}
	}
}
void mostrarPedidos(tListaPedidos lista) {
	for (int i = 0; i < lista.cont; i++) {
		cout << "Numero Pedido:" << lista.pedidos[i].numPed << endl;
		cout << "Cliente:" << lista.pedidos[i].nombre << endl;
		cout << "Direccion:" << lista.pedidos[i].direccion << endl;
		cout << "Repartidor:" << lista.pedidos[i].codRepartidor << endl;
		if (lista.pedidos[i].entregado == false) {
			cout << "Entrega Pendiente." << endl << endl;
		}
		else {
			cout << "Pedido entregado." << endl << endl;
		}		
	}
}
bool guardarPedidos(tListaPedidos lista) {
	ofstream archivo;
	archivo.open("pendientes.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < lista.cont; i++) {
			if (lista.pedidos[i].entregado == false) {
				archivo << lista.pedidos[i].numPed << endl;
				archivo << lista.pedidos[i].nombre << endl;
				archivo << lista.pedidos[i].direccion << endl;
				archivo << lista.pedidos[i].codRepartidor << endl;
			}
		}
		cout << "0";
		archivo.close();
		return true;
	}
	else {
		archivo.close();
		return false;
	}
}