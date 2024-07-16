//Trabajo realizado por Javier Orbis Ramirez y Enrique Martin Rodriguez
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

void verprestamos(int mes2, int dia2, int anio2);//En esta funcion se leen los datos del fichero prestamos.txt y se muestra si estan retrasados o no.
void Aprestamos();//En esta funcion se lee el fichero prestamos.txt, copia los datos y los mete en el archivo creado, y te pide los datos de un nuevo prestamo.
void prestamosre1(int mes2, int dia2, int anio2);//En esta funcion vuelve a leer prestamos.txt y copia los archivos retrasados en Retrasos.txt.
void prestamosre2(int mes2, int dia2, int anio2);//En esta funcion a lee Prestamos2.txt y copia los archivos retrasados en Retrasos.txt.
void penalizaciones(int mes2, int dia2, int anio2);//En esta funcion se abre Retrasos.txt y se calcula la nueva fecha de uso de la biblioteca y sale en el fichero Penalizaciones.txt.

int main() {
	int sel = 0, mes2 = 0, dia2 = 0, anio2 = 0;
	bool caso = false; 
	while ((((mes2 > 12) || (mes2 < 1)) || ((dia2 < 1) || (dia2 > 31))) || ((mes2 == 2) && (dia2 > 28)) || ((mes2 == 4) && (dia2 >= 31)) || ((mes2 == 6) && (dia2 >= 31)) || ((mes2 == 9) && (dia2 >= 31)) || ((mes2 == 11) && (dia2 >= 31))) {
		cout << "Indique la fecha actual dejando espacios entre el dia, el mes y el anio:";
		cin >> dia2 >> mes2 >> anio2;
	}
	while (sel != 5) {
		cout << "Fecha actual:" << dia2 << "/" << mes2 << "/" << anio2 << endl << endl;
		cout << " 1 - Ver prestamos." << endl;
		cout << " 2 - Aniadir prestamos." << endl;
		cout << " 3 - Ver prestamos retrasados." << endl;
		cout << " 4 - Calcular penalizaciones." << endl;
		cout << " 5 - Salir del programa." << endl;
		cout << "Elija una opcion:";
		cin >> sel;
		
		switch (sel) {

		case 1: {
			system("cls");
			verprestamos(mes2, dia2, anio2);
			
		}
			  break;
		case 2: {
			system("cls");
			Aprestamos();
			caso = true;
			
		}
			  break;
		case 3: {
			system("cls");
			if (caso == true) {
				prestamosre2(mes2, dia2, anio2);
			}
			else {
				prestamosre1(mes2, dia2, anio2);
			}
			
		}
			  break;
		case 4: {
			system("cls");
			penalizaciones(mes2, dia2, anio2);
			
		}
			  break;

		}
		
	}
}
void verprestamos(int mes2, int dia2, int anio2) {
	string nif, libro;
	int dia = 0, mes = 0, anio = 0;
	char aux;
	bool retraso = 0;
	ifstream archivo;
	archivo.open("prestamos.txt");
	if (archivo.is_open()) {
		archivo >> nif;
		while (nif != "Fin") {
			archivo >> dia;
			archivo.get(aux);
			archivo >> mes;
			archivo.get(aux);
			archivo >> anio;
			archivo.get(aux);
			getline(archivo, libro);
			cout << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
			if (anio >= anio2) {

				if (mes >= mes2) {

					if (dia >= dia2) {
						retraso = false;
					}
					else {
						retraso = true;
					}
				}
				else {
					retraso = false;
				}
			}
			else {
				retraso = true;
			}

			if (retraso == true) {
				cout << "Retraso." << endl;
			}
			else {
				cout << "Esta en fecha." << endl;
			}
			archivo >> nif;
		}
		archivo.close();

	}
	else {
		cout << "No se ha podido abrir el archivo." << endl;
	}

}
void Aprestamos() {
	ofstream archivo2, archivop;
	ifstream archivo;
	string nif, libro, arc;
	char aux;
	int dia = 0, mes = 0, anio = 0;
	cout << "Inserte nombre del archivo que desea crear sin dejar espacios poniendo .txt al final:";
	cin >> arc;
	archivo2.open(arc);
	if (archivo2.is_open()) {
		archivo.open("prestamos.txt");
		if (archivo.is_open()) {
			archivo >> nif;
			while (nif != "Fin") {
				archivo >> dia;
				archivo.get(aux);
				archivo >> mes;
				archivo.get(aux);
				archivo >> anio;
				archivo.get(aux);
				getline(archivo, libro);
				archivo2 << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
				archivo >> nif;
			}
			archivo.close();
		}
		cout << "A continuacion se van a pedir los datos del prestamo. Para finalizar escriba Fin." << endl;
		cout << "Inserte el NIF:";
		cin >> nif;
		while (nif != "Fin") {
			do {
				cout << "Inserte la fecha de devolucion:";
				cin >> dia >> mes >> anio;
			} while ((((mes > 12) || (mes < 1)) || ((dia < 1) || (dia > 31))) || ((mes == 2) && (dia > 28)) || ((mes == 4) && (dia >= 31)) || ((mes == 6) && (dia >= 31)) || ((mes == 9) && (dia >= 31)) || ((mes == 11) && (dia >= 31)));
			cin.get(aux);
			cout << "Inserte el nombre del libro:";
			getline(cin, libro);
			archivo2 << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
			cout << "Inserte el NIF (Fin para terminar):";
			cin >> nif;

		}
		archivo2 << "Fin";
		archivo2.close();
		ifstream archivo2;
		ofstream archivop;
		archivop.open("Prestamos2.txt");
		if (archivop.is_open()) {
			archivo2.open(arc);
			if (archivo2.is_open()) {
				archivo2 >> nif;
				while (nif != "Fin") {
					archivo2 >> dia;
					archivo2.get(aux);
					archivo2 >> mes;
					archivo2.get(aux);
					archivo2 >> anio;
					archivo2.get(aux);
					getline(archivo2, libro);
					archivop << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
					archivo2 >> nif;
				}
			}
			archivo2.close();
		}
		archivop << "Fin";
		archivop.close();
	}

}
void prestamosre1(int mes2, int dia2, int anio2) {
	ifstream archivo;
	ofstream retrasos, archivop;
	string nif, libro, arc;
	char aux;
	int dia = 0, mes = 0, anio = 0;
	bool retraso = 0;
	archivo.open("prestamos.txt");
	if (archivo.is_open()) {
		retrasos.open("Retrasos.txt");
		if (retrasos.is_open()) {
			archivo >> nif;
			while (nif != "Fin") {
				archivo >> dia;
				archivo.get(aux);
				archivo >> mes;
				archivo.get(aux);
				archivo >> anio;
				archivo.get(aux);
				getline(archivo, libro);
				if (anio >= anio2) {

					if (mes >= mes2) {

						if (dia >= dia2) {
							retraso = false;
						}
						else {
							retraso = true;
						}
					}
					else {
						retraso = false;
					}
				}
				else {
					retraso = true;
				}
				if (retraso == true) {
					retrasos << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
					cout << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
				}
				archivo >> nif;
			}
		}
		retrasos << "Fin";
		retrasos.close();
	}
	archivo.close();
	cout << "Los libros con retraso saldran en el fichero Retrasos.txt" << endl;
}
void prestamosre2(int mes2, int dia2, int anio2) {
	ifstream archivo, archivo4;
	ofstream retrasos, archivop;
	string nif, libro, arc;
	char aux;
	int dia = 0, mes = 0, anio = 0;
	bool retraso = 0;
	archivo4.open("Prestamos2.txt");
	if (archivo4.is_open()) {
		retrasos.open("Retrasos.txt");
		if (retrasos.is_open()) {
			archivo4 >> nif;
			while (nif != "Fin") {
				archivo4 >> dia;
				archivo4.get(aux);
				archivo4 >> mes;
				archivo4.get(aux);
				archivo4 >> anio;
				archivo4.get(aux);
				getline(archivo4, libro);

				if (anio >= anio2) {

					if (mes >= mes2) {

						if (dia >= dia2) {
							retraso = false;
						}
						else {
							retraso = true;
						}
					}
					else {
						retraso = false;
					}
				}
				else {
					retraso = true;
				}
				if (retraso == true) {
					retrasos << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
					cout << nif << " " << dia << "/" << mes << "/" << anio << " " << libro << endl;
				}
				archivo4 >> nif;
			}

		}
		retrasos << "Fin";
		retrasos.close();


	}
	else {
		cout << "No se ha podido encontrar el archivo." << endl;
	}
	archivo4.close();
	cout << "Los libros con retraso saldran en el fichero Retrasos.txt" << endl;
}
void penalizaciones(int mes2, int dia2, int anio2) {
	ifstream archivo5;
	ofstream archivo;
	string nif, libro;
	char aux;
	int dia = 0, mes = 0, anio = 0, suma, diar, mesr, anior, diar2, mesr2, anior2, mesr3, anior3;
	archivo5.open("Retrasos.txt");
	if (archivo5.is_open()) {
		archivo.open("Penalizaciones.txt");
		if (archivo.is_open()) {
			archivo5 >> nif;
			while (nif != "Fin") {
				archivo5 >> dia;
				archivo5.get(aux);
				archivo5 >> mes;
				archivo5.get(aux);
				archivo5 >> anio;
				archivo5.get(aux);
				getline(archivo5, libro);
				//para simplificar las operaciones con las fechas se asumen que los meses son de 30 dias y no hay años bisiestos.
				suma = ((anio2 - anio) * 365 + (mes2 - mes) * 30 + (dia2 - dia)) * 2;
				anior = suma / 365;
				mesr = (suma % 365) / 30;
				diar = (suma % 365) % 30;
				anior2 = anio2 + anior;
				mesr2 = mes2 + mesr;
				diar2 = dia2 + diar;
				while (diar2 > 30) {
					diar2 = diar2 - 30;
					mesr2++;
				}
				while (mesr2 > 12) {
					mesr2 = mesr2 - 12;
					anior2++;
				}
				cout << "Las penalizaciones son:" << nif << " " << diar2 << "/" << mesr2 << "/" << anior2 << endl;
				archivo << nif << " " << diar << "/" << mesr << "/" << anior << endl;
				archivo5 >> nif;
			}
		}
		cout << "Los usuarios penalizados saldran en el fichero Penalizaciones.txt." << endl;
	}
	else {
		cout << "No se ha podido abrir el archivo o no ha seleccionado la opcion 3." << endl;
	}
	archivo5.close();
}