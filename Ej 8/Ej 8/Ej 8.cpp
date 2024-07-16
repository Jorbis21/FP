#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main(){
	double SB, CD, CCA, HEx, H, M, SBr, Pirpf, Rirpf, SN;//SB-sueldo base,CD-complemento de destino, CCA-complemento de cargo academico, 
	//HEx-horas extra realizadas, H-hijos, M-mayores, SBr-sueldo bruto, Pirpf-porcentaje de IRPF, Rirpf-retencion por IRPF, SN-sueldo neto
	cout << "Inserte sueldo base:\n";
	cin >> SB;
    cout << "Inserte complemento de destino:\n";
	cin >> CD;
	cout << "Inserte complemento de cargo academico:\n";
	cin >> CCA;
	cout << "Inserte horas extra realizadas:\n";
	cin >> HEx;
	cout << "Inserte numero de hijos:\n";
	cin >> H;
	cout << "Inserte numero de mayores:\n";
	cin >> M;
	SBr = SB + CD + CCA + (HEx * 23);//Aqui se calcula el sueldo bruto del empleado
	Pirpf = 24 - (2 * H) - (1 * M);//Aqui se calcula el porcentaje de IRPF que ha de pagar el empleado
	Rirpf = SBr * (Pirpf / 100);//Aqui se calcula la retencion del IRPF
	SN = SBr - Rirpf;//Aqui se calcula el sueldo neto
	cout << "Sueldo base:" << SB << "€" << endl;
	cout << "Complemento de destino:" << CD << "€" << endl;
	cout << "Complemento de cargo academico:" << CCA << "€" << endl;
	cout << "Horas extra realizadas:" << HEx << endl;
	cout << "Hijos:" << H << endl;
	cout << "Mayores:" << M << endl;
	cout << "Calculo de la nomina.-\n";
	cout << "Sueldo bruto:" << SBr << "€" << endl;
	cout << "Porcentaje de IRPF:" << Pirpf << "%" << endl;
	cout << "Retencion por IRPF:" << Rirpf << "€" << endl;
	cout << "Sueldo neto:" << SN << "€" << endl;
	return 0;
}
