#include <iostream>
#include <cmath>
#include <string>
using namespace std;
int main(){
	double x = 12, sigma = 2.1836, y = 3, lambda = 1.11695, alfa = 328.67, f;
	cout << "A continuacion se va a calcular la funcion definida en el ejercicio 7\n";
	f = 3 * ((x + sigma + y) / (pow(x, 2) - pow(y, 2))) - lambda * (alfa - 13.7);
	cout << "El resultado es:" << f << endl;
	return 0;
}