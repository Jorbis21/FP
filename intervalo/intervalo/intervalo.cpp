#include <iostream>
//#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iomanip>
using namespace std;
const int N = 50;
typedef struct {
    int array[N];
    int cont;
}tListaNum;

void RandNum(tListaNum &lista);
int calcularCuadrados(int num);
bool guardarNumero(tListaNum listaNum);
int numIntervalo(tListaNum lista, int a, int b);

int main(){
    srand(time(NULL));
    tListaNum lista;
    int a = 0, b = 0;
    RandNum(lista);
    if (!guardarNumero(lista)) {
        cout << "No se ha podido guardar los numeros." << endl;
    }
    else {
        cout << "Lista guardada con exito." << endl;
    }
    cout << "Inserte dos numeros, uno mayor que el otro:" << endl;
    cin >> a >> b;// a menor b mayor
    int aux = 0;
    if (a > b) {
        aux = b;
        b = a;
        a = aux;
    }
    system("cls");
    aux = numIntervalo(lista, a, b);
    if (aux > -1) {
        cout << lista.array[aux] << endl;
    }
    else if (aux == -1) {
        cout << "No se ha encontrado el numero." << endl;
    }
    system("PAUSE");
}

void RandNum(tListaNum &lista) {
    for (int i = 0; i < N; i++) {
        lista.array[i] = rand() % (1000 - (1 + 1)) + 1;
    }
}

int calcularCuadrados(int num) {
    int total = 0;
    for (int i = 1; i <= 2*num; i++) {
        if (i%2 != 0) {
            total += i;
        }
    }
    return total;
}

bool guardarNumero(tListaNum listaNum) {
    ofstream archivo;
    archivo.open("secuencia.txt");
    if (archivo.is_open()) {
        for (int i = 0; i < N; i++) {
            archivo << calcularCuadrados(listaNum.array[i]) << endl;
            cout << calcularCuadrados(listaNum.array[i]) << endl;
        }
        archivo.close();
        return true;
    }
    else {
        archivo.close();
        return false;
    }
}

int numIntervalo(tListaNum lista, int a, int b) {
    for (int i = 0; i < N; i++) {
        if (lista.array[i] > a && lista.array[i] < b) {
            return i;
        }
    }
    return -1;
}

