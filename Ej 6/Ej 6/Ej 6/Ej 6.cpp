#include <iostream>
#include <cmath>
#include <string>
using namespace std;
int main(){
	double a,b,c,d,r;
	double funcion;
    cout << "Introduzca la variable a:\n";
	cin >> a;
	cout << "Introduzca la variable b:\n";
	cin >> b;
	cout << "Introduzca la variable c:\n";
	cin >> c;
	cout << "Introduzca la variable d:\n";
	cin >> d;
	cout << "Introduzca la variable r:\n";
	cin >> r;
	funcion = (4 / 3*(r + 34)) - (9 * (a + b * c)) + (3 + d*(2 + a) / a + b * d);
	cout << "El resultado es:" << funcion << endl;
}
