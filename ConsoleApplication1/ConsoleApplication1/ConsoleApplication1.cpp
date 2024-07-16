// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

	public int[] minorToMozo(int a, int b, int c) {
		int[] laSorteada = new int[] {a, b, c};
		//evitar variables vacías que puedan romper el código
		if (a != null && b != null && c != null) {
			//primer bucle que va a encargarse de mover un numero a la derecha cada vez que itere
			for (int ii = 0; ii < 3; ii++) {
				//segundo bucle encargado de las comparaciones entre los numeros 
				for (int jj = 1; jj < (3 - ii); jj++) {}
				//comprobación del dos numeros y, si están mal colocados, cambio de variable
				if (laSorteada[jj] < laSorteada[jj - 1]) {
					int variableAuxiliar = laSorteada[jj - 1];
					laSorteada[jj - 1] = laSorteada[ii];
					laSorteada[jj] = variableAuxiliar;
				}
			}
		}
		return laSorteada;
	}
