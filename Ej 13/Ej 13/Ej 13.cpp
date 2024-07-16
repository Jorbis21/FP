#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
	double num1, num2, num3, pos1, pos2, pos3;
	cout << "Introduzca tres numeros" << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	cout << "Ahora se mostraran en orden de menor a mayor" << endl;
	if ((num1 > num2) && (num1 > num3)) {
		pos1 = num1;
		if (num2 > num3) {
			pos2 = num2;
			pos3 = num3;
			cout << pos3 << pos2 << pos1;
		}
		else {
			pos2 = num3;
			pos3 = num2;
			cout << pos3 << pos2 << pos1;
		}
	}
	if ((num2 > num1) && (num2 > num3)) {
		pos1 = num2;
		if (num1 > num3) {
			pos2 = num1;
			pos3 = num3;
			cout << pos3 << pos2 << pos1;
		}
		else {
			pos2 = num3;
			pos3 = num1;
			cout << pos3 << pos2 << pos1;
		}
	}
	if ((num3 > num2) && (num3 > num1)) {
		pos1 = num3;
		if (num2 > num1) {
			pos2 = num2;
			pos3 = num1;
			cout << pos3 << pos2 << pos1;
		}
		else {
			pos2 = num1;
			pos3 = num2;
			cout << pos3 << pos2 << pos1;
		}
	}
	return 0;
}
